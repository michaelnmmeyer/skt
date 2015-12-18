PREFIX = /usr/local
LUA_VERSION = 5.2

CFLAGS = -std=c11 -fPIC -shared -g -Wall -Werror
CFLAGS += -O2 -DNDEBUG -march=native -mtune=native -fomit-frame-pointer

LIB = skt.so

all: $(LIB)

clean:
	rm -f $(LIB)

check: $(LIB)
	lua$(LUA_VERSION) test.lua

install: $(LIB)
	install -pm 0755 $(LIB) $(PREFIX)/lib/lua/$(LUA_VERSION)/$(LIB)

uninstall:
	rm -f $(PREFIX)/lib/lua/$(LUA_VERSION)/$(LIB)

.PHONY: all clean check install uninstall

skt.so: lua_skt.c ../skt.c
	$(CC) $(CFLAGS) $^ -o $@
