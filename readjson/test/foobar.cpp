#include "foobar.h"
#include "libhu_msgq.h"

#include <stdio.h>

#define FOREACH_FRUIT(FRUIT) \
        FRUIT(apple)   \
        FRUIT(orange)  \
        FRUIT(grape)   \
        FRUIT(banana)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define str(x) #x
#define xstr(x) str(x)

enum FRUIT_ENUM {
    FOREACH_FRUIT(GENERATE_ENUM)
};

static const char *FRUIT_STRING[] = {
    FOREACH_FRUIT(GENERATE_STRING)
};

int enum_test()
{
    printf("enum apple as a string: %s\n", FRUIT_STRING[apple]);
    printf("enum apple as a string: %s\n", xstr(apple));

    printf("enum: %s = 0x%08x\n", str(MSGQ_KEY_RADIOUI), MSGQ_KEY_RADIOUI);
    return 0;
}
