#include "../src/translate.h"

#include <lib211.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>


/////
///// TEST HELPER SIGNATURES
/////

// Runs an expand_charseq() test case. Asserts that
// `expand_charseq(input)` will return `expected`.
static void
assert_expand(const char* input, const char* expected);

// Runs a translate() test case. Asserts that `translate(input,
// from0, to0)` changes `input` to `expected`. (But uses a copy of
// `input`, since `input` might be a string literal, and changing those
// is UB.)
static void
assert_tr(const char* input,
          const char* from0,
          const char* to0,
          const char* expected);

// Clones a string into fresh, `malloc`ed memory. Some C implementations
// provide a function `strdup` to do this, but it's non-standard.
static char*
clone_string(const char* src);


/////
///// TEST CASES FOR charseq_length
/////

static void test_charseq_length(void)
{
    CHECK_SIZE( charseq_length("abc"), 3 );
    CHECK_SIZE( charseq_length("a-z"), 26 );

    //
    CHECK_SIZE( charseq_length("a-e_"), 6 );
    CHECK_SIZE( charseq_length("a-df-i"), 8 );

    CHECK_SIZE( charseq_length("\\t"), 1 );

}


/////
///// TEST CASES FOR expand_charseq
/////

static void test_expand_charseq(void)
{
    assert_expand( "abc", "abc" );
    assert_expand( "a-e", "abcde" );

    //
    assert_expand( "a-e_", "abcde_" );
    assert_expand( "a-df-i", "abcdfghi" );
    assert_expand( "\\t", "\t" );

}


/////
///// TEST CASES FOR translate_char
/////

static void test_translate_char(void)
{
    CHECK_CHAR( translate_char('a', "xyz", "XYZ"), 'a' );
    CHECK_CHAR( translate_char('y', "xyz", "XYZ"), 'Y' );

    //
    // TODO: Add more tests for translate_char() here
    //
}


/////
///// TEST CASES FOR translate
/////

static void test_translate(void)
{
    assert_tr( "Hello, world!", ",! ",    "___",    "Hello__world_" );
    assert_tr( "hELLO, WORLD!", "a-zA-Z", "A-Za-z", "Hello, world!" );

    //
    // TODO: Add more tests for translate() here
    //
}


/////
///// main
/////

int main()
{
    test_expand_charseq();
    test_translate_char();
    test_translate();
    test_charseq_length();
}


/////
///// HELPER FUNCTION DEFINITIONS
/////

static void assert_expand(const char* input, const char* expected)
{
    char* actual = expand_charseq(input);
    CHECK_STRING( actual, expected );
    free(actual);
}

static void assert_tr(const char* input,
                      const char* from0,
                      const char* to0,
                      const char* expected)
{
    char* from   = expand_charseq(from0);
    char* to     = expand_charseq(to0);

    // avoids UB in case of OOM:
    assert(from);
    assert(to);

    char* actual = clone_string(input);

    translate(actual, from, to);

    CHECK_STRING( actual, expected );

    free(from);
    free(to);
    free(actual);
}

static char* clone_string(const char* src)
{
    char* dst = malloc(strlen(src) + 1);
    assert( dst ); // avoids UB in case of OOM
    strcpy(dst, src);
    return dst;
}
