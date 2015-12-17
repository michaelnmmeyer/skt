#!/usr/bin/env bash

set -o errexit

./mksort.py < data/sort/iast.txt > skt_sort.rl

for file in data/wtranslit/*; do
   echo $file > /dev/stderr
   ./mkwtranslit.py $file
done

for file in data/itranslit/*; do
   echo $file > /dev/stderr
   ./mkitranslit.py $file
done

./mkiastc.py

for file in *.rl; do
   ragel -e $file -o $(trimext $file).ic
done

./mkmaps.py > skt_maps.ic
