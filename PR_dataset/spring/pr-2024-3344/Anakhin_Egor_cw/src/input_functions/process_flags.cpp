#include "process_flags.h"


void processArguments(int& argc, char**& argv) {
    // Проверяем, есть ли флаг --input
    bool hasInputFlag = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--input") {
            hasInputFlag = true;
            break;
        }
    }

    if (!hasInputFlag) {
        std::vector<char*> newArgv(argc + 2, nullptr);

        for (int i = 0; i < argc; ++i) {
            newArgv[i] = argv[i];
        }

        newArgv[argc - 1] = const_cast<char*>("--input");
        newArgv[argc] = argv[argc - 1]; 

        delete[] argv;

        argc += 1;
        argv = new char*[argc];
        for (int i = 0; i < argc; ++i) {
            argv[i] = newArgv[i];
        }

        if (argc > (int)newArgv.size()) {
            for (int i = newArgv.size(); i < argc; ++i) {
                delete[] argv[i];
            }
        }
    }
}