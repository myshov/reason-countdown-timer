let component = ReasonReact.statelessComponent("Timer");

let make = (~startTime, ~currentTime, _children) => {
  ...component,

  render: _self => {
    let displayTime =  TimerUtils.getTimerData(startTime, currentTime);
    <div> (ReasonReact.string(displayTime)) </div>;
  },
};
