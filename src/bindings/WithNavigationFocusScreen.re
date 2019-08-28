// see: https://reactnavigation.org/docs/en/with-navigation-focus.html#example
// import React from 'react';
// import { Text } from 'react-native';
// import { withNavigationFocus } from 'react-navigation';

// class FocusStateLabel extends React.Component {
//   render() {
//     return <Text>{this.props.isFocused ? 'Focused' : 'Not focused'}</Text>;
//   }
// }
open ReactNative;
open ReactNavigation;
module FocusStateLabel = {
  [@react.component]
  let make = (~isFocused: bool) => {
    // withNavigationFocus is a higher order component which passes the isFocused prop into a wrapped component. It's useful if you need to use the focus state in the render function of your screen component or another component rendered somewhere inside of a screen. So this should log.
    Js.log2("isFocused",isFocused);
    <Text>
      {isFocused ? "Focused" |> React.string : "Focused" |> React.string}
    </Text>;
  };
};
// withNavigationFocus returns a component that wraps FocusStateLabel and passes
// in the navigation prop
module Wrapper = {
  open WithNavigationFocus;
  let makeProps = FocusStateLabel.makeProps;
  let make = withNavigationFocus(FocusStateLabel.make);
};