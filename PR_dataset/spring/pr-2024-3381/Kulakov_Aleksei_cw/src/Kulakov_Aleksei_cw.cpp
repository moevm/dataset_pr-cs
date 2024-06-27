#include <cstdint>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)
struct RGBColor {
    char r, g, b;
};
int input_param = -1;
const char* short_options = "habcd:e:f:g:j:k:l:m:i:o:zpq:r:";
const struct option long_options[] = {
    { "help", no_argument, NULL, 'h' },
    { "color_replace", no_argument, NULL, 'a' },
    { "rgbfilter", no_argument, NULL, 'b' },
    { "split", no_argument, NULL, 'c' },
    { "old_color", required_argument, NULL, 'd' },
    { "new_color", required_argument, NULL, 'e' },
    { "component_name", required_argument, NULL, 'f' },
    { "component_value", required_argument, NULL, 'g' },
    { "number_x", required_argument, NULL, 'j' },
    { "number_y", required_argument, NULL, 'k' },
    { "thickness", required_argument, NULL, 'l' },
    { "color", required_argument, NULL, 'm' },
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "info", no_argument, NULL, 'z' },
    { "outside_rect", no_argument, NULL, 'p' },
    { "left_up", required_argument, NULL, 'q' },
    { "right_down", required_argument, NULL, 'r' },
    { NULL, 0, NULL, '\0' }
};

void func_help()
{
    cout << "1) Replaces all pixels of a specified color with another color. "
            "Flag to execute this operation: `--color_replace/-a`. Functionality is determined by:\n"
            "- The color to be replaced. Flag `--old_color/-d` (the color is specified as a string `rrr.ggg.bbb`, "
            "where rrr/ggg/bbb are numbers specifying the color component. For example, `--old_color 255.0.0` sets the color to red).\n"
            "- The color to replace with. Flag `--new_color/-e` (works similarly to the `--old_color` flag).\n\n";

    cout << "2) Filters the RGB component. Flag to execute this operation: `--rgbfilter/-b`. This tool should allow "
            "setting the value of the specified component for the entire image in the range from 0 to 255. "
            "Functionality is determined by:\n"
            "- Which component needs to be changed. Flag `--component_name/-f`. Possible values are `red`, `green`, and `blue`.\n"
            "- What value it needs to be changed to. Flag `--component_value/-g`. Accepts a value as a number from 0 to 255.\n\n";

    cout << "3) Divides the image into N*M parts. Flag to execute this operation: `--split/-c`. Implementation: "
            "draw lines of a specified thickness. Functionality is determined by:\n"
            "- The number of parts along the 'Y-axis'. Flag `--number_x/-j`. Accepts a number greater than 1 as input.\n"
            "- The number of parts along the 'X-axis'. Flag `--number_y/-k`. Accepts a number greater than 1 as input.\n"
            "- The thickness of the line. Flag `--thickness/-l`. Accepts a number greater than 0 as input.\n"
            "- The color of the line. Flag `--color/-m` (the color is specified as a string `rrr.ggg.bbb`, "
            "where rrr/ggg/bbb are numbers specifying the color component. For example, `--color 255.0.0` sets the color to red).\n";
}

int set_val(char c)
{
    if (input_param == -1) {
        if (c == 'p') {
            input_param = 3;
        } else {
            input_param = c - 'a';
        }
    } else {
        return 1;
    }
    return 0;
}

int set_flag(vector<vector<string>>& vec, char c)
{
    int pos;
    if (c >= 'd' and c <= 'e') {
        pos = c - 'd';
        vec[0][pos] = optarg;
    } else if (c >= 'f' and c <= 'g') {
        pos = c - 'f';
        vec[1][pos] = optarg;
    } else if (c >= 'j' and c <= 'm') {
        pos = c - 'j';
        vec[2][pos] = optarg;
        if (c == 'm') {
            vec[3][0] = optarg;
        }
    } else {
        if (c == 'm') {
            pos = 0;
        } else {
            pos = c - 'q' + 1;
        }
        vec[3][pos] = optarg;
    }
    return 0;
}

int readBMP(string filename, vector<char>& vec, BMPHeader& header, BMPInfoHeader& infoHeader)
{
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening BMP file.";
        return 0;
    }
    file.read((char*)(&header), sizeof(header));
    file.read((char*)(&infoHeader), sizeof(infoHeader));
    if (header.type != 0x4D42) {
        cout << "Not a BMP file.";
        return 0;
    }
    if (infoHeader.bitsPerPixel != 24 or infoHeader.compression != 0) {
        cout << "Only 24-bit BMP files without compression are supported.";
        return 0;
    }
    uint64_t h = infoHeader.height, w = infoHeader.width;
    vec.resize(h * w * 3);
    file.seekg(header.offset, file.beg);
    for (uint64_t i = 0; i < h; i++) {
        file.read(vec.data() + i * w * 3, w * 3);
        file.seekg((4 - (w * 3 % 4)) % 4, ios::cur);
    }
    return 1;
}

void funcInfo(BMPHeader& header, BMPInfoHeader& infoHeader)
{
    cout << "Image width: " << infoHeader.width << endl;
    cout << "Image height: " << infoHeader.height << endl;
    cout << "Image size: " << infoHeader.size << endl;
    cout << "BitsPerPixel: " << infoHeader.bitsPerPixel << endl;
}

RGBColor* func_cheker(string s)
{
    cout << "INFUNC\n";
    int tmp = 0, k = 0, rev = 1;
    vector<char> colors(3);
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            if (k == 3) {
                return nullptr;
            }
            colors[k] = char(rev * tmp);
            cout << int(colors[k]) << " " << rev * tmp << endl;
            k++;
            tmp = 0;
        } else if (isdigit(s[i])) {
            tmp *= 10;
            tmp += s[i] - '0';
        } else if (s[i] == '-' and tmp == 0) {
            rev = 1;
        } else {
            return nullptr;
        }
    }
    if (k != 2) {
        return nullptr;
    }
    colors[2] = rev * tmp;
    cout << "ENDFUNC\n";
    RGBColor* ans = new RGBColor { colors[0], colors[1], colors[2] };
    return ans;
}

int color_replace(vector<char>& pixels, vector<string> param)
{
    RGBColor *val1 = func_cheker(param[0]), *val2 = func_cheker(param[1]);
    if (val1 == nullptr or val2 == nullptr) {
        if (val1 != nullptr)
            delete val1;
        if (val2 != nullptr)
            delete val2;
        return 1;
    }
    int k = 0;
    char ROld = val1->r, GOld = val1->g, BOld = val1->b;
    char RNew = val2->r, GNew = val2->g, BNew = val2->b;
    for (size_t i = 0; i < pixels.size(); i += 3) {
        if (pixels[i] == BOld and pixels[i + 1] == GOld and pixels[i + 2] == ROld) {
            pixels[i] = BNew;
            pixels[i + 1] = GNew;
            pixels[i + 2] = RNew;
            k++;
        }
    }
    cout << "Pixels have been changed: " << k << endl;
    delete val1;
    delete val2;
    return 0;
}

int rgbfilter(vector<char>& pixels, vector<string> param)
{
    int component = -1;
    if (param[0] == "red") {
        component = 2;
    } else if (param[0] == "green") {
        component = 1;
    } else if (param[0] == "blue") {
        component = 0;
    } else {
        return 1;
    }
    if (param[1].size() > 3) {
        return 1;
    }
    for (size_t i = 0; i < param[1].size(); i++) {
        if (!isdigit(param[1][i])) {
            return 1;
        }
    }
    for (size_t i = 0; i < pixels.size(); i += 3) {
        pixels[i + component] = stoi(param[1]);
    }
    return 0;
}

int split(vector<char>& pixels, vector<string> param, int w, int h)
{
    RGBColor* val1 = func_cheker(param[3]);
    if (val1 == nullptr) {
        return 1;
    }
    try {
        int y = stoi(param[0]), x = stoi(param[1]), t = stoi(param[2]);
        for (int i = 0; i < 3; i++) {
            for (size_t j = 0; j < param[i].size(); j++) {
                if (!isdigit(param[i][j])) {
                    throw "error";
                }
            }
        }
        char RNew = val1->r, GNew = val1->g, BNew = val1->b;
        if (x <= 1 or y <= 1 or t <= 0 or (x - 1) * (t + 1) >= w or (y - 1) * (t + 1) >= h) {
            throw "error";
        }
        for (int k = 0; k < x - 1; k++) {
            for (int i = 0; i < h; i++) {
                for (int j = ((1 + t) * k + 1) * 3; j < ((1 + t) * k + 1 + t) * 3; j += 3) {
                    pixels[i * w * 3 + j] = BNew;
                    pixels[i * w * 3 + j + 1] = GNew;
                    pixels[i * w * 3 + j + 2] = RNew;
                }
            }
        }
        for (int k = 0; k < y - 1; k++) {
            for (int i = (1 + t) * k + 1; i < (1 + t) * k + 1 + t; i++) {
                for (int j = 0; j < w * 3; j += 3) {
                    pixels[i * w * 3 + j] = BNew;
                    pixels[i * w * 3 + j + 1] = GNew;
                    pixels[i * w * 3 + j + 2] = RNew;
                }
            }
        }
    } catch (...) {
        delete val1;
        return 1;
    }
    delete val1;
    return 0;
}

int outside_rect(vector<char>& pixels, vector<string> param, int w, int h)
{
    RGBColor* val1 = func_cheker(param[0]);
    if (val1 == nullptr) {
        return 1;
    }
    char RNew = val1->r, GNew = val1->g, BNew = val1->b;
    vector<vector<int>> xy(2, vector<int>(2));
    for (int i = 1; i <= 2; i++) {
        int pos = 0;
        for (size_t j = 0; j < param[i].size(); j++) {
            if (isdigit(param[i][j])) {
                xy[i - 1][pos] *= 10;
                xy[i - 1][pos] += param[i][j] - '0';
            } else if (param[i][j] == '.') {
                pos++;
            } else {
                return 1;
            }
        }
    }
    if (xy[0][0] > xy[1][0] or xy[0][1] > xy[1][1]) {
        return 1;
    }
    for (int i = 0; i < h; i++) {
        int realY = h - i - 1;
        for (int j = 0; j < w * 3; j += 3) {
            if (realY < xy[0][1] or realY > xy[1][1] or j / 3 < xy[0][0] or j / 3 > xy[1][0]) {
                pixels[i * w * 3 + j] = BNew;
                pixels[i * w * 3 + j + 1] = GNew;
                pixels[i * w * 3 + j + 2] = RNew;
            }
        }
    }
    return 0;
}

int saveBMP(vector<char>& pixels, BMPHeader& header, BMPInfoHeader& infoHeader, string outnameBMP)
{
    ofstream file(outnameBMP, ios::binary);
    if (!file) {
        return 1;
    }
    file.write((char*)(&header), sizeof(header));
    file.write((char*)(&infoHeader), sizeof(infoHeader));
    int w = infoHeader.width, h = infoHeader.height, t = (4 - (w * 3 % 4)) % 4;
    for (int i = 0; i < h; i++) {
        file.write(&pixels[i * w * 3], w * 3);
        for (int j = 0; j < t; j++) {
            file.put(0);
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Course work for option 4.2, created by Aleksei Kulakov.\n";
    if (argc == 1) {
        func_help();
        return 0;
    }
    int rez;
    vector<vector<string>> used = { { "", "" }, { "", "" }, { "", "", "", "" }, { "", "", "" } };
    string nameBMP = "";
    string outnameBMP = "out.bmp";
    bool infoBMP = false;
    while ((rez = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        cout << char(rez) << endl;
        switch (rez) {
        case 'h': {
            if (argc > 2) {
                cout << "Invalid input! Don't use --help/-h with other flags!";
                exit(40);
            }
            func_help();
            return 0;
        };
        case 'z': {
            infoBMP = true;
            break;
        }
        case 'o': {
            if (outnameBMP != "out.bmp" or optarg == NULL) {
                cout << "Invalid input! Error flag: -o";
                exit(40);
            }
            outnameBMP = optarg;
            break;
        }
        case 'i': {
            if (nameBMP != "" or optarg == NULL) {
                cout << "Invalid input! Error flag: -i";
                exit(40);
            }
            nameBMP = optarg;
            break;
        }
        case 'a':
        case 'b':
        case 'p':
        case 'c': {
            if (set_val(rez)) {
                cout << "Invalid input! You can use only 1 flag like: -a,-b,-c and their long forms!";
                exit(40);
            }
            break;
        }
        case '?': {
            cout << "Invalid input! Unkown flag!";
            exit(40);
        };
        default:
            if (set_flag(used, rez)) {
                cout << "Invalid input! Function not choised or the argument is not entered.";
                exit(40);
            }
            break;
        };
    }

    if ((input_param != -1 or outnameBMP != "out.bmp") and infoBMP) {
        cout << "Invalid input!";
        exit(40);
    }
    if (nameBMP == outnameBMP) {
        cout << "Invalid input! Input name can't be like output name!";
        exit(40);
    }
    if (nameBMP == "") {
        nameBMP = argv[argc - 1];
    }
    vector<char> pixels;
    BMPHeader header;
    BMPInfoHeader infoHeader;
    if (!readBMP(nameBMP, pixels, header, infoHeader)) {
        exit(41);
    }
    if (infoBMP) {
        funcInfo(header, infoHeader);
        return 0;
    }
    if (input_param == -1) {
        cout << "Invalid input!";
        exit(40);
    }
    for (size_t i = 0; i < used[input_param].size(); i++) {
        if (used[input_param][i] == "") {
            cout << "Not enough arguments!";
            exit(40);
        }
    }

    if (input_param == 0) {
        if (color_replace(pixels, used[input_param])) {
            cout << "Invalid input! (Function color_replace)";
            exit(42);
        }
    } else if (input_param == 1) {
        if (rgbfilter(pixels, used[input_param])) {
            cout << "Invalid input! (Function rgbfilter)";
            exit(42);
        }
    } else if (input_param == 2) {
        if (split(pixels, used[input_param], infoHeader.width, infoHeader.height)) {
            cout << "Invalid input! (Function split)";
            exit(42);
        }
    } else {
        if (outside_rect(pixels, used[input_param], infoHeader.width, infoHeader.height)) {
            cout << "Invalid input! (Function outside_rect)";
            exit(42);
        }
    }
    if (saveBMP(pixels, header, infoHeader, outnameBMP)) {
        cout << "Failed to save BMP!";
        exit(43);
    }
    cout << "Work successfully done!";
}