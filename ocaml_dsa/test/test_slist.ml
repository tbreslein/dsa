open Ocaml_dsa
open OUnit2

let to_string_with_int xs =
  let rec foo acc xs =
    match xs with
    | Slist.Nil -> acc
    | Node (x, rest) -> foo (acc ^ Int.to_string x ^ " ") rest
  in
  foo "[ " xs ^ "]"

let empty_slist _ctxt = Slist.Nil
let one_element_slist _ctxt = Slist.Node (1, Nil)
let two_element_slist _ctxt = Slist.Node (1, Node (2, Nil))
let three_element_slist _ctxt = Slist.Node (1, Node (2, Node (3, Nil)))
let teardown _stack _ctxt = ()

let length_suite =
  "test_length"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_equal 0 (Slist.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal 1 (Slist.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal 2 (Slist.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal 3 (Slist.length xs) ~printer:Int.to_string );
       ]

let empty_suite =
  "test_empty"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_equal true (Slist.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal false (Slist.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal false (Slist.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal false (Slist.empty xs) ~printer:Bool.to_string );
       ]

let tail_suite =
  "test_tail"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_raises Slist.Empty (fun () -> Slist.tail xs) );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal Slist.Nil (Slist.tail xs) ~printer:to_string_with_int );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (2, Nil))
             (Slist.tail xs) ~printer:to_string_with_int );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (2, Node (3, Nil)))
             (Slist.tail xs) ~printer:to_string_with_int );
       ]

let drop_suite =
  "test_drop"
  >::: [
         ( "empty list" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_raises Slist.TooLong (fun () -> Slist.drop 2 xs) );
         ( "drop zero from one element list" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (1, Nil))
             (Slist.drop 0 xs) ~printer:to_string_with_int );
         ( "one element from one element list" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal Slist.Nil (Slist.drop 1 xs) ~printer:to_string_with_int
         );
         ( "drop zero from two element list" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (1, Node (2, Nil)))
             (Slist.drop 0 xs) ~printer:to_string_with_int );
         ( "drop one from two element list" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (2, Nil))
             (Slist.drop 1 xs) ~printer:to_string_with_int );
         ( "drop 2 from two element list" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal Slist.Nil (Slist.drop 2 xs) ~printer:to_string_with_int
         );
       ]

let head_suite =
  "test_head"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_raises Slist.Empty (fun () -> Slist.tail xs) );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal 1 (Slist.head xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal 1 (Slist.head xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal 1 (Slist.head xs) ~printer:Int.to_string );
       ]

let push_suite =
  "test_push"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_equal
             (Slist.Node (10, Nil))
             (Slist.push xs 10) ~printer:to_string_with_int );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (10, Node (1, Nil)))
             (Slist.push xs 10) ~printer:to_string_with_int );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (10, Node (1, Node (2, Nil))))
             (Slist.push xs 10) ~printer:to_string_with_int );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal
             (Slist.Node (10, Node (1, Node (2, Node (3, Nil)))))
             (Slist.push xs 10) ~printer:to_string_with_int );
       ]

let pop_suite =
  "test_pop"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_slist teardown ctxt in
           assert_raises Slist.Empty (fun () -> Slist.pop xs) );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_slist teardown ctxt in
           assert_equal
             (1, Slist.Nil)
             (Slist.pop xs));
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_slist teardown ctxt in
           assert_equal
             (1, Slist.Node(2, Nil))
             (Slist.pop xs));
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_slist teardown ctxt in
           assert_equal
             (1, Slist.Node(2, Node(3, Nil)))
             (Slist.pop xs));
       ]

let suite =
  "slist tests"
  >::: [ length_suite; empty_suite; tail_suite; head_suite; drop_suite; push_suite; pop_suite ]
