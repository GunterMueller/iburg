[![Build Status](https://travis-ci.org/ibara/iburg.svg?branch=master)](https://travis-ci.org/ibara/iburg)
iburg
=====
`iburg` is a code generator generator. It uses dynamic programming at
compile time. It is described in
```
C. W. Fraser, D. R. Hanson and T. A. Proebsting,
Engineering a simple, efficient code generator generator,
ACM Letters on Prog. Languages and Systems 1, 3 (Sep. 1992), 213-226.
```
http://storage.webhop.net/documents/iburg.pdf

`iburg` is written in C. It requires a C compiler and a Yacc program to
build. If you need a Yacc program, a dependency-free, cross-platform Yacc
can be found here: https://github.com/ibara/yacc

Compiling
---------
Once you have a C compiler and a Yacc program, you can compile `iburg`
by typing `make`. There should be no warnings or errors with most
modern compilers.

Testing
-------
`make test` runs `iburg` on `sample[45].brg` and executes the resulting
programs. The output should be something like:
```
$ make test
./iburg -I sample4.brg sample4.c; cc -o test4 sample4.c; ./test4
sample4.c
i = c + 4;
stmt: ASGNI(disp,reg)
 disp: ADDRLP
 reg: disp
  disp: ADDI(reg,con)
   reg: CVCI(INDIRC(disp))
    disp: ADDRLP
   con: CNSTI
./iburg -I sample5.brg sample5.c; cc -o test5 sample5.c; ./test5
sample5.c
stm: MOVE(MEM(loc),reg)
 loc: NAME
 reg: PLUS(MEM(loc),reg)
  loc: PLUS(NAME,reg)
   reg: MEM(loc)
    loc: NAME
  reg: con
   con: CONST

$
```

Installing
----------
To install `iburg`, run `make install` with root privileges.

Licensing
---------
`iburg` is distributed under the terms of the MIT license.
Please see `LICENSE` for details.

Get a tarball
-------------
https://devio.us/~bcallah/iburg/iburg-20170103.tar.gz
