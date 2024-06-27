#pragma once
#define ERROR(msg, code)              \
    do {                              \
        std::cerr << msg << "\n"      \
                  << "seek --help\n"; \
        exit(code);                   \
    } while (0)
#define ArgERROR(msg) ERROR("ArgError: " << msg, 40)
#define ArgInvalidERROR(msg) ArgERROR("invalid " << msg)
#define IOERROR(msg) ERROR("IOError: " << msg, 43)
