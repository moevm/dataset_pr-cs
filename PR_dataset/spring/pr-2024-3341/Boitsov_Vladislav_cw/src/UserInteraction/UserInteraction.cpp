#include "UserInteraction.h"
#include <set>
#include <map>
#include <iostream>

int UserInteraction::parseIntValue(int optind)
{
    int value;
    if(sscanf(flagValues[optind].c_str(), "%d", &value)!=1)
        throwInvalidFormat("Invalid int format!");
    return value;
}

Rgb UserInteraction::parseColorValue(int optind)
{
    Rgb color;
    int r, g, b;
    if(sscanf(flagValues[optind].c_str(), "%d.%d.%d", &(r), &(g), &(b))!=3)
        throwInvalidFormat("Invalid Color format!");
    color.r=r;
    color.g=g;
    color.b=b;
    return color;
}

Point UserInteraction::parseCoordValue(int optind)
{
    Point coord;
    if(sscanf(flagValues[optind].c_str(), "%d.%d", &(coord.x), &(coord.y))!=2)
        throwInvalidFormat("Invalid Coords format!");
    return coord;
}

void UserInteraction::readFlags(int argc, char** argv)
{
    int rez;
    int option_index;
    while((rez=getopt_long(argc, argv, short_options, long_options, &option_index))!=-1)
    {
        if(flagValues.count(rez)==0)
        {
            if(rez=='?')
            {
                throwUnknownFlag("Unknown option!");
            }
            else
            {
                if(optarg)
                {
                    std::string arg(optarg);
                    flagValues[rez]=arg;
                }
                else
                    flagValues[rez]="";
            }
        }
    }
    if(argc==1)
    {
        flagValues['h']="";
    }
    else if(flagValues.count('i')==0)
    {
        std::string arg(argv[argc-1]);
        flagValues['i']=arg;
    }
}

void UserInteraction::checkRequiredFlags(std::set<int> requiredArgs)
{
    for (auto i : requiredArgs)
        if(flagValues.count(i)==0)
            throwMissingArgs("Some required arguments missed!");
}

void UserInteraction::checkExtraFlags(std::set<int> argsList)
{
    for(auto i: flagValues)
        if(argsList.count(i.first)==0)
        {
            std::cout<<"Some args will be ignored!"<<"\n";
            break;
        }
}

std::string UserInteraction::getInputPath()
{
    if(flagValues.count('i')==0)
        throwMissingArgs("No input path received!");
    return flagValues['i'];
}

std::string UserInteraction::getOutputPath()
{
    if(flagValues.count('o')==0)
        throwMissingArgs("No output path received!");
    return flagValues['o'];
}

int UserInteraction::getOption()
{
    std::set<int> mode;
    if(checkReceivedFlag(HELP_INDEX))
        mode.insert(HELP_INDEX);
    if(checkReceivedFlag(INFO_INDEX))
        mode.insert(INFO_INDEX);
    if(checkReceivedFlag(RECT_INDEX))
        mode.insert(RECT_INDEX);
    if(checkReceivedFlag(ORNAMENT_INDEX))
        mode.insert(ORNAMENT_INDEX);
    if(checkReceivedFlag(ROTATE_INDEX))
         mode.insert(ROTATE_INDEX);
    if(checkReceivedFlag(RHOMBUS_INDEX))
        mode.insert(RHOMBUS_INDEX);
    if(mode.size()==0)
        throwMissingArgs("No valid option received!");
    else if(mode.size()>1)
        throwMultipleArgsError("Too many options received!");
    return *(mode.begin());
}

int UserInteraction::checkReceivedFlag(int flagIndex)
{
    return flagValues.count(flagIndex)!=0;
}

std::string UserInteraction::getFlagValue(int flagIndex)
{
    return flagValues[flagIndex];
}

void UserInteraction::printDevInfo()
{
    std::cout<<"Course work for option 4.3, created by Vladislav Boitsov"<<std::endl;
}

void UserInteraction::printImageInfo(BmpFileHeader bmfh, BmpInfoHeader bmih)
{
    std::cout<<"Signature:\t"<<std::hex<<bmfh.signature<<" ("<<std::dec<<bmfh.signature<<")\n";
    std::cout<<"Filesize:\t"<<std::hex<<bmfh.fileSize<<" ("<<std::dec<<bmfh.fileSize<<")\n";
    std::cout<<"Reserved 1:\t"<<std::hex<<bmfh.reserved1<<" ("<<std::dec<<bmfh.reserved1<<")\n";
    std::cout<<"Reserved 2:\t"<<std::hex<<bmfh.reserved2<<" ("<<std::dec<<bmfh.reserved2<<")\n";
    std::cout<<"PixelArrOffset:\t"<<std::hex<<bmfh.pixelArrOffset<<" ("<<std::dec<<bmfh.pixelArrOffset<<")\n\n";
    std::cout<<"Header Size:\t"<<std::hex<<bmih.headerSize<<" ("<<std::dec<<bmih.headerSize<<")\n";
    std::cout<<"Width:\t\t"<<std::hex<<bmih.width<<" ("<<std::dec<<bmih.width<<")\n";
    std::cout<<"Height:\t\t"<<std::hex<<bmih.height<<" ("<<std::dec<<bmih.height<<")\n";
    std::cout<<"Planes:\t\t"<<std::hex<<bmih.planes<<" ("<<std::dec<<bmih.planes<<")\n";
    std::cout<<"Bits per Pixel:\t"<<std::hex<<bmih.bitsPerPixel<<" ("<<std::dec<<bmih.bitsPerPixel<<")\n";
    std::cout<<"Compression:\t"<<std::hex<<bmih.compression<<" ("<<std::dec<<bmih.compression<<")\n";
    std::cout<<"Image Size:\t"<<std::hex<<bmih.imageSize<<" ("<<std::dec<<bmih.imageSize<<")\n";
    std::cout<<"X Pixels per Meter:\t"<<std::hex<<bmih.xPixelsPerMeter<<" ("<<std::dec<<bmih.xPixelsPerMeter<<")\n";
    std::cout<<"Y Pixels per Meter:\t"<<std::hex<<bmih.yPixelsPerMeter<<" ("<<std::dec<<bmih.yPixelsPerMeter<<")\n";
    std::cout<<"Colors in Color Table:\t"<<std::hex<<bmih.colorsInColorTable<<" ("<<std::dec<<bmih.colorsInColorTable<<")\n";
    std::cout<<"Important Color Number:\t"<<std::hex<<bmih.importantColorCount<<" ("<<std::dec<<bmih.importantColorCount<<")\n"<<std::endl;
}

void UserInteraction::printHelp()
{
    std::cout<<"\nHello! I'm Andrea, your personal assistent UwU!\n";
    std::cout<<"Let me tell you, how to handle with this program)\n";
    std::cout<<"For proper functioning, you need to print proper flags!\n";
    std::cout<<"For all of them except of 'help', which is obviously me,\n";
    std::cout<<"You will need to set a path to the image you want to work with!\n";
    std::cout<<"For this purpose, use -i or --input or simply print path as last arument!\n\n";
    std::cout<<"Today we have these options:\n\n";
    std::cout<<"1) Getting some info about an image with --info\n\n";
    std::cout<<"For next options you will need to set a path for saving the image!\n";
    std::cout<<"Use -o or --output to do this\n\n";
    std::cout<<"2) Drawing a rectangle with --rect. Use:\n";
	std::cout<<"\t--left_up and --right_down to set points of the rectangle in 'x.y' format\n";
	std::cout<<"\t--thickness to set a thickness of the border\n";
	std::cout<<"\t--color to set border color in 'rrr.ggg.bbb' format\n";
	std::cout<<"\t--fill to set if to fill rectangle\n";
	std::cout<<"\t--fill_color to set the filling color in 'rrr.ggg.bbb' format\n\n";
    std::cout<<"3) Drawing an ornament with --ornament. Use:\n";
	std::cout<<"\t--pattent to set one of three patterns:\n";
	std::cout<<"\t'circle'. Use:\n";
	std::cout<<"\t\t--color to set the outer color in 'rrr.ggg.bbb' format\n";
	std::cout<<"\t'rectangle'. Use:\n";
	std::cout<<"\t\t--color to set the color of the ornament in 'rrr.ggg.bbb' format\n";
	std::cout<<"\t\t--thickness to set the borders thickness\n";
	std::cout<<"\t\t--count to set how many borders you want to draw\n";
	std::cout<<"\t'semicircles'. Use:\n";
	std::cout<<"\t\t--color to set the color of the ornament in 'rrr.ggg.bbb' format\n";
	std::cout<<"\t\t--thickness to set the semicircles thickness\n";
	std::cout<<"\t\t--count to set how many semicircles you want to draw\n\n";
    std::cout<<"4) Rotating a part of an image with --rotate. Use:\n";
	std::cout<<"\t--left_up and --right_down to set points of the rotation zone in 'x.y' format\n";
	std::cout<<"\t--angle to set the rotation angle. Today we support only 90, 180 and 270 deg. rotation\n\n";
    std::cout<<"Still have any questions? Use -h or --help to call me!\n\n";
    std::cout<<"Have a nice day)\n"<<std::endl;
}

void throwInvalidFormat(std::string message)
{
    std::cout<<message<<std::endl;
    exit(ARG_FORMAT_ERROR);
}

void throwUnknownFlag(std::string message)
{
    std::cout<<message<<std::endl;
    exit(UNKNOWN_FLAG_ERROR);
}

void throwMissingArgs(std::string message)
{
    std::cout<<message<<std::endl;
    exit(MISSING_ARGS_ERROR);
}

void throwMultipleArgsError(std::string message)
{
    std::cout<<message<<std::endl;
    exit(MULTIPLE_ARGS_ERROR);
}

const char* InvalidImageException::what() const noexcept
{
    return message.c_str();
}