#!/usr/bin/env python3

"""
Creates additional machines for conversion to iastc, which we define
to be identical to iast save for the representation of ṛ, etc., with become
r̥, etc.

We merge mappings iast-X and iastc-X for all possible X since there is no
ambiguity.
"""

import os, sys, unicodedata
import mkwtranslit, mkitranslit

COMBINING_DOT_BELOW = chr(0x323)
COMBINING_RING_BELOW = chr(0x0325)

TO_REPLACE = ["ṛ", "ṝ", "ḷ", "ḹ"]
TO_REPLACE += [p.upper() for p in TO_REPLACE]

def replace_diacritic(phonem):
   code_points = unicodedata.normalize("NFD", phonem)
   code_points = code_points.replace(COMBINING_DOT_BELOW, COMBINING_RING_BELOW)
   return unicodedata.normalize("NFC", code_points)

SUBSTITUTIONS = {phonem: replace_diacritic(phonem) for phonem in TO_REPLACE}

def wsubstitute(old_table):
   table = {}
   for key, value in old_table.items():
      key = SUBSTITUTIONS.get(key, key)
      value = SUBSTITUTIONS.get(value, value)
      assert not key in table
      table[key] = value
   return table

def isubstitute(old_table):
   table = {}
   for category, sub_table in old_table.items():
      table[category] = {}
      for key, values in sub_table.items():
         key = SUBSTITUTIONS.get(key, key)
         values = tuple(SUBSTITUTIONS.get(value, value) for value in values)
         assert not key in table[category]
         table[category][key] = values
   return table

def mkmachines(module, substitute, schemes_dir):
   for file in os.listdir(schemes_dir):
      if not os.path.splitext(file)[0].endswith("iast"):
         continue
      path = "%s/%s" % (schemes_dir, file)
      print(path, file=sys.stderr)
      table = module.load_table(open(path))
      table = substitute(table)
      module.mkmachine(table, file.replace("iast", "iastc"))

mkmachines(mkwtranslit, wsubstitute, "data/wtranslit")
mkmachines(mkitranslit, isubstitute, "data/itranslit")

# iast <-> iastc
mkwtranslit.mkmachine(SUBSTITUTIONS, "iast-iastc")
mkwtranslit.mkmachine({v: k for k, v in SUBSTITUTIONS.items()}, "iastc-iast")
