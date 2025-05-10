#include <iostream>

// For offsetof()
#include <stddef.h>

struct S
{
    char a;  // 1 byte
             // 1 byte padding
             // 1 byte padding
             // 1 byte padding
    int b;   // 4 bytes
    short c; // 2 bytes
    char d;  // 1 byte
             // 1 byte padding
};

// Trailing padding is necessary to ensure every type is always consistent with its natural alignment.
// If S is 11 bytes long then, at some point, int will not be aligned on a multiple of 4.
// This could happen on an array:
//
//  0       4       8   10  11      15 (not multiple of 4)
// [a # # # b b b b c c d | a # # # b b b b c c d # | ...]
//
//  0       4       8   10    12      16 (multiple of 4)
// [a # # # b b b b c c d # | a # # # b b b b c c d # | ...]
//
// If the padding is added such that sizeof(S) % sizeof(maxsize) == 0 then all alignments are satisfied.
//
// In general, any composite type is aligned to its largest type alignment.

int main()
{
    std::cout << "sizeof(S): " << sizeof(S) << std::endl;
    std::cout << "alignof(S): " << alignof(S) << std::endl;
    std::cout << "offsetof S.c: " << offsetof(S, c) << std::endl;
}
