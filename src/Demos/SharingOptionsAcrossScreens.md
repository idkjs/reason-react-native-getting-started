# Sharing common `navigationOptions` across screens

convert to reasonml from <https://reactnavigation.org/docs/en/headers.html#sharing-common-navigationoptions-across-screens>

From the docs:
> There are three key properties to use when customizing the style of your > header: `headerStyle`, `headerTintColor`, and `headerTitleStyle`.

> `headerStyle`: a style object that will be applied to the View that wraps the header. If you set backgroundColor on it, that will be the color of your header.

> `headerTintColor`: the back button and title both use this property as their color. In the example below, we set the tint color to white (#fff) so the back button and the header title would be white.

> `headerTitleStyle`: if we want to customize the `fontFamily`, `fontWeight` and other Text style properties for the title, we can use this to do it.

```js
class HomeScreen extends React.Component {
  static navigationOptions = {
    title: 'Home',
    headerStyle: {
      backgroundColor: '#f4511e',
    },
    headerTintColor: '#fff',
    headerTitleStyle: {
      fontWeight: 'bold',
    },
  };

  /* render function, etc */
}
```

Using `ReasonML` I had to do a few things to get this to work. The `reason-react-navigation` bindings don't have `initialRouteName` and `defaultNavigationOptions` so I created [StackUtils.re]("./src/bindings/StackUtils.re") which copies over all of `ReactNavigation.StackNavigator`  and overides the definition of `config` so that it has just the properties from `react-navigation` that I need to reproduce the example. It looks like this:

```reason
// include this file: https://github.com/reasonml-community/reason-react-native/blob/53dc7f9ebf6ae72fb88c2cfe957dc45b993265fa/reason-react-navigation/src/StackNavigator.re then override `config` definition
include ReactNavigation.StackNavigator;

[@bs.obj]
external config:
  (
    ~initialRouteName: string=?,
    ~defaultNavigationOptions: Js.t('a)=?,
    unit
  ) =>
  config =
  "";
```

Then I removed the `NavigatorOptions` calls from the `HomeScreen` and `DetailsScreen` modules and defined them in the `routes` object in `AppContainer`. I then use `StackUtils` to define our config object that we pass to `StackNavigator.makeWithConfig()`;

```reason
module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};

    let routes = {
      "Home": {
        screen: HomeScreen.make,
        navigationOptions: () => {
          title: "Home",
        },
      },
      "Details": {
        screen: DetailsScreen.make,
        navigationOptions: (params: {. navigation: Navigation.t}) => {
          let navigation = params##navigation;
          let title =
            navigation->Navigation.getParamWithDefault(
              "otherParam",
              "A Nested Details Screen",
            );
            // here we have to do `title:title` or change the name of `let title` identifier because the compiler will pun it away to `title` instead of `{title}` which compiles it away.
            {
              title:title,
            };
        },
      },
    };
    // create a `Js.t('a)` object containing the values we want to use as `defaultNavigationOptions`.
    let configFromHomeScreen = {
      "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
      "headerTintColor": "#fff",
      "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
    };
    // define our `config` object passing in `configFromHomeScreen` to `~defaultNavigationOptions`
    let configOptions = StackUtils.config(
        ~initialRouteName="Home",
        /* The header config from HomeScreen is now here */
        ~defaultNavigationOptions=configFromHomeScreen,
        (),
      );
    let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  });
```

This is what it looks like:

![sharing-options](../../images/sharingOptions.gif)
