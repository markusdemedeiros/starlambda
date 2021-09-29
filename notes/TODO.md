## TODO

### Bugs, Fixes, Little Tasks
- [ ] Fix makefile for edits to test suites
- [ ] Clean up parser methods, extract better helper methods/remove unused
- [ ] More robust stack in parser method (current has 100 term limit)
- [ ] Refactor tests from `p.test.cpp` to new file `e.test.cpp`
- [ ] Refactor `parse_lc_line` to take a single global state handler
- [ ] Refactor `parse_lc_line` to return 0 on rejection, 1 on success.
- [ ] Unify error handling in parser. Eg: -1 is always error ..., helper to check errror, advance to token...
- [ ] Rename `*token` to `*name` where appropriate. Token == non-space character (superset of alphanumeric chars)


### Project Development, short term
- [✓] Lambda calculus interpreteer
- [✓] Parser for basic language


### Haskell short term project development
- [ ] Review C code, make sure the interface is complete and complies with HS FFI
- [ ] Haskell FFI interop
- [ ] Make AST
- [ ] Parsec parsers for simply untyped LC
- [ ] Parser for literate LC (basic combinators, numbers, etc)
- [ ] Type chekcing (in C)
- [ ] Parsec parser for systemF

### C short term project directions
- [ ] Implementation of optimal graph reduction algorithm !!!
- [ ] Hardcode Church Encodings
- [ ] Expand test suite for parser edge cases, larger expressions
- [ ] Formalize `f.c` tests (no printf, encode graph structure)
- [ ] Serialization of lambda terms (generalize print to buffer)
- [ ] Compilation of `.lcs` to `.lc`
- [ ] `.lcs` interpreter (as a higher level language)
- [ ] Type checker for System F, "compile" to `.lc`
- [ ] Sugar for System F (uses basic lambda calculus)


### Devops
- [✓] Update makefile to organize code
- [ ] Doccumentation
- [ ] Code formatting plugin
- [ ] Find a C style guide to follow
- [ ] Vim script lambda calculus languages highlighting
- [ ] Learn how to setup and use the debugger
- [ ] Write README
- [ ] Put on Git


### Project Development, long term
- [ ] `.lcs` 
- [ ] `.sk` 
- [ ] Higer level languages with more interesting type systems
- [ ] More efficient interpreter algorithms