# skt



Sanskrit transliteration and collation.





## Purpose



This is a set of finite-state machines for sorting and transliterating Sanskrit

texts.





## Building



A modern C compiler is required, which means either GCC or CLang. Then:



    $ make && sudo make install



The above installs two binaries: `skt_sort` and `skt_translit`. Internal

routines used by these tools are defined in the two source files in this

directory. A Lua binding is available in the `lua` directory.





## Usage



Two things to be borne in mind:

* Strings provided as input must be UTF-8 encoded, otherwise the routines won't

  work correctly. Likewise, they must be normalized to either of NFC and NFKC.

  Transliteration mappings always generate NFC strings.

* Transliteration is not necessarily a reversible process. For this reason,

  replacing a string with its transliteration and permanently discarding the

  original string is not a good idea.



Transliteration example:



    $ skt_translit -i velthuis -o iast a.mza

    aṃśa



Sorting example:



    $ sort -R test/monier.txt | head -5 | skt_sort

    āyurdāvan

    jaraṇyu

    tūṣa

    lalitāgadyanirūpaṇa

    vināyakasahasranāman

