/**
 * @file bmp.h
 * @brief Заголовочный файл, содержащий определения структур и классов.
 */

#pragma once

#include "operation_params.hpp"
#include "structures.hpp"
#include <cstring>
#include <fstream>

/**
 * @brief Класс для работы с изображениями в формате BMP.
 */
class BMP
{
public:
    BMPHeader header;            ///< Заголовок BMP файла.
    bool validate_header() const; ///< Проверка корректности заголовка.

    std::vector<uint8_t> pixel_data; ///< Пиксельные данные изображения.


    /**
     * @brief Конструктор класса BMP.
     * @param fileName Путь к файлу изображения.
     */
    BMP(const std::string& file_name);

    /**
     * @brief Получить информацию о изображении.
     */
    void get_info() const;
    void initialize(int32_t width, int32_t height);
    void ornament(int thickness, const RGB& color);
    /**
     * @brief Отразить изображение относительно указанной оси.
     * @param axis Ось отражения ("x" или "y").
     * @param left_up Координаты левого верхнего угла области отражения.
     * @param right_down Координаты правого нижнего угла области отражения.
     */
    void mirror(const std::string& axis, const Coordinate& left_up, const Coordinate& right_down);

    /**
     * @brief Сохранить изображение в файл.
     * @param fileName Имя файла для сохранения изображения.
     */
    void save(const std::string& fileName);

    /**
     * @brief Проверить, является ли изображение валидным.
     * @return true, если изображение валидно, иначе false.
     */
    bool is_valid() const;

    /**
     * @brief Копировать область изображения.
     * @param src_left_up Координаты левого верхнего угла исходной области.
     * @param src_right_down Координаты правого нижнего угла исходной области.
     * @param dest_left_up Координаты левого верхнего угла целевой области.
     */
    void copy(const Coordinate& src_left_up, const Coordinate& src_right_down, const Coordinate& dest_left_up);

    /**
     * @brief Заменить цвет на изображении.
     * @param old_color Старый цвет.
     * @param new_color Новый цвет.
     */
    void color_replace(const RGB& old_color, const RGB& new_color);

    /**
     * @brief Разделить изображение на части.
     * @param number_x Количество частей по горизонтали.
     * @param number_y Количество частей по вертикали.
     * @param thickness Толщина разделительных линий.
     * @param color Цвет разделительных линий.
     */
    void split(int number_x, int number_y, int thickness, const RGB& color);

    /**
     * @brief Получить цвет пикселя по координатам.
     * @param x Координата x пикселя.
     * @param y Координата y пикселя.
     * @return Цвет пикселя.
     */
    RGB get_color(int x, int y) const;

    /**
     * @brief Установить цвет пикселя по координатам.
     * @param x Координата x пикселя.
     * @param y Координата y пикселя.
     * @param newColor Новый цвет пикселя.
     */
    void set_color(int x, int y, const RGB& new_color);
};
