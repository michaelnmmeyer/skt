#!/usr/bin/env bash

VG="valgrind --leak-check=no"

set -o errexit
set -o pipefail

# Two test files:
# * monier.txt: basic tests.
# * capitals.txt: used to make sure we handle capitals correctly.

for file in monier.txt capitals.txt; do
   sort -R $file > $file.scrambled.tmp
   $VG ../skt_sort $file.scrambled.tmp > $file.reordered.tmp
   cmp $file $file.reordered.tmp
done

rm *.tmp

exit 0
