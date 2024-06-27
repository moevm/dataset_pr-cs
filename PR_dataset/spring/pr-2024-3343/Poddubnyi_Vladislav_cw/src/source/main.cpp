#include "../include/main.hpp"

int main(int argc, char *argv[]) {
    try {
        std::cout << "Course work for option 5.4, created by Vladislav Poddubnyi." << std::endl;
        Opts opts = OptsReader::getOpts(argc, argv);
        if (opts.help) {
            printHelp();
            return 0;
        }
        Picture picture(opts.input_file);
        if (opts.info) picture.printInfo();
        if (opts.gray) ImageProcessor::gray(picture, opts.left_up, opts.right_down);
        if (opts.inverse) ImageProcessor::inverse(picture, opts.left_up, opts.right_down);
        if (opts.resize) ImageProcessor::resize(picture, opts.left, opts.above, opts.right, opts.below, opts.color);
        if (opts.line) ImageProcessor::line(picture, opts.start, opts.end, opts.color, opts.thickness);
        if (opts.outside_ornament) ImageProcessor::ornament(picture, opts.thickness, opts.color);
        picture.save(opts.output_file);
    } catch (std::invalid_argument &e){
        std::cerr << "Use only nums for flags with nums!" << std::endl;
        return 40;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 40;
    }
    return 0;
}

void printHelp() {
    std::cout << "Available flags:" << std::endl;

    std::cout << "--inverse: Invert colors within a specified region." << std::endl;
    std::cout << "\t--left_up x.y: Coordinates of the top-left corner (e.g., --left_up 10.20)." << std::endl;
    std::cout << "\t--right_down x.y: Coordinates of the bottom-right corner (e.g., --right_down 50.80)." << std::endl;

    std::cout << "--gray: Convert the image to grayscale within a specified region." << std::endl;
    std::cout << "\t--left_up x.y: Coordinates of the top-left corner." << std::endl;
    std::cout << "\t--right_down x.y: Coordinates of the bottom-right corner." << std::endl;

    std::cout << "--resize: Resize the image by cropping or extending the background." << std::endl;
    std::cout << "\t--<side> <change>: Specify the change in pixels for each side (left, right, above, below)." << std::endl;
    std::cout << "\t\tPositive values for extension, negative for cropping (e.g., --left 100, --above -50)." << std::endl;
    std::cout << "\t--color rrr.ggg.bbb: Set the background color for extension (e.g., --color 255.255.255 for white)." << std::endl;

    std::cout << "--line: Draw a line segment." << std::endl;
    std::cout << "\t--start x.y: Coordinates of the starting point." << std::endl;
    std::cout << "\t--end x.y: Coordinates of the ending point." << std::endl;
    std::cout << "\t--color rrr.ggg.bbb: Set the color of the line." << std::endl;
    std::cout << "\t--thickness <value>: Set the thickness of the line (value > 0)." << std::endl;
}
