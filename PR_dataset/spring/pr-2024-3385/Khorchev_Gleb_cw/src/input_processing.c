#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

#include "bmp_structs.h"
#include "define.h"
#include "help_functions.h"

void process_center_input(char* optarg, int* x_coord, int* y_coord)
{
    char* regexString_point = "^([0-9]+)\\.([0-9]+)$";
    size_t maxGroups_point = 3;
    regex_t regexCompiled_point;
    regmatch_t groupArray_point[maxGroups_point];

    if (regcomp(&regexCompiled_point, regexString_point, REG_EXTENDED))
        {
            short_error("Regex compilation porblem while processing center coords. Program will be stopped");
        }
        if (regexec(&regexCompiled_point, optarg, maxGroups_point, groupArray_point, 0) == 0)
        {
          char buf1[BUFFER];
          char buf2[BUFFER];
          for(size_t i = groupArray_point[1].rm_so; i < groupArray_point[1].rm_eo; i++)
          {
            buf1[i] = optarg[i];
          }
          buf1[groupArray_point[1].rm_eo] = '\0';
          for(size_t i = groupArray_point[2].rm_so; i < groupArray_point[2].rm_eo; i++)
          {
            buf2[i-groupArray_point[2].rm_so] = optarg[i];
          }
          buf2[groupArray_point[2].rm_eo] = '\0';
          *x_coord = atoi(buf1), *y_coord = atoi(buf2); // no need in coord check becouse of regex
        }
        else short_error("Coords for --center (-a) are not correct. Program will be stopped");
}

int process_integer_input(char* optarg, int* radius)
{
    if (check_digit(optarg))
    {
      int temp = atoi(optarg);
      if ( temp > 0)
      {
        *radius = temp;
      } else return 0;
    } else return 0;
    return 1;
}

void process_color_input(char* optarg, Rgb* color, int flag)
{
    char* regexString_color = "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$"; 
    size_t maxGroups_color =  4;
    regex_t regexCompiled_color;
    regmatch_t groupArray_color[maxGroups_color];

        if (regcomp(&regexCompiled_color, regexString_color, REG_EXTENDED))
        {
          short_error("Regex compilation porblem while processing color value. Program will be stopped");
        }
        if (regexec(&regexCompiled_color, optarg, maxGroups_color, groupArray_color, 0) == 0)
        {
          char buf1[BUFFER] = "";
          char buf2[BUFFER]= "";
          char buf3[BUFFER] = "";
          for(size_t i = groupArray_color[1].rm_so; i < groupArray_color[1].rm_eo; i++)
          {
            buf1[i] = optarg[i];
          }
          buf1[groupArray_color[1].rm_eo] = '\0';
          for(size_t i = groupArray_color[2].rm_so; i < groupArray_color[2].rm_eo; i++)
          {
            buf2[i-groupArray_color[2].rm_so] = optarg[i];
          }
            buf2[groupArray_color[2].rm_eo] = '\0'; 
          for(size_t i = groupArray_color[3].rm_so; i < groupArray_color[3].rm_eo; i++)
          {
            buf3[i-groupArray_color[3].rm_so] = optarg[i];
          }
            buf3[groupArray_color[3].rm_eo] = '\0';
          (*color).r = atoi(buf1), (*color).g = atoi(buf2), (*color).b = atoi(buf3);
          if ((*color).r >= 256 || (*color).b >= 256 || (*color).g >= 256) 
          {
            if ( flag) short_error("Values for --color (-c) are not correct. Program will be stopped");
            else short_error("Values for --fill_color (-g) are not correct. Program will be stopped");
          }
        }
        else
        { 
            if (flag) short_error("Values for --color (-c) are not correct. Program will be stopped");
            else short_error("Values for --fill_color (-g) are not correct. Program will be stopped");
        }
}

void process_component_name(char* optarg, char* component_name)
{
    if ( !strcmp("red", optarg) || !strcmp("blue", optarg) || !strcmp("green", optarg))
    {
      component_name = strncpy(component_name, optarg, sizeof(optarg));
    } else short_error("Value for --component_name (-e) is not correct, it must be 'red', 'green' or 'blue'. Program will be stopped");
}

void process_component_value(char* optarg, int* component_value)
{
    if (check_digit(optarg))
    {
      int temp = atoi(optarg);
      if ( temp >= 0 && temp < 256)
      {
        *component_value = temp;
      } else short_error("Argument for --component_value (-v)  is not correct. Program will be stopped");
    } else short_error("Argument for --component_value (-v)  is not correct. Program will be stopped");
}

int process_split_coords_input(char* optarg, int* radius)
{
    if (check_digit(optarg))
    {
      int temp = atoi(optarg);
      if ( temp > 1)
      {
        *radius = temp;
      } else return 0;
    } else return 0;
    return 1;
}

int process_file_name(char* optarg, char*output_file_name)
{
    char* regexString_bmp = "^((\\./)?[a-zA-Z0-9]+\\.[a-zA-Z0-9]+)$";
    size_t maxGroups_bmp = 1;
    regex_t regexCompiled_bmp;
    regmatch_t groupArray_bmp[maxGroups_bmp];    
    if (regcomp(&regexCompiled_bmp, regexString_bmp, REG_EXTENDED))
      {
        return 0;
        short_error("Regex compilation porblem while processing file name. Program will be stopped");
      }
      if (regexec(&regexCompiled_bmp, optarg, maxGroups_bmp, groupArray_bmp, 0) != 0)
      {
        return 0;
      }
      char str[BUFFER];
      for(size_t i=groupArray_bmp[0].rm_so; i<groupArray_bmp[0].rm_eo; i++)
      {
          str[i-groupArray_bmp[0].rm_so] = optarg[i];
      }
      str[groupArray_bmp[0].rm_eo] = '\0';
    output_file_name  = strcpy(output_file_name, str);
    output_file_name[strlen(str)+1] = '\0';
    return 1;
}

void check_for_inputfile(int argc, char** argv, char* filename, int optind)
{
  if (argc == optind) short_error("No input file. Program will be stopped");
  else if (optind == argc -1 )
  {
      process_file_name(argv[argc-1], filename);
  } else
  {
      fprintf(stderr, "Invalid input:\n");
      for(size_t i=optind; i<argc; i++)
      {
          printf("%s ", argv[i]);
      }
      fprintf(stderr, "Program will be stopped\n");
  }
}