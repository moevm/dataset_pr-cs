#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<stdint.h>
#include<getopt.h>
#include<cmath>

#define BMP_type 19778
#define File_error 40
#define Option_error 41
#define ArgumentFormat_error 42
#define Memory_error 43

using namespace std;

#pragma pack(push, 2)
struct BITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfSize;
	uint32_t bfReserved;
	uint32_t bfOffBits;
};
#pragma pack(pop)

struct BITMAPINFO_3 {
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

struct BITMAPINFO_4 : BITMAPINFO_3 {
	uint32_t bV4RedMask;
	uint32_t bV4GreenMask;
	uint32_t bV4BlueMask;
	uint32_t bV4AlphaMask;
	uint32_t bv4CSType;
	int32_t bV4Endpoints[9];
	uint32_t bV4GammaRed;
	uint32_t bV4GammaGreen;
	uint32_t bV4GammaBlue;
};

struct BITMAPINFO_5 : BITMAPINFO_4 {
	uint32_t bV5Intent;
	uint32_t bV5ProfileData;
	uint32_t bV5ProfileSize;
	uint32_t bV5Reserved;
};

struct Pixel{
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Pixel reverse() {
		return Pixel{blue, green, red};
	}

	Pixel inverse() {
		return Pixel{(uint8_t)(255 - red), (uint8_t)(255 - green), (uint8_t)(255 - blue)};
	}
};

struct Vector2{
	int32_t x;
	int32_t y;

	Vector2 swap() {
		return Vector2{y, x};
	}

	Vector2 operator-(Vector2 other) {
		return Vector2{x - other.x, y - other.y};
	}

	Vector2 operator+(Vector2 other) {
		return Vector2{x + other.x, y + other.y};
	}
};

void set_corners(Vector2 &lu, Vector2 &rd, Vector2 res) {
	int tmp;
	if (lu.x > rd.x) {
		tmp = lu.x;
		lu.x = rd.x;
		rd.x = tmp;
	}
	if (lu.y > rd.y) {
		tmp = lu.y;
		lu.y = rd.y;
		rd.y = tmp;
	}
	lu.x = clamp(lu.x, 0, res.x);
	lu.y = clamp(lu.y, 0, res.y);
	rd.x = clamp(rd.x, 0, res.x);
	rd.y = clamp(rd.y, 0, res.y);
}

class BmpFile {
private:
	BITMAPFILEHEADER* file_header;
	BITMAPINFO_5* file_info; 

	uint8_t alignment;
	Pixel* p_array;

public:
	BmpFile() {
		file_header = new BITMAPFILEHEADER;
		if (!file_header) {
			cerr << "Error: memory allocation error";
			throw Memory_error;
		}
		file_info = new BITMAPINFO_5;

		if (!file_info) {
			delete file_header;
			cerr << "Error: memory allocation error";
			throw Memory_error;
		}

		p_array = nullptr;
	}

	~BmpFile() {
		delete file_header;
		delete file_info;
		if (p_array != nullptr) delete[] p_array;
	}

	void read_file(string file_path) {
		ifstream input_file;
		input_file.open(file_path, ios::binary);


		if (!input_file) {
			cerr << "Error: failed to access input file " << file_path;
			throw File_error; 
		}

		// reading header

		input_file.read((char*)file_header, sizeof(BITMAPFILEHEADER));

		if (file_header->bfType != BMP_type) {
			cerr << "Error: file is not in bmp format or uses an unsupported version";
			input_file.close();
			throw File_error;
		}

		// reading info 

		input_file.read((char*)file_info, 4);

		if(file_info->biSize != 40 && file_info->biSize != 108 && file_info->biSize != 124) {
			cerr << "Error: file is not in bmp format or uses an unsupported version";
			input_file.close();
			throw File_error;
		}

		input_file.read((char*)file_info + 4, file_info->biSize - 4);

		if(file_info->biBitCount != 24 || file_info->biCompression != 0) {
			cerr << "Error: file is not in bmp format or uses an unsupported version";
			input_file.close();
			throw File_error;
		}	

		// reading pixel array

		p_array = new Pixel[file_info->biHeight * file_info->biWidth];
		if (!p_array) {
			cerr << "Error: memory allocation error";
			input_file.close();
			throw Memory_error;
		}


		alignment = (4 - ((sizeof(Pixel) * file_info->biWidth) % 4)) % 4;
		input_file.seekg(file_header->bfOffBits);	
		
		for (int i = 0; i < file_info->biHeight; i++) {	
			input_file.read((char*)(p_array + file_info->biWidth * (file_info->biHeight - i - 1)), file_info->biWidth * 3);
			input_file.seekg(alignment, ios::cur);
		}

		input_file.close();
	}

	void write_file(string file_path) {
		ofstream output_file;
		output_file.open(file_path, ios::binary);

		if (!output_file) {
			cerr << "Error: failed to access output file " << file_path;
			output_file.close();
			throw File_error;
		}

		output_file.write((char*)file_header, sizeof(BITMAPFILEHEADER));
		output_file.write((char*)file_info, file_info->biSize);

		output_file.seekp(file_header->bfOffBits);
		for (int i = 0; i < file_info->biHeight; i++) {
			output_file.write((char*)(p_array + (file_info->biWidth * (file_info->biHeight - i - 1))), file_info->biWidth * sizeof(Pixel));
			output_file.write("\0\0\0", alignment);
		}

		output_file.close();
	}

	Vector2 get_resolution() {
		return Vector2{file_info->biWidth, file_info->biHeight};
	}

	void trim(Vector2 left_up, Vector2 right_down) {
    	if (left_up.x >= right_down.x || left_up.y >= right_down.y) {
	    	cerr << "Error: unsuitable area for trim";
			throw ArgumentFormat_error;
	    }
		Vector2 new_resolution = right_down - left_up;

		Pixel* new_p_array = new Pixel[new_resolution.x * new_resolution.y];
		if (!new_p_array) {
			cerr << "Error: memory allocation error";
			throw Memory_error;
		}

		uint8_t new_alignment = (4 - ((new_resolution.x * sizeof(Pixel)) % 4)) % 4;

		Pixel white = Pixel{255, 255, 255};

		for (int y = left_up.y; y < right_down.y; y++) {
			if (y < 0 || y >= file_info->biHeight) {
				for (int x = left_up.x; x < right_down.x; x++) {
					new_p_array[(y - left_up.y) * new_resolution.x + (x - left_up.x)] = white;
				}
			}
			else {
				for (int x = left_up.x; x < right_down.x; x++) {
					if (x < 0 || x >=file_info->biWidth) {
						new_p_array[(y - left_up.y) * new_resolution.x + (x - left_up.x)] = white;
					}
					else {
						new_p_array[(y - left_up.y) * new_resolution.x + (x - left_up.x)] = p_array[y * file_info->biWidth + x];
					}
				}
			}
		}

		delete[] p_array;
		p_array = new_p_array;

		file_info->biSizeImage = (new_resolution.x * sizeof(Pixel) + new_alignment) * new_resolution.y;
		file_header->bfSize -= (file_info->biWidth * sizeof(Pixel) + alignment) * file_info->biHeight - (new_resolution.x * sizeof(Pixel) + new_alignment) * new_resolution.y;
		alignment = new_alignment;

		file_info->biWidth = new_resolution.x;
		file_info->biHeight = new_resolution.y;

	}

	Pixel get_pixel(Vector2 point) {
		if (point.x < 0 || point.x >= file_info->biWidth || point.y < 0 || point.y >= file_info->biHeight) {
			return Pixel{255, 255, 255};
		}
		return p_array[point.x + point.y * file_info->biWidth].reverse();
	}

	void set_pixel(Vector2 point, Pixel* color) {
		if (point.x < 0 || point.x >= file_info->biWidth || point.y < 0 || point.y >= file_info->biHeight) {
			return;
		}
		if (color != nullptr) {
			p_array[point.x + point.y * file_info->biWidth] = color->reverse();
		}
		else {
			p_array[point.x + point.y * file_info->biWidth] = p_array[point.x + point.y * file_info->biWidth].inverse();
		}
	}

	void print_info(string& name) {
		cout << "signature: " << file_header->bfType << endl;
		cout << "filesize: " << file_header->bfSize << endl;
		cout << "reserved: " << file_header->bfReserved << endl;
		cout << "pixelArrOffset: " << file_header->bfOffBits << endl; 
		
		cout << "headerSize: " << file_info->biSize << endl;
		cout << "width:  " << file_info->biWidth << endl;
		cout << "height: " << file_info->biHeight << endl;
		cout << "planes: " << file_info->biPlanes << endl;
		cout << "bitsPerPixel: " << file_info->biBitCount << endl;
		cout << "compression: " << file_info->biCompression << endl;
		cout << "imageSize: " << file_info->biSizeImage << endl;
		cout << "xPixelsPerMeter: " << file_info->biXPelsPerMeter << endl;
		cout << "yPixelsPerMeter: " << file_info->biYPelsPerMeter << endl;
		cout << "colorsInColorTable: " << file_info->biClrUsed << endl;
		cout << "importantColorCount: " << file_info->biClrImportant << endl;
	}

	void set_p_array(Pixel* new_p_array) {
		delete[] p_array;
		p_array = new_p_array;
	}
};

void print_help() {
	cout << "Course work for option 4.6, created by Savranskii Danila" << endl;
	cout << "ОПИСАНИЕ КОМАНД:" << endl;
	cout << "\t-h --help" << endl;
	cout << "\t\tВыводит эту справку" << endl;
	cout << "\t--info" << endl;
	cout << "\t\tВыводит информацию о входном файле" << endl;
	cout << "\t-i --input" << endl;
	cout << "\t\tФлаг для указания входного файла" << endl;
	cout << "\t-o --output" << endl;
	cout << "\t\tФлаг для указания выходного файла" << endl;
	cout << "\t-l --line" << endl;
	cout << "\t\tРисует отрезок в файле" << endl;
	cout << "\t\t\t-s --start 'x.y' - координаты начала отрезка" << endl;
	cout << "\t\t\t-e --end 'x.y' - координаты конца отрезка" << endl;
	cout << "\t\t\t--color 'rrr.ggg.bbb' - цвет отрезка" << endl;
	cout << "\t\t\t-t --thickness - толщина отрезка, на вход принимает число, больше 0" << endl;
	cout << "\t--inverse_circle" << endl;
	cout << "\t\tИнвертирует цвета в заданной окружности" << endl;
	cout << "\t\t\t-c --center 'x.y' - координаты центра окружности" << endl;
	cout << "\t\t\t-r --radius - радиус окружности, на вход принимает число больше 0" << endl;
	cout << "\t--trim" << endl;
	cout << "\t\tОбрезает изображение по заданной области" << endl;
	cout << "\t\t\t--left_up 'x.y' - координаты левого верхнего угла" << endl;
	cout << "\t\t\t--right_down 'x.y' - координаты правого нижнего угла" << endl; 
}

struct option_args {
	// general
	string name;
	string input_file;
	string output_file;

	// line
	Vector2 start;
	Vector2 end;
	Pixel color;
	int thickness;
	
	// inverse_circle
	Vector2 center;
	int radius;
	
	//trim
	Vector2 left_up;
	Vector2 right_down;

	// gamma
	float value;

	// circle pixel 
	int size;
	Pixel circle_color;
};

void opt_error(string* cur_name, const char* opt_name, const char* name) {

	if (*cur_name == "0") {
		*cur_name = name;
	}
	else if (*cur_name != name) {
		cerr << "Error: \"" << opt_name << "\" invalid option for \"" << *cur_name << "\"";
		throw Option_error;
	}
}

Vector2 to_vector(string str, const char* opt) {
	istringstream my_stream(str);
	
	int x;
	int y;
	char c;

	if (!(my_stream >> x >> c >> y) || c != '.' || my_stream >> c) {
		cerr << "Error: argument \"" << str << "\" of option " << opt << " doesn't match \"x.y\" format";
		throw ArgumentFormat_error;
	}
	return Vector2{x, y};
}

Pixel to_pixel(string str, const char* opt) {
	istringstream my_stream(str);

	int r;
	int g;
	int b;
	char c[2];

	if (!(my_stream >> r >> c[0] >> g >> c[1] >> b) || my_stream >> c[1]) {
		cerr << "Error: argument \"" << str << "\" of option " << opt << " doesn't match \"r.g.b\"(0-255) format";
		throw ArgumentFormat_error;
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || c[0] != '.' || c[1] != '.') {
		cerr << "Error: argument \"" << str << "\" of option " << opt << " doesn't match \"r.g.b\"(0-255) format";
		throw ArgumentFormat_error;
	}

	return Pixel{(uint8_t)r, (uint8_t)g, (uint8_t)b};
}

int to_int(string str, const char* opt) {
	istringstream my_stream(str);

	int n;
	char c;

	if(!(my_stream >> n) || my_stream >> c) {
		cerr << "Error: argument \"" << str << "\" of option " << opt << " isn't an integer";
		throw ArgumentFormat_error;
	}
	return n;
}

float to_float(string str, const char* opt) {
	istringstream my_stream(str);

	float n;
	char c;

	if(!(my_stream >> n) || my_stream >> c) {
		cerr << "Error: argument \"" << str << "\" of option " << opt << " isn't a flaot";
		throw ArgumentFormat_error;
	}
	return n;
}

void flag_check(bool arr[], int size, const char* name) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == false) {
			cerr << "Error: too few options for \"" << name << "\"";
			throw Option_error;
		}
	}
}

option_args handle_input(int argc, char** argv) {

	static option long_opt[] = {
	{"help"          , 0, 0, 'h'},	
	{"input"         , 1, 0, 'i'},
	{"output"        , 1, 0, 'o'},
	{"info"          , 0, 0, 'I'},

	// line
	{"line"          , 0, 0, 'L'},
	{"start"         , 1, 0, 's'},
	{"end"           , 1, 0, 'e'},
	{"color"         , 1, 0, 'C'},
	{"thickness"     , 1, 0, 't'},

	// inverse_circle
	{"inverse_circle", 0, 0, 'N'},
	{"center"        , 1, 0, 'c'},
	{"radius"        , 1, 0, 'r'},

	// trim
	{"trim"          , 0, 0, 'T'},
	{"left_up"       , 1, 0, '<'},
	{"right_down"    , 1, 0, '>'},


	// gamma 
	{"gamma", 0, 0, 'G'},
	{"value", 1, 0, 'v'},

	// circle_pixel
	{"circle_pixel", 0, 0, 'P'},
	// color
	{"size", 1, 0, 'z'},
	{"circle_color", 1, 0, '2'},
	{0, 0, 0, 0}};

	int opt;

	option_args opt_args;
	opt_args.name = "0";
	opt_args.output_file = "out.bmp";
	opt_args.input_file = "\0";

	bool line_flag[5] = {false};
	opt_args.thickness = 1;
	line_flag[3] = true;

	bool circle_flag[3] = {false};

	bool trim_flag[3] = {false};

	bool gamma_flag[2] = {false};

	bool p_circle_flag[4] = {false};

	opterr = 0;

    while((opt = getopt_long(argc, argv, "-i:o:hs:e:t:c:r:", long_opt, nullptr)) != - 1) {

    	switch(opt) {

    		// help
    		case 'h':
    			print_help();
    			throw 0;
 			// info
 			case 'I':
 				opt_error(&opt_args.name, argv[optind - 1], "info");
 				break;

 			// input
 			case 'i':
 				opt_args.input_file = optarg;
 				break;

 			// output
 			case 'o':
 				opt_args.output_file = optarg;
 				break;

 			// line
 			case 's':
 				opt_args.start = to_vector(optarg, argv[optind - 2]);
 				line_flag[0] = true;
 				break;
 			case 'e':
 				opt_args.end = to_vector(optarg, argv[optind - 2]);
 				line_flag[1] = true;
 				break;
 			case 'C':
 				opt_args.color = to_pixel(optarg, argv[optind - 2]);
 				line_flag[2] = true;
 				p_circle_flag[0] = true;
 				break;
 			case 't':
 				opt_args.thickness = to_int(optarg, argv[optind - 2]);
 				if (opt_args.thickness < 1) {
 					cerr << "Error: argument of option --thickness has to be equal to 1 or above";
 					throw ArgumentFormat_error;
 				}
 				line_flag[3] = true;
 				break;
 			case 'L':
 				opt_error(&opt_args.name, argv[optind - 1], "line");
 				line_flag[4] = true;
 				break;

 			// inverse_circle 
			case 'c':
				opt_args.center = to_vector(optarg, argv[optind - 2]);

 				circle_flag[0] = true;
 				break;
 			case 'r':
 				opt_args.radius = to_int(optarg, argv[optind - 2]);
 				if (opt_args.radius < 1) {
 					cerr << "Error: argument of option --radius has to be equal to 1 or above";
 					throw ArgumentFormat_error;
 				}
 				circle_flag[1] = true;
 				break;
 			case 'N':
 				opt_error(&opt_args.name, argv[optind - 1], "inverse_circle");
 				circle_flag[2] = true;
 				break;

 			// trim
 			case '<':
 				opt_args.left_up = to_vector(optarg, argv[optind - 2]);
 				trim_flag[0] = true;
 				break;
 			case '>':
 				opt_args.right_down = to_vector(optarg, argv[optind - 2]);
 				trim_flag[1] = true;
 				break;
 			case 'T':
 				opt_error(&opt_args.name, argv[optind - 1], "trim");
 				trim_flag[2] = true;
 				break;

 			// gamma 
 			case 'v':
 				opt_args.value = to_float(optarg, argv[optind - 2]);
 				gamma_flag[0] = true;
 				break;
 			case 'G':
 				opt_error(&opt_args.name, argv[optind - 1], "gamma");
 				gamma_flag[1] = true;
 				break;

 			// circle pixel
 			case 'z': // size
 				opt_args.size = to_int(optarg, argv[optind - 2]);
 				if (opt_args.size < 1) {
 					cerr << "Error: argument of option --size has to be equal to 1 or above";
 					throw ArgumentFormat_error;
 				}
 				p_circle_flag[1] = true;
 				break;
 			case '2': // circle color
 				opt_args.circle_color = to_pixel(optarg, argv[optind - 2]);
 				p_circle_flag[2] = true;
 				break;
 			case 'P':
 				opt_error(&opt_args.name, argv[optind - 1], "circle_pixel");
 				p_circle_flag[3] = true;
 				break;

 			case '\1':
 				if (optind == argc) {
 					opt_args.input_file = argv[optind - 1];
 				}
 				else {
 					cerr << "Error: excess argument \"" << argv[optind - 1] << '\"';
 					throw Option_error;
 				}
 				break;

 			case '?':
 				cerr << "Error: invalid option or too few arguments passed \"" << argv[optind - 1] << '\"';
 				throw Option_error;
    	}
    }
	
	if (opt_args.input_file == "\0") {
		cerr << "Error: no input file specified";
		throw ArgumentFormat_error;
	} 
    if (opt_args.input_file == opt_args.output_file) {
    	cerr << "Error: input and output files can't be the same";
    	throw ArgumentFormat_error;
    }

    if (opt_args.name == "0") {
    	cerr << "Error: option not specified";
    	throw Option_error;
    }
    else if (opt_args.name == "line") {
    	flag_check(line_flag, 5, "line");
    }
    else if (opt_args.name == "inverse_circle") {
    	flag_check(circle_flag, 3, "inverse_circle");
    }
    else if (opt_args.name == "trim") {
    	flag_check(trim_flag, 3, "trim");
    }
    else if (opt_args.name == "gamma") {
    	flag_check(gamma_flag, 2, "gamma");
    }
    else if (opt_args.name == "circle_pixel") {
    	flag_check(p_circle_flag, 4, "circle_pixel");
    }


   	return opt_args;
}

void cirlce_pixel(int size, Pixel color, Pixel circle_color, BmpFile* file) {
	Vector2 res = file->get_resolution();

	Vector2 p;
	Vector2 dp;

	Pixel p_color;

	Vector2 mn;
	Vector2 mx;

	for (p.y = 0; p.y < res.y; p.y++) {
		for (p.x = 0; p.x < res.x; p.x++) {
			p_color = file->get_pixel(p);
			if (p_color.red != color.red || p_color.green != color.green || p_color.blue != color.blue) {
				continue;
			}

			mn.x = clamp(p.x - size, 0, res.x - 1);
			mn.y = clamp(p.y - size, 0, res.y - 1);

			mx.x = clamp(p.x + size, 0, res.x - 1);
			mx.y = clamp(p.y + size, 0, res.y - 1);

			// cout << mn.x << " " << mx.x <<endl;

			for (dp.y = mn.y; dp.y <= mx.y; dp.y++) {
				for (dp.x = mn.x; dp.x <= mx.x; dp.x++) {
					p_color = file->get_pixel(dp);
					if (p_color.red != color.red || p_color.green != color.green || p_color.blue != color.blue) {
						file->set_pixel(dp, &circle_color);
					}
				}
			}
		}
	}
}

void gamma(float value, BmpFile* file) {
	Vector2 res = file->get_resolution();

	Vector2 p;

	Pixel color;
	for (p.y = 0; p.y < res.y; p.y++) {
		for (p.x = 0; p.x < res.x; p.x++) {
			color = file->get_pixel(p);

			color.red = pow((color.red / 255.0), value) * 255;
			color.blue = pow((color.blue / 255.0), value) * 255;
			color.green = pow((color.green / 255.0), value) * 255;

			file->set_pixel(p, &color);
		}
	}
}

void fill_cirle(Vector2 center, int x, float dx, int y, Pixel* color, BmpFile* file) {

	Vector2 resolution = file->get_resolution();

	if (y == 0) {
		for (int i = max(center.x - x, 0); i <= min(center.x + x, resolution.x - 1); i++) {
			file->set_pixel(Vector2{i, center.y}, color);
		}
		file->set_pixel(Vector2{center.x, center.y + x}, color);
		file->set_pixel(Vector2{center.x, center.y - x}, color);
		return;
	}

	for (int i = max(center.x - x, 0); i <= min(center.x + x, resolution.x - 1); i++) {
		file->set_pixel(Vector2{i, center.y + y}, color);
		file->set_pixel(Vector2{i, center.y - y}, color);
	}

	if (x == y) {
		return;
	}

	if (dx == false) {
		file->set_pixel(Vector2{center.x + y, center.y + x}, color);
		file->set_pixel(Vector2{center.x - y, center.y + x}, color);
		file->set_pixel(Vector2{center.x + y, center.y - x}, color);
		file->set_pixel(Vector2{center.x - y, center.y - x}, color);
	}
	else {
		for (int i = max(center.x - y, 0); i <= min(center.x + y, resolution.x - 1); i++) {
			file->set_pixel(Vector2{i, center.y + x}, color);
			file->set_pixel(Vector2{i, center.y - x}, color);
		}
	}
}

void draw_filled_circle(Vector2 center, int radius, Pixel* color, BmpFile* file) {
	int err = 3 - 2 * radius;

	int x = radius;
	int y = 0;
	bool dx = false;

	while (x >= y) {
		fill_cirle(center, x, dx, y, color, file);

		dx = false;
		y++;
		if (err > 0) {
			dx = true;
			x--;
			err += 2 * (5 - 2 * x + 2 * y);
		}
		else {
			err += 2 * (3 + 2 * y);
		}
	}
}

void draw_line(Vector2 p1, Vector2 p2, Pixel* color, int thickness, BmpFile* file) {
	bool steep = abs(p1.y - p2.y) > abs(p1.x - p2.x);

	if (steep) {
		p1 = p1.swap();
		p2 = p2.swap();
	}

	if (p1.x > p2.x) {
		Vector2 tmp = p1;
		p1 = p2;
		p2 = tmp;
	}

	Vector2 dVec = p2 - p1;
	dVec.y = abs(dVec.y);

	int y_dir;
	if (p1.y < p2.y) {
		y_dir = 1;
	}
	else {
		y_dir = -1;
	}

	int r = thickness / 2;

	int err = 2 * dVec.y - dVec.x;

	for (Vector2 p = p1; p.x < p2.x; p.x++) {
		if (steep) {
			draw_filled_circle(p.swap(), r, color, file);
		}
		else if (!steep) {
			draw_filled_circle(p, r, color, file);
		}
		
		if (err > 0) {
			p.y += y_dir;
			err -= 2 * dVec.x;
		}
		err += 2 * dVec.y;
	}
}

int main(int argc, char** argv) {

	if (argc == 1) {
		print_help();
		return 0;
	}

	option_args args;

	try {
		args = handle_input(argc, argv);

		BmpFile file;

    	file.read_file(args.input_file);

	    if (args.name == "info") {
	    	file.print_info(args.input_file);
	    	return 0;
	    }
	    else if (args.name == "line") {
	    	draw_line(args.start, args.end, &args.color, args.thickness, &file);
	    }
	    else if (args.name == "inverse_circle") {
	    	draw_filled_circle(args.center, args.radius, nullptr, &file);
	    }
	    else if (args.name == "trim") {
			set_corners(args.left_up, args.right_down, file.get_resolution());
			file.trim(args.left_up, args.right_down);
	    }
	    else if (args.name == "gamma") {
	    	gamma(args.value, &file);
	    }
	    else if (args.name == "circle_pixel") {
	    	cirlce_pixel(args.size, args.color, args.circle_color, &file);
	    }

	    file.write_file(args.output_file);
    }
    catch(int error_code) {
    	return error_code;
    }
}