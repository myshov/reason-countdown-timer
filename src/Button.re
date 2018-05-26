let component = ReasonReact.statelessComponent("Button");

let make = (~disabled, ~text, ~onClick, _children) => {
  ...component,

  render: _self => {
    if (disabled == true) {
      <button disabled>
        (ReasonReact.string(text))
      </button>
    } else {
      <button onClick={onClick}>
        (ReasonReact.string(text))
      </button>
    }
  },
};

