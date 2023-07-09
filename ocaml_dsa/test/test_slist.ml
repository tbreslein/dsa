open Ocaml_dsa
open OUnit2

let to_string_with_int xs =
  let rec foo acc xs =
    match xs with
    | Slist.Nil -> acc
    | Node (x, rest) -> foo (acc ^ Int.to_string x ^ " ") rest
  in
  foo "[ " xs ^ "]"

let length_empty ctxt =
  OUnit2.assert_equal 0 (Slist.length Nil) ~ctxt ~printer:Int.to_string

let length_1 ctxt =
  OUnit2.assert_equal 1
    (Slist.length (Node (2, Nil)))
    ~ctxt ~printer:Int.to_string

let length_2 ctxt =
  OUnit2.assert_equal 2
    (Slist.length (Node (2, Node (1, Nil))))
    ~ctxt ~printer:Int.to_string

let length_suite =
  "slist length tests"
  >::: [
         "empty list" >:: length_empty;
         "one element list" >:: length_1;
         "two elements list" >:: length_2;
       ]

let tail_1 ctxt =
  OUnit2.assert_equal Slist.Nil
    (Slist.tail (Node (2, Nil)))
    ~ctxt ~printer:to_string_with_int

let tail_2 ctxt =
  OUnit2.assert_equal
    (Slist.Node (1, Nil))
    (Slist.tail (Node (2, Node (1, Nil))))
    ~ctxt ~printer:to_string_with_int

let tail_suite =
  "slist tail tests"
  >::: [ "one element list" >:: tail_1; "two elements list" >:: tail_2 ]

let suite = "slist tests" >::: [ length_suite; tail_suite ]
