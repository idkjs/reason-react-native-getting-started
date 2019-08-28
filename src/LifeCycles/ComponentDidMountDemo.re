[@react.component]
let make = (~name: string) => {
  let (counter, setCounter) = React.useState(() => 0);
  // this useEffect ignores passed in prop `name`
  // Enter any thing you want to enter in componentDidMount.
  React.useEffect1(
    () => {
      setCounter(_ => counter + 1);
      None;
    },
    [||] // This is the key as this effect will be independent of any change in props.
  );

  "counter is rendered only 1 time"->React.string;
};