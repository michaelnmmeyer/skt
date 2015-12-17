#!/usr/bin/env python3

"""
Creates transliteration tables.
"""

import sys, os, unicodedata

def load_table(fp):
   import mkiastc
   table = {}
   for line in fp:
      line = line.strip()
      if not line or line.startswith("#"):
         continue
      key, value = line.split()
      assert not key in table
      table[key] = value
      #  ṛ -> r̥, etc., only for keys.
      key = mkiastc.SUBSTITUTIONS.get(key)
      if key:
         assert not key in table
         table[key] = value
   return table

def all_case_combinations(s):
   s = s.lower()
   def iterate():
      for i in range(len(s)):
         for j in range(i, len(s) + 1):
            yield s[:i] + s[i:j].upper() + s[j:]
   return set(iterate())

def make_case_insensitive(old_table):
   table = old_table.copy()
   for key, value in old_table.items():
      keys = all_case_combinations(key)
      for key in keys:
         # Only add a mapping if not defined.
         if not key in table:
            table[key] = value
   return table

def remove_useless_mappings(old_table):
   # This must be done _after_ generating case combinations.
   table = {}
   for key, value in old_table.items():
      if key == value:
         continue
      table[key] = value
   return table

# We don't add mappings for NFD and NFKD strings because, for the output to be
# valid NFD whatever be the provided input, we'd also need to normalize every
# code point not present in the input scheme, which is to say, to perform a full
# unicode normalization. Otherwise, we could end up with mixed normalization
# forms, which is undesirable. It is better to not make any promise from the
# start if the input is incorrect. And we don't check if the input is valid
# UTF-8 anyway.
def check_normalization(table):
   for key, value in table.items():
      for x in (key, value):
         assert unicodedata.normalize("NFC", x) == x
         assert unicodedata.normalize("NFKC", x) == x

def add_action(value, actions, index):
   if value in index:
      return
   index[value] = "A%d" % len(actions)
   bytes = value.encode("UTF-8")
   action = []
   _ = action.append
   _("# %s" % value)
   _("action A%d {" % len(actions))
   _("   skt_buf_grow(buf, %d);" % len(bytes))
   for byte in bytes:
      _("   buf->data[buf->size++] = %d;" % byte)
   _("}")
   actions.append("\n".join(action))

# We merge together several actions of the state machine when possible. Maybe
# GCC does it already, but we better be safe than sorry.
def mkactions(table):
   actions = []
   index = {}
   for value in table.values():
      add_action(value, actions, index)
   return actions, index

def mkrules(table):
   check_normalization(table)
   actions, actions_index = mkactions(table)
   rules = []
   for key, value in sorted(table.items()):
      action = actions_index[value]
      rule = '   "%s" => %s; # %s' % (key, action, value)
      rules.append(rule)
   return '\n'.join(actions), '\n'.join(rules)

ESCAPE = {
	"\n": "n",
	"\t": "t",
	"\\": "\\",
	"\"": '"',
}
for key, value in ESCAPE.copy().items():
	ESCAPE[key] = "\\" + value

def escape(s):
   return "".join(ESCAPE.get(c, c) for c in s)

def mkmachine(table, mapping):
   input_scheme, output_scheme = os.path.splitext(os.path.basename(mapping))[0].split("-")

   # Special case: need to generate case-insensitive mappings
   if input_scheme in {"iast", "iastc"}:
      table = make_case_insensitive(table)
   table = remove_useless_mappings(table)
   actions, rules = mkrules(table)
   
   data = open("skt_translit.tpl").read().rstrip()
   data = data.replace("$INPUT_SCHEME", input_scheme)
   data = data.replace("$OUTPUT_SCHEME", output_scheme)
   data = data.replace("$ACTIONS", actions)
   data = data.replace("$FROM_CONSONANT", "")
   data = data.replace("$EOF_CHECK", "")
   data = data.replace("$RULES", rules)

   output_file = "skt_translit_%s_%s.rl" % (input_scheme, output_scheme)
   with open(output_file, "w") as fp:
      fp.write(data)
   output_file = "skt_translit_%s_%s.descr" % (input_scheme, output_scheme)
   with open(output_file, "w") as fp:
      for pair in sorted(table.items()):
         pair = escape("%s\t%s\n" % pair)
         print('"%s"' % pair, file=fp)

if __name__ == "__main__":
   mapping_path = sys.argv[1]
   table = load_table(open(mapping_path))
   mkmachine(table, mapping_path)
