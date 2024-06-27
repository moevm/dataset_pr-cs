#include "Output.h"
#include "FlagsHandler.h"


int main(int argc, char **argv)
{
    Output::showAuthorInfo("5.17", "Kirill", "Maltsev");
    FlagsHandler handler;
    handler.getFlags(argc, argv);
    handler.handleFlags();
    return 0;
}