type action =
  | Tick
  | Start
  | Stop
  ;

type state = {
  active: bool,
  startTime: float,
  currentTime: float,
  timeLimit: float,
  intervalId: ref(option(Js.Global.intervalId)),
};

let component = ReasonReact.reducerComponent("App");

Notifications.requestPermission((_) => ());

let make = _children => {
  ...component,

  initialState: () => {
    active: false,
    startTime: 0.0,
    currentTime: 0.0,
    timeLimit: 20.0 *. TimerUtils.minute,
    intervalId: ref(None),
  },

  reducer: (action, state) =>
    switch (action) {
    | Tick => {
        let currentTime = Js.Date.now();
        let timeRemaining = state.timeLimit -. (currentTime -. state.startTime);
        if (timeRemaining > 0.0) {
          ReasonReact.Update({...state, currentTime});
        } else {
          ReasonReact.UpdateWithSideEffects(
            {...state, active: false},
            (self => {
              switch(self.state.intervalId^) {
              | Some(id) => Js.Global.clearInterval(id);
              | None => ();
              };
              Notifications.sendNotification("Time slice is done!");
            }),
          );
        }
      }
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
    <div className="root">
      <h1 className="title">
        (ReasonReact.string("Simple Timer"))
      </h1>
      <Timer currentTime={state.currentTime} startTime={state.startTime} timeLimit={state.timeLimit} />
      <div className="controls">
        <Button onClick={_event => send(Start)} disabled={state.active} text="Start" />
        <Button onClick={_event => send(Stop)} disabled={false} text="Stop" />
      </div>
    </div>,
};
