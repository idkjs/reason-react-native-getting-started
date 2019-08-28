open ReactNative;
open ReactNavigation;
let styles =
  Style.(
    StyleSheet.create({
      "root": style(~flex=1., ()),
      "aButton": style(~fontSize=30., ~color="red", ~margin=4.->dp, ()),
      "title":
        style(
          ~height=25.->dp,
          ~fontSize=18.,
          ~textAlign=`center,
          ~color="black",
          (),
        ),
    })
  );
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
module DebounceScreen = {
  [@react.component]
  let make = () => {
    <Screen name="DebounceDemo" />;
  };
};
let routes = [|
  "Home",
  "Debounce",
  "Profile",
  "Settings",
  "UnstatedDemo",
  "SharedStateDemo",
|];
module HomeButton = {
  [@react.component]
  let make = (~title: string, ~navigation: Navigation.t) => {
    <View style=styles##aButton>
      <Button title onPress={_ => navigation->Navigation.navigate(title)} />
    </View>;
  };
};
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <ScrollView style=styles##root>
      <View style=Style.(style(~height=8.->dp, ())) />
      <Text style=styles##title> "React Native Tutorial"->React.string </Text>
      {routes->Belt.Array.mapWithIndex((i, title) =>
         <HomeButton key={string_of_int(i)} title navigation />
       )
       |> React.array}
    </ScrollView>;
  };
  make->NavigationOptions.(
          setNavigationOptions(
            t(
              ~title="Home",
              //  ~headerLeft=<View />,
              (),
            ),
          )
        );
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = {
      "Home": {
        screen: HomeScreen.make,
      },
      "Debounce": {
        screen: DebounceScreen.make,
      },
      "Profile": {
        screen: ProfileScreen.make,
      },
      "Settings": {
        screen: SettingsScreen.make,
      },
      "UnstatedDemo": {
        screen: UnstatedDemo.make,
      },
      "SharedStateDemo": {
        screen: SharedStateDemo.navigator,
      },
    };

    let navigator = StackNavigator.(make(routes));
  });

[@react.component]
let make = () =>
// had to wrap the whole project in Unstated to get the on demo to work. How do you use a container per route?
  <CounterState.Counter.Provider initialState=0>
    <AppContainer />
  </CounterState.Counter.Provider>;