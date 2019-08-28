[@bs.module("react-native-paper","Button")][@react.component]
external make:
(
  ~mode: [@bs.string][ |`text |`outlined |`contained ],
  ~onPress:'a => unit,
  ~style:ReactNative.Style.t,
  ~children:'b
) =>
 React.element = "Button";