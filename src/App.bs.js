// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Timer$ReactTemplate = require("./Timer.bs.js");
var Button$ReactTemplate = require("./Button.bs.js");
var TimerUtils$ReactTemplate = require("./TimerUtils.bs.js");
var Notifications$ReactTemplate = require("./Notifications.bs.js");

var component = ReasonReact.reducerComponent("App");

if (Notifications$ReactTemplate.isEnabled) {
  window.Notification.requestPermission((function () {
          return /* () */0;
        }));
}

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var send = param[/* send */3];
              var state = param[/* state */1];
              var match = state[/* page */5];
              if (match) {
                return React.createElement("div", {
                            className: "root"
                          }, React.createElement("div", {
                                className: "menu"
                              }, React.createElement("a", {
                                    className: "menu__item",
                                    href: "#",
                                    onClick: (function () {
                                        return Curry._1(send, /* ChangePage */Block.__(1, [/* Main */0]));
                                      })
                                  }, "App"), React.createElement("a", {
                                    className: "menu__item menu__item_active",
                                    href: "#"
                                  }, "Settings")), React.createElement("h1", {
                                className: "title"
                              }, "Settings"), React.createElement("div", {
                                className: "form-group"
                              }, React.createElement("label", undefined, "Minutes"), React.createElement("input", {
                                    defaultValue: TimerUtils$ReactTemplate.toReadableTime(state[/* timeLimit */3]),
                                    className: "form-control",
                                    type: "number",
                                    onChange: (function ($$event) {
                                        return Curry._1(send, /* SetTimeLimit */Block.__(0, [$$event.target.value]));
                                      })
                                  })));
              } else {
                return React.createElement("div", {
                            className: "root"
                          }, React.createElement("div", {
                                className: "menu"
                              }, React.createElement("a", {
                                    className: "menu__item menu__item_active",
                                    href: "#"
                                  }, "App"), React.createElement("a", {
                                    className: "menu__item",
                                    href: "#",
                                    onClick: (function () {
                                        return Curry._1(send, /* ChangePage */Block.__(1, [/* Settings */1]));
                                      })
                                  }, "Settings")), React.createElement("h1", {
                                className: "title"
                              }, "Simple Timer"), ReasonReact.element(/* None */0, /* None */0, Timer$ReactTemplate.make(state[/* startTime */1], state[/* currentTime */2], state[/* timeLimit */3], /* array */[])), React.createElement("div", {
                                className: "controls"
                              }, ReasonReact.element(/* None */0, /* None */0, Button$ReactTemplate.make(/* Some */[state[/* active */0]], "Start", (function () {
                                          return Curry._1(send, /* Start */1);
                                        }), /* array */[])), ReasonReact.element(/* None */0, /* None */0, Button$ReactTemplate.make(/* Some */[false], "Stop", (function () {
                                          return Curry._1(send, /* Stop */2);
                                        }), /* array */[]))));
              }
            }),
          /* initialState */(function () {
              return /* record */[
                      /* active */false,
                      /* startTime */0.0,
                      /* currentTime */0.0,
                      /* timeLimit */20.0 * TimerUtils$ReactTemplate.minute,
                      /* intervalId */[/* None */0],
                      /* page : Main */0
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                switch (action) {
                  case 0 : 
                      var currentTime = Date.now();
                      var timeRemaining = state[/* timeLimit */3] - (currentTime - state[/* startTime */1]);
                      if (timeRemaining > 0.0) {
                        return /* Update */Block.__(0, [/* record */[
                                    /* active */state[/* active */0],
                                    /* startTime */state[/* startTime */1],
                                    /* currentTime */currentTime,
                                    /* timeLimit */state[/* timeLimit */3],
                                    /* intervalId */state[/* intervalId */4],
                                    /* page */state[/* page */5]
                                  ]]);
                      } else {
                        return /* UpdateWithSideEffects */Block.__(2, [
                                  /* record */[
                                    /* active */false,
                                    /* startTime */state[/* startTime */1],
                                    /* currentTime */state[/* currentTime */2],
                                    /* timeLimit */state[/* timeLimit */3],
                                    /* intervalId */state[/* intervalId */4],
                                    /* page */state[/* page */5]
                                  ],
                                  (function (self) {
                                      var match = self[/* state */1][/* intervalId */4][0];
                                      if (match) {
                                        clearInterval(match[0]);
                                      }
                                      new Notification("Time slice is done!");
                                      return /* () */0;
                                    })
                                ]);
                      }
                  case 1 : 
                      return /* UpdateWithSideEffects */Block.__(2, [
                                /* record */[
                                  /* active */true,
                                  /* startTime */Date.now(),
                                  /* currentTime */Date.now(),
                                  /* timeLimit */state[/* timeLimit */3],
                                  /* intervalId */state[/* intervalId */4],
                                  /* page */state[/* page */5]
                                ],
                                (function (self) {
                                    self[/* state */1][/* intervalId */4][0] = /* Some */[setInterval((function () {
                                              return Curry._1(self[/* send */3], /* Tick */0);
                                            }), 1000)];
                                    return /* () */0;
                                  })
                              ]);
                  case 2 : 
                      return /* UpdateWithSideEffects */Block.__(2, [
                                /* record */[
                                  /* active */false,
                                  /* startTime */state[/* startTime */1],
                                  /* currentTime */state[/* currentTime */2],
                                  /* timeLimit */state[/* timeLimit */3],
                                  /* intervalId */state[/* intervalId */4],
                                  /* page */state[/* page */5]
                                ],
                                (function (self) {
                                    var match = self[/* state */1][/* intervalId */4][0];
                                    if (match) {
                                      clearInterval(match[0]);
                                      return /* () */0;
                                    } else {
                                      return /* () */0;
                                    }
                                  })
                              ]);
                  
                }
              } else if (action.tag) {
                return /* Update */Block.__(0, [/* record */[
                            /* active */state[/* active */0],
                            /* startTime */state[/* startTime */1],
                            /* currentTime */state[/* currentTime */2],
                            /* timeLimit */state[/* timeLimit */3],
                            /* intervalId */state[/* intervalId */4],
                            /* page */action[0]
                          ]]);
              } else {
                var minutes = action[0];
                if (minutes.length !== 0) {
                  return /* Update */Block.__(0, [/* record */[
                              /* active */state[/* active */0],
                              /* startTime */state[/* startTime */1],
                              /* currentTime */state[/* currentTime */2],
                              /* timeLimit */Caml_format.caml_float_of_string(minutes) * TimerUtils$ReactTemplate.minute,
                              /* intervalId */state[/* intervalId */4],
                              /* page */state[/* page */5]
                            ]]);
                } else {
                  return /* NoUpdate */0;
                }
              }
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
