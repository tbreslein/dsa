all: c go ocaml

c:
    cd c && cmake -S. -Bbuild && make -C build && ./build/main
go:
    cd go && go test ./...
ocaml:
    cd ocaml_dsa && OUNIT_CI=true dune runtest
