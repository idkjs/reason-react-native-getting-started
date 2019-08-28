module type Config = {
  type state;
  type value;
  let useHook: (~initialState: state=?, unit) => value;
};

module CreateContainer:
  (Config: Config) =>
   {
    module Provider: {
      [@react.component]
      let make:
        (~children: React.element, ~initialState: Config.state=?) =>
        React.element;
    };

    let useContainer: unit => Config.value;
  };