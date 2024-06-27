#include "structs.h"
#include "image_bmp.h"

void Image::set_pixel(Rgb &pix, Rgb new_pix)
{
    pix.r = new_pix.r;
    pix.g = new_pix.g;
    pix.b = new_pix.b;
}

void Image::swap_pixel(Rgb &pix, Rgb &new_pix)
{
    Rgb t = pix;

    pix.r = new_pix.r;
    pix.g = new_pix.g;
    pix.b = new_pix.b;

    new_pix.r = t.r;
    new_pix.g = t.g;
    new_pix.b = t.b;
}

	void Image::outside_ornament(int thickness, Rgb color){

		Rgb **new_img = new Rgb *[H + thickness + thickness];

		for (int i = 0; i < H + thickness + thickness; i++)
		{

			new_img[i] = new Rgb[W + thickness + thickness];

			for (int j = 0; j < W + thickness + thickness; j++)
			{
				if (check_coords(i - thickness, j - thickness))
					{
						set_pixel(new_img[i][j], arr[i - thickness][j - thickness]);
					}else{
						set_pixel(new_img[i][j], color);
					}
			}
		}
		arr = new_img;
		bmif.height = H + thickness + thickness;
		bmif.width = W + thickness + thickness;
		bmfh.filesize = bmif.height * bmif.width * sizeof(Rgb) + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
		bmif.imageSize = bmif.height * bmif.width * sizeof(Rgb);

	}

void Image::fill_zone(int i, int j, Rgb border)
{
    if (!check_coords(i, j) || arr[i][j] == border)
    {
        return;
    }
    set_pixel(arr[i][j], border);
    fill_zone(i + 1, j, border);
    fill_zone(i - 1, j, border);
    fill_zone(i, j + 1, border);
    fill_zone(i, j - 1, border);
}

void Image::plort_circle(int x, int y, int x0, int y0, Rgb new_pix, int thickness)
{
    for (int i = -thickness; i <= thickness; i++)
    {
        for (int j = -thickness; j <= thickness; j++)
        {
            if (check_coords(y0 + y + i, x0 + x + j) && abs(i) <= thickness && abs(j) <= thickness)
            {
                set_pixel(arr[y0 + y + i][x0 + x + j], new_pix);
            }
            if (check_coords(y0 + y + i, x0 - x - j) && abs(i) <= thickness && abs(j) <= thickness)
            {
                set_pixel(arr[y0 + y + i][x0 - x - j], new_pix);
            }
            if (check_coords(y0 - y - i, x0 + x + j) && abs(i) <= thickness && abs(j) <= thickness)
            {
                set_pixel(arr[y0 - y - i][x0 + x + j], new_pix);
            }
            if (check_coords(y0 - y - i, x0 - x - j) && abs(i) <= thickness && abs(j) <= thickness)
            {
                set_pixel(arr[y0 - y - i][x0 - x - j], new_pix);
            }
        }
    }
}

// Модифицированный пример из книги Г.Шилдта «Си для профессиональных программистов» (алгоритм мичнера)
void Image::draw_circle(int y0, int x0, int radius, Rgb new_pix, bool isfill /*=false*/, int thickness /*=0*/, bool fillcolor /*=false*/, Rgb new_in_pix /*={0, 0, 0}*/)
{
    if (!fillcolor)
    {
        new_in_pix = new_pix;
    }
    int x = 0;
    int y = radius;
    int delta = 3 - 2 * radius;

    if (isfill)
    {
        for (int i = y0 - radius; i <= y0 + radius; i++)
        {
            for (int j = x0 - radius; j <= x0 + radius; j++)
            {
                if (check_coords(i, j) && sqrt(pow(i - y0, 2) + pow(j - x0, 2)) <= radius)
                {
                    set_pixel(arr[i][j], new_in_pix);
                }
            }
        }
    }

    while (x < y)
    {
        plort_circle(x, y, x0, y0, new_pix, thickness);
        plort_circle(y, x, x0, y0, new_pix, thickness);

        if (delta < 0)
        {
            delta += 4 * x + 6;
        }
        else
        {
            delta += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    if (x == y)
    {
        plort_circle(x, y, x0, y0, new_pix, thickness);
    }
}

void Image::draw_line(int x1, int y1, int x2, int y2, Rgb &new_pix, int thickness /*=0*/)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    Rgb &pix = arr[y2][x2];
    if (thickness > 0)
    {
        for (int i = thickness / 2; i > 0; i--)
        {
            draw_circle(y2, x2, i, new_pix, true, 0);
        }
    }
    if (check_coords(y2, x2))
    {
        set_pixel(pix, new_pix);
    }
    while (x1 != x2 || y1 != y2)
    {
        Rgb &pix = arr[y1][x1];
        if (thickness > 0)
        {
            for (int i = thickness / 2; i > 0; i--)
            {
                draw_circle(y1, x1, i, new_pix, true, 0);
            }
        }
        if (check_coords(y1, x1))
        {
            set_pixel(pix, new_pix);
        }
        int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void Image::rgbfilter(string comp_n, int comp_v)
{
    if (comp_v < 0 || comp_v > 255)
    {
        cout << "Error in rgbfilter: comp_v is incorrect" << endl;
        exit(42);
    }

    if (comp_n != "red" && comp_n != "green" && comp_n != "blue")
    {
        cout << "Error in rgbfilter: comp_n is incorrect" << endl;
        exit(42);
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            Rgb &pix = arr[i][j];
            if (comp_n == "red" and check_coords(i, j))
            {
                set_pixel(pix, Rgb{pix.b, pix.g, (unsigned char)comp_v});
            }
            else if (comp_n == "green" and check_coords(i, j))
            {
                set_pixel(pix, Rgb{pix.b, (unsigned char)comp_v, pix.r});
            }
            else if (comp_n == "blue" and check_coords(i, j))
            {
                set_pixel(pix, Rgb{(unsigned char)comp_v, pix.g, pix.r});
            }
        }
    }
}

void Image::draw_square(int h, int w, int side_size, Rgb new_pix, int thickness /*=1*/, bool isfill /*=false*/, Rgb new_in_pix /*={0, 0, 0}*/)
{
    if (side_size <= 0)
    {
        cout << "Error in draw_square: side_size is incorrect" << endl;
        exit(43);
    }
    if (thickness <= 0)
    {
        cout << "Error in draw_square: thickness is incorrect" << endl;
        exit(43);
    }

    side_size--;

    if (isfill)
    {
        for (int i = 1; i < side_size; i++)
        {
            draw_line(w, h + i, w + side_size, h + i, new_in_pix);
            // for(int j = 1; j<side_size; j++){
            // 	set_pixel(arr[h+i][w+j], new_in_pix);
            // 	set_pixel(arr[h+side_size-i][w+side_size-j], new_in_pix);
            // }
        }
    }

    draw_line(w, h, w + side_size, h, new_pix, thickness - 1);
    draw_line(w, h, w, h + side_size, new_pix, thickness - 1);
    draw_line(w + side_size, h, w + side_size, h + side_size, new_pix, thickness - 1);
    draw_line(w, h + side_size, w + side_size, h + side_size, new_pix, thickness - 1);

    // for(int i=0, j = 0; i<=side_size; i++, j++){
    // 		set_pixel(arr[h+i][w], new_pix);
    // 		set_pixel(arr[h][w+j], new_pix);
    // 		set_pixel(arr[h+side_size-i][w+side_size], new_pix);
    // 		set_pixel(arr[h+side_size][w+side_size-j], new_pix);
    // }
}

void Image::exchange(int left_up[], int right_down[], string exchange_type)
{

    if (exchange_type != "clockwise" && exchange_type != "counterclockwise" && exchange_type != "diagonals")
    {
        cout << "Error in exchange: exchange_type is incorrect" << endl;
        exit(44);
    }

    int lu_y = left_up[0] < right_down[0] ? left_up[0] : right_down[0];
    int lu_x = left_up[1] < right_down[1] ? left_up[1] : right_down[1];
    int rd_y = left_up[0] >= right_down[0] ? left_up[0] : right_down[0];
    int rd_x = left_up[1] >= right_down[1] ? left_up[1] : right_down[1];

    int x_side = (rd_x - lu_x + (1 - (rd_x - lu_x) % 2)) / 2;
    int y_side = (rd_y - lu_y + (1 - (rd_y - lu_y) % 2)) / 2;

    // lu_y += (rd_y - lu_y + 1) % 2;
    // lu_x += (rd_x - lu_x + 1) % 2;

    Rgb **first_part = new Rgb *[y_side];
    Rgb **second_part = new Rgb *[y_side];
    Rgb **third_part = new Rgb *[y_side];
    Rgb **forth_part = new Rgb *[y_side];

    for (int i = 0; i < y_side; i++)
    {

        first_part[i] = new Rgb[x_side];
        second_part[i] = new Rgb[x_side];
        third_part[i] = new Rgb[x_side];
        forth_part[i] = new Rgb[x_side];

        for (int j = 0; j < x_side; j++)
        {
            if (check_coords(lu_y + i, lu_x + j))
            {
                first_part[i][j] = arr[lu_y + i][lu_x + j];
            }
            if (check_coords(lu_y + i, x_side + lu_x + j))
            {
                second_part[i][j] = arr[lu_y + i][x_side + lu_x + j];
            }
            if (check_coords(y_side + lu_y + i, x_side + lu_x + j))
            {
                third_part[i][j] = arr[y_side + lu_y + i][x_side + lu_x + j];
            }
            if (check_coords(y_side + lu_y + i, lu_x + j))
            {
                forth_part[i][j] = arr[y_side + lu_y + i][lu_x + j];
            }

            // if (exchange_type == "diagonals")
            // {
            // 	swap_pixel(arr[lu_y + i][lu_x + j], arr[y_side + lu_y + i][x_side + lu_x + j]);
            // 	swap_pixel(arr[lu_y + i][x_side + lu_x + j], arr[y_side + lu_y + i][lu_x + j]);
            // }
            // if (exchange_type == "clockwise")
            // {
            // 	swap_pixel(arr[lu_y + i][lu_x + j], arr[y_side + lu_y + i][lu_x + j]);
            // 	swap_pixel(arr[y_side + lu_y + i][lu_x + j], arr[y_side + lu_y + i][x_side + lu_x + j]);
            // 	swap_pixel(arr[y_side + lu_y + i][x_side + lu_x + j], arr[lu_y + i][x_side + lu_x + j]);
            // }
            // if (exchange_type == "counterclockwise") {
            // 	swap_pixel(arr[lu_y + i][lu_x + j], arr[lu_y + i][x_side + lu_x + j]);
            // 	swap_pixel(arr[lu_y + i][x_side + lu_x + j], arr[y_side + lu_y + i][x_side + lu_x + j]);
            // 	swap_pixel(arr[y_side + lu_y + i][x_side + lu_x + j], arr[y_side + lu_y + i][lu_x + j]);
            // }
        }
    }

    for (int i = 0; i < y_side; i++)
    {
        for (int j = 0; j < x_side; j++)
        {
            if (exchange_type == "diagonals")
            {
                if (check_coords(lu_y + i, x_side + lu_x + j) && check_coords(y_side + lu_y + i, lu_x + j))
                {
                    set_pixel(arr[lu_y + i][x_side + lu_x + j], forth_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, x_side + lu_x + j) && check_coords(lu_y + i, lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][x_side + lu_x + j], first_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, lu_x + j) && check_coords(lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][lu_x + j], second_part[i][j]);
                }
                if (check_coords(lu_y + i, lu_x + j) && check_coords(y_side + lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[lu_y + i][lu_x + j], third_part[i][j]);
                }
            }
            if (exchange_type == "clockwise")
            {
                if (check_coords(lu_y + i, x_side + lu_x + j) && check_coords(lu_y + i, lu_x + j))
                {
                    set_pixel(arr[lu_y + i][x_side + lu_x + j], first_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, x_side + lu_x + j) && check_coords(lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][x_side + lu_x + j], second_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, lu_x + j) && check_coords(y_side + lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][lu_x + j], third_part[i][j]);
                }
                if (check_coords(lu_y + i, lu_x + j) && check_coords(y_side + lu_y + i, lu_x + j))
                {
                    set_pixel(arr[lu_y + i][lu_x + j], forth_part[i][j]);
                }
            }
            if (exchange_type == "counterclockwise")
            {
                if (check_coords(lu_y + i, x_side + lu_x + j) && check_coords(y_side + lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[lu_y + i][x_side + lu_x + j], third_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, x_side + lu_x + j) && check_coords(y_side + lu_y + i, lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][x_side + lu_x + j], forth_part[i][j]);
                }
                if (check_coords(y_side + lu_y + i, lu_x + j) && check_coords(lu_y + i, lu_x + j))
                {
                    set_pixel(arr[y_side + lu_y + i][lu_x + j], first_part[i][j]);
                }
                if (check_coords(lu_y + i, lu_x + j) && check_coords(lu_y + i, x_side + lu_x + j))
                {
                    set_pixel(arr[lu_y + i][lu_x + j], second_part[i][j]);
                }
            }
        }
    }
}

Rgb Image::get_frequent()
{

    unordered_map<Rgb, int> color_count;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            color_count[arr[i][j]]++;
        }
    }

    Rgb frequent_color = arr[0][0];
    int max_count = 1;
    for (const auto &entry : color_count)
    {
        if (entry.second > max_count)
        {
            max_count = entry.second;
            frequent_color = entry.first;
        }
    }
    return frequent_color;
}

void Image::swap_frequent(Rgb new_pix)
{

    Rgb frequent = get_frequent();

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (check_coords(i, j) and arr[i][j] == frequent)
            {
                set_pixel(arr[i][j], new_pix);
            }
        }
    }
}