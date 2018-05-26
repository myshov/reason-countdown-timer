let padWithZeros = (str) => (String.length(str) == 1) ? "0" ++ str : str;

let toReadableString = (value) =>
  value
    |> int_of_float
    |> string_of_int
    |> padWithZeros
    ;

let getTimerData = (timeStart, timeEnd) => {
  let timeDiff = Js.Date.fromFloat(timeEnd -. timeStart);
  let seconds = toReadableString(Js.Date.getSeconds(timeDiff));
  let minutes = toReadableString(Js.Date.getMinutes(timeDiff));

  minutes ++ ":" ++ seconds;
};
