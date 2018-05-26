let component = ReasonReact.statelessComponent("Timer");

let make = (~startTime, ~currentTime, ~timeLimit, _children) => {
  ...component,

  render: _self => {
    let displayTime =  TimerUtils.getCountdownTimerData(startTime, currentTime, timeLimit);
    <div className="timer">
      (ReasonReact.string(displayTime))
    </div>;
  },
};
