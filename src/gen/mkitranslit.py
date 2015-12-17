#!/usr/bin/env python3

"""
Creates transliteration tables for nāgarī.
"""

import os, sys, unicodedata
import mkwtranslit

CATEGORIES = {"VOWEL_A", "VOWEL", "CONSONANT", "VIRAMA", "REST"}

def load_table(fp):
   import mkiastc
   table = {}
   data = fp.read()
   assert unicodedata.normalize("NFC", data) == data
   assert unicodedata.normalize("NFKC", data) == data
   for line in data.splitlines():
      # Strip trailing ' but not for the avagraha.
      fields = [(f.strip("'") if len(f) > 1 else f) for f in line.strip().split()]
      category, key, values = fields[0], fields[1], tuple(fields[2:])
      assert category in CATEGORIES
      assert not key in table
      sub_table = table.setdefault(category, {})
      sub_table[key] = values
      #  ṛ -> r̥, etc., only for keys.
      key = mkiastc.SUBSTITUTIONS.get(key)
      if key:
         assert not key in sub_table
         sub_table[key] = values
   assert len(table["VOWEL_A"]) == 1
   return table

def add_action_fgoto(value, goto_dest, do_fhold, actions, index):
   if value in index:
      return
   index[value] = "A%d" % len(actions)
   bytes = value.encode("UTF-8")
   action = []
   _ = action.append
   _("# %s" % value)
   _("action A%d {" % len(actions))
   if do_fhold:
      _("   fhold;")
   _("   skt_buf_grow(buf, %d);" % len(bytes))
   for byte in bytes:
      _("   buf->data[buf->size++] = %d;" % byte)
   _("   fgoto %s;" % goto_dest)
   _("}")
   actions.append("\n".join(action))

vowel_a_action = """\
# trailing 'a'
action A%d {
   fgoto main;
}"""
def mkactions(table):
   actions = []
   actions_index = {}
   # Main table.
   for category in ("VOWEL_A", "VOWEL", "REST"):
      for values in sorted(table[category].values()):
         mkwtranslit.add_action(values[0], actions, actions_index)
   for values in sorted(table["CONSONANT"].values()):
      add_action_fgoto(values[0], "from_consonant", False, actions, actions_index)
   # From consonant.
   for values in sorted(table["VOWEL"].values()):
      add_action_fgoto(values[1], "main", False, actions, actions_index)
   for values in sorted(table["VIRAMA"].values()):
      add_action_fgoto(values[0], "main", True, actions, actions_index)
   actions_index["VOWEL_A_ACTION"] = "A%d" % len(actions)
   actions.append(vowel_a_action % len(actions))
   return '\n'.join(actions), actions_index

from_consonant_tpl = """\
from_consonant := |*
$RULES
*|;
"""
# Consonants scanner.
def mkconsonants(table, actions_index):
   rules = []
   _ = rules.append
   # Consonant + vowel
   for key, values in table["VOWEL"].items():
      value = values[1]
      _('"%s" => %s; # %s' % (key, actions_index[value], value))
   # Consonant + A (last defined action).
   for key in sorted(table["VOWEL_A"]):
      _('"%s" => %s; # trailing \'a\'' % (key, actions_index["VOWEL_A_ACTION"]))
   # Consonant + anything but a vowel
   virama = list(table["VIRAMA"].values())[0][0]
   _('any => %s; # %s' % (actions_index[virama], virama))
   rules = '\n'.join("   " + rule for rule in rules)
   return from_consonant_tpl.replace("$RULES", rules)

# Main scanner.
def mkrules(table, actions_index):
   rules = []
   _ = rules.append
   # Direct mappings
   for category in ("VOWEL_A", "VOWEL", "REST", "CONSONANT"):
      for key, values in sorted(table[category].items()):
         value = values[0]
         _('"%s" => %s; # %s' % (key, actions_index[value], value))
   return '\n'.join("   " + rule for rule in rules)

# Handle the final virāma (at EOF).
# This is brittle at best, but there is no better way to do that in Ragel.
def mkeofcheck(table, input_scheme, output_scheme):
   virama = list(table["VIRAMA"].values())[0][0].encode()
   code = []
   _ = code.append
   _("if (cs == skt_translit_%s_%s_en_from_consonant) {" % (input_scheme, output_scheme))
   _("   skt_buf_grow(buf, %d);" % len(virama))
   for byte in virama:
      _("   buf->data[buf->size++] = %d;" % byte)
   _("}")
   return '\n'.join("   " + line for line in code)

def mkmachine(table, mapping):
   input_scheme, output_scheme = os.path.splitext(os.path.basename(mapping))[0].split("-")
   
   if input_scheme in {"iast", "iastc"}:
      for category, sub_table in table.copy().items():
         if category == "VIRAMA":
            continue
         table[category] = mkwtranslit.make_case_insensitive(sub_table)
   for category, sub_table in table.copy().items():
      table[category] = mkwtranslit.remove_useless_mappings(sub_table)

   actions, actions_index = mkactions(table)
   consonants_rules = mkconsonants(table, actions_index)
   rules = mkrules(table, actions_index)
   eof_check = mkeofcheck(table, input_scheme, output_scheme)

   data = open("skt_translit.tpl").read().rstrip()
   data = data.replace("$INPUT_SCHEME", input_scheme)
   data = data.replace("$OUTPUT_SCHEME", output_scheme)
   data = data.replace("$ACTIONS", actions)
   data = data.replace("$FROM_CONSONANT", consonants_rules)
   data = data.replace("$RULES", rules)
   data = data.replace("$EOF_CHECK", eof_check)
   
   output_file = "skt_translit_%s_%s.rl" % (input_scheme, output_scheme)
   with open(output_file, "w") as fp:
      fp.write(data)
   output_file = "skt_translit_%s_%s.descr" % (input_scheme, output_scheme)
   with open(output_file, "w") as fp:
      for category, sub_table in sorted(table.items()):
         for key, values in sorted(sub_table.items()):
            values = "\t".join(values)
            entry = mkwtranslit.escape("%s\t%s\t%s\n" % (category, key, values))
            print('"%s"' % entry, file=fp)

if __name__ == "__main__":
   mapping_path = sys.argv[1]
   table = load_table(open(mapping_path))
   mkmachine(table, mapping_path)
