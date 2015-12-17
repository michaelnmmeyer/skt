#!/usr/bin/env bash

VG="valgrind --leak-check=no"

set -o errexit
set -o pipefail

cat translit.txt | \
   while read input_scheme output_scheme input output; do
      test -z $input_scheme && continue;
      echo $input_scheme | grep -q "#" && continue;
      ret=$($VG ../skt_translit -i$input_scheme -o$output_scheme "$input")
      test "$ret" = "$output" || (echo "Fail" && exit 1);
   done

exit 0
