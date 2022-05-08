#ifndef LIC_UTIL_H
#define LIC_UTIL_H

#include <stdio.h>

#define BUF_LEN 256
#define TAG_LEN 40

#define INDENT() for (size_t ix = 0; ix < 2 * indent; ix++) printf(" ");
#define UNDENT() for (size_t ix = 0; ix < 2 * indent; ix++) printf("\b");

#define INFO(fmt, ...)                                                          \
    {                                                                           \
        INDENT();                                                               \
        TAG();                                                                  \
        char buf[BUF_LEN];                                                      \
        snprintf(buf, BUF_LEN, fmt, __VA_ARGS__);                               \
        UNDENT();                                                               \
        printf("%s\n", buf);                                                    \
        }

#define IN()                                                                    \
    INFO("Called %s", __FUNCTION__);                                            \
    indent++;                                                                   

#define OUT()                                                                   \
    indent--;                                                                   \
    INFO("Return from %s.", __FUNCTION__);

#define TAG()                                                                   \
    {                                                                           \
        char tag[TAG_LEN];                                                      \
        char fmt[8];                                                            \
        snprintf(fmt, 8, "%%-%us", TAG_LEN);                                    \
        snprintf(tag, TAG_LEN, "%s:%u:%s: ", __FILE__, __LINE__, __FUNCTION__); \
        printf(fmt, tag);                                                       \
    }

#define LOGCALLOC(x, y)                                                       \
    (printf("Allocating %zu bytes for %zu objs of size %zu.\n", (long)((x) * (y)), (long)(x), (long)(y)), calloc((x), (y)))

extern char indent;
//extern char buf[BUF_LEN];

#endif
