#include "structures.h"
#include "bmpInteraction.h"
#include "functionsInteraction.h"
#include "cliInterface.h"


int main(int argc, char *argv[]) {
    Option currentOption = getCliFlagsInfo(argc, argv);

    BMP currentBmp = readBMP(currentOption.inputFileName);
    choiceTask(&currentBmp, currentOption);
    saveBMP(currentOption.outputFileName, currentBmp);
    freeArrayOfPixels(&currentBmp);

    return 0;
}