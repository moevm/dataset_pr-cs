#ifndef HANDLER
#define HANDLER

#include <getopt.h>
#include <map>
#include <string>
#include <set>

#define HANDLER_ERROR           45

#define FLAGS_NUMBER            23

#define HELP_IDX                'h'
#define INPUT_IDX               'i'
#define OUTPUT_IDX              'o'
#define INFO_IDX                1001

#define THICKNESS_IDX           1002
#define COLOR_IDX               1003
#define FILL_IDX                1004
#define FILL_COLOR_IDX          1005

#define BORDER_RECTS_IDX        1006
#define BORDER_COLOR_IDX        1007

#define CIRCLE_IDX              1008
#define CENTER_IDX              1009
#define RADIUS_IDX              1010

#define RGBFILTER_IDX           1011
#define COMPONENT_NAME_IDX      1012
#define COMPONENT_VALUE_IDX     1013

#define SPLIT_IDX               1014
#define NUMBER_X_IDX            1015
#define NUMBER_Y_IDX            1016

#define CONCAT_IDX              1017
#define AXIS_IDX                1018
#define INPUT_SECOND_IDX        1019

namespace hdlr
{

void throwError(const char *message, int exit_code);

struct Flag
{
    bool entered;
    std::string parameter;
};

class Handler
{
private:
    std::map<int, Flag>    flags;
    const char             *short_options;
    const struct option    long_options[FLAGS_NUMBER];
    std::string            last_argument;
    
    std::set<int> getRedundantFlags(std::set<int>& required_flags, 
        std::set<int>& optional_flags);

    bool checkFlagCompliance(std::set<int>& required_flags, 
        std::set<int>& redundant_flags);

    void getFinFoutNames(std::string &input_file_name, std::string &output_file_name);
    void getSecondFinName(std::string &second_file_name);

    bool isHelp();
    bool isInfo();
    bool isBorderRectangles();
    bool isCircle();
    bool isRGBFilter();
    bool isSplit();
    bool isConcat();
    
    void doHelp();
    void doInfo();
    void doBorderRectangles();
    void doCircle();
    void doRGBFilter();
    void doSplit();
    void doConcat();

public:
    Handler();
    ~Handler();
    void show_author_info(const char *option, const char *name, const char *surname);
    void getFlags(int argc, char **argv);
    void handleFlags();
};
}

#endif