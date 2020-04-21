#include "translate.h"

#include <stddef.h>
#include <stdlib.h>

// Helper function for interpreting escapes. Given the character that
// follows a backslash, returns the character that the combination
// should be replaced with. Recognizes the seven standard C escapes, and
// maps every other character to itself.
char interpret_escape(char c)
{
    switch (c) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    default:  return c;
    }
}

size_t charseq_length(const char* src)
{
     size_t count = 0;
    size_t pos = 0;
    while(*src != 0){
        if (pos + 2 < strlen(src) && src[pos + 1] == '-'
            && src[pos + 2] != 0){
            char start = src[pos];
            char end = src[pos + 2];
            if (start <= end){
                count = count + end - start + 1;
                pos = pos + 3;
            }
        }
        if (src[pos] == '\\' && src[pos + 1] != 0){
            count = count + 1;
            pos = pos + 2;
        } else {
            count = count + 1;
            pos = pos + 1;
        }
    }
    return count;
}
    

char* expand_charseq(const char* src)
{
    char* result = malloc(charseq_length(src) + 1);
    if (!result) return NULL;

    char* dst    = result;

    //
    // TODO: Your code goes here
    //

    *dst = 0;

    return result;
}

char translate_char(char c, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //

    return c;
}

void translate(char* s, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //
}

