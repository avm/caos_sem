#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>

struct State {
    int symbols;
    int lines;
    int words;
    int in_word;
    unsigned codepoint;
};

void process_bytes(struct State* state, unsigned char byte) {
    state->symbols++;
    if (byte == '\n') {
        state->lines++;
    }
    if (state->in_word && !isalnum(byte)) {
        state->words++;
    }
    state->in_word = isalnum(byte);
}

//  0x44f я
//  0x7a z
//  0x5973 女
//  а́
//
//  0 -> 1-byte ASCII symbol
//  10 -> 2-nd or later byte of a multibyte sequence
//  110 -> 1st byte of a 2-byte sequence
//  1110 -> 1 3
//  11110 -> 1 4
//
//  \0 ->  00
//  z -->  7a
//  я -->  d1 8f   110 10


int is_letter(unsigned codepoint) {
    return (codepoint >= 'a' && codepoint <= 'z') ||
           (codepoint >= L'а' && codepoint <= L'я');
}

void process_utf8(struct State* state, unsigned char byte) {
    if (((unsigned char) byte) >> 5 == 6) { // 110
        state->codepoint = (unsigned char) byte & 0x1fu;
        return;
    } else if (((unsigned char) byte) >> 6 == 2) {
        state->codepoint <<= 6;
        state->codepoint += byte & 0x3fu;
    } else {
        state->codepoint = byte;
    }

    state->symbols++;

    if (state->codepoint == '\n') {
        state->lines++;
    }

    int alnum = is_letter(state->codepoint);
    if (state->in_word && !alnum) {
        state->words++;
    }
    state->in_word = alnum;
}

typedef void (*function_type)(struct State* state, unsigned char byte);

int main(int argc, char** argv) {
    function_type function;
    struct State state = { 0, 0, 0, 0, 0 };

    if (argc > 1 && !strcmp(argv[1], "--unicode")) {
        function = process_utf8;
    } else {
        function = process_bytes;
    }

    int ch;
    while ((ch = getchar()) != EOF) {
        function(&state, ch);
    }
    printf("%d %d %d\n", state.symbols, state.words, state.lines);
}
