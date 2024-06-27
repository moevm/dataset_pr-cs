#include "bmp_reader.h"
#include "print_func.h"
#include "processing_bmp.h"
#include "processing_data.h"

int main(int argc, char* argv[])
{
  printf("Course work for option 5.6, created by Roman Kuznetsov.\n");
  Arguments args = get_arguments(argc, argv);
  
  if(!args.in_flag) {
    args.in_flag = 1;
    args.in_name = argv[argc - 1];
  }
  
  if (strcmp(args.in_name, args.out_name) == 0) {
    printf("The input and output file names must not be the same\n");
    exit(41);
  }
  
  BMPfile* bmp = loadBMP(args.in_name);
  
  if(args.flag_info == 1) {
    printBMPHeaders(bmp);
    writeBMP(args.out_name, bmp);
    freeBMP(bmp);
    return 0;
  }  
  
  if (args.left_up.x > args.right_down.x) {
        swap(&args.left_up.x, &args.right_down.x);
  }
  if (args.left_up.y > args.right_down.y) {
        swap(&args.left_up.y, &args.right_down.y);
  }
  
  if (args.flag_collage == 1 && args.flag_num_x == 1 && args.flag_num_y == 1) {
    if (more_zero(args.num_y) == 1 && more_zero(args.num_x) == 1) {
      writeBMP(args.out_name, bmp);
      freeBMP(bmp);
      return 0;
    } else if (more_zero(args.num_y) == 1 || more_zero(args.num_x) == 1) {
      printf("Incorrect value\nNum_y || num_x can't be less then zero\n");
      exit(43);
    } else collage(bmp, args.num_y, args.num_x);
  
  } else if (args.flag_mirror == 1 && args.flag_axis == 1 && args.flag_left_up == 1 && args.flag_right_down == 1) {
    mirror(bmp, args.axis, args.left_up, args.right_down);
  
  } else if (args.flag_center == 1 && args.flag_radius == 1 && args.flag_thickness == 1 && args.flag_color == 1) {
    drawPentagram(bmp, args.center[0], args.center[1], args.radius, args.thickness, args.color);
  
  } else if (args.flag_left_up == 1 && args.flag_right_down == 1 && args.flag_thickness == 1 && args.flag_color == 1) {
    drawRectangle(bmp, args.left_up, args.right_down, args.thickness, args.color, args.fill, args.fill_color);
  
  }else if (args.flag_rhombus == 1) {
    romb(bmp, args.color);
  
  } else {
    printf("Incorrect flag\n");
    exit(42);
  }
  writeBMP(args.out_name, bmp);
  
  freeBMP(bmp);
  return 0;
}
