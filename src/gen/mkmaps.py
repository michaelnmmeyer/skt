#!/usr/bin/env python3

"""
Creates a table of function pointers for all available transliteration mappings.
"""

import os, re, sys

INDENT = "   "

files = []
schemes = set()
mappings = {}

for file in os.listdir():
   match = re.match(r"skt_translit_(.+?)_(.+?)\.ic", file)
   if not match:
      continue
   files.append(match.group(0))
   input_scheme = match.group(1).upper()
   output_scheme = match.group(2).upper()
   schemes.add(input_scheme)
   schemes.add(output_scheme)
   descr = open(os.path.splitext(match.group(0))[0] + ".descr").read()
   ent = mappings.setdefault(input_scheme, {})
   ent[output_scheme] = descr

for file in files:
   print('#include "%s"' % file)
print()
print("static const skt_translit skt_maps[NUM_SCHEMES][NUM_SCHEMES] = {")
for input_scheme in sorted(schemes):
   output_schemes = mappings.get(input_scheme, {})
   print(INDENT + "[%s] = {" % input_scheme)
   for output_scheme in sorted(schemes):
      descr = output_schemes.get(output_scheme)
      if descr:
         func = "skt_translit_%s_%s" % (input_scheme.lower(), output_scheme.lower())
      elif input_scheme == output_scheme:
         func = "skt_translit_identity"
         descr = ['""']
      else:
         continue
      print(2 * INDENT + "[%s] = %s," % (output_scheme, func))
   print(INDENT + "},")
print("};")

print()
print("static const char *const skt_maps_description[NUM_SCHEMES][NUM_SCHEMES] = {")
for input_scheme in sorted(schemes):
   output_schemes = mappings.get(input_scheme, {})
   print(INDENT + "[%s] = {" % input_scheme)
   for output_scheme in sorted(schemes):
      descr = output_schemes.get(output_scheme)
      if descr:
         descr = descr.splitlines()
      elif input_scheme == output_scheme:
         descr = ['""']
      else:
         continue
      print(2 * INDENT + "[%s] =" % output_scheme)
      for line in descr:
         print(3 * INDENT + line)
      print(3 * INDENT + ",")
   print(INDENT + "},")
print("};")
