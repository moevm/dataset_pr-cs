#include "handler.h"

int main(int argc, char **argv)
{   
    hdlr::Handler handler;
    
    handler.show_author_info("5.8", "Egor", "Shapovalenko");
    handler.getFlags(argc, argv);
    handler.handleFlags();
    
    return 0;
}