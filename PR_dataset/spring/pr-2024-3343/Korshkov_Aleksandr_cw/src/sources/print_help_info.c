/* импорт библиотек с описанием структур и дополнительными операциями */
#include "../include/print_help_info.h"
#include "../include/add_operations.h"

/* вывод информации об изображении */
void print_info(char *input_file, Png *png) {
    printf("Information about PNG file \"%s\":\n", input_file);

    printf("Width: %d\n", png->width);
    printf("Height: %d\n", png->height);

    printf("Color type: %d\n", png->color_type);
    printf("Bit depth: %d\n", png->bit_depth);
    free_png(png); /* освобождение памяти */
}


/* Вывод информации о программе, как её использовать */
void print_help() {
    puts("Usage: cw [OPTIONS]\n"
         "OPTIONS:\n"
         "-h, --help - print information about flags\n"
         "--info - print information about PNG file\n"
         "-i, --input <argument> - set input file name\n"
         " -o, --output <argument> - set output file name\n"
         "--line <arguments> - set line drawing mode\n"
         "\t--start <x.y> - set start point of line\n"
         "\t--end <x.y> - set end point of line\n"
         "\t--color <r.g.b> - set color of line\n"
         "\t --thickness <argument> - set thickness of line\n"
         "--mirror <arguments> - set mirror mode\n"
         "\t --axis <argument> - set axis of mirror (must me 'x' or 'y')\n"
         "\t--left_up <x.y> - set left_up point of mirror's edge\n"
         "\t--right_up <x.y> - set right_up point of mirror's edge\n"
         "--pentagram <arguments> - set pentagram in circle mode\n"
         "\t--center <x.y> - set center point of pentagram\n"
         "\t--radius <argument> - set radius of pentagram\n"
         "\t--color <r.g.b> - set color of pentagram\n"
         "\t--thickness <argument> - set thickness of pentagram");
}