#include "structs.h"
#include "image_bmp.h"
#include "input.h"

int main(int argc, char *argv[])
{
    cout << "Course work for option 5.3, created by Petr Korshunov" << endl;

    Config config = get_config(argc, argv);

    if (!config.name_in_in)
    {
        config.name_in_in = 1;
        config.name_in = argv[argc - 1];
    }

    if (argc == 1)
    {
        print_usage();
        return 0;
    }

    if (config.name_in == config.name_out)
    {
        cout << "Error in main: input and output file names cannot be the same" << endl;
        exit(41);
    }

    if (config.name_in_in)
    {
        Image img(config.name_in);

        if (config.info == 1)
        {
            img.printFileHeader();
            img.printInfoHeader();
            return 0;
        }
        else if (config.rgb_filter && config.rgb_name_in && config.rgb_val_in)
        {
            img.rgbfilter(config.rgb_name, config.rgb_val);
        }
        else if (config.square && config.sq_color_in && config.sq_side_in && config.sq_thickness_in && config.sq_lu_in)
        {
            img.draw_square(config.sq_lu[0], config.sq_lu[1], config.sq_side, config.sq_color, config.sq_thickness, config.sq_fill, config.sq_fill_color);
        }
        else if (config.exchange && config.ex_lu_in && config.ex_rd_in && config.ex_type_in)
        {
            img.exchange(config.ex_lu, config.ex_rd, config.ex_type);
        }
        else if (config.frequent && config.freq_color_in)
        {
            img.swap_frequent(config.freq_color);
        }else if (config.outside)
		{
			img.outside_ornament(config.outside_thickness, config.outside_color);
		}
		img.write_bmp(config.name_out);
    }
    else
    {
        cout << "Error in parsing arguments: --input argument does not exist" << endl;
        exit(41);
    }
    return 0;
}