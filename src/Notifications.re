type permission = [
  | `granted
  | `default
  | `denied
  ];

type permissionRequest = permission => unit;

[@bs.scope ("window", "Notification")] [@bs.val]
external requestPermission : permissionRequest => unit = "";

[@bs.new] external sendNotification : string => unit = "Notification";

[@bs.val] external document : {. [@bs.set] "title": string} = "";

let set_title : string => unit = str => document##title #= str;
