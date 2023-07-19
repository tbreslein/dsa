type 'e t = {
    mutable start: int;
    mutable stop: int;
    mutable len: int;
    mutable cap: int;
    mutable buf: 'e option Array.t;
}

exception Empty
exception OutOfBounds
exception TODO

let grow xs = xs.buf <- Array.append xs.buf (Array.make xs.cap None); xs.cap <- max (xs.cap * 2) 1

let create cap = { start = 0; stop = 0; len = 0; cap = cap; buf = Array.make 1 None; }

let length xs = xs.len 

let empty xs = xs.len = 0

let push xs x =
    if xs.len = xs.cap
    then grow xs
    else ();
    Array.set xs.buf xs.len (Some x);
    xs.len <- xs.len + 1

let pop xs =
    if xs.len = 0
    then ()
    else xs.len <- xs.len - 1;
    let out = Array.get xs.buf xs.len in
    Array.set xs.buf xs.len None;
    out

let insert xs i x = raise TODO
let remove xs i = raise TODO

let set xs i x =
    if i >= xs.len
    then raise OutOfBounds
    else Array.unsafe_set xs.buf i (Some x)

let get xs i =
    if i >= xs.len
    then raise OutOfBounds
    else Array.unsafe_get xs.buf i
