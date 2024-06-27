#include "data_processing.h"

void data_processing(Args &args) {
  if (args.help) return;
//
  BmpImage image(args.input_file.c_str());
  ImageEditor editor(image);


  if (args.info) {
    image.print_info();
	return;
  }

  if (args.rectangle) {
    editor.draw_rectangle(args.left_up.first,
                          args.left_up.second,
                          args.right_down.first,
                          args.right_down.second,
                          (args.thickness + 1) / 2,
                          args.color,
                          args.fill,
                          args.fill_color);
  } else if (args.ornament) {
    editor.draw_ornament(args.pattern,
                         args.color,
                         args.thickness,
                         args.count);

  } else if (args.rotate) {
	editor.rotate(args.left_up.first,
				  args.left_up.second,
				  args.right_down.first,
				  args.right_down.second,
				  args.angle);

  } else if (args.circle) {
    editor.draw_circle(args.center.first,
                       args.center.second,
                       args.radius,
                       args.thickness,
                       args.color,
                       args.fill,
                       args.fill_color);
  } else if (args.circle_pixel){
    editor.circle_pixel(args.size, args.color, args.circle_color);
  }

  image.export_image(args.output_file.c_str());
}