/**
 * Demo `Shared Options` React Navigation Module
 * https://reactnavigation.org/
 *
 * Converted to reasonml from https://reactnavigation.org/docs/en/headers.html#overriding-shared-navigationoptions
 *
 */

open ReactNative;
external unsafeCast: ReactNavigation.NavigationOptions.t => 'a = "%identity";
open ReactNavigation;

module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
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
  // use binding to set page title
  make->NavigationOptions.(setNavigationOptions(t(~title="Home", ())));
};
module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    //  ~navigationOptions: NavigationOptions.t

    // Js.log2("DETAIL_navigationOptions", navigationOptions); //undefined here but available on `setDynamicNavigationOptions` below.

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
    let navigation = params##navigation;
    let navigationOptions = params##navigationOptions;
    Js.log2("DETAIL_navigationOptions", navigationOptions);
    // output:
    // DETAIL_navigationOptions Object {
    //   "headerStyle": Object {
    //     "backgroundColor": "#f4511e",
    //   },
    //   "headerTintColor": "#fff",
    //   "headerTitleStyle": Object {
    //     "fontWeight": "bold",
    //   },
    // }
    // identity type switch at top of file: `external unsafeCast: ReactNavigation.NavigationOptions.t => 'a = "%identity";` converts from one type to `'a`:any type which we can then use later to switch colors. This cant be right but it works.
    // have to do identity hack because:
    // ```
    // ReactNavigation.NavigationOptions.t
    // type t
    // <root>/src/OverrideSharedOptionsDemo.re

    // Error: This expression has type
    //          ReactNavigation.NavigationOptions.t =
    //            ReactNavigation.NavigationOptions.t
    //        but an expression was expected of type Js.t('a
    // ```
    // comment out this line to see the error generated
    let navigationOptions = unsafeCast(navigationOptions);
    // Js.log2("DETAIL_navigationOptions", navigationOptions);
    let navigationOptionsheaderTintColor = navigationOptions##headerTintColor;
    let navigationOptionsheaderStylebackgroundColor =
      navigationOptions##headerStyle##backgroundColor;
    // this should be the same as the old headerStyle bg color
    let newHeaderTintColor = navigationOptionsheaderStylebackgroundColor;
    // let oldHeaderStyle = navigationOptions##headerStyle;
    // this should be the same as the old headerTintColor
    let newHeaderStyle: ReactNative.Style.t =
      Style.(style(~backgroundColor=navigationOptionsheaderTintColor, ()));

    let title =
      navigation->Navigation.getParamWithDefault(
        "otherParam",
        "A Nested Details Screen",
      );
    // pass new values to NavigationOptions
    NavigationOptions.t(
      ~title,
      ~headerStyle=newHeaderStyle,
      ~headerTintColor=newHeaderTintColor,
      (),
    );
  });
};

let routes = {
  "Home": {
    screen: HomeScreen.make,
  },
  "Details": {
    screen: DetailsScreen.make,
  },
};

let defaultNavigationOptions = {
  "headerTintColor": "#fff",
  "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
  "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
};
let configOptions =
  StackUtils.config(~initialRouteName="Home", ~defaultNavigationOptions, ());
let navigator = StackNavigator.(makeWithConfig(routes, configOptions));