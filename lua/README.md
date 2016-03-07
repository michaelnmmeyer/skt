# skt-lua



Lua binding of skt.



## Building



Check the value of the variable `LUA_VERSION` in the makefile in this directory.

Then invoke the usual:



    $ make && sudo make install



You can also pass in the correct version number on the command-line:



    $ make LUA_VERSION=5.3 && sudo make install LUA_VERSION=5.3



## Usage



`skt.schemes`  

A table containing the names of the supported transliteration schemes.



`skt.translit(str[, input_scheme[, output_scheme]])`  

Transliterates a string.



`skt.sort_key(str)`  

Creates a sort key for a IAST-encoded string. Equivalent to `strxfrm(3)`.

