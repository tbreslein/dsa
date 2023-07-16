type 'e t

val create : int -> 'e t
val empty : 'e t -> bool
val length : 'e t -> int
val push : 'e t -> 'e -> 'e t
val pop : 'e t -> 'e
val set : 'e t -> 'e -> unit
val get : 'e t -> int -> unit
