open ReactNative;

open ReactNavigation;
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Home Screen">
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams(
            "Details",
            {"itemId": 86, "otherParam": "anything you want here"},
          )
        }
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
    // Js.log2("itemId: ",itemId);
    // Js.log2("otherParam: ",otherParam);

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
      <Button title="Go back" onPress={_ => navigation->Navigation.goBack} />
    </View>;
  };
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

let navigator =
  ReactNavigation.TabNavigator.Bottom.make({
    "Home": HomeStack.navigator,
    "Settings": SettingsStack.navigator,
  });