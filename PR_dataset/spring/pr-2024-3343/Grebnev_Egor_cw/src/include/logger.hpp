/**
 * @file logger.h
 * @brief Заголовочный файл, содержащий определения структур и классов.
 */
#pragma once

#include <iostream> // Include <iostream> for std::ostream
#include <string>

// Enum для цветов
enum class Color
{
    RED,     /**< Красный цвет */
    GREEN,   /**< Зеленый цвет */
    YELLOW,  /**< Желтый цвет */
    BLUE,    /**< Синий цвет */
    MAGENTA, /**< Пурпурный цвет */
    CYAN,    /**< Голубой цвет */
    WHITE    /**< Белый цвет */
};

class Logger
{
private:
    static bool colors_enabled; /**< Флаг, определяющий, разрешены ли цвета в выводе. */

public:
    /**
     * @brief Конструктор для класса Logger.
     * @param enable_colors Если true, разрешает использование цветов в логах, иначе - нет.
     */
    Logger(bool enable_colors);

    /**
     * @brief Устанавливает разрешение использования цветов в выводе.
     * @param enableColors Если true, разрешает использование цветов в логах, иначе - нет.
     */
    static void set_colors_enabled(bool enableColors);

    /**
     * @brief Записывает сообщение в лог с определенным цветом.
     * @param message Сообщение для записи в лог.
     * @param color Цвет сообщения (по умолчанию GREEN).
     * @param stream Поток вывода (по умолчанию std::cout).
     */
    template<typename Message>
    static void log(const Message& message, Color color = Color::GREEN, std::ostream& stream = std::cout);

    /**
     * @brief Записывает предупреждение в лог с желтым цветом.
     * @param message Сообщение предупреждения для записи в лог.
     * @param stream Поток вывода (по умолчанию std::cout).
     */
    static void warn(const std::string& message, std::ostream& stream = std::cout);

    /**
     * @brief Записывает ошибку в лог с красным цветом.
     * @param message Сообщение ошибки для записи в лог.
     * @param stream Поток вывода (по умолчанию std::cerr).
     */
    static void error(const std::string& message, std::ostream& stream = std::cerr);

    /**
     * @brief Записывает сообщение и завершает программу с заданным кодом выхода.
     * @param exitCode Код выхода.
     * @param exitMessage Сообщение о завершении программы.
     * @param stream Поток вывода (по умолчанию std::cerr).
     */
    static void exit(int exitCode, const std::string& exitMessage = "", std::ostream& stream = std::cerr);
};
