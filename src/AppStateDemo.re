
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
    AppState.addEventListener(`change(state => handleAppStateChange(state)))
    |> ignore;
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
// let styles =
//   Style.(
//     StyleSheet.create({
//       "container":
//         style(
//           ~flex=1.,
//           ~justifyContent=`center,
//           ~alignItems=`center,
//           ~backgroundColor="#F5FCFF",
//           (),
//         ),
//       "instructions": style(~textAlign=`center, ~color="#ffffff", ()),
//     })
//   );

// [@react.component]
// let make = () => {
//   let (appState, setAppState) = React.useState(_ => AppState.currentState);

//   let handleAppStateChange = nextAppState => {
//     switch (appState, nextAppState) {
//     | (_, state) when state === AppState.background =>
//       Js.log("App has come to the background!")
//     | (_, state) when state === AppState.active =>
//       Js.log("App has come to the foreground!")
//     | _ => ()
//     };
//     setAppState(_ => nextAppState);
//   };

//   React.useEffect(() => {
//     AppState.addEventListener(
//       `change(state => handleAppStateChange(state)),
//     );
//     // |> ignore;
//     Some(
//       () =>
//         AppState.removeEventListener(
//           `change(state => handleAppStateChange(state)),
//         ),
//     );
//   });

//   let renderAppState =
//     switch (appState) {
//     | appState when appState === AppState.active => "active"
//     | appState when appState === AppState.background => "background"
//     | appState when appState === AppState.inactive => "inactive"
//     | _ => "unknown"
//     };
//   <Text> {"Current state is: " ++ renderAppState |> React.string} </Text>;
// };