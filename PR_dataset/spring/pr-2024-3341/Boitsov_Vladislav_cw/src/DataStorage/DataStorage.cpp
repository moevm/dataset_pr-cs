#include "DataStorage.h"
#include "OptionParsingConsts.h"

DataStorage::DataStorage()
{
    BmpImage mImage;
    mOption=UserInteraction::getOption();
    if(mOption!=HELP_INDEX)
    {
        mInputImagePath=UserInteraction::getInputPath();
        if(mOption!=INFO_INDEX)
            mOutputImagePath=UserInteraction::getOutputPath();
    }
}

void DataStorage::openImage()
{
    try
    {
        mImage.open(mInputImagePath);
    }
    catch(const InvalidImageException& excp)
    {
        std::cout << excp.what() << '\n';
        exit(IMG_FILE_ERROR);
    }
}

void DataStorage::saveImage()
{
    try
    {
        mImage.save(mOutputImagePath);
    }
    catch(const InvalidImageException& excp)
    {
        std::cout << excp.what() << '\n';
        exit(IMG_FILE_ERROR);
    }
}

void DataStorage::executeOption()
{
    if(mOption!=HELP_INDEX)
        openImage();
    switch(mOption)
    {
        case HELP_INDEX:
        {
            UserInteraction::printHelp();
            break;
        };
        case INFO_INDEX:
        {
            DataStorage::execInfo();
            break;
        };
        case RECT_INDEX:
        {
            DataStorage::execRect();
            break;
        };
        case ORNAMENT_INDEX:
        {
            DataStorage::execOrnament();
            break;
        };
        case ROTATE_INDEX:
        {
            DataStorage::execRotate();
            break;
        };
        case RHOMBUS_INDEX:
        {
            DataStorage::execRhombus();
            break;
        };
    };
    if(mOption!=HELP_INDEX && mOption!=INFO_INDEX)
        saveImage();
}

void DataStorage::execInfo()
{
    BmpFileHeader bmfh = mImage.getFileHeader();
    BmpInfoHeader bmih = mImage.getInfoHeader();
    UserInteraction::printImageInfo(bmfh, bmih);
}

void DataStorage::execRect()
{
    Point leftUp, rightDown;
    int thickness;
    Rgb lineColor, fillColor={0, 0, 0};
    bool isFill=false;
    UserInteraction::checkRequiredFlags({LEFT_UP_INDEX, RIGHT_DOWN_INDEX, THICKNESS_INDEX, COLOR_INDEX});
    UserInteraction::checkExtraFlags({RECT_INDEX, LEFT_UP_INDEX, RIGHT_DOWN_INDEX, THICKNESS_INDEX, FILL_INDEX, COLOR_INDEX, FILL_COLOR_INDEX, INPUT_INDEX, OUTPUT_INDEX});
    leftUp=UserInteraction::parseCoordValue(LEFT_UP_INDEX);
    rightDown=UserInteraction::parseCoordValue(RIGHT_DOWN_INDEX);
    thickness=UserInteraction::parseIntValue(THICKNESS_INDEX);
    lineColor=UserInteraction::parseColorValue(COLOR_INDEX);
    if(UserInteraction::checkReceivedFlag(FILL_INDEX)!=0)
    {
        isFill=true;
        UserInteraction::checkRequiredFlags({FILL_COLOR_INDEX});
        fillColor=UserInteraction::parseColorValue(FILL_COLOR_INDEX);
    }
    try
    {
        mImage.drawRectangle(leftUp, rightDown, thickness, lineColor, isFill, fillColor, true);
    }
    catch(const std::invalid_argument& excp)
    {
        std::cout << excp.what() << '\n';
        exit(ARG_VALUE_ERROR);
    }
}

void DataStorage::execOrnament()
{
    UserInteraction::checkRequiredFlags({PATTERN_INDEX});
    UserInteraction::checkExtraFlags({ORNAMENT_INDEX, PATTERN_INDEX, THICKNESS_INDEX, COUNT_INDEX, COLOR_INDEX, INPUT_INDEX, OUTPUT_INDEX});
    std::string pattern = UserInteraction::getFlagValue(PATTERN_INDEX);
    if(pattern == "rectangle" || pattern == "semicircles")
    {
        UserInteraction::checkRequiredFlags({THICKNESS_INDEX, COUNT_INDEX, COLOR_INDEX});
        int thickness=UserInteraction::parseIntValue(THICKNESS_INDEX);
        int count=UserInteraction::parseIntValue(COUNT_INDEX);
        Rgb color=UserInteraction::parseColorValue(COLOR_INDEX);
        try
        {
            if(pattern=="rectangle")
                mImage.rectangleOrnament(color, thickness, count);
            else
                mImage.semiCircleOrnament(color, thickness, count);
        }
        catch(const std::invalid_argument& excp)
        {
            std::cerr << excp.what() << '\n';
            exit(ARG_VALUE_ERROR);
        }
    }
    else if(pattern == "circle")
    {
        UserInteraction::checkRequiredFlags({COLOR_INDEX});
        Rgb color=UserInteraction::parseColorValue(COLOR_INDEX);
        try
        {
            mImage.circleOrnament(color);
        }
        catch(const std::invalid_argument& excp)
        {
            std::cerr << excp.what() << '\n';
            exit(ARG_VALUE_ERROR);
        } 
    }
    else
        throwUnknownFlag("Unknown ornament pattern!");
}

void DataStorage::execRotate()
{
    Point leftUp, rightDown;
    int angle;
    UserInteraction::checkRequiredFlags({LEFT_UP_INDEX, RIGHT_DOWN_INDEX, ANGLE_INDEX});
    UserInteraction::checkExtraFlags({ROTATE_INDEX, LEFT_UP_INDEX, RIGHT_DOWN_INDEX, ANGLE_INDEX, INPUT_INDEX, OUTPUT_INDEX});
    leftUp=UserInteraction::parseCoordValue(LEFT_UP_INDEX);
    rightDown=UserInteraction::parseCoordValue(RIGHT_DOWN_INDEX);
    angle=UserInteraction::parseIntValue(ANGLE_INDEX);
    try
    {
        mImage.rotate(leftUp, rightDown, angle);
    }
    catch(const std::invalid_argument& excp)
    {
        std::cerr << excp.what() << '\n';
        exit(ARG_VALUE_ERROR);
    }
}

void DataStorage::execRhombus()
{
    Point upper_vertex;
    int size=0;
    Rgb fill_color;
    UserInteraction::checkRequiredFlags({UPPER_VERTEX_INDEX, SIZE_INDEX, FILL_COLOR_INDEX});
    UserInteraction::checkExtraFlags({UPPER_VERTEX_INDEX, SIZE_INDEX, FILL_COLOR_INDEX, INPUT_INDEX, OUTPUT_INDEX});
    upper_vertex=UserInteraction::parseCoordValue(UPPER_VERTEX_INDEX);
    size=UserInteraction::parseIntValue(SIZE_INDEX);
    fill_color=UserInteraction::parseColorValue(FILL_COLOR_INDEX);
    BmpImage myImage;
    try
    {
        myImage.drawRhombus(upper_vertex, size, fill_color);
    }
    catch(const std::invalid_argument& excp)
    {
        std::cerr << excp.what() << '\n';
        exit(ARG_VALUE_ERROR);
    }
}