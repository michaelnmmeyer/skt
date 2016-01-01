PREFIX = /usr/local

CFLAGS = -std=c11 -Wall -Werror -g
CFLAGS += -O2 -s -DNDEBUG -march=native -mtune=native -fomit-frame-pointer
CFLAGS += -flto -fdata-sections -ffunction-sections -Wl,--gc-sections

AMALG = skt.h skt.c
BINARIES = skt_sort skt_translit

SOURCES = $(wildcard src/*.h) $(wildcard src/*.c) $(wildcard src/gen/*.ic)

#--------------------------------------
# Abstract targets
#--------------------------------------

all: $(AMALG) $(BINARIES)

check: $(BINARIES)
	cd test && ./test_translit.sh
	cd test && ./test_sort.sh

clean:
	rm -f $(BINARIES)

install: $(BINARIES)
	for file in $(BINARIES); do                                                 \
	   install -spm 0755 $$file $(PREFIX)/bin/$$file;                           \
	done

uninstall:
	for file in $(BINARIES); do                                                 \
	   rm -f $(PREFIX)/bin/$$file;                                              \
	done

.PHONY: all check clean install uninstall


#--------------------------------------
# Concrete targets
#--------------------------------------

skt.c: $(SOURCES)
	scripts/mkamalg.py src/*.c > $@

skt.h: src/skt.h
	cp $< $@

cmd/%.ih: cmd/%.hlp
	scripts/mkcstring.py < $< > $@

%: cmd/%.c cmd/cmd.c cmd/util.c skt.c
	$(CC) $(CFLAGS) $^ -o $@
