# Setting Header Title

convert to reasonml from <https://reactnavigation.org/docs/en/headers.html#setting-the-header-title)>

```js
 static navigationOptions = {
    title: 'Home',
  };
```

```reason
[@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Home Screen">
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams("Details", {"itemId": 86, "otherParam": "anything you want here"})
        }>
    </Screen>;
  };
  make->NavigationOptions.setNavigationOptions(NavigationOptions.t(~title="Home", ()));
```

## [Using Params in the Title](https://reactnavigation.org/docs/en/headers.html#using-params-in-the-title)

```js
class DetailsScreen extends React.Component {
  static navigationOptions = ({ navigation }) => {
    return {
      title: navigation.getParam('otherParam', 'A Nested Details Screen'),
    };
  };

  /* render function, etc */
}
```

Use `setDynamicNavigationOptions` and pass in the `params` object. The `title` is on `params##navigation`, here we are you `getParamsWithDefault` to get the value `otherParam` and if not there, use the default.

```reason
[@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Details Screen">
      /* rest of your component*/
    </Screen>;
  };

  make->NavigationOptions.setDynamicNavigationOptions(params => {
    let title = params##navigation->Navigation.getParamWithDefault("otherParam", "A Nested Details Screen");
    (NavigationOptions.t(~title, ()));
  });
```
