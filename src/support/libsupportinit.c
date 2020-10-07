// This file is a part of Julia. License is MIT: https://julialang.org/license

#include <locale.h>
#include "libsupport.h"

#ifdef __cplusplus
extern "C" {
#endif

void libsupport_init(void)
{
    static int isInitialized = 0;
    if (!isInitialized) {
        ios_init_stdstreams();

        // adopt the user's locale for most formatting
        setlocale(LC_ALL, "");
        // but use locale-independent numeric formats (for parsing)
        setlocale(LC_NUMERIC, "C");
        // and try to specify ASCII or UTF-8 (preferred) for our Libc and Cstring functions
        setlocale(LC_CTYPE, "C"); // ASCII
#ifndef _OS_WINDOWS_
        if (setlocale(LC_CTYPE, "C.UTF-8") == NULL) { // Linux name
            if (setlocale(LC_CTYPE, "UTF-8") == NULL) { // BSD name
                ios_puts("WARNING: failed to select UTF-8 encoding, using ASCII\n", ios_stderr);
            }
        }
#endif

        isInitialized = 1;
    }
}

#ifdef __cplusplus
}
#endif
