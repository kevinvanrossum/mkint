#!/bin/sh

[ -d "$1" ] || {
    echo "usage: $(basename $0) dir file0 [file1 ...]" >&2
    exit 1
}

build_dir="$1"
checks='*,-google*,-fuchsia*,-llvm-namespace-comment,-llvm-header-guard,-cert-dcl21-cpp'

shift
clang-tidy -checks=${checks} -header-filter=.'*' -p "$build_dir" "$@"
