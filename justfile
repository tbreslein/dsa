c:
    cd c && cmake -S. -Bbuild && make -C build && ./build/main
go:
    cd go && go test ./...
