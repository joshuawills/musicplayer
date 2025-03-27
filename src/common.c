#include "common.h"

int max_number(int a, int b) {
    return a > b ? a : b;
}

void convert_encoding(const char *input, char *output, size_t out_size) {
    iconv_t cd = iconv_open("UTF-8", "ISO-8859-1");
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return;
    }

    char *inbuf = (char *)input;
    size_t inbytesleft = strlen(input);
    char *outbuf = output;
    size_t outbytesleft = out_size;

    if (iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1) {
        perror("iconv failed");
        iconv_close(cd);
        return;
    }

    *outbuf = '\0'; // Null terminate the output string
    iconv_close(cd);
}