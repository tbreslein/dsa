open OUnit2

let suite =
  "ocaml data structures tests"
  >::: [ Test_slist.suite; Test_arraybuffer.suite ]

let () = run_test_tt_main suite
