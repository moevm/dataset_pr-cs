#include<iostream>
#include"UserInteraction.h"
#include"DataStorage.h"

int main(int argc, char* argv[])
{
    UserInteraction::printDevInfo();
    UserInteraction::readFlags(argc, argv);
    DataStorage tempData;
    tempData.executeOption();
}