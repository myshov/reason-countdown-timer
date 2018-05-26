let padWithZeros = (str) => (String.length(str) == 1) ? "0" ++ str : str;

let toReadableString = (value) =>
  value
    |> int_of_float
    |> string_of_int
    |> padWithZeros
    ;

let getTimerData = (timeStart, timeEnd) => {
  let unixTimeShift = 17.0 *. 60.0 *. 60.0 *. 1000.0;
  let timeDiff = Js.Date.fromFloat(timeEnd -. timeStart +. unixTimeShift);
  let seconds = toReadableString(Js.Date.getSeconds(timeDiff));
  let minutes = toReadableString(Js.Date.getMinutes(timeDiff));
  let hours = toReadableString(Js.Date.getHours(timeDiff));

  hours ++ ":" ++ minutes ++ ":" ++ seconds;
};
