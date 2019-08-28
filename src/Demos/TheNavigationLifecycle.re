/**
 * Demo `The Navigation Lifecycle` React Navigation Module
 * https://reactnavigation.org/
 *
 * Converted to reasonml from https://reactnavigation.org/docs/en/navigation-lifecycle.html#example-scenario
 *
 */
open ReactNative;
open ReactNavigation;
module MyScreen = {
  [@react.component]
  let make = () => {
    // let make = (~navigation: Navigation.t) => {
    <Screen name="NavFocus Screen">
      <WithNavigationFocusScreen.Wrapper isFocused=false />
    </Screen>;
  };
};
module WithNavFocusScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="NavEvents Screen">
      <NavigationEventsScreen navigation />
    </Screen>;
  };
};
module HomeScreen = {
  [@react.component]
  let make = (~navigation: Navigation.t) => {
    <Screen name="Home Screen">
      <NavigationEvents
        onWillFocus={payload => Js.log2("will focus", payload)}
        onDidFocus={payload => Js.log2("did focus", payload)}
        onWillBlur={payload => Js.log2("will blur", payload)}
        onDidBlur={payload => Js.log2("did blur", payload)}
      />
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
    <Screen name="Details Screen">
      <Button
        title="Go to Details Screen Again"
        /* js version: `onPress={() => this.props.navigation.push('Details'}`
           `navigate` doesnt go anywhere because you are already on this page
           `push` in js, lets you indicate that you want to go to that screen anyway. */
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
      <Button title="Go back" onPress={_ => navigation->Navigation.goBack} />
      <Button
        title="Go to Home"
        onPress={_ => navigation->Navigation.navigate("Home")}
      />
      <Button
        title="Go to NavEvents Screen"
        onPress={_ => navigation->Navigation.navigate("NavEvents")}
      />
      /* `popToTop` take you to the top route in the current stack so this will go back to `Home` route. */
      <Button
        title="PopToTop"
        onPress={_ => navigation->Navigation.popToTop}
      />
      /* here im trying to `navigateWithParams` but I dont have any params I dont think. This compiles but doesn nothing. */
      <Button
        title="NavigateTo RouteName"
        onPress={_ =>
          navigation->Navigation.navigateWithParams(
            "NewRoute",
            {"route": Js.Obj.empty()},
          )
        }
      />
    </Screen>;
  };
};

let navigator =
  StackNavigator.(
    make({
      "Home": HomeScreen.make,
      "Details": DetailsScreen.make,
      "NavEvents": WithNavFocusScreen.make,
      "initialRouteName": "Home",
    })
  );