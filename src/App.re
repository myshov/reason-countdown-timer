type appPage =
  | Main
  | Settings
  ;

type action =
  | Tick
  | Start
  | Stop
  | SetTimeLimit(string)
  | ChangePage(appPage)
  ;

type state = {
  active: bool,
  startTime: float,
  currentTime: float,
  timeLimit: float,
  intervalId: ref(option(Js.Global.intervalId)),
  page: appPage,
};

let component = ReasonReact.reducerComponent("App");

if (Notifications.isEnabled) {
  Notifications.requestPermission((_) => ());
};

let make = _children => {
  ...component,

  initialState: () => {
    page: Main,
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
    | ChangePage(page) => ReasonReact.Update({...state, page});
    | SetTimeLimit(minutes) => {
        if (String.length(minutes) > 0) {
          ReasonReact.Update({...state, timeLimit: float_of_string(minutes) *. TimerUtils.minute});
        } else {
          ReasonReact.NoUpdate;
        }
      }
    },

  render: ({state, send}) => {
    let showMain = (_) => {
      <div className="root">
        <div className="menu">
          <a href="#" className="menu__item menu__item_active">
            (ReasonReact.string("App"))
          </a>
          <a href="#" className="menu__item" onClick={_event => send(ChangePage(Settings))}>
            (ReasonReact.string("Settings"))
          </a>
        </div>
        <h1 className="title">
          (ReasonReact.string("Simple Timer"))
        </h1>
        <Timer currentTime={state.currentTime} startTime={state.startTime} timeLimit={state.timeLimit} />
        <div className="controls">
          <Button onClick={_event => send(Start)} disabled={state.active} text="Start" />
          <Button onClick={_event => send(Stop)} disabled={false} text="Stop" />
        </div>
      </div>
    };

    let showSettings = (_) => {
      <div className="root">
        <div className="menu">
          <a href="#" className="menu__item" onClick={_event => send(ChangePage(Main))}>
            (ReasonReact.string("App"))
          </a>
          <a href="#" className="menu__item menu__item_active">
            (ReasonReact.string("Settings"))
          </a>
        </div>
        <h1 className="title">
          (ReasonReact.string("Settings"))
        </h1>
        <div className="form-group">
          <label >(ReasonReact.string("Minutes"))</label>
          <input
            _type="number"
            className="form-control"
            defaultValue={TimerUtils.toReadableTime(state.timeLimit)}
            onChange=(
              event =>
                send(
                  SetTimeLimit(
                    ReactDOMRe.domElementToObj(
                      ReactEventRe.Form.target(event),
                    )##value,
                  ),
                )
            )
          />
        </div>
      </div>
    };

    switch (state.page) {
    | Main => showMain();
    | Settings => showSettings();
    };
  }
};
