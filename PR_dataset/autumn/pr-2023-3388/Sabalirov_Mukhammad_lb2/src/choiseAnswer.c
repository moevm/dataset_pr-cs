#include <stdio.h>
#include "choiseAnswer.h"
#include "writeAnswer.h"
void choiceAnswer(int array[], int lenghtArray, int functionNumber){
        switch (functionNumber){
                case 0:
                        writeAnswer(indexFirstZero(array, lenghtArray));
                        break;
                case 1:
                        writeAnswer(indexLastZero(array, lenghtArray));
                        break;
                case 2:
                        writeAnswer(sumBetween(array, lenghtArray));
                        break;
                case 3:
                        writeAnswer(sumBeforeAndAfter(array, lenghtArray));
                        break;
                default:
                        writeAnswer(-1);

        }

}

