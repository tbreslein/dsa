type 'e t = Nil | Node of 'e * 'e t [@@deriving show, eq]

exception Empty
exception TooShort
exception TooLong

let empty xs = match xs with Nil -> true | Node _ -> false

let length xs =
  let rec length' n xs =
    match xs with Nil -> n | Node (_, rest) -> length' (n + 1) rest
  in
  length' 0 xs

let head xs = match xs with Node (x, _) -> x | Nil -> raise Empty
let tail xs = match xs with Node (_, rest) -> rest | Nil -> raise Empty

let take n xs =
  let rec take' n acc xs =
    match (n, xs) with
    | 0, _ -> acc
    | _, Node (x, rest) -> take' (n - 1) (Node (x, acc)) rest
    | _, Nil -> raise TooShort
  in
  take' n Nil xs

let rec drop n xs =
  match (n, xs) with
  | 0, _ -> xs
  | _, Node (_, rest) -> drop (n - 1) rest
  | _, Nil -> raise TooLong

let push x xs = Node (x, xs)
let pop xs = match xs with Node (x, rest) -> (x, rest) | Nil -> raise Empty
