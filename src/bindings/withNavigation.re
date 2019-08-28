[@bs.module ("react-navigation", "withNavigation")]
external withNavigation: React.component('props) => React.component('props) =
  "withNavigation";

module NavigationEvents = {
  type payload;
  type eventProps = {
    onWillFocus: payload => unit,
    onDidFocus: payload => unit,
    onWillBlur: payload => unit,
    onDidBlur: payload => unit,
  };
  [@bs.module ("react-navigation", "NavigationEvents")] [@react.component]
  external make: eventProps => React.element = "NavigationEvents";
};
// module WrappedMain = {
//   let makeProps = NavigationEvents.makeProps;
//   let make = withNavigation(NavigationEvents.make);
// };

let makeProps = NavigationEvents.makeProps;
let make = withNavigation(NavigationEvents.make);