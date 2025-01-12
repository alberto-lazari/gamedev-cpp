(*
  This requires the '-rectypes' OCaml flag.
  It allows for modeling states as pure functions to other states.
*)
type state = char -> state

let in_range (lower, upper) c =
  let code = Char.code c in
  code >= Char.code lower && code <= Char.code upper


let rec init input = match input with
| _ when in_range ('A', 'Z') input -> upper
| _ -> error

and upper input = match input with
| _ when in_range ('A', 'Z') input -> upper
| _ when in_range ('a', 'z') input -> lower
| ',' | ';' -> comma
| '.' | '!' | '?' -> period
| ' ' -> space
| _ -> upper

and lower input = match input with
| _ when in_range ('a', 'z') input -> lower
| ' ' -> space
| ',' | ';' -> comma
| '.' | '!' | '?' -> period
| _ -> error

and space input = match input with
| _ when in_range ('A', 'Z') input -> upper
| _ when in_range ('a', 'z') input -> lower
| _ -> error

and comma input = match input with
| ' ' -> space
| _ -> error

and period input = match input with
| ' ' -> init
| _ -> error

and error _ = error

let check input = match input with
| "" -> true
| _ -> let input_list = String.to_seq input |> List.of_seq in
    (* Perform transitions for each character in the sentence and reach the final state *)
    let final_state = List.fold_left (fun transition input -> transition input) init input_list in
    final_state == period

let () = if (Array.length Sys.argv) > 1 then
  let sentence = Sys.argv.(1) in
  if not (check sentence) then exit 1
