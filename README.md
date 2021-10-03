# PunyInform Minimal Build Harness

This repo contains three files:

1. A `Makefile` that needs only python 3, a C compiler, GNU make and npm to build all the tools you need.
2. `minimal.inf` from the PunyInform distribution
3. A `minimal.test` file that will test the correctness of the resulting `minimal.z5` game

## How do I use this?

Just type `make`.

If you have all the dependencies satisfied, you should see a `minimal.out` file that just lists the successful test suites.

## It broke!

* Do you have a `time` binary outside of your shell?  
* Is `python3` perhaps just named `python` on your system?

## So what do I do next?

First of all, you could install `frotz` or some other Z-machine Interpreter, and play the `minimal.z5` game with it.

But you probably want to write your own game.  I recommend making a `mynewgame.test` file (named after your cool game idea) and entering a transcript of how you'd imagine your game could be played successfully.  Then make a `mynewgame.inf` (also named to match the test file) and keep coding until the tests all pass!

## A whole transcript?

Well no need for that exactly.  Just enter the commands and use the `!` and `/` features listed in the comments of `minimal.test` to set conditions based on substring matches and negative matches.
