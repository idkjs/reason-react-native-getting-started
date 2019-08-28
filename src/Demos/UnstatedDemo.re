open ReactNative;
let styles =
  Style.(
    StyleSheet.create({
      "buttons": style(~flexDirection=`column, ~padding=8.->dp, ()),
      "button": style(~margin=8.->dp, ()),
    })
  );
type counter = {
  count: int,
  decrement: unit => unit,
  increment: unit => unit,
  reset: unit => unit,
};

let useState = initial => {
  React.useReducer((_, action) => action, initial);
};

let useCounter = (~initialState=0, ()) => {
  let (count, setCount) = useState(initialState);
  let decrement = () => setCount(count - 1);
  let increment = () => setCount(count + 1);
  let reset = () => setCount(initialState);
  {count, decrement, increment, reset};
};

module Counter =
  UnstatedNext.CreateContainer({
    type state = int;
    type value = counter;
    let useHook = useCounter;
  });

module CounterDisplay = {
  [@react.component]
  let make = () => {
    let counter = Counter.useContainer();
    // <View style=styles##buttons>
    <View style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Paper.IconButton
        mode=`contained
        onPress={_ => counter.decrement()}
        style=styles##button
        icon="remove"
      />
      <Text style=Style.(style(~fontSize=50., ()))>
        {React.string(string_of_int(counter.count))}
      </Text>
      <Paper.IconButton
        mode=`contained
        onPress={_ => counter.increment()}
        style=styles##button
        icon="add"
      />
      <Paper.Button
        mode=`contained onPress={_ => counter.reset()} style=styles##button>
        "Reset"->React.string
      </Paper.Button>
    </View>;
  };
};

module App = {
  [@react.component]
  let make = () =>
    <Counter.Provider>
      <CounterDisplay />
      <Counter.Provider initialState=2> <CounterDisplay /> </Counter.Provider>
    </Counter.Provider>;
};

[@react.component]
let make = () => <App />;