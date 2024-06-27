#include <set>
#include <string>
#include <iostream>
#ifndef STRUCTS_H
#define STRUCTS_H

using namespace std;

struct FileData {
    const char *output;
    const char *input1;
    const char *input2;

FileData() : output("out.bmp"), input1(nullptr), input2(nullptr) {}
};

struct Counter {
    int Gray;
    int Inverse;
    int Line;
    int Resize;
    int left_up;
    int right_down;
    int start;
    int end;
    int thickness;
    int color;
    int Left;
    int Right;
    int Above;
    int Below;
    int GrayInverseFunction;
    int ResizeFunction;
    int LineFunction;
    int Ornament;

    Counter() : Gray(0), Inverse(0), Line(0), left_up(0), right_down(0), start(0), end(0), thickness(0), color(0), Resize(0), Left(0), Right(0), Below(0), Above(0), GrayInverseFunction(0), ResizeFunction(0), LineFunction(0), Ornament(0){}

    void updateGrayInverseFunction(){
        GrayInverseFunction = Gray + Inverse + left_up + right_down;
    }

    void updateResizeFunction(){
        ResizeFunction = Resize + Left + Right + Above + Below;
    }
    void updateLineFunction(){
        LineFunction = Line + thickness + start + end;
    }
};

struct CorrectFlags {
    set<string> GrayInverseArg = {"-l", "--left_up", "-r", "--right_down"};
    set<string> InputOutputFlags = {"-i", "--input", "-o", "--output"};
    set<string> FlagsForColor = {"-c", "--color", "-H", "--resize", "-d", "--line"};
    set<string> LineArg = {"-s", "--start", "-e", "--end", "-t", "--thickness", "-c", "--color"}; 
    set<string> ResizeArg = {"-L", "--left", "-R", "--right", "-A", "--above", "-B", "--below", "-c", "--color"};
    set<string> grayInverseFlag = {"-g", "--gray", "-I", "--inverse"};
    set<string> LineFlag = {"-d", "--line"};
    set<string> ResizeFlag = {"-H", "--resize"};
    set<string> InputFlag = {"-i", "--input"};
    set<string> OrnamentFlag = {"-O", "--outside_ornament"};
    set<string> OrnamentArgv = {"-c", "--color", "-t", "--thickness"};

};

struct Values{
    //GrayInverse
    int leftInverseGray;
    int upInverseGray;
    int rightInverseGray;
    int downInverseGray;
    //Line
    int startX;
    int startY;
    int endX;
    int endY;
    int thickness;

    Values() : leftInverseGray(0), upInverseGray(0), rightInverseGray(0), downInverseGray(0),
            startX(0), startY(0), endX(0), endY(0), thickness(0){}
};

struct Point{
    int x;
    int y;
};

struct Tuple{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Size{
    int a;
};

#endif
