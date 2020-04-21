# For building CS 211 Homework 2
# You don’t need to edit this file, and you probably shouldn’t.

# Programs we can build:
EXES        = tr test_translate

# C compiler to use:
CC         ?= cc
# Extra options for catching bad stuff:
SANFLAGS   += -fsanitize=address,undefined
# Flags for compiling individual files:
CFLAGS     += -g -std=c11 -pedantic-errors -Wall $(SANFLAGS)
# Flags for linking the final program:
LDFLAGS    += -l211 $(SANFLAGS)

all: $(EXES)

test: test_translate
	./$<

tr: src/tr.o src/translate.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_translate: test/test_translate.o src/translate.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(EXES) */*.o

# Header dependencies:
src/translate.o src/tr.o test/test_translate.o: src/translate.h

# Targets that are not actually files we can build:
.PHONY: all test clean

# Ensure we have the correct C compiler version:
CSHOST = .northwestern.edu
ifeq ($(DEV211)$(CSHOST),$(findstring $(CSHOST),$(shell hostname)))
  $(error You need to run ‘dev’ first)
endif
