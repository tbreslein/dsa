open Ocaml_dsa
open OUnit2

let to_string_with_int xs =
  let rec foo acc i =
    match Arraybuffer.get xs i with
    | None -> acc
    | Some x -> foo (acc ^ Int.to_string x) (i+1)
  in
  foo "[ " 0 ^ "]"

let empty_buffer _ctxt = Arraybuffer.create 0
let one_element_buffer _ctxt =
    let xs = Arraybuffer.create 0 in
    Arraybuffer.push xs 1;
    xs

let two_element_buffer _ctxt =
    let xs = Arraybuffer.create 0 in
    Arraybuffer.push xs 1;
    Arraybuffer.push xs 2;
    xs

let three_element_buffer _ctxt =
    let xs = Arraybuffer.create 0 in
    Arraybuffer.push xs 1;
    Arraybuffer.push xs 2;
    Arraybuffer.push xs 3;
    xs

let teardown _stack _ctxt = ()

let length_suite =
  "test_length"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_buffer teardown ctxt in
           assert_equal 0 (Arraybuffer.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_buffer teardown ctxt in
           assert_equal 1 (Arraybuffer.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_buffer teardown ctxt in
           assert_equal 2 (Arraybuffer.length xs) ~printer:Int.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_buffer teardown ctxt in
           assert_equal 3 (Arraybuffer.length xs) ~printer:Int.to_string );
       ]

let empty_suite =
  "test_empty"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_buffer teardown ctxt in
           assert_equal true (Arraybuffer.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_buffer teardown ctxt in
           assert_equal false (Arraybuffer.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_buffer teardown ctxt in
           assert_equal false (Arraybuffer.empty xs) ~printer:Bool.to_string );
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_buffer teardown ctxt in
           assert_equal false (Arraybuffer.empty xs) ~printer:Bool.to_string );
       ]

let pop_suite =
  "test_pop"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_buffer teardown ctxt in
           assert_equal None (Arraybuffer.pop xs));
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_buffer teardown ctxt in
           assert_equal (Some 1) (Arraybuffer.pop xs));
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_buffer teardown ctxt in
           assert_equal (Some 2) (Arraybuffer.pop xs));
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_buffer teardown ctxt in
           assert_equal (Some 3) (Arraybuffer.pop xs));
       ]

let set_get_suite =
  "test_set_get"
  >::: [
         ( "empty" >:: fun ctxt ->
           let xs = bracket empty_buffer teardown ctxt in
           assert_raises Arraybuffer.OutOfBounds (fun () -> Arraybuffer.set xs 0 1));
         ( "one element" >:: fun ctxt ->
           let xs = bracket one_element_buffer teardown ctxt in
           assert_equal (Some 10) (Arraybuffer.set xs 0 10; Arraybuffer.get xs 0));
         ( "one element" >:: fun ctxt ->
           let xs = bracket two_element_buffer teardown ctxt in
           assert_equal (Some 20) (Arraybuffer.set xs 1 20; Arraybuffer.get xs 1));
         ( "one element" >:: fun ctxt ->
           let xs = bracket three_element_buffer teardown ctxt in
           assert_equal (Some 100) (Arraybuffer.set xs 2 100; Arraybuffer.get xs 2));
       ]

let suite =
  "arraybuffer tests"
  >::: [ length_suite; empty_suite; pop_suite; set_get_suite ]
