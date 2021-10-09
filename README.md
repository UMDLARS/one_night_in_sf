# PunyInform Minimal Build Harness

This repo contains three files:

1. A `Makefile` that needs only:
   * [git](https://git-scm.com/docs/gitcli)
   * [python 3](https://python.org)
   * a [C](http://gcc.gnu.org) [compiler](https://clang.llvm.org/)
   * [GNU make](https://www.gnu.org/software/make/)
   * and [npm](https://npmjs.com)
   to build all the tools you need.
2. `minimal.inf` from the PunyInform distribution
3. A `minimal.test` file that will test the correctness of the resulting `minimal.z5` game

## How do I use this?

Just type:

```
make
```

If you have all the dependencies satisfied, you should eventually have a `minimal.out` file that just lists the successful test suites.

## So what do I do next?

First of all, you could install [frotz](https://gitlab.com/DavidGriffith/frotz) or some other Z-machine interpreter, and play the `minimal.z5` game with it.

But you probably want to write your own game.  I recommend making a `mynewgame.test` file (named after your cool game idea) and entering a transcript of how you'd imagine your game could be played successfully (at least as far as you've planned it).  Then make a `mynewgame.inf` (also named to match the test file) and keep coding until the tests all pass!

### A whole transcript?

Well no need for that exactly.  Just enter the commands and use the `!` and `/` features listed in the comments of `minimal.test` to set conditions based on substring matches and negative matches.

## There's a new version of inform6 or PunyInform out!

You can refresh the sources by running `make dep`.  The compiler should re-build (if needed) the next time you run `make`, before compiling your game.

## This builds a z5 game, but I want z3!

We build z5 because that is what the `zvm` interpreter implements, and we use that for our test suite.  You may find yourself wanting to craft a custom compile command to optimise for abbreviations and other command-line switches, but if you want to quickly churn out a `.z3` version to save around a kilobyte or more, just run:

```
make mynewgame.z3
```

Note that z3 format has limitations on (among other things) the number of objects and synonyms for a given object.  You may notice compiler warnings that some `name` words are being dropped, etc.

## It broke!

* Are you running this from a POSIX shell such as busybox sh, dash, bash, or zsh?  This won't work on DOS/PowerShell systems to our knowledge.
* Is your game compatible with the latest version of PunyInform?

