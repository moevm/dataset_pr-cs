/**
 * @file operation_params.h
 * @brief Заголовочный файл, содержащий определения структур и классов.
 */

#pragma once

#include "structures.hpp"
#include <getopt.h>
#include <vector>

#include <cstring>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>
/**
 * @brief Парсинг командной строки и создание объекта Operations.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк, содержащих аргументы командной строки.
 * @return Operations объект, содержащий параметры операции.
 */
Operations parse_command_line(int argc, char* argv[]);

/**
 * @brief Парсинг строки с числами, разделенными пробелами.
 *
 * @param str Строка, содержащая числа, разделенные пробелами.
 * @return Вектор целых чисел, полученных из строки.
 */
std::vector<int> parse_values(const std::string& str);

/**
 * @brief Парсинг строки с RGB-значением цвета.
 *
 * @param str Строка, содержащая RGB-значение цвета в формате "R,G,B".
 * @return Структура RGB, представляющая цвет.
 */
RGB parse_RGB(const std::string& str);

/**
 * @brief Отображение справки о возможных параметрах командной строки.
 */
void display_help();
