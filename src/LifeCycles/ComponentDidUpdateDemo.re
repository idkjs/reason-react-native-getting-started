[@react.component]
let make = (~name) => {
  let (counter, setCounter) = React.useState(() => 0);

  // This will allow the change of the state/props only if certain props are passed or changed to.
  React.useEffect1(
    () => {
      if (name === "componentDidUpdate") {
        setCounter(_ => counter + 1);
      }
      None;
    },
    [|name|] // Here we are listing dependency on which component will be re-rendered.
  );

  (name ++ "is called " ++ counter -> string_of_int ++ " times.") -> React.string;
};