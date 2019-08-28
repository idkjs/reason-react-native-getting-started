/**
 * AppState Demo React Native Module
 * https://github.com/facebook/react-native
 *
 * Converted to reasonml from https://facebook.github.io/react-native/docs/appstate.html
 * See Api: https://reasonml-community.github.io/reason-react-native/en/docs/apis/AppState/
 *
 */

open ReactNative;
[@react.component]
let make = () => {
  let (appState, setAppState) = React.useState(_ => AppState.currentState);

  let handleAppStateChange = nextAppState => {
    switch (appState, nextAppState) {
    | (_, state) when state === AppState.background =>
      Js.log("App has come to the background!")
    | (_, state) when state === AppState.active =>
      Js.log("App has come to the foreground!")
    | _ => ()
    };
    setAppState(_ => nextAppState);
  };

  React.useEffect(() => {
    AppState.addEventListener(`change(state => handleAppStateChange(state)));
    Some(
      () =>
        AppState.removeEventListener(
          `change(state => handleAppStateChange(state)),
        ),
    );
  });

  let renderAppState =
    switch (appState) {
    | appState when appState === AppState.active => "active"
    | appState when appState === AppState.background => "background"
    | appState when appState === AppState.inactive => "inactive"
    | _ => "unknown"
    };
  <Text> {"Current state is: " ++ renderAppState |> React.string} </Text>;
};