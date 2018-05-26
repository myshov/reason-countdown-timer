let component = ReasonReact.statelessComponent("Button");

let make = (~disabled, ~text, ~onClick, _children) => {
  ...component,

  render: _self => {
    if (disabled == true) {
      <button className="btn btn-default" disabled>
        (ReasonReact.string(text))
      </button>
    } else {
      <button className="btn btn-default" onClick={onClick}>
        (ReasonReact.string(text))
      </button>
    }
  },
};

