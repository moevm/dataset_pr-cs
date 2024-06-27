#include "check_line_metainfo.h"

void check_line_metainfo(rgb * color, int red_c, int green_c, int blue_c){
	if (red_c < 0 || red_c > 255 || green_c < 0 || green_c > 255 || blue_c < 0 || blue_c > 255){
		failure("Error color info");
	}
	color->r = red_c;
	color->g = green_c;
	color->b = blue_c;	
}
