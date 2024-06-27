#ifndef USER_INTERACTION_H
#define USER_INTERACTION_H

#include <map>
#include <set>
#include <string>
#include <getopt.h>
#include "bmpStructures.h"
#include "OptionParsingConsts.h"

extern const struct option long_options[];
extern const char* short_options;

class UserInteraction
{
private:
    static inline std::map<int, std::string> flagValues={};

public:
    static std::string getInputPath();
    static std::string getOutputPath();
    static int getOption();
    static std::string getFlagValue(int flagIndex);
    static void readFlags(int argc, char** argv);
    static void checkRequiredFlags(std::set<int> requiredArgs);
    static void checkExtraFlags(std::set<int> argsList);
    static int checkReceivedFlag(int flagIndex);
    static int parseIntValue(int optind);
    static Rgb parseColorValue(int optind);
    static Point parseCoordValue(int optind);
    static void printHelp();
    static void printDevInfo();
    static void printImageInfo(BmpFileHeader bmfh, BmpInfoHeader bmih);
};

#define ARG_FORMAT_ERROR 40
#define IMG_FILE_ERROR 41
#define ARG_VALUE_ERROR 42
#define UNKNOWN_FLAG_ERROR 43
#define MISSING_ARGS_ERROR 44
#define MULTIPLE_ARGS_ERROR 45

void throwInvalidFormat(std::string message);
void throwUnknownFlag(std::string message);
void throwMissingArgs(std::string message);
void throwMultipleArgsError(std::string message);

class InvalidImageException: public std::exception
{
private:
    std::string message;
public:
    InvalidImageException(std::string message): message{message}{}
    const char* what() const noexcept override;
};

#endif