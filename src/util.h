#ifndef LIC_UTIL_H
#define LIC_UTIL_H

#include <stdio.h>

#define BUF_LEN 256
#define TAG_LEN 50

#define INDENT() for (size_t ix = 0; ix < 2 * indent; ix++) printf(" ");
#define UNDENT() ;; // for (size_t ix = 0; ix < 2 * indent; ix++) printf("\b");

#define INFO(...)                                                               \
    {                                                                           \
        INDENT();                                                               \
        TAG();                                                                  \
        char buf[BUF_LEN];                                                      \
        snprintf(buf, BUF_LEN, __VA_ARGS__);                                    \
        UNDENT();                                                               \
        printf("%s\n", buf);                                                    \
    }

#define IN()                                                                    \
    INFO("%s {", __FUNCTION__);                                                 \
    indent++;                                                                   

#define OUT()                                                                   \
    indent--;                                                                   \
    INFO("}");

#define TAG()                                                                   \
    {                                                                           \
        char tag[TAG_LEN];                                                      \
        char fmt[8];                                                            \
        snprintf(fmt, 8, "%%-%us", TAG_LEN);                                    \
        snprintf(tag, TAG_LEN, "%s:%u:%s: ", __FILE__, __LINE__, __FUNCTION__); \
        printf(fmt, tag);                                                       \
    }

#define LOGCALLOC(name, type, count)                                            \
    name = calloc(count, sizeof(type));                                         \
    INFO("Allocating %zu bytes for %zu objs of size %zu.", (long)((count) * (sizeof(type))), (long)(count), (long)(sizeof(type))); \

#define LINE()                                                                  \
    for (size_t ix = 0; ix < 80; ix++) printf("-");                             \
    printf("\n");

extern char indent;
//extern char buf[BUF_LEN];

#endif
