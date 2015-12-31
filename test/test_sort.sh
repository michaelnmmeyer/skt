#!/usr/bin/env bash

VG="valgrind --leak-check=no"

set -o errexit
set -o pipefail

# Test files:
# * monier.txt: basic tests.
# * capitals.txt: used to make sure we handle capitals correctly.
# * ignorable.txt: characters to be ignored in collations.

for file in monier.txt capitals.txt ignorable.txt; do
   sort -R $file > $file.scrambled.tmp
   $VG ../skt_sort $file.scrambled.tmp > $file.reordered.tmp
   cmp $file $file.reordered.tmp
done

rm *.tmp

exit 0
