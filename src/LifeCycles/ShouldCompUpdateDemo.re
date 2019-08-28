[@react.component]
let make = (~name) => name -> React.string;

// If you want to shallow compare the props then use React.memo
// let make = React.memo(make);

// // If you want to custom compare the nested props then use React.memoCustomCompareProps
// let deepCompare = (nextProps, currentProps) => nextProps === currentProps;

// let make = React.memoCustomCompareProps(
//   make,
//   (nextProps, currentProps) => {
//     let result = deepCompare(nextProps, currentProps);
//     result;
//   }
// );