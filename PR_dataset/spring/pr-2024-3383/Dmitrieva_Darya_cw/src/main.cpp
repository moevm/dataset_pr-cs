#include "checkers.h"
#include "BitMap.h"
#include "help.h"
#include <cstring>
#include <getopt.h>
#include "structs.h"


int main(int argc, char **argv){

    char **arguments = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        size_t length = strlen(argv[i]) + 1; 
        arguments[i] = new char[length];
        strcpy(arguments[i], argv[i]);
    }

    if (strcmp(argv[0], "./cw") == 0 && !argv[1]){
        HELP();
        return 0;
    }

    const char *short_options = "IgdHhfl:r:s:e:c:t:L:R:A:B:i:o:O";
    static struct option long_options[] = {
        {"inverse", no_argument, 0, 'I'},
        {"gray", no_argument, 0, 'g'},
        {"left_up", required_argument, 0, 'l'},
        {"right_down", required_argument, 0, 'r'},
        {"line", no_argument, 0, 'd'},
        {"start", required_argument, 0, 's'},
        {"end", required_argument, 0, 'e'},
        {"color", required_argument, 0, 'c'},
        {"thickness", required_argument, 0, 't'},
        {"resize", no_argument, 0, 'H'},
        {"left", required_argument, 0, 'L'},
        {"right", required_argument, 0, 'R'},
        {"above", required_argument, 0, 'A'},
        {"below", required_argument, 0, 'B'},
        {"help", no_argument, 0, 'h'},
        {"info", no_argument, 0, 'f'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"outside_ornament", no_argument, 0, 'O'},
        {0, 0, 0, 0}
    };

    FileData FileData;

    Counter Counter;

    CorrectFlags CorrectFlags;

    Values values;

    vector<pair<string, int>> ResizePairs;

    int option_index = 0;
    int c;

    while ((c = getopt_long(argc, arguments, short_options, long_options, &option_index)) != -1) {
        switch (c) {

            //--input
            case 'i':{
                if (optind < argc){
                    if (arguments[optind][0]!='-'){
                        FileData.input2 = arguments[optind];
                    }
                }
                FileData.input1 = optarg;
                break;
            };

            //--output
            case 'o': {
                FileData.output = optarg;
                break;
            };

            default:{
                break;
            };

        }
        option_index = 0;
        c = 0;
    }



    if ((!FileData.input1 && (strcmp(argv[argc-1], "--help") != 0 || strcmp(argv[argc-1], "-h") != 0)) && argv[argc-1][0]!='-'){
        FileData.input1 = argv[argc-1];
    }

    if ((FileData.input1 && strcmp(FileData.input1, FileData.output) == 0) || (FileData.input2 && (FileData.input2, FileData.output) == 0)){
        cout<<"Ошибка: имена входного и выходного файлов не могут совпадать."<<endl;
        exit(40);
    }



    BMP bmp1;
    BMP bmp2;
    Bgr color = {0,0,0};

    optind = 1;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {

        switch (c) {
        //--color
            case 'c':{
                if (optind < argc){
                    if (CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.ResizeArg.count(argv[optind]) == 0 && CorrectFlags.LineArg.count(argv[optind]) == 0 && CorrectFlags.FlagsForColor.count(argv[optind])==0 && argv[optind]!=FileData.input1 && CorrectFlags.OrnamentFlag.count(argv[optind]) ==0 && CorrectFlags.OrnamentArgv.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -c/--color был введен неверный параметр."<<endl;
                        exit(40);
                    }
                }
                string value = optarg;
                Tuple* rgb = RgbChecker(value);
                if (!rgb){
                    cout<<"Ошибка: Неверно введен аргумент флага -c/--color."<<endl;
                    exit(40);
                    
                }
                color = {rgb->b,rgb->g,rgb->r};
                delete[] rgb;
                Counter.color+=1;
                break;
            };

        //--help
            case 'h': {
                if (argv[optind] || optind!=2){
                    cout<<"Ошибка: Для получения справки введите название исполняемого файла в командной строке, за которым следует флаг -h/--help."<<endl;
                    exit(40);
                }   
                HELP();
                return 0;
                break;
            };
        
        //info
            case 'f': {
                if (argc!=4 && argc!=3){
                    cout<<"Ошибка: Неверное количество аргументов для просмотра информации о файле."<<endl;
                    exit(40);
                }
                if (optind < argc){
                    if (argv[optind]!=FileData.input1 && CorrectFlags.InputFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: Ошибка: После флага -f/--info был введен неверный параметр."<<endl;
                        exit(40);
                    }
                }
                if (!bmp1.readBitmapFile(FileData.input1)) {
                    exit(40);
                }
                cout<<"Информация о изображении "<<FileData.input1<<endl;
                bmp1.INFO();
                return 0;
                break;
            };

        //inverse
            case 'I': {
                if (optind < argc){
                    if (CorrectFlags.GrayInverseArg.count(argv[optind]) == 0 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && argv[optind]!=FileData.input1){
                        cout<<"Ошибка: После флага -I/--inverse был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                Counter.Inverse +=1;
                break;
            };

        //gray
            case 'g': {
                if (optind < argc){
                    if (CorrectFlags.GrayInverseArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -g/--gray был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                Counter.Gray +=1;
                break;
            };

        //left_up
            case 'l': {
                if (optind < argc){
                    if (CorrectFlags.GrayInverseArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.grayInverseFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -l/--left_up был введен неверный параметр."<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Point* point = PointChecker(value);
                if (!point){
                    cout<<"Ошибка: Неверно введен аргумент флага -l/--left."<<endl;
                    exit(40);
                    
                }
                values.leftInverseGray = point->x;
                values.upInverseGray = point->y;
                delete[] point;
                Counter.left_up +=1;
                break;
            };

        //right_down
            case 'r': {
                if (optind < argc){
                    if (CorrectFlags.GrayInverseArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.grayInverseFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -r/--right_down был введен неверный параметр."<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Point* point = PointChecker(value);
                if (!point){
                    cout<<"Ошибка: Неверно введен аргумент флага -r/--right."<<endl;
                    exit(40);
                    
                }
                values.rightInverseGray = point->x;
                values.downInverseGray = point->y;
                delete[] point;
                Counter.right_down +=1;
                break;
            };

        //--line
            case 'd': {
                if (optind < argc){
                    if (CorrectFlags.LineArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -d/--line был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                Counter.Line +=1;
                break;
            };

        //--start
            case 's': {
                if (optind < argc){
                    if (CorrectFlags.LineArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.LineFlag.count(argv[optind]) == 0 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -s/--start был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Point* point = PointChecker(value);
                if (!point){
                    cout<<"Ошибка: Неверно введен аргумент флага -s/--start."<<endl;
                    exit(40);
                    
                }
                values.startX = point->x;
                values.startY = point->y;
                delete[] point;
                Counter.start +=1;
                break;
            };

        //--end
            case 'e': {
                if (optind < argc){
                    if (CorrectFlags.LineArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.LineFlag.count(argv[optind]) == 0 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -e/--end был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Point* point = PointChecker(value);
                if (!point){
                    cout<<"Ошибка: Неверно введен аргумент флага -e/--end."<<endl;
                    exit(40);
                    
                }
                values.endX = point->x;
                values.endY = point->y;
                Counter.end +=1;
                break;
            };

        //--thickness
            case 't': {
                if (optind < argc){
                    if (CorrectFlags.LineArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.LineFlag.count(argv[optind]) == 0 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.OrnamentFlag.count(argv[optind]) == 0 && CorrectFlags.OrnamentArgv.count(argv[optind]) ==0){
                        cout<<"Ошибка: После флага -t/--thickness был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                if (all_of(value.begin(), value.end(), [](unsigned char c) {
                    return isdigit(c);
                }) != 1) {
                    cout << "Ошибка: Толщина не может быть отрицательной." << endl;
                    exit(40);
                }
                values.thickness = stoi(value);
                Counter.thickness+=1;
                break;
            };

        //--resize
            case 'H': {
                if (optind < argc){
                    if (CorrectFlags.ResizeArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -H/--resize был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                Counter.Resize+=1;
                break;
            };

        //left
            case 'L': {
                if (optind < argc){
                    if (CorrectFlags.ResizeArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.ResizeFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -L/--left был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Size *size = ResizeChecker(value);
                if (!size){
                    cout<<"Ошибка: Неверно введен аругмент флага -L/--left."<<endl;
                    exit(40);
                }
                int left = size->a;
                delete[] size;
                ResizePairs.push_back(make_pair("left", left));
                break;
            };

        //right
            case 'R': {
                if (optind < argc){
                    if (CorrectFlags.ResizeArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.ResizeFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -R/--right был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Size *size = ResizeChecker(value);
                if (!size){
                    cout<<"Ошибка: Неверно введен аругмент флага -R/--right."<<endl;
                    exit(40);
                }
                int right = size->a;
                delete[] size;
                ResizePairs.push_back(make_pair("right", right));
                break;
            };

        //above
            case 'A': {
                if (optind < argc){
                    if (CorrectFlags.ResizeArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.ResizeFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -A/--above был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Size *size = ResizeChecker(value);
                if (!size){
                    cout<<"Ошибка: Неверно введен аругмент флага -A/--above."<<endl;
                    exit(40);
                }
                int above = size->a;
                delete[] size;
                ResizePairs.push_back(make_pair("above", above));
                break;
            };

        //below
            case 'B': {
                if (optind < argc){
                    if (CorrectFlags.ResizeArg.count(argv[optind]) == 0 && argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.ResizeFlag.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -B/--below был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                string value = optarg;
                Size *size = ResizeChecker(value);
                if (!size){
                    cout<<"Ошибка: Неверно введен аругмент флага -B/--below."<<endl;
                    exit(40);
                }
                int below = size->a;
                delete[] size;
                ResizePairs.push_back(make_pair("below", below));
                break;
            };

        //Ornament
            case 'O':{
                if (optind < argc){
                    if (argv[optind]!=FileData.input1 && CorrectFlags.InputOutputFlags.count(argv[optind]) == 0 && CorrectFlags.OrnamentArgv.count(argv[optind]) == 0){
                        cout<<"Ошибка: После флага -O/--outside_ornament был введен неверный параметр"<<endl;
                        exit(40);
                    }  
                }
                Counter.Ornament+=1;
                break;
            };

            default:{
                break;
            };

        }
    }
    Counter.updateGrayInverseFunction();
    Counter.updateLineFunction();
    Counter.updateResizeFunction();


    if (Counter.Inverse && Counter.left_up && Counter.right_down){
        if (!Counter.Gray && !Counter.LineFunction && !Counter.ResizeFunction &&!Counter.color){
            if (!bmp1.readBitmapFile(FileData.input1)) {
                exit(40);
            }
            bmp1.inversion(FileData.output, values.leftInverseGray, values.upInverseGray, values.rightInverseGray, values.downInverseGray);
        }
        else{
            cout<<"Ошибка: Для функции инверсии введен лишний аргумент."<<endl;
            exit(40);
        }

    }

    else if (Counter.Gray && Counter.right_down && Counter.left_up){
        if (!Counter.Inverse && !Counter.LineFunction && !Counter.ResizeFunction &&!Counter.color){
            if (!bmp1.readBitmapFile(FileData.input1)) {
                exit(40);
            }
            bmp1.black_and_white(FileData.output, values.leftInverseGray, values.upInverseGray, values.rightInverseGray, values.downInverseGray);
        }
        else{
            cout<<"Ошибка: Для функции Ч/Б введен лишний аргумент."<<endl;
            exit(40);
        }

    }

    else if(Counter.Line && Counter.color && Counter.start && Counter.end && Counter.thickness){
        if (!Counter.GrayInverseFunction && !Counter.ResizeFunction){
            if (!bmp1.readBitmapFile(FileData.input1)) {
                exit(40);
            }
            bmp1.draw_lines_with_thickness(FileData.output, values.startX, values.startY, values.endX, values.endY, values.thickness, color);
        }
        else{
            cout<<"Ошибка: Для функции рисования отрезка введен лишний аргумент."<<endl;
            exit(40);
        }

    }
    else if (Counter.Resize && ResizePairs.size()!=0){
        if (!Counter.GrayInverseFunction && !Counter.LineFunction){
            for (int i = 0; i < ResizePairs.size(); ++i) {
                string direction = ResizePairs[i].first;
                int size = ResizePairs[i].second;
                if (size > 0 && !Counter.color){
                    cout<<"Ошибка: Положительный размер требует флаг -c/--color."<<endl;
                    exit(40);
                }
                if (i == 0){
                    if (!bmp1.readBitmapFile(FileData.input1)) {
                        exit(40);
                    }
                    bmp1.resize(FileData.output, direction, size, color);
                }
                else{
                    if (!bmp1.readBitmapFile(FileData.output)) {
                        exit(40);
                    }

                    bmp1.resize(FileData.output, direction, size, color);
                }
            }
        }
        else{
            cout<<"Ошибка: Для функции обрезки/расширения введен лишний аргумент."<<endl;
            exit(40);
        }
    }
    else if (Counter.Ornament && Counter.color && Counter.thickness){
        if (!bmp1.readBitmapFile(FileData.input1)) {
            exit(40);
        }
        bmp1.ornament(FileData.output, values.thickness, color);
    }
    else{
        cout<<"Ошибка: Недостаточно аргументов для вызова функциии."<<endl;
        exit(40);
    }

    for (int i = 0; i < argc; ++i) {
        delete[] arguments[i];
    }
    
    delete[] arguments;

    return 0;
}
