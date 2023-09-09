type 'e t = Nil | Node of 'e * 'e t [@@deriving show, eq];;

exception Empty;;
exception TooShort;;
exception TooLong;;

val empty : 'e t -> bool;;
val length : 'e t -> int;;
val head : 'e t -> 'e;;
val tail : 'e t -> 'e t;;
val take : int -> 'e t -> 'e t;;
val drop : int -> 'e t -> 'e t;;
val push : 'e t -> 'e -> 'e t;;
val pop : 'e t -> 'e * 'e t;;
