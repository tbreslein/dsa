type 'e t 

exception Empty
exception OutOfBounds

val create : int -> 'e t
val empty : 'e t -> bool
val length : 'e t -> int
val push : 'e t -> 'e -> unit
val pop : 'e t -> 'e option
val set : 'e t -> int -> 'e -> unit
val get : 'e t -> int -> 'e option
