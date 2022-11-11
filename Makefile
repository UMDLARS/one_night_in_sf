INF=$(wildcard *.inf)
Z8=$(patsubst %.inf,%.z8,$(INF))
Z5=$(patsubst %.inf,%.z5,$(INF))
Z3=$(patsubst %.inf,%.z3,$(INF))

TEST=$(wildcard *.test)
OUT=$(patsubst %.test,%.out,$(TEST))

# We use wildcards to catch whatever the current version is.
INFORM:=inform6unix/inform-6.*
LIB=inform6unix/punyinform/lib/*.h
PYTHON:=$(shell which python3)
ifdef PYTHON
# We're all right here
else
PYTHON:=$(shell which python)
endif
TIME:=$(shell which time) # Should be null if it's a shell builtin, which is fine

# This rule will make any *possible* test output files, which may build zfiles.
# It wil re-build any extant zfiles that have newer dependencies, whether or
# not there are new test files.
all: ${OUT} $(wildcard *.z?) parchment/dist/web/main.js VT323/fonts/ttf/VT323-Regular.ttf

inform6unix/src/*.c:
${LIB}:
inform6unix/Makefile:
	git clone --recursive https://gitlab.com/DavidGriffith/inform6unix.git

dep: inform6unix/Makefile node_modules/.bin/zvm plotex/regtest.py
	git -C inform6unix pull
	git -C inform6unix submodule update --init --recursive
	git -C plotex pull
	git -C parchment pull || true

build: dep ${INFORM}

inform6unix/inform%: inform6unix/Makefile inform6unix/src/*.c
	rm -f ${INFORM}
	cd inform6unix; $(MAKE) -j

# npm isn't great, but this is the only z-machine I've found that both:
# 1. Installs cleanly on both Debian/Ubuntu and termux under android
# 2. Works with the regtest.py tool 
node_modules/.bin/zvm:
	npm install ifvms --no-package-lock

plotex/regtest.py: 
	git clone https://github.com/erkyrath/plotex

# We use z5 for tests because that is what zvm implements.
%.out: %.test %.z5 plotex/regtest.py node_modules/.bin/zvm 
	$(TIME) $(PYTHON) plotex/regtest.py -t 5 -i node_modules/.bin/zvm $< > $@ || $(TIME) $(PYTHON) plotex/regtest.py -v -t 5 -i node_modules/.bin/zvm $< | tee $@

%.z3: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/ -v3 $<

%.z5: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/ -v5 $<

%.z8: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/ -v8 $<

clean:
	rm -f *.z? *.out

parchment/build.js:
	git clone --recursive https://github.com/curiousdannii/parchment

parchment/dist/web/main.js: parchment/build.js
	cd parchment && npm install --no-package-lock

VT323/fonts/ttf/VT323-Regular.ttf:
	git clone --recursive https://github.com/phoikoi/VT323.git

.PRECIOUS: %.z3 %.z5 %.z8 ${INFORM}
