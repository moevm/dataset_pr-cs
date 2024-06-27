#include "../include/image.h"

#define clip(value, min, max) ( \
    (value < min) ? min : ((value > max) ? max : value) \
)

#define min(a, b) ((a <= b) ? a : b)
#define max(a, b) ((a >  b) ? a : b)


// This function creates new Image, filled with solid color
// Note: creating empty images (filled with [0, 0, 0, 0] pixels)
//       is faster, than creating filled ones
//
// Arguments:
// img - ptr to Image to create
// width - target width of the image
// height - target height of the image
// color - color to fill image with, pass NULL to create empty Image
// status_code - ptr to variable to write status code into
//
// Return:
// Status codes should be handled with handle_error() from "errors.h"
void image_create(Image **img, uint32_t width, uint32_t height,
                  Pixel *color, int *status_code)
{
    // Allocate memory for image object
    Image *new_img = (Image *) malloc(sizeof(Image));
    if(new_img == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    // Allocate memory for image, check for errors
    Pixel** arr = (Pixel**) malloc(sizeof(Pixel*) * height);
    if(arr == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    for(uint32_t row = 0; row < height; row++)
    {
        if(color) arr[row] = (Pixel*) malloc(sizeof(Pixel) * width);
        else arr[row] = (Pixel*) calloc(width, sizeof(Pixel));
        
        if(arr[row] == NULL)
        {
            *status_code = RETCODE_MEMORY_ERROR;
            for(uint32_t i = 0; i < row; i++)
            {
                free(arr[row]);
            }
            free(arr);
            return;
        }

        if(color) 
        {
            for(uint32_t x = 0; x < width; x++)
            {
                arr[row][x] = *color;
            }
        }
    }
    new_img->arr = arr;
    new_img->height = height;
    new_img->width = width;
    *img = new_img;
    *status_code = RETCODE_OK;
}


// This function pastes Image in another Image
//
// Arguments:
// dest - ptr to *Image to paste in
// src - ptr to Image to copy
// pos_x - X position of left top corner of src in dest to paste in
// pos_x - Y position of left top corner of src in dest to paste in
void image_paste(Image **dest, Image *src, uint32_t pos_x,
                 uint32_t pos_y)
{
    // some checks for sizes
    if(pos_y >= (*dest)->height) return;
    if(pos_x >= (*dest)->width)  return;

    uint32_t y_end = min((*dest)->height, pos_y+src->height);
    uint32_t x_end = min((*dest)->width, pos_x+src->width);

    for(uint32_t y = pos_y; y < y_end; y++)
    {
        for(uint32_t x = pos_x; x < x_end; x++)
        {
            (*dest)->arr[y][x] = src->arr[y-pos_y][x-pos_x];
        }
    }
}


// This function destroys Image object
//
// Arguments:
// img - ptr to Image to destroy
void image_destroy(Image *img)
{
    for (int i = 0; i < img->height; i++) {
        free(img->arr[i]);
    }
    free(img->arr);
    free(img);
}


// This function searches for largest rectangle of "color" in picture
//
// Arguments:
// img - ptr to Image to search in
// color - color of the rectangle to search
//
// Return (as values written to ptrs):
// x0 - left top angle of the rectangle X coordinate
// y0 - left top angle of the rectangle Y coordinate
// x1 - right bottom angle of the rectangle Y coordinate
// y1 - right bottom angle of the rectangle Y coordinate
// status_code - operation status code
//
// Returned status codes should be handled with handle_error() from "errors.h"
// Note: RETCODE_ARG_ERROR means that no rectangles
//       of selected color was found
void image_find_largest_rect(Image *img, uint32_t *x0, uint32_t *y0,
                             uint32_t *x1, uint32_t *y1, Pixel color, 
                             int *status_code)
{
    // First let's convert image into array of 0 and 1
    // Where "1" means target color and "0" means any other color
    uint8_t **img_bin = (uint8_t **) malloc(sizeof(uint8_t *) * img->height);
    if(img_bin == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    for(uint32_t row = 0; row < img->height; row++)
    {
        img_bin[row] = (uint8_t *) malloc(img->width);
        if(img_bin[row] == NULL)
        {
            for(uint32_t i = 0; i < row; i++)
            {
                free(img_bin[i]);
            }
            free(img_bin);
            *status_code = RETCODE_MEMORY_ERROR;
            return;
        }
        for(uint32_t pos = 0; pos < img->width; pos++)
        {
            img_bin[row][pos] = (img->arr[row][pos].r == color.r &&
                                 img->arr[row][pos].g == color.g &&
                                 img->arr[row][pos].b == color.b &&
                                 img->arr[row][pos].a == color.a);
        }
    }
    
    // Now let's create auxiliary array
    // Rules for this array:
    // 1) First row is equal to first row of the image
    // 2) All other pixels calculated using this algorithm:
    //    - if img_bin at this point is 0, than 0
    //    - if img_bin at this point is 1, than upper pixel value + 1
    uint32_t **aux = (uint32_t **) malloc(sizeof(uint32_t *) * img->height);
    if(aux == NULL)
    {
        for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
        free(img_bin);
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    for(uint32_t row = 0; row < img->height; row++)
    {
        aux[row] = (uint32_t *) malloc(sizeof(uint32_t) * img->width);
        if(img_bin[row] == NULL)
        {
            for(uint32_t i = 0; i < row; i++) free(aux[i]);
            free(aux);
            for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
            free(img_bin);
            *status_code = RETCODE_MEMORY_ERROR;
            return;
        }
        if(row == 0)
        {
            for(uint32_t pos = 0; pos < img->width; pos++) aux[row][pos] =
                img_bin[row][pos];
        }
        else
        {
            for(uint32_t pos = 0; pos < img->width; pos++)
            {
                if(img_bin[row][pos] == 0) aux[row][pos] = 0;
                else aux[row][pos] = aux[row-1][pos] + 1;
            }
        }
    }

    uint64_t max_area = 0;
    // Now let's check every row in this aux array
    for(uint32_t row = 0; row < img->height; row++)
    {
        // Every value means "amount of colored pixels above"
        // Let's find largest rectangle starting from this row
        // and laying upper
        uint32_t rowmax_pos0 = 0;
        uint32_t rowmax_pos1 = 0;
        uint64_t rowmax_area = 0;
        uint64_t rowmax_height = 0;
        Set *heights_set = set_new();
        if(heights_set == NULL)
        {
            for(uint32_t i = 0; i < img->height; i++) free(aux[i]);
            free(aux);
            for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
            free(img_bin);
            *status_code = RETCODE_MEMORY_ERROR;
            return;
        }

        // Find all available heights
        for(uint32_t pos = 0; pos < img->width; pos++)
        {
            set_add(heights_set, aux[row][pos], status_code);
            if(*status_code != RETCODE_OK)
            {
                set_destroy(heights_set);
                for(uint32_t i = 0; i < img->height; i++) free(aux[i]);
                free(aux);
                for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
                free(img_bin);
                return;
            }
        }

        int64_t *heights_arr;
        size_t heights_len;
        set_listall(heights_set, &heights_arr, &heights_len, status_code);
        set_destroy(heights_set);
        if(*status_code != RETCODE_OK)
        {
            for(uint32_t i = 0; i < img->height; i++) free(aux[i]);
            free(aux);
            for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
            free(img_bin);
            return;
        }

        // Skip empty rows
        if(heights_len == 1 && heights_arr[0] == 0)
        {
            free(heights_arr);
            continue;
        }

        // For every height find longest sequence in heights_arr
        // every value of which is greater or equal to that height
        for(int i = 0; i < heights_len; i++)
        {
            int64_t cur_height = heights_arr[i];
            uint32_t current_seq_len = 0;
            uint32_t max_seq_len = 0;
            uint32_t max_seq_pos0 = 0;
            uint32_t max_seq_pos1 = 0;
            for(uint32_t pos = 0; pos < img->width; pos++)
            {
                if(aux[row][pos] >= cur_height)
                {
                    current_seq_len++;
                    // Check for max if reached right end of the image
                    if(pos == img->width-1 && current_seq_len > max_seq_len)
                    {
                        max_seq_len = current_seq_len;
                        max_seq_pos0 = pos - current_seq_len;
                        max_seq_pos1 = pos;
                    }
                }
                else
                {
                    // Searching max seq len
                    if(current_seq_len > max_seq_len)
                    {
                        max_seq_len = current_seq_len;
                        max_seq_pos0 = pos - current_seq_len;
                        max_seq_pos1 = pos - 1;
                    }
                    current_seq_len = 0;
                }
            }
            // Searching max area rectangle in this row
            if(max_seq_len * cur_height > rowmax_area)
            {
                rowmax_area = max_seq_len * cur_height;
                rowmax_pos0 = max_seq_pos0;
                rowmax_pos1 = max_seq_pos1;
                rowmax_height = cur_height;
            }
        }
        free(heights_arr);
        // At this point we have data about largest rectangle
        // of target color, starting from this row and going up
        // Now let's select largest area rectangle from this ones
        if(rowmax_area > max_area)
        {
            max_area = rowmax_area;
            *x0 = rowmax_pos0;
            *x1 = rowmax_pos1;
            *y0 = row - rowmax_height + 1;
            *y1 = row;
        } 
    }
    if(max_area == 0) *status_code = RETCODE_ARG_ERROR;
    else *status_code = RETCODE_OK;
    
    for(uint32_t i = 0; i < img->height; i++) free(aux[i]);
    free(aux);
    for(uint32_t i = 0; i < img->height; i++) free(img_bin[i]);
    free(img_bin);
}
