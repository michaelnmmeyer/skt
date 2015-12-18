local skt = require("skt")

assert(type(skt.schemes) == "table" and skt.schemes[1] == "iast")
assert(skt.translit("afga", "velthuis", "iast") == "aṅga")
assert(skt.sort_key("k") < skt.sort_key("c"))
