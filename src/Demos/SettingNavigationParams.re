/**
 * Demo `Using Navigation Params In The Title` React Navigation Module
 * https://reactnavigation.org/
 *
 * Converted to reasonml from https://reactnavigation.org/docs/en/headers.html#using-params-in-the-title
 *
 */
open ReactNative;

open ReactNavigation;
module HomeScreen = {
  //  open ReactNavigation;
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    // trying this to see if we can work towards json serializable values to use with deeplinking as mentioned here: https://reactnavigation.org/docs/en/params.html
    // let bucklescript = {
    //   "info": {
    //     itemId: 86,
    //     otherParam: "anything you want here",
    //   },
    // };

    // let param = bucklescript##info;
    let param = {"itemId": 86, "otherParam": "anything you want here"};
    Js.log2("TEST", Js.Json.test(param, Object)); // true
    <Screen name="Home Screen">
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams("Details", param)
        }
        // {"itemId": 86, "otherParam": "anything you want here"},
        // js version
        // onPress={() => {
        //     /* 1. Navigate to the Details route with params */
        //     this.props.navigation.navigate('Details', {
        //       itemId: 86,
        //       otherParam: 'anything you want here',
        //     });
        //   }}
      />
    </Screen>;
  };
  make->NavigationOptions.setNavigationOptions(
    NavigationOptions.t(~title="Home", ()),
  );
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
  make->NavigationOptions.setDynamicNavigationOptions(params => {
    let title =
      params##navigation
      ->Navigation.getParamWithDefault(
          "otherParam",
          "A Nested Details Screen",
        );
    NavigationOptions.t(~title, ());
  });
};
module SettingsScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Settings Screen" />;
  };
};
module ProfileScreen = {
  [@react.component]
  let make = () => {
    <Screen name="Profile Screen" />;
  };
};

module HomeStack = {
  let navigator =
    StackNavigator.(
      make({"Home": HomeScreen.make, "Details": DetailsScreen.make})
    );
};
module SettingsStack = {
  let navigator =
    StackNavigator.(
      make({
        "Profile": ProfileScreen.make,
        "SettingsScreen": SettingsScreen.make,
      })
    );
};

/** this creates a bottom tab navigator */
let navigator =
  ReactNavigation.TabNavigator.Bottom.make({
    "Home": HomeStack.navigator,
    "Settings": SettingsStack.navigator,
  });