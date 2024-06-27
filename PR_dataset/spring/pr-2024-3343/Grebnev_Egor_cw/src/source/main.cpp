/**
 * @file   main.cpp
 * @brief  Главный файл программы
 */

#include "bmp.hpp"
#include "logger.hpp"
#include "messages.hpp"
#include "operation_params.hpp"
#include "proc_function.hpp"
#define IMG_DIR ""
/**
 * @brief  Главная функция программы
 * @param  argc Количество аргументов командной строки
 * @param  argv Массив аргументов командной строки
 * @return Код возврата
 */
int main(int argc, char* argv[])
{
    Logger::log(hello_message);

    // Парсинг параметров командной строки
    Operations params = parse_command_line(argc, argv);

    const std::string input_file = IMG_DIR + params.input_file;

    // Загрузка изображения BMP
    BMP bmp(input_file);
    if (!bmp.is_valid()) { Logger::exit(1, invalid_bmp_message); }

    // Вывод информации о изображении, если соответствующий флаг установлен
    if (params.info) { bmp.get_info(); }

    // Зеркальное отображение изображения, если соответствующий флаг установлен
    if (params.mirror)
    {
        Logger::warn(mirror_warning);
        bmp.mirror(params.axis, params.left_up, params.right_down);
        Logger::log(success_message);
    }

    // Замена цветов на изображении, если соответствующий флаг установлен
    if (params.color_replace)
    {
        Logger::warn(color_replace_warning);
        bmp.color_replace(params.old_color, params.new_color);
        Logger::log(success_message);
    }

    // Разделение изображения на части, если соответствующий флаг установлен
    if (params.split)
    {
        Logger::warn(image_split_warning);
        bmp.split(params.number_x, params.number_y, params.thickness, params.line_color);
        Logger::log(success_message);
    }

    // Копирование области изображения, если соответствующий флаг установлен
    if (params.copy)
    {
        Logger::warn(image_copy_warning);
        bmp.copy(params.left_up, params.right_down, params.dest_left_up);
        Logger::log(success_message);
    }

    if (params.outside_ornament)
    {
        BMP new_bmp = ornament(bmp, params.thickness, params.line_color);
        Logger::log(success_message);
        new_bmp.save(params.output_file);
        return 0;
    }

    // Сохранение изображения
    bmp.save(params.output_file);

    return EXIT_SUCCESS;
}
