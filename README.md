# c-nostalgia

Repository to document my journey through classic computer science books.


## Current progress

- The C Programming Language, by Kernighan & Ritchie
  - Chapter 1, Exercises 1-2


## Project Structure

```
src/
├── books/
│   └── kr/               # Solutions to exercises from K&R
└── core/
    ├── include/          # Public header files
    │   └── c_nostalgia.h # Master header file
    ├── bitwise/          # Bit manipulation functions
    ├── strings/          # String manipulation functions  
    ├── io/               # Input/Output functions
    └── memory/           # Memory manipulation functions
```


## Building and Running

The target directory for build is `build/`.

```
make           # build all exercises
make kr-1_01   # build a specific exercise, eg. K&R Exercise 1-1
make run-1_01  # run a specific exercise
```

