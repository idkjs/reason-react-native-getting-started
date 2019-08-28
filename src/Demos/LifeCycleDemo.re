/* See: https://reactnavigation.org/docs/en/navigation-lifecycle.html#example-scenario
   const HomeStack = createStackNavigator({
     Home: HomeScreen,
     Details: DetailsScreen,
   });

   const SettingsStack = createStackNavigator({
     Settings: SettingsScreen,
     Profile: ProfileScreen,
   });

   const TabNavigator = createBottomTabNavigator(
     {
       Home: HomeStack,
       Settings: SettingsStack,
     }
   ); */
open ReactNative;
open ReactNavigation;
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
        /*         js version: `onPress={() => this.props.navigation.push('Details')}`
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