#ifndef __HANDLE_OPT_H__
#define __HANDLE_OPT_H__

#define CHECK_IF_DEBUG(x)   \
    if (gDebug) { \
        x; \
    }

enum EXIT_REASON {
    EXIT_OK,
    EXIT_INVALID_OPT,
    EXIT_WORKER,
    EXIT_ERROR,
};

void print_help();
void handleopt(int argc, char** argv);

extern bool gDebug;

#endif  // __HANDLE_OPT_H__
