type action =
  | Tick
  | Activate
  | Deactivate
  ;

type state = {
  intervalId: ref(option(Js.Global.intervalId)),
  startTime: float,
  displayTime: string,
  active: bool,
};

let component = ReasonReact.reducerComponent("Timer");

let make = (~active, _children) => {
  ...component,

  initialState: () => {
    active: false,
    startTime: Js.Date.now(),
    displayTime: "00:00",
    intervalId: ref(None),
  },

  reducer: (action, state) =>
    switch (action) {
    | Tick => ReasonReact.Update({...state, displayTime: TimerUtils.getTimerData(state.startTime, Js.Date.now())});
    | Activate => ReasonReact.Update({...state, active: true});
    | Deactivate => ReasonReact.Update({...state, active: false});
    },

  didUpdate: ({newSelf}) => {
    if (newSelf.state.active == false && active == true) {
      newSelf.send(Activate);
      let intervalId = Js.Global.setInterval(() => newSelf.send(Tick), 1000);
      newSelf.onUnmount(() => Js.Global.clearInterval(intervalId));
      newSelf.state.intervalId := Some(intervalId);
    };
    if (newSelf.state.active == true && active == false) {
      newSelf.send(Deactivate);
      switch(newSelf.state.intervalId^) {
      | Some(id) => Js.Global.clearInterval(id);
      | None => ();
      }
    };
  },

  render: ({state}) =>
    <div> (ReasonReact.string(state.displayTime)) </div>,
};
