open ReactNative;
open ReactNavigation;
external unsafeCast: ReactNavigation.NavigationOptions.t => 'a = "%identity";
open CounterState;

module LogoTitle = {
  [@react.component]
  let make = () => {
    <Image
      source={Image.Source.fromRequired(
        Packager.require("./assets/spiro.png"),
      )}
      style=Style.(style(~width=30.->dp, ~height=30.->dp, ()))
    />;
  };
};

module IncButton = {
  [@react.component]
  let make = () => {
    let counter = Counter.useContainer();
    <Button title="+" color="#fff" onPress={_ => counter.increment()} />;
  };
};
module DecButton = {
  [@react.component]
  let make = () => {
    let counter = Counter.useContainer();
    <Button title="-" color="#fff" onPress={_ => counter.decrement()} />;
  };
};
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    let param = {"itemId": 86, "otherParam": "anything you want here"};
    // let counter = Counter.useContainer();
    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Text> {"Home Screen" |> React.string} </Text>
      <Text>
        {"Count: " ++ string_of_int(Counter.useContainer().count) |> React.string}
      </Text>
      <Button
        title="Go to Details"
        onPress={_ =>
          navigation->Navigation.navigateWithParams("Details", param)
        }
      />
    </View>;
  };
  make->NavigationOptions.(
          setNavigationOptions(
            t(
              ~headerTitle=
                NavigationOptions.HeaderTitle.element(<LogoTitle />),
              ~headerRight=<IncButton />,
              // uncomment to see decrement button example
              // ~headerLeft=<DecButton />,
              (),
            ),
          )
        );
};
module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
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

    let navigationOptions = unsafeCast(navigationOptions);

    let navigationOptionsheaderTintColor = navigationOptions##headerTintColor;
    let navigationOptionsheaderStylebackgroundColor =
      navigationOptions##headerStyle##backgroundColor;

    let newHeaderTintColor = navigationOptionsheaderStylebackgroundColor;

    let newHeaderStyle: ReactNative.Style.t =
      Style.(style(~backgroundColor=navigationOptionsheaderTintColor, ()));

    let title =
      navigation->Navigation.getParamWithDefault(
        "otherParam",
        "A Nested Details Screen",
      );

    NavigationOptions.t(
      ~title,
      ~headerStyle=newHeaderStyle,
      ~headerTintColor=newHeaderTintColor,
      (),
    );
  });
};

module RootStack = {
  let routes = {
    "Home": {
      screen: HomeScreen.make,
    },
    "Details": {
      screen: DetailsScreen.make,
    },
  };
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = RootStack.routes;
    let defaultNavigationOptions = {
      "headerTintColor": "#fff",
      "headerStyle": Style.(style(~backgroundColor="#f4511e", ())),
      "headerTitleStyle": Style.(style(~fontWeight=`bold, ())),
    };
    let configOptions =
      StackUtils.config(
        ~initialRouteName="Home",
        ~defaultNavigationOptions,
        (),
      );
    let navigator = StackNavigator.(makeWithConfig(routes, configOptions));
  });

[@react.component]
let make = () =>
  <Counter.Provider initialState=0> <AppContainer /> </Counter.Provider>;