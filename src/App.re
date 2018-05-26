type action =
  | Start
  | Stop
  ;

type state = {
  active: bool,
};

let component = ReasonReact.reducerComponent("App");


let make = _children => {
  ...component,

  initialState: () => {
    active: false,
  },

  reducer: (action, _state) =>
    switch (action) {
    | Start => ReasonReact.Update({active: true});
    | Stop => ReasonReact.Update({active: false});
    },

  render: ({state, send}) =>
    <div>
      <Timer active={state.active}/>
      <button onClick={_event => send(Start)}>(ReasonReact.string("Start"))</button>
      <button onClick={_event => send(Stop)}>(ReasonReact.string("Stop"))</button>
    </div>,
};
