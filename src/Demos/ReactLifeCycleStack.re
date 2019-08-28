open ReactNative;

module ComponentDidMountDemo = {
  [@react.component]
  let make = (~name: string) => {
    let (counter, setCounter) = React.useState(() => 0);
    Js.log(name);
    // this useEffect ignores passed in prop `name`
    // Enter any thing you want to enter in componentDidMount.
    React.useEffect1(
      () => {
        setCounter(_ => counter + 1);
        None;
      },
      [||] // This is the key as this effect will be independent of any change in props.
    );

    <Text> "counter is rendered only 1 time"->React.string </Text>;
  };
};

module ComponentDidUpdateDemo = {
  [@react.component]
  let make = (~name) => {
    let (counter, setCounter) = React.useState(() => 0);

    // This will allow the change of the state/props only if certain props are passed or changed to.
    React.useEffect1(
      () => {
        if (name === "componentDidUpdate") {
          setCounter(_ => counter + 1);
        };
        None;
      },
      [|name|] // Here we are listing dependency on which component will be re-rendered.
    );

    <Text>
      {(name ++ "is called " ++ counter->string_of_int ++ " times.")
       ->React.string}
    </Text>;
  };
};
module ComponentWillUnmountDemo = {
  [@react.component]
  let make = () => {
    let (counter, setCounter) = React.useState(() => 0);

    React.useEffect(() => {
      let clearTimeout =
        Js.Global.setTimeout(() => setCounter(_ => counter + 1), 500);

      Some(() => Js.Global.clearTimeout(clearTimeout)); // This will be called when the component will be un-mounted
    });
    <Text>
      {("Counter is updated " ++ counter->string_of_int ++ " times.")
       ->React.string}
    </Text>;
  };
};
module ShouldComponentUpdateDemo = {
  [@react.component]
  let make = (~name) => <Text> name->React.string </Text>;
};