#!/usr/bin/env python3

"""
Creates a machine for sorting IAST-encoded strings.
"""

import sys, unicodedata
import functools
from mkwtranslit import all_case_combinations

def load_phonems(fp):
   phonems = []
   for line in fp:
      line = line.strip()
      assert unicodedata.normalize("NFC", line) == line
      assert unicodedata.normalize("NFKC", line) == line
      if line and not line.startswith("#"):
         phonems.append(line)
   assert len(phonems) == len(set(phonems))
   return phonems

def mkactions(phonems):
   actions = []
   actions_index = {}
   for i, base_phonem in enumerate(phonems, 1):
      for j, phonem in enumerate(sorted(all_case_combinations(base_phonem)), 1):
         assert not phonem in actions_index
         actions_index[phonem] = "A%d" % len(actions)
         action = []
         _ = action.append
         _('action A%d {' % len(actions))
         _('   skt_buf_grow(buf, 2);')
         _('   buf->data[buf->size++] = %d;' % i)
         _('   buf->data[buf->size++] = %d;' % j)
         _('}')
         actions.append("\n".join(action))
   return "\n".join(actions), actions_index

def mkrules(phonems):
   assert len(phonems) < 0xff
   rules = []
   _ = rules.append
   actions, actions_index = mkactions(phonems)
   for phonem in phonems:
      for phonem in sorted(all_case_combinations(phonem)):
         _('"%s" => %s;' % (phonem, actions_index[phonem]))
   return actions, '\n'.join('   ' + rule for rule in rules)

def mkmachine(phonems):
   actions, rules = mkrules(phonems)
   data = open("skt_sort.tpl").read().rstrip() 
   data = data.replace("$ACTIONS", actions)
   data = data.replace("$RULES", rules)
   return data

if __name__ == "__main__":
   phonems = load_phonems(sys.stdin)
   print(mkmachine(phonems))
