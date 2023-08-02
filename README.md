# Avery Burke presents Lisp

the aim of this porject is to build a fast and fully functional Lisp, in C

## Features

At the time of writing the only feature is runtime type checking in the REPL. This is done with NaN boxing. There are currently only three types: `symbol`, `float` (double) and `int` (32-bit). The numeric types can be stored and retrieved directly, without the use of pointers.

## Dependencies

You will need [just](https://github.com/casey/just) installed if you want to build and test the project. You can also simply run the REPL from the binary

## Usage

Start the REPL with `./repl` or with `just run`. Enter Lisp-like expressions and see the resulting tokens and types

```lisp
$> (+ 8 -8 .1234)
type symbol. value: (
type symbol. value: +
type int. value: 8
type int. value: -8
type float. value: 0.123400
type symbol. value: )
```

Run tests with `just test`.