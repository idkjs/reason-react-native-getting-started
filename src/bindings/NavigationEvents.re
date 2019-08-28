[@bs.module ("react-navigation", "NavigationEvents")] [@react.component]
external make:
  (
    ~onWillFocus: 'a => unit,
    ~onDidFocus: 'a => unit,
    ~onWillBlur: 'a => unit,
    ~onDidBlur: 'a => unit
  ) =>
  React.element =
  "NavigationEvents";