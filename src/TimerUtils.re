let minute = 60.0 *. 1000.0;

let unixTimeShift = 17.0 *. 60.0 *. 60.0 *. 1000.0;

let padWithZeros = (str) => (String.length(str) == 1) ? "0" ++ str : str;

let toReadableString = (value) =>
  value
    |> int_of_float
    |> string_of_int
    |> padWithZeros
    ;

let toReadableTime = (value) =>
  value
    |> (x) => x /. minute
    |> int_of_float
    |> string_of_int
    |> padWithZeros
    ;

let formatTime = (time) => {
  let seconds = toReadableString(Js.Date.getSeconds(time));
  let minutes = toReadableString(Js.Date.getMinutes(time));
  let hours = toReadableString(Js.Date.getHours(time));

  hours ++ ":" ++ minutes ++ ":" ++ seconds;
};

let getTimerData = (timeStart, timeEnd) => {
  let time = Js.Date.fromFloat(timeEnd -. timeStart +. unixTimeShift);
  formatTime(time);
};

let getCountdownTimerData = (timeStart, timeEnd, timeLimit) => {
  let timeDiff = timeEnd -. timeStart;
  let time = Js.Date.fromFloat(timeLimit -. timeDiff +. unixTimeShift);
  formatTime(time);
};
