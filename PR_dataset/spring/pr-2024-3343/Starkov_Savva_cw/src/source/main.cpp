#include <queue>
#include <functional>
#include "../include/functions.h"
#include "../include/write.h"
#include <getopt.h>
#include "../include/helps.h"

using namespace std;


int main(int argc, char *argv[]) {
    deque<function<void()>> queuefunction;

    OptionFlags flags;

    int opt;
    BMPImage image{};

    const struct option opts[] =
            {
                    {"help",           no_argument,       NULL, 'h'},

                    {"shift",          no_argument,       NULL, 269},

                    {"step",           required_argument, NULL, 283},

                    {"axis",           required_argument, NULL, 287},

                    {"info",           no_argument,       NULL, 'i'},

                    {"inverse_image",  no_argument,       NULL, 258},

                    {"input",          required_argument, NULL, 257},

                    {"output",         required_argument, NULL, 'o'},

                    {"component_name", required_argument, NULL, 256},

                    {"hsv",no_argument,NULL, 284},

                    {"component_sum",  no_argument,       NULL, 259},

                    {0, 0, 0,                                   0}
            };

    while ((opt = getopt_long(argc, argv, "ho:i:c:", opts, NULL)) != -1) {


        switch (opt) {
            case 287: {
                flags.axisFlag = true;
                flags.axisfield = optarg;
                break;
            }
            case 284:
                flags.hsvFlag = true;
                break;
            case 283: {
                flags.stepValue = stoi(optarg);
                break;
            }
            case 269: {
                flags.shiftFlag = true;
                break;
            }
            case 258: {
                flags.inverseFlag = true;
                break;
            }
            case 259: {
                flags.component_sumFlag = true;
                break;
            }
            case 'h': {
                flags.helpFlag = true;
                break;
            }
            case 256: {
                flags.color = optarg;
                break;
            }
            case 'o': {
                flags.filenameoutput = optarg;
                break;
            }
            case 257: {
                flags.filenameinput = optarg;
                break;
            }
            case 'i': {
                flags.infoFlag = true;
                break;
            }
            default: {
                std::cerr << MESSAGE_UnknownFlag << std::endl;
                break;
            }
        }
    }

    if (flags.helpFlag == true) {
        std::cout << MESSAGE_HelpInfo << std::endl;
        exit(0);
        /* code */
    }

    if (flags.filenameinput.empty()) {
        flags.filenameinput = argv[argc - 1];
    }

    if (flags.filenameoutput.empty()) {
        flags.filenameoutput = "out.bmp";
    }

    if (flags.filenameinput == flags.filenameoutput) {
        std::cerr << "The names of the input and output files are the same" << std::endl;
        exit(ERR_INPUTQUALS);
    }


    auto read = [&flags, &image]() { image = readBMP(flags.filenameinput.c_str()); };
    queuefunction.emplace_front(read);


    if (validateShift(flags)) {
        auto shift = [&flags, &image]() {
            shift_func(image, flags.stepValue, flags.axisfield);
        };
        queuefunction.emplace_back(shift);
    }

    if (flags.inverseFlag) {
        auto inverse = [&flags, &image]() {
            inverse_all(image);
        };
        queuefunction.emplace_back(inverse);
    }
    if (flags.component_sumFlag != false) {
        if (!flags.color.compare(RED) && !flags.color.compare(GREEN) && !flags.color.compare(BLUE)) {
            std::cerr << MESSAGE_WrongColor << std::endl;
            exit(ERR_WRONGCOLOR);
        }
        auto component_sumfunc = [&image, &flags]() {
            component_max(image, flags.color);
        };

        queuefunction.emplace_back(component_sumfunc);
    }

    if(flags.hsvFlag != false){
        auto hsvconvertfunc = [&image](){
            hsvconvert(image);
        };
        queuefunction.emplace_back(hsvconvertfunc);
    }

    if (flags.infoFlag == true) {
        auto infofunc = [&image, &flags] {
            printInfo(image, flags.filenameinput);
        };
        queuefunction.emplace_back(infofunc);
    };

    auto write = [&image, &flags] {
        writeBMP(flags.filenameoutput, image);
    };
    queuefunction.emplace_back(write);


    while (!queuefunction.empty()) {
        queuefunction.front()();
        queuefunction.pop_front();
    }

    if (!image.data.empty()) {
        image.data.clear();
    }


}