type 'e t = Nil | Node of 'e * 'e t [@@deriving show, eq]

let empty xs = match xs with Nil -> true | Node _ -> false

let length xs =
  let rec length' n xs =
    match xs with Nil -> n | Node (_, rest) -> length' (n + 1) rest
  in
  length' 0 xs

let head xs =
  match xs with Node (x, _) -> x | Nil -> failwith "Called head on empty list"

let tail xs =
  match xs with
  | Node (_, rest) -> rest
  | Nil -> failwith "called tail on empty list"

let take n xs =
  let rec take' n acc xs =
    match (n, xs) with
    | 0, _ -> acc
    | _, Node (x, rest) -> take' (n - 1) (Node (x, acc)) rest
    | _, Nil -> failwith "Called take n xs, where n < length xs"
  in
  take' n Nil xs

let rec drop n xs =
  match (n, xs) with
  | 0, _ -> xs
  | _, Node (_, rest) -> drop (n - 1) rest
  | _, Nil -> failwith "Called drop n xs, where n < length xs"

(* let%test "length of empyt list" = length Nil = 0 *)
(* let%test "tail" = tail (Node (2, Node (3, Nil))) = Node (3, Nil) *)
