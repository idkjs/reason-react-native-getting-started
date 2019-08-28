module Button = {
  [@bs.module ("react-native-paper", "Button")] [@react.component]
  external make:
    (
      ~mode: [@bs.string] [ | `text | `outlined | `contained],
      ~onPress: unit => unit,
      ~color: string=?,
      ~icon: string=?,
      ~style: ReactNative.Style.t,
      ~children:'b
    ) =>
    // ~children:'b
    React.element =
    "Button";
};

module IconButton = {
  [@bs.module ("react-native-paper", "IconButton")] [@react.component]
  external make:
    (
      ~icon: string,
      ~color: string=?,
      ~size: float=?,
      ~accessibilityLabel: string=?,
      ~onPress: unit => unit,
      ~style: ReactNative.Style.t=?,
      ~theme: 'a=?,
      // ~children:'b,
      ~mode: [@bs.string] [ | `text | `outlined | `contained]
    ) =>
    React.element =
    "IconButton";
};