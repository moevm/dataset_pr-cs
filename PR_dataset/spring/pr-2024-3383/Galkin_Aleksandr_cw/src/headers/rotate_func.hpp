#ifndef COURSE_WORK_ROTATE_FUNC_HPP
#define COURSE_WORK_ROTATE_FUNC_HPP

#include "additional_funcs.hpp"
#include "structuresDefinition.hpp"

Rgb **
full_right_angle(Rgb **source, std::pair<int, int> leftUp, std::pair<int, int> rightDown);

Rgb **
copy(Rgb **source, std::pair<int, int> leftUp, std::pair<int, int> rightDown, BitmapInfoHeader *info);

void
save_copy_for_check(Rgb **source, std::pair<int, int> leftUp, std::pair<int, int> rightDown, BitmapInfoHeader *info,
                    BitmapFileHeader *header);

#endif //COURSE_WORK_ROTATE_FUNC_HPP
