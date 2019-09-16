let styles: {
  .
  "aButton": ReactNative.Style.t,
  "button": ReactNative.Style.t,
  "root": ReactNative.Style.t,
  "title": ReactNative.Style.t,
};
let routes: array(string);
module HomeButton: {
  let makeProps:
    (
      ~name: string,
      ~navigation: ReactNavigation.Navigation.t,
      ~key: string=?,
      unit
    ) =>
    Js.t({
      .
      "name": string,
      "navigation": ReactNavigation.Navigation.t,
    });
  let make:
    {
      .
      "name": string,
      "navigation": ReactNavigation.Navigation.t,
    } =>
    React.element;
};
module HomeScreen: {
  let makeProps:
    (~navigation: ReactNavigation.Navigation.t, ~key: string=?, unit) =>
    Js.t({. "navigation": ReactNavigation.Navigation.t});
  let make: {. "navigation": ReactNavigation.Navigation.t} => React.element;
};
module AppContainer: {
  let makeProps:
    (
      ~persistNavigationState: ReactNavigation.AppContainer.persistNavigationState
                                 =?,
      ~loadNavigationState: ReactNavigation.AppContainer.loadNavigationState=?,
      ~screenProps: {. "someProp": int}=?,
      ~setNavigatorRef: Js.Nullable.t(
                          ReactNavigation.NavigationContainer.t,
                        ) =>
                        unit
                          =?,
      ~key: string=?,
      unit
    ) =>
    ReactNavigation.AppContainer.appContainerProps(Js.t({. "someProp": int}));
  let make:
    React.component(
      ReactNavigation.AppContainer.appContainerProps({. "someProp": int}),
    );
};
let makeProps: (~key: string=?, unit) => Js.t({.});
let make: Js.t({.}) => React.element;