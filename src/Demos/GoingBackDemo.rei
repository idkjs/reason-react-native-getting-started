module HomeScreen: {
  let makeProps:
    (~navigation: ReactNavigation.Navigation.t, ~key: string=?, unit) =>
    Js.t({. "navigation": ReactNavigation.Navigation.t});
  let make: {. "navigation": ReactNavigation.Navigation.t} => React.element;
};
module DetailsScreen: {
  let makeProps:
    (~navigation: ReactNavigation.Navigation.t, ~key: string=?, unit) =>
    Js.t({. "navigation": ReactNavigation.Navigation.t});
  let make: {. "navigation": ReactNavigation.Navigation.t} => React.element;
};
/*  There is no `initialScreenName config on `StackNavigator` in reason.

The initial screen is the first item in you array, here `Home`. Flip them around to see `Details` rendered first
    // let navigator =
    //   StackNavigator.(
    //     make({
    //       "Home": HomeScreen.make,
    //       "Details": DetailsScreen.make,
    //       "initialRouteName":"Details"
    //     })
    //   );
    // Reason version of https://snack.expo.io/@react-navigation/hello-react-navigation-v3 and https://reactnavigation.org/docs/en/hello-react-navigation.html#summary */
let navigator: ReactNavigation.Types.navigator;