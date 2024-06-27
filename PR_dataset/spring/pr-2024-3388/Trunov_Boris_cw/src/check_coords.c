#include "check_coords.h"

int check_coords(image_bmp * img, int * x_start, int *x_end, int * y_start, int *  y_end){
	int img_height = img->dheader.height;
	*y_start = img_height - *y_start;
	*y_end = img_height - *y_end;
	return 1;
}
