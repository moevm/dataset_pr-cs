#include "utils.h"
#include "functions.h"
#include "readwrite.h"


int
main(int argc, char* argv[]){
    printf("Course work for option 4.2, created by Kostromitin Mikhail\n");
    
    BitmapFileHeader file_header;
    BitmapInfoHeader file_info;
    Rgb** arr;

    parse_CLI(&arr, &file_header, &file_info, argc, argv);

    for (int i = 0; i < file_info.height; i++)
        free(arr[i]);
    free(arr);
    return 0;
}