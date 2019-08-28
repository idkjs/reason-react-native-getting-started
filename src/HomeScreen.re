open ReactNative;
open ReactNavigation;
let styles =
  Style.(
    StyleSheet.create({
      "root": style(~flex=1., ()),
      "aButton": style(~fontSize=30., ~color="red", ~margin=4.->dp, ()),
      "button": style(~margin=8.->dp, ()),
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

let routes = [|
  // "Home",
  "Unstated Demo",
  "Shared State Demo",
  "Setting Header Demo",
  "Going Back",
  "Sharing Options Across Screens",
  "Overriding Shared Options",
  "Setting Navigation Params",
  "Passing Params To Components",
  "The Navigation Lifecycle"
|];
module HomeButton = {
  [@react.component]
  let make = (~name: string, ~navigation: Navigation.t) => {
    <Paper.Button
      mode=`contained
      onPress={_ => navigation->Navigation.navigate(name)}
      style=styles##button>
      name->React.string
    </Paper.Button>;
  };
};
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <ScrollView style=styles##root>
      <View style=Style.(style(~height=8.->dp, ())) />
      <Text style=styles##title>
        "Reason React Native Demos"->React.string
      </Text>
      {routes->Belt.Array.mapWithIndex((i, name) =>
         <HomeButton key={string_of_int(i)} name navigation />
       )
       |> React.array}
    </ScrollView>;
  };
  // make->NavigationOptions.(
  //         setNavigationOptions(
  //           t(
  //             ~title="Home",
  //             //  ~headerLeft=<View />,
  //             (),
  //           ),
  //         )
  //       );
};

module AppContainer =
  AppContainer.Make({
    type screenProps = {. "someProp": int};
    let routes = {
      "Home": {
        screen: HomeScreen.make,
      },
      "Unstated Demo": {
        screen: UnstatedDemo.make,
      },
      "Shared State Demo": {
        screen: SharedStateDemo.navigator,
      },
      "Setting Header Demo": {
        screen: SettingHeaderDemo.navigator,
      },
      "Setting Navigation Params": {
        screen: SettingNavigationParams.navigator,
      },
      "Going Back": {
        screen: GoingBackDemo.navigator,
      },
      "Sharing Options Across Screens": {
        screen: SharingOptionsAcrossScreens.navigator,
      },
      "Overriding Shared Options": {
        screen: OverridingSharedOptions.navigator,
      },
      "Passing Params To Components": {
        screen: PassingParamsToComponents.navigator,
      },
      "The Navigation Lifecycle": {
        screen: TheNavigationLifecycle.navigator,
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