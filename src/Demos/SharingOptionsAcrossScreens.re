/**
 * Demo `Sharing common `navigationOptions` across screens` React Navigation Module
 * https://reactnavigation.org/
 *
 * Converted to reasonml from https://reactnavigation.org/docs/en/headers.html#sharing-common-navigationoptions-across-screens
 *
 */
open ReactNative;

open ReactNavigation;
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    // trying this to see if we can work towards json serializable values to use with deeplinking as mentioned here: https://reactnavigation.org/docs/en/params.html
    let param = {"itemId": 86, "otherParam": "anything you want here"};
    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Text> {"Home Screen" |> React.string} </Text>
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams("Details", param)
        }
      />
    </View>;
  };
};

module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    // in reason-react-native you have to use `navigateWithParams` to get be able to use the default value behaviour shown in the example here: https://reactnavigation.org/docs/en/params.html
    let itemId =
      navigation->Navigation.getParamWithDefault("itemId", "NO-ID");

    let otherParam =
      navigation->Navigation.getParamWithDefault(
        "otherParam",
        "some default value",
      );

    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Text> {"Details Screen" |> React.string} </Text>
      <Text> {"itemId: " ++ itemId |> React.string} </Text>
      <Text> {"otherParam: " ++ otherParam |> React.string} </Text>
      <Button
        title="Go to Details... again"
        onPress={_ =>
          navigation->Navigation.navigateWithParams(
            "Details",
            {
              "itemId": [%bs.raw {| String(Math.floor(Math.random() * 100)) |}],
            },
          )
        }
      />
      <Button
        title="Go to Home"
        onPress={_ => navigation->Navigation.navigate("Home")}
      />
      <Button
        title="Update the title"
        onPress={_ =>
          navigation->NavUtils.setParams({"otherParam": "Updated!"})
        }
      />
      <Button title="Go back" onPress={_ => navigation->Navigation.goBack} />
    </View>;
  };
};

let routes = {
  "Home": {
    screen: HomeScreen.make,
    navigationOptions: () => {title: "Home"},
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
      {title: title};
    },
  },
};
let configFromHomeScreen = {
  "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
  "headerTintColor": "#fff",
  "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
};
let configOptions =
  StackUtils.config(
    ~initialRouteName="Home",
    /* The header config from HomeScreen is now here */
    ~defaultNavigationOptions=configFromHomeScreen,
    (),
  );
let navigator = StackNavigator.(makeWithConfig(routes, configOptions));