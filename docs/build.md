# Build

In the middle of K&R Chapter 2, I realized that I wrote a lot of duplicate
code, in those exercises that needed to solve similar problems. I chose to turn
this repo into a small project that mimics the structure of a real world, open
source project.

With this doc, I'm going to document my dive into GNU Make and, more in
general, the structuring of the project. 


## Project Structure

I'm planning to cover more books than just K&R, so I want a collection of
exercises by book. In addition, I want to build a library that can be reused as
I progress.

This is how I am going to structure the project:

```
c-nostalgia/                   # Project root
├── build/                     # Compilation target directory
│   └── kr-1_01                # Compiled K&R Exercise 1-1
└── src/
    ├── books/
    │   └── kr/                # Solutions to exercises from K&R
    │       └── chap-1/        # K&R Chapter 1 exercises
    │           └── ex-1_01.c
    └── core/
        ├── include/
        │   ├── c_nostalgia.h  # Master header file
        │   ├── kr_bitwise.h   # Bit manipulation headers
        │   └── kr_strings.h   # String manipulation headers
        ├── bitwise/           # Bit manipulation functions
        └── strings/           # String manipulation functions
            └── kr_strings.c
```

I'll write a Makefile that:

  1. provides a shorthand to build any exercise, by book
  2. provides a shorthand to build all exercises
  3. builds a set of shared libraries, semantically scoped, that are
  dynamically linked to exercises that use their functions


## Compilation

Let's focus on project structure's upper portion.

```
c-nostalgia/
├── build/
│   └── kr-1_01                # Compiled executable file
└── src/
    ├── books/
    │   └── kr/
    │       └── chap-1/
    │           └── ex-1_01.c  # Self-contained code, with no dependencies
   ...
```

In order to compile a simple self-contained exercise by direct command that
creates a named executable file in a target directory named `build/`, the
simplest command to run is:

```
  $ gcc src/books/kr/chap-1/ex-1_01.c -o build/kr-1_01
```
We can also choose to specify options to `gcc`, eg. to enable all warnings,
turn warnings into errors and use `c99` standard, the command becomes:

```
  $ gcc -Wall -Werror -std=c99 src/books/kr/chap-1/ex-1_01.c -o build/kr-1_01
```
As we continue adding more self-contained exercises, we should manually change
the source and the target file names. This process by itself does not scale
well and here's where `make` comes into play.

We can instruct `make` to build our code through a `Makefile` containing a set
of rules that, for each target, checks the prerequisites and executes a recipe.
You can find the documentation for GNU make at this
[link](https://www.gnu.org/software/make/manual/make.html).

Going on with our example above, if we have only K&R Exercise 1-1 to build, we
can write a `Makefile` that looks as follows:

```
kr-1_01:
	gcc src/books/kr/chap-1/ex-1_01.c -o build/kr-1_01
```

and run `make` to build the only specified rule or run `make kr-1_01` to
explicitly build our only exercise.

When we start Exercise 1-2, we will add another rule:

```
kr-1_02:
	gcc src/books/kr/chap-1/ex-1_02.c -o build/kr-1_02
```

so we can run `make kr-1_02` and explicitly build our new exercise, but if we
just run `make`, only `kr-1_01` will be built. In order to tell `make` to build
all the targets we can add a [Phony
Target](https://www.gnu.org/software/make/manual/make.html#Phony-Targets) that
includes the other rules as prerequisites.

```
all: kr-1_01 kr_1_02

# the rules above

.PHONY: all
```

You see why the approach as is does not scale? Every time we work on a new
exercise we have to manually add a new rule and link that rule to `all`
prerequisites.


### Variables

Let's see how the use of variables can simplify our use cases. We can declare
some variables and use them in our recipes:

```
CC = gcc

BUILD_DIR = build
CHAP_DIR = src/books/kr/chap-1

kr-1_01:
	$(CC) $(CHAP_DIR)/ex-1_01.c -o $(BUILD_DIR)/kr-1_01

kr-1_02:
	$(CC) $(CHAP_DIR)/ex-1_02.c -o $(BUILD_DIR)/kr-1_02
```

`make` also provides some rule-scoped [Automatic
Variables](https://www.gnu.org/software/make/manual/make.html#Automatic-Variables).
The ones we are going to use are `$@`, which carries the filename of the target
of the current rule, and `$<`, which is the name of the first prerequisite.

```
CC = gcc

BUILD_DIR = build
CHAP_DIR = src/books/kr/chap-1

kr-1_01: $(CHAP_DIR)/ex-1_01.c
	$(CC) $< -o $(BUILD_DIR)/$@

kr-1_02: $(CHAP_DIR)/ex-1_02.c
	$(CC) $< -o $(BUILD_DIR)/$@
```

Can you see that the recipe `$(CC) $< -o $(BUILD_DIR)/$@` is the same in both
rules? If we are able to find a way to express the rule "for each source file
in `CHAP_DIR`, build a corresponding target", we would solve our scalability
problem.


### Pattern Match

Targets can include the symbol `%`, called _stem_, to match a pattern. The stem
can be carried to the prerequisite of the same rule, where it will be expanded
to the value that was matched in the target. Let's see how this works for our
use case:

```
all: kr-1_01 kr-1_02

kr-%: $(CHAP_DIR)/ex-%.c
	$(CC) $< -o $(BUILD_DIR)/$@
```

  1. We run `make` and the rule `all` matches. It has two prerequisites:
  `kr-1_01` and `kr-1_02`
  2. For each prerequisite, `make` looks for a matching rule by target
  3. `kr-1_01` matches the rule `kr-%`, and the stem has value `1_01`
  4. the prerequisite `$(CHAP_DIR)/ex-%.c` is expanded to
  `src/books/kr/chap-1/ex-1_01.c`, which needs to be built, and the recipe is
  ran
  5. the same applies to `kr-1_02`

At this point we have half of our problem solved, because we don't need to
write a new rule each time we add an exercise any more, but we still need to
add a new prerequisite to `all` target each time. Here we can start being
creative: our objective is to create a variable that contains a target name for
each existing file in our sources directory. eg. `CHAP_TARGETS -> kr-1_01
kr-1_02 ... kr-1_n`.

In order to do so, `make` provides some
[Functions](https://www.gnu.org/software/make/manual/make.html#Functions) that
will help us to achieve our goal. Let's start with getting the list of existing
files under `CHAP_DIR`.

```
CHAP_SRCS := $(wildcard $(CHAP_DIR)/*.c)
```

`wildcard` is the function name, `$(CHAPDIR)/*.c` is the argument. Two things
are important to note. We are using `:=` as assignment operator, which implies
_immediate_ assignment to the variable, whereas `=` _defers_ the variable
evaluation to when it is referenced. We can't use pattern matching (the `%`
thingy) to get the same result, because it only works with strings, while
`wildcard` interfaces with the filesystem to expand the values.

We can check the value of `CHAP_SRCS` calling the `info` function:

```
$(info $(CHAP_SRCS))
# output: src/books/kr/chap-1/ex-1_01.c src/books/kr/chap-1/ex-1_02.c
```

From `CHAP_SRCS`, what really matters is the filename, so we can make our life
easier using the function `notdir` in this way:

```
CHAP_FILENAMES := $(notdir $(CHAP_SRCS))

$(info $(CHAP_FILENAMES))
# output: ex-1_01.c ex-1_02.c
```

Finally, we want to generate a target name from each filename. We can use the
function `patsubst` in this case:

```
CHAP_TARGETS   := $(patsubst ex-%.c,kr-%,$(CHAP_FILENAMES))

$(info $(CHAP_TARGETS))
# output: kr-1_01 kr-1_02
```

We can now use `CHAP_TARGETS` in `all` rule prerequisites to automatically
build each source file we add to our chapter's exercises. The `Makefile` now
looks like this.

```
CC = gcc

BUILD_DIR = build
CHAP_DIR = src/books/kr/chap-1

CHAP_SRCS      := $(wildcard $(CHAP_DIR)/*.c)
CHAP_FILENAMES := $(notdir $(CHAP_SRCS))
CHAP_TARGETS   := $(patsubst ex-%.c,kr-%,$(CHAP_FILENAMES))

all: $(CHAP_TARGETS)

kr-%: $(CHAP_DIR)/ex-%.c
	$(CC) $< -o $(BUILD_DIR)/$@

.PHONY: all
```


### Compilation Options

Turning on all the compilation warnings is a good practice, but for this
educational project, I want also to turn all the warnings into errors. This can
be achieved by adding `-Wall -Werror` to compiler options. By convention, this
is done by declaring a `CFLAGS` variable and then passing it to the recipe.
Note that both `CC` and `CFLAGS` belong to a list of [Implicit
Variables](https://www.gnu.org/software/make/manual/make.html#Implicit-Variables).
I'm also targeting the `c99` standard, as it's the most modern standard that
aligns to the content of K&R book.

```
CC     = gcc
CFLAGS = -Wall -Werror -std=c99

# other variables

all: $(CHAP_TARGETS)

kr-%: $(CHAP_DIR)/ex-%.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

.PHONY: all
```

## The `clean` rule

Adding a `clean` rule to the `Makefile` provides a simple way to delete build
artifacts. In our specific case, at the moment, it's just a simple way to empty
the `build/` directory.  This is another rule with a Phony Target, because the
target of the rule is not the name of a file.

```
# variables and previously declared rules

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: all clean
```


## Shared Libraries

Like in any real world scenario, it may happen that you face the same problem
multiple times. In these cases you may choose to re-implement the function from
scratch, or to create an external library that can be statically or dynamically
linked when needed.

Static Linking means that the machine code corresponding to the functions that
are used in the program are copied into the final executable, resulting in a
single self-contained binary. This is simple to deal with and slightly more
performant, but on the other hand, it's less memory efficient and the
executables are larger.

Dynamic Linking means that, at compile time, the compiler includes references
to the functions, instead of the actual code, and when the program runs, the
operating system's dynamic loader finds and loads the libraries into memory.
Advantages and disadvantages are in general the opposite of what we mentioned
about static linking.

In this project, we'll explore dynamic linking.


### Project Re-Structure

In order to better fit the Dynamic Linking approach, we need to change a couple
of things. Our rules can be improved to implement a two-stage compilation, the
first step will produce obect files and the second will combine them into
either executables or shared libraries. By doing so, `make` is able to
understand what's changed and will compile only what is necessary. There are
more improvements on this aspect, but we'll cover them later. The second thing
we are going to change is the structure of `build/` directory, that now needs a
place where to store the object files and the shared libraries in addition to
the executables. The project structure is then going to be:

```
c-nostalgia/                    # Project root
├── build/                      # Compilation target directory
│   ├── bin/                    # Compiled Executables
│   │   └── kr-1_01             # K&R Exercise 1-1 executable
│   ├── lib/                    # Shared libraries
│   │   └── libkr_strings.so    # K&R string manipulation shared library
│   └── obj/                    # Compiled objects
│       └── kr_strings.o        # K&R string manipulation object file
└── src/
    ├── books/
    │   └── kr/                 # Solutions to exercises from K&R
    │       └── chap-1/         # K&R Chapter 1 exercises
    │           └── ex-1_01.c
    └── core/
        ├── include/
        │   ├── c_nostalgia.h   # Master header file
        │   ├── kr_bitwise.h    # K&R bit manipulation headers
        │   └── kr_strings.h    # K&R string manipulation headers
        ├── bitwise/            # Bit manipulation functions
        └── strings/            # String manipulation functions
            └── kr_strings.c    # K&R string manipulation library source
```


### Single-Stage -> Multi-Stage

Until now, the `Makefile` rules have been written to compile in one step the
source files into executables. In other words the command we were using in the
recipes, stripping out the flags, was:

```
  $ gcc -o build/kr-1_01 src/books/kr/chap-1/ex-1_01.c 
```

We need to change the above into:

```
  $ gcc -c -o build/obj/ex-1_01.o src/books/kr/chap-1/ex-1_01.c
  $ gcc -o build/bin/kr-1_01 build/obj/ex-1_01.o
```

and the `Makefile` rules into something like:

```
all: build/bin/kr-1_01 build/bin/kr-1_02

build/bin/kr-1_01: build/obj/ex-1_01.o
	gcc -o build/bin/kr-1_01 build/obj/ex-1_01.o

build/obj/ex-1_01.o: src/books/kr/chap-1/ex-1_01.c
	gcc -c -o build/obj/ex-1_01.o src/books/kr/chap-1/ex-1_01.c

build/bin/kr-1_02: build/obj/ex-1_02.o
	gcc -o build/bin/kr-1_02 build/obj/ex-1_02.o

build/obj/ex-1_02.o: src/books/kr/chap-1/ex-1_02.c
	gcc -c -o build/obj/ex-1_02.o src/books/kr/chap-1/ex-1_02.c
```

By applying the same strategy we described above when talking about Pattern
Matching, Variables and Functions, the `Makefile` changes to apply are:

```
CHAP_SRCS := $(wildcard $(CHAP_DIR)/*.c)
CHAP_OBJS := $(patsubst $(CHAP_DIR)/%.c,$(OBJ_DIR)/%.o,$(CHAP_SRCS))
CHAP_BINS := $(patsubst $(OBJ_DIR)/ex-%.o,$(BIN_DIR)/kr-%,$(CHAP_OBJS))

# Make sure that target build directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

all: $(CHAP_BINS)

$(BIN_DIR)/kr-%: $(OBJ_DIR)/ex-%.o
	$(CC) -o $@ $<

$(OBJ_DIR)/ex-%.o: $(CHAP_DIR)/ex-%.c
	$(CC) $(CFLAGS) -c -o $@ $<
```

We need to update our `clean` rule though, because it now contains directories.

```
clean:
	rm -rf $(BUILD_DIR)/*
```


### Compiling Shared Libraries in Two-Stages

Chapter 1.7 introduces functions and from Exercise 1-16 on, and some of the
functions you are asked to implement are actually reusable in the following
ones. This is a good opportunity to experiment with shared libraries. We
already explained what they are, but in a nutshell it's a piece of code that is
dynamically loaded in memory when required.

As we did for the executables, we are going to compile the shared libraries in
two steps: from source to object file, and from object file to shared library.

```
  $ gcc -c -fPIC -I src/core/include \
      -o build/obj/kr_strings.o src/core/strings/kr_strings.c
  $ gcc -shared -o build/lib/libkr_strings.so build/obj/kr_strings.o
```

The `-fPIC` option tells the compiler to produce Position Independent Code
(PIC), which solves the fundamental challenge of loading shared libraries at
different memory addresses. When a program uses a shared library, each process
has its own virtual address space, but they all need to access the same
physical memory where the shared library is loaded. Without PIC, the code would
contain hardcoded memory addresses that would only work if the library were
loaded at exactly the same address for every process, which is impossible in
modern operating systems. With PIC, the code uses the Global Offset Table (GOT)
to dynamically resolve the actual memory locations at runtime, regardless of
where the library is loaded in memory.

The `-shared` link option tells the compiler to produce a shared object that
can be linked to other objects to form an executable.

The `Makefile` rules should be updated to:

```
all: build/lib/libkr_strings.so

build/lib/libkr_strings.so: build/obj/kr_strings.o
	gcc -shared -o build/lib/libkr_strings.so build/obj/kr_strings.o

build/obj/kr_strings.o: src/core/strings/kr_strings.c
	gcc -c -fPIC -I src/core/include -o build/obj/kr_strings.o src/core/strings/kr_strings.c
```
