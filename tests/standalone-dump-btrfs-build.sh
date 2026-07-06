#!/bin/sh
# Smoke-test the standalone dump.btrfs package.
set -eu

top=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
pkg="$top/dump.btrfs"

make -C "$pkg" clean
make -C "$pkg" dump.btrfs
test -x "$pkg/dump.btrfs"
"$pkg/dump.btrfs" --help >/dev/null
