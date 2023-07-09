type 'e t = Nil | Node of 'e * 'e t [@@deriving show, eq]

val empty : 'e t -> bool
val length : 'e t -> int
val head : 'e t -> 'e
val tail : 'e t -> 'e t
val take : int -> 'e t -> 'e t
val drop : int -> 'e t -> 'e t
(* val show_t : 'e t -> string *)
(* val equal : 'e t -> string *)
