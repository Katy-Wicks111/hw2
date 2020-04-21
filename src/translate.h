/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#pragma once

#include <stddef.h>

// Returns the length that `unexpanded` will have when expanded by
// `expand_charseq` (not including the terminating '\0').
//
// PRECONDITION (UNCHECKED): If `unexpanded` is null then the behavior
// is undefined.
size_t charseq_length(const char* unexpanded);

// Expands ranges and escapes in `unexpanded`. The resulting string is
// allocated with `malloc` and must be `free`d when you are done with
// it.
//
// A range is two characters with a hypohen in between, and stands for
// all characters between the two, inclusive. For example, "a-e" expands
// to "abcde". An escape is a backslash followed by another character
// which has the same meaning as in C string literals. For example,
// "\\n" (two characters) stands for "\n" (one character), and "\\b"
// stands for "\b". Unrecognized escapes just stand for the escaped
// character; for example, "\\*" means "*".
//
// PRECONDITION (UNCHECKED): If `unexpanded` is null then the behavior
// is undefined.
char* expand_charseq(const char* unexpanded);

// Translates character `c` from charseq `from` to charseq `to`. In
// particular, if there is some minimal index `i` such that `from[i] ==
// c`, returns `to[i]`; otherwise returns `c`.
//
// PRECONDITION (UNCHECKED): If `from` or `to` is null, or if
// `strlen(from) > strlen(to)`, then the behavior is undefined
char translate_char(char c, const char* from, const char* to);

// Modifies `s` in place by replacing any characters found in `from`
// with the character at the same index in `to`.
//
// PRECONDITION (UNCHECKED): If `s`, `from`, or `to` is null, or if
// `strlen(from) > strlen(to)`, then the behavior is undefined
void translate(char* s, const char* from, const char* to);

