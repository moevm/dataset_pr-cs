#ifndef COURSE_WORK_OPTIONS_HPP
#define COURSE_WORK_OPTIONS_HPP

#include "structuresDefinition.hpp"
#include <getopt.h>

const char *smallOpts = "hi:r:CRl:c:t:fo:n:p:Od:";
const struct option options[22] = {{"help", no_argument, NULL, 'h'},
                                   {"info", no_argument, NULL, 'g'},
                                   {"rect", no_argument, NULL, 'R'},
                                   {"circle", no_argument, NULL, 'C'},
                                   {"left_up", required_argument, NULL, 'l'},
                                   {"right_down", required_argument, NULL, 'r'},
                                   {"thickness", required_argument, NULL, 't'},
                                   {"color", required_argument, NULL, 'c'},
                                   {"fill", no_argument, NULL, 'f'},
                                   {"fill_color", required_argument, NULL, 'F'},
                                   {"output", required_argument, NULL, 'o'},
                                   {"input", required_argument, NULL, 'i'},
                                   {"center", required_argument, NULL, 'a'},
                                   {"radius", required_argument, NULL, 'd'},
                                   {"ornament", no_argument, NULL, 'O'},
                                   {"pattern", required_argument, NULL, 'p'},
                                   {"count", required_argument, NULL, 'n'},
                                   {"rotate", no_argument, NULL, 's'},
                                   {"angle", required_argument, NULL, 'u'},
                                   {"compress", no_argument, NULL, 'Z'},
                                   {"num", required_argument, NULL, 'N'},
                                   {NULL, 0, NULL, 0}};
#endif //COURSE_WORK_OPTIONS_HPP
