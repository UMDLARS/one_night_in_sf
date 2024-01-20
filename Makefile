INF=$(wildcard *.inf)
Z8=$(INF:.inf=.z8)
Z5=$(INF:.inf=.z5)
Z3=$(INF:.inf=.z3)

TEST=$(wildcard *.test)
OUT=$(TEST:.test=.out)
C64=$(addprefix c64_,$(TEST:.test=.d64))


# We use wildcards to catch whatever the current version is.
INFORM:=inform6unix/inform-6.*
LIB=inform6unix/punyinform/lib/*.h *.h
PYTHON:=$(shell which python3)
ifdef PYTHON
# We're all right here
WEBSERVER:=$(PYTHON) -m http.server
else
PYTHON:=$(shell which python)
WEBSERVER:=$(PYTHON) -m SimpleHTTPServer 8000
endif
TIME:=$(shell which time) # Should be null if it's a shell builtin, which is fine

# This rule will make any *possible* test output files, which may build zfiles.
# It wil re-build any extant zfiles that have newer dependencies, whether or
# not there are new test files.
all: ${OUT} $(wildcard *.d64) $(wildcard *.z?) VT323/fonts/ttf/VT323-Regular.ttf

c64: ${C64}


inform6unix/src/*.c:
${LIB}:
inform6unix/Makefile:
	git clone --recursive https://gitlab.com/DavidGriffith/inform6unix.git

dep: inform6unix/Makefile node_modules/.bin/zvm plotex/regtest.py parchment-src/build.js
	git -C inform6unix pull
	git -C inform6unix submodule update --init --recursive
	git -C plotex pull
	git -C parchment-src pull || true

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
	$(TIME) $(PYTHON) plotex/regtest.py -v -t 5 -i node_modules/.bin/zvm $< > $@ || ! grep -Hn '^\*\*\*' $@

%.z3: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/,./ -v3 $<

%.z5: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/,./ -v5 $<

%.z8: %.inf ${LIB} ${INFORM}
	${INFORM} -e -E1 -d2 -s +include_path=./inform6unix/punyinform/lib/,./ -v8 $<

clean:
	rm -f *.z? *.out 
	rm -rf build

parchment-src/build.js:
	git clone --recursive https://github.com/curiousdannii/parchment parchment-src

parchment: parchment-src/build.js
	cd parchment-src && npm install --no-package-lock
	mkdir -p parchment/dist
	cp -alf parchment-src/dist/web parchment/dist/


VT323/fonts/ttf/VT323-Regular.ttf:
	git clone --recursive https://github.com/phoikoi/VT323.git

# Make a distribution tree

dist: $(addprefix build/parchment/dist/web/,jquery.min.js main.js zvm.js web.css) $(addprefix build/,retro.css vt220.webp index.html untitledHeistGame.z5 favicon.ico) build/VT323/fonts/ttf/VT323-Regular.ttf 
	tar czvf untitledHeistGame-$(shell date +%y%m%d).tar.gz build/

build/%: %
	@mkdir -p $(dir $@)
	cp -alf $< $@

web: dist 
	@echo "You can play your game at http://localhost:8000/ now."
	cd build; $(WEBSERVER) || true

# This will build a C64 disk image with the oldest z-machine version you have.
# So if you have a foo.z3 and a foo.z8 file, the c64_foo.d64 image will use the z3.
c64_%.d64: %.z? ozmoo/exomizer/src/exomizer /usr/bin/ruby /usr/bin/acme
	/usr/bin/ruby ozmoo/make.rb $<

ozmoo/make.rb:
	git clone --recursive https://github.com/johanberntsson/ozmoo.git

ozmoo/exomizer/src/Makefile: ozmoo/make.rb
	git clone https://bitbucket.org/magli143/exomizer.git ozmoo/exomizer

ozmoo/exomizer/src/exomizer: ozmoo/exomizer/src/Makefile
	make -C ozmoo/exomizer/src

/bin/%:
/usr/bin/%:
	/usr/lib/command-not-found $*

.PRECIOUS: %.z3 %.z5 %.z8 ${INFORM}
.PHONY: parchment
