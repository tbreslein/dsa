type 'e t = {
    mutable start: int;
    mutable stop: int;
    buf: 'e Array.t;
}

exception Empty
exception Todo

let create cap = raise Todo
let empty xs = xs.start = xs.stop
let length xs = raise Todo
let push xs x = raise Todo
let pop xs = raise Todo
let set xs x = raise Todo
let get xs i = raise Todo

