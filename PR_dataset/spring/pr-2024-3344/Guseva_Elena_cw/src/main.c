#include "structs.h"
#include "work_with_bmp.h"
#include "functions.h"
#include "checkers.h"

void print_file_header(BitmapFileHeader header){
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:s\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
} 

void print_info_header(BitmapInfoHeader header){
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width); 
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes,header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize,header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
} 


struct {
    int rect,
    hexagon,
    copy,
    info,
    input,
    output,
    help,
    center,
    fill,
    vertex,
    thickness;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
} flags;

typedef struct copy{
    coords start, end, dest_start;
}copy;
typedef struct vertex
{
    coords upper_vertex;
    int size;
    rgb fill_color;
}vertex;

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"info", no_argument, 0, 'I'},
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},

    {"rect", no_argument, 0, 'p'},
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'd'},
    {"thickness", required_argument, 0, 't'},
    {"color", required_argument, 0, 'c'},
    {"fill", no_argument, 0, 'f'},
    {"fill_color", required_argument, 0, 'z'},

    {"hexagon", no_argument, 0, 'x'},
    {"center", required_argument, 0, 'e'}, 
    {"radius", required_argument, 0, 'r'},
    {"square_rhombus", no_argument, 0, 'q'},
    {"upper_vertex", required_argument, 0, 'w'},
    {"size", required_argument, 0, 'a'},
    {"copy", no_argument, 0, 'k'},
    {"dest_left_up", required_argument, 0, 's'},
    
    {NULL, 0, NULL, 0}
};
//BMPFile* img = readBMPFile("Airplane.bmp");                            ^
//writeBMPFile("fill.bmp", img);
int main(int argc, char** argv)
{

    BMPFile* img = NULL;

    rectangle rectangle = {0};
    hexagon hexagon = {0};
    copy cope = {0};
    vertex vertex;

    coords left_up;
    coords rigth_down;
    coords upper_vertex;
    rgb color;

    int radius = 0;
    int fill = 0;
    rgb fill_color;
    int thickness;

    flags.info = 0;
    flags.fill = 0;

    char *input_name, *output_name;
    char *short_options="kpxhIqi:u:d:t:c:f:e:r:s:o:z:w:a";
    int opt, option_index = 0;
    opterr = 0;
    while ((opt=getopt_long_only(argc, argv, short_options, long_options, &option_index)) != -1){
        //printf("%c\n", opt);
        //printf("%d\n", option_index);
        switch (opt){
            case 'i':
                bmp_namechecker(optarg);
                flags.input = 1;
                input_name = optarg;
                break;
            case 'o':
                flags.output = 1;
                output_name = optarg;
                break;
            case 'h':
                no_argschecker(argv[optind], "--help");
                flags.help = 1;
                break;
            case 'I':
                no_argschecker(argv[optind], "--info");
                flags.info = 1;
                break;
            case 'p':
                no_argschecker(argv[optind], "--rect");
                flags.rect = 1;
                break;
            case 'u':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--left_up");
                coordschecker(optarg);
                sscanf(optarg, "%d.%d", &left_up.x, &left_up.y);
                break;
            case 'd':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--right_down");
                coordschecker(optarg);
                sscanf(optarg, "%d.%d", &rigth_down.x, &rigth_down.y);
                break;
            case 't':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--thickness");
                thickchecker(optarg);
                sscanf(optarg, "%d", &thickness);
                break;
            case 'c':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--color");
                colorchecker(optarg);
                sscanf(optarg, "%hhd.%hhd.%hhd", &color.red, &color.green, &color.blue);
                break;
            case 'f':
                flags.fill = 1;
                fill = 1;    
                break;
            case 'z':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--fill_color");
                colorchecker(optarg);
                sscanf(optarg, "%hhd.%hhd.%hhd", &fill_color.red, &fill_color.green, &fill_color.blue);
                break;
            case 'x':
                no_argschecker(argv[optind], "--hexagon");
                flags.hexagon = 1;
                break;
            case 'e':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--center");
                coordschecker(optarg);
                flags.center = 1;
                sscanf(optarg, "%d.%d", &hexagon.centre.x, &hexagon.centre.y);
                break;
            case 'r':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--radius");
                thickchecker(optarg);
                sscanf(optarg, "%d", &radius);
                break;
            case 'k':
                no_argschecker(argv[optind], "--copy ");
                flags.copy = 1;
                break;
            case 's':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--dest_left_up");
                coordschecker(optarg);
                sscanf(optarg, "%d.%d", &cope.dest_start.x, &cope.dest_start.y);
                break;
            case 'q':
                no_argschecker(argv[optind], "--square_rhombus");
                flags.vertex = 1;
                break;
            case 'w':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--upper_vertex");
                coordschecker(optarg);
                sscanf(optarg, "%d.%d", &vertex.upper_vertex.x, &vertex.upper_vertex.y);
                break;
            case 'a':
                count_argscheck(argv[optind - 1], argv[optind], argv[optind + 1], "--size");
                thickchecker(optarg);
                sscanf(optarg, "%d", &vertex.size);
                break;
            default:
                printf("false");
        }

    }

    if(flags.help){
        printf("Course work for option 4.9, created by Elena Guseva.\n");
        if(!(flags.rect || flags.hexagon || flags.copy)){
            return 0;
        }
    }

    if(!flags.input){
        bmp_namechecker(argv[argc - 1]);
        input_name = argv[argc - 1];
    }

    if(!flags.output){
        output_name = "out.bmp";
    }

    nameschecker(input_name, output_name);
    img = readBMPFile(input_name);

    if(flags.info == 1){
        if(input_name){
        print_file_header(img->bmfh);
        print_info_header(img->bmih);
        } else {
        printf("Error: BMPii file not loaded.\n");
        }
    }
    

    if(flags.rect){
        rectangle.start = left_up;
        rectangle.end = rigth_down;
        rectangle.thickness = thickness;
        rectangle.color = color;
        rectangle.fill_color = fill_color;
        rectangle.filled = fill;
        drawingRectangle(rectangle, img);
    }

    if(flags.hexagon){
        hexagon.color = color;
        hexagon.fill_color = fill_color;
        hexagon.filled = fill;
        hexagon.thickness = thickness;
        hexagon.radius = radius;
        drawingHexagon(hexagon, img);
    }

    if(flags.copy){
        cope.start = left_up;
        cope.end = rigth_down;
        copy_and_paste_area(img, cope.start, cope.end, cope.dest_start);
    }

    if(flags.vertex){
        vertex.fill_color = fill_color;
        drawVertex(img, vertex.upper_vertex, vertex.size, vertex.fill_color);
    }
    
    
    writeBMPFile(output_name, img);
    


    return 0;

}
