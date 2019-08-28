/**
 * Demo React Navigation Module
 * https://reactnavigation.org/
 *
 * Converted to reasonml from https://reactnavigation.org/docs/en/navigating.html#going-back
 *
 */

open ReactNative;
open ReactNavigation;

module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Home Screen">
      <Button
        title="Go to Details"
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
    </Screen>;
  };
};
module DetailsScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Details Screen"><Button
        title="Go to Details Screen Again"
/**================================================== *
 * ==========  Navigating  ========== *
 * ================================================== */

/* js version:
```
onPress={() => this.props.navigation.push('Details')}
```
`navigate` doesnt go anywhere because you are already on this page
`push` in js, lets you indicate that you want to go to that screen anyway */

/* =======  End of Navigating  ======= */
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
      <Button
          title="Go back"
          onPress={_ => navigation->Navigation.goBack}
        />
    </Screen>;
  };
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
let navigator =
    StackNavigator.(
      make({
        "Home": HomeScreen.make,
        "Details": DetailsScreen.make,
        "initialRouteName": "Details",
      })
    );
