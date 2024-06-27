#include "structurs.h"
#include "functions.h"
#include "bmpfunc.h"
#include "checkers.h"

struct {
    int help,
    info,
    inverse,
    resize,
    line,
    gray,
    rhombus,
    input,
    output,
    start,
    end,
    thickness,
    leftdist,
    rightdist,
    abovedist,
    belowdist,
    left_up,
    right_down,
    color;
} flags;

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"info", no_argument, 0, 'I'},
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},

    {"inverse", no_argument, 0, 'n'},
    {"gray", no_argument, 0, 'g'},
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'd'},

    {"resize", no_argument, 0, 'z'},
    {"right", required_argument, 0, 'r'},
    {"above", required_argument, 0, 'a'},
    {"below", required_argument, 0, 'b'},
    {"left", required_argument, 0, 'l'},
    {"color", required_argument, 0, 'c'},

    {"line", no_argument, 0, 'f'},
    {"start", required_argument, 0, 's'},
    {"end", required_argument, 0, 'e'},
    {"thickness", required_argument, 0, 't'},

    {"rhombus",no_argument, 0, 'j'},
    {NULL, 0, NULL, 0}
};

int main(int argc,char** argv){

    if (argc == 1){
        description();
        return 0;
    }

    Image img;

    image_resize resizing;
    line drawing;

    coords lu_corners;
    coords rd_corners;
    Rgb colors;

    char* inputname,*outputname;
    char *short_options = "jngzfhIi:u:d:r:a:b:l:c:s:e:t:o:";
    int opt, option_index = 0;
    opterr = 0;
    while  ((opt = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch(opt) {
            case 'n':
                no_argschecker(argv[optind],argv[optind + 1],"--inverse");
                flags.inverse = 1;
                break;
            case 'g':
                no_argschecker(argv[optind],argv[optind + 1],"--gray");
                flags.gray = 1;
                break;
            case 'z':
                no_argschecker(argv[optind],argv[optind + 1],"--resize");
                flags.resize = 1;
                break;
            case 'f':
                no_argschecker(argv[optind],argv[optind + 1],"--line");
                flags.line = 1;
                break;
            case 'h':
                no_argschecker(argv[optind],argv[optind + 1],"--help");
                flags.help = 1;
                break;
            case 'I':
                no_argschecker(argv[optind],argv[optind + 1],"--info");
                flags.info = 1;
                break;
            case 'j':
                no_argschecker(argv[optind],argv[optind + 1],"--rhombus");
                flags.rhombus = 1;
                break;
            case 'i':
                inputname = optarg;
                flags.input = 1;
                break;
            case 'o':
                outputname = optarg;
                flags.output = 1;
                break;
            case 'u':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--left_up");
                coordschecker(optarg);
                sscanf(optarg,"%d.%d", &lu_corners.x,&lu_corners.y);
                flags.left_up = 1;
                break;

            case 'd':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--right_down");
                coordschecker(optarg);
                sscanf(optarg,"%d.%d", &rd_corners.x,&rd_corners.y);
                flags.right_down =1;
                break;
            
            case 'r':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--right");
                distancechecker(optarg);
                sscanf(optarg,"%d", &resizing.right_dist);
                flags.rightdist = 1;
                break;
            
            case 'l':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--left");
                distancechecker(optarg);
                sscanf(optarg,"%d", &resizing.left_dist);
                flags.leftdist = 1;
                break;
            
            case 'a':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--above");
                distancechecker(optarg);
                sscanf(optarg,"%d", &resizing.above_dist);
                flags.abovedist = 1;
                break;
            
            case 'b':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--below");
                distancechecker(optarg);
                sscanf(optarg,"%d", &resizing.below_dist);
                flags.belowdist = 1;
                break;
            
            case 'c':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--color");
                colorchecker(optarg);
                sscanf(optarg,"%hhd.%hhd.%hhd", &colors.r, &colors.g, &colors.b);
                flags.color = 1;
                break;
            
            case 't':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1],"--thickness");
                thickchecker(optarg);
                sscanf(optarg,"%d", &drawing.thickness);
                flags.thickness = 1;
                break;
            
            case 's':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--start");
                coordschecker(optarg);
                sscanf(optarg,"%d.%d", &drawing.start.x,&drawing.start.y);
                flags.start = 1;
                break;
            
            case 'e':
                count_argscheck(argv[optind-1],argv[optind],argv[optind+1], "--end");
                coordschecker(optarg);
                sscanf(optarg,"%d.%d", &drawing.end.x,&drawing.end.y);
                flags.end = 1;
                break;
            default:
                fprintf(stderr,"incorrect flag has been entered\n");
                exit(41);
        }
    }
    
    if(flags.help){
        description();
        if(!(flags.inverse || flags.gray || flags.resize || flags.line)){
            return 0;
        }
    }

    if(!flags.input){
        inputname = argv[argc - 1];
    }

    if(!flags.output){
        outputname = "out.bmp";
    }

    nameschecker(inputname,outputname);

    read_bmp(inputname,&img);
    
    if(flags.info){
        print_imageinfo(img.bmih,img.bmfh);
        return 0;
    }

    if (flags.inverse) {
        if(flags.left_up && flags.right_down){
            inverse(&img,lu_corners.x,lu_corners.y,rd_corners.x,rd_corners.y);
        }else{
            fprintf(stderr,"some argument flags are missing for inverse\n");
            exit(41);
        }
    }

    if (flags.gray) {
        if(flags.left_up && flags.right_down){
            black_white(&img,lu_corners.x,lu_corners.y,rd_corners.x,rd_corners.y);
        }else{
            fprintf(stderr,"some argument flags are missing for gray\n");
            exit(41);
        }
    }

    if (flags.resize) {
        if((flags.abovedist || flags.belowdist || flags.rightdist || flags.leftdist) && flags.color){
            if(flags.abovedist){
                resize(&img,"above",resizing.above_dist,colors);
            }

            if(flags.belowdist){
                resize(&img,"below",resizing.below_dist,colors);
            }

            if(flags.leftdist){
                resize(&img,"left",resizing.left_dist,colors);
            }

            if(flags.rightdist){
                resize(&img,"right",resizing.right_dist,colors);
            }
        }else{

            fprintf(stderr,"some argument flags are missing for resize\n");
            exit(41);
        }
    }

    if(flags.line){
        if(flags.start && flags.end && flags.thickness && flags.color){
            drawThickLine(&img,drawing.start.x,drawing.start.y,drawing.end.x,drawing.end.y,drawing.thickness,colors);
        }else{
            fprintf(stderr,"some argument flags are missing for line\n");
            exit(41);
        }
    }
    if(flags.rhombus){
        if(flags.color){
            drawRhombus(&img, colors);
        }else{
            fprintf(stderr,"some argument flags are missing for rhombus\n");
            exit(41);
        }
    }

    write_bmp(outputname,img);

    return 0;
}
