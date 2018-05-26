type action =
  | Tick
  | Start
  | Stop
  ;

type state = {
  active: bool,
  startTime: float,
  currentTime: float,
  intervalId: ref(option(Js.Global.intervalId)),
};


let component = ReasonReact.reducerComponent("App");


let make = _children => {
  ...component,

  initialState: () => {
    active: false,
    startTime: 0.0,
    currentTime: 0.0,
    intervalId: ref(None),
  },

  reducer: (action, state) =>
    switch (action) {
    | Tick => ReasonReact.Update({...state, currentTime: Js.Date.now()});
    | Start => ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          active: true,
          startTime: Js.Date.now(),
          currentTime: Js.Date.now(),
        },
        (self => {
          self.state.intervalId := Some(Js.Global.setInterval(() => self.send(Tick), 1000));
        }),
      );
    | Stop => ReasonReact.UpdateWithSideEffects(
        {...state, active: false},
        (self => {
          switch(self.state.intervalId^) {
          | Some(id) => Js.Global.clearInterval(id);
          | None => ();
          }
        }),
      );
    },

  render: ({state, send}) =>
    <div>
      <Timer currentTime={state.currentTime} startTime={state.startTime} />
      <Button onClick={_event => send(Start)} disabled={state.active} text="Start" />
      <Button onClick={_event => send(Stop)} disabled={false} text="Stop" />
    </div>,
};
