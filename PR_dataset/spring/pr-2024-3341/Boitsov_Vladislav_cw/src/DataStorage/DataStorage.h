#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>
#include "BmpImage.h"
#include "UserInteraction.h"

class DataStorage
{
private:
    std::string mInputImagePath;
    std::string mOutputImagePath;
    int mOption;
    BmpImage mImage;

    void execInfo();
    void execRect();
    void execOrnament();
    void execRotate();
    void execRhombus();
public:
    DataStorage();
    void openImage();
    void executeOption();
    void saveImage();
};

#endif