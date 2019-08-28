[@react.component]
let make = () => {
  let (counter, setCounter) = React.useState(() => 0);

  React.useEffect(() => {
    let clearTimeout = Js.Global.setTimeout(() => setCounter(_ => counter + 1), 500);

    Some(()=>Js.Global.clearTimeout(clearTimeout)) // This will be called when the component will be un-mounted
  });
  ("Counter is updated " ++ counter -> string_of_int ++ " times.") -> React.string;
};