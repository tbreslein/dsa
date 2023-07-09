open Ocaml_dsa
open OUnit2

let test1 ctxt = OUnit2.assert_equal ~ctxt 0 (Slist.length Nil)
let test2 ctxt = OUnit2.assert_equal ~ctxt 1 (Slist.length (Node (2, Nil)))

let test3 ctxt =
  OUnit2.assert_equal ~ctxt Slist.Nil (Slist.tail (Node (2, Nil)))

let suite =
  "suite" >::: [ "test1" >:: test1; "test2" >:: test2; "test3" >:: test3 ]

let () = run_test_tt_main suite
