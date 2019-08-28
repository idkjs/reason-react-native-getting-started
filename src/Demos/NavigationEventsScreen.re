open ReactNative;
open ReactNavigation;
[@react.component]
let make = (~navigation: Navigation.t) => {
  <View>
    <NavigationEvents
      onWillFocus={payload => Js.log2("NAV_EVENTS:will focus", payload)}
      onDidFocus={payload => Js.log2("NAV_EVENTS:did focus", payload)}
      onWillBlur={payload => Js.log2("NAV_EVENTS:will blur", payload)}
      onDidBlur={payload => Js.log2("NAV_EVENTS:did blur", payload)}
    />
    <Screen name="Navigation Events Screen">
      <Text value="Check the console" />
      <Button
        title="Go to Details"
        onPress={_ => navigation->Navigation.navigate("Details")}
      />
    </Screen>
  </View>;
};