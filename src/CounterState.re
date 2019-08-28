type counter = {
  count: int,
  decrement: unit => unit,
  increment: unit => unit,
};

let useState = initial => {
  React.useReducer((_, action) => action, initial);
};

let useCounter = (~initialState=0, ()) => {
  let (count, setCount) = useState(initialState);
  let decrement = () => setCount(count - 1);
  let increment = () => setCount(count + 1);
  {count, decrement, increment};
};

module Counter =
  UnstatedNext.CreateContainer({
    type state = int;
    type value = counter;
    let useHook = useCounter;
  });