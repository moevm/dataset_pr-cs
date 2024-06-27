#pragma once

#ifndef _INFORMATION_H
#define _INFORMATION_H

#define LOCALE ""

#define VERSION L"5.15"
#define AUTHOR L"Stepan Ivanov"
#define PATTERN_OPTION_MESSAGE L"Course work for option %ls, created by %ls.\n"

#define INFO_PREFACE L"Доступные действия:"
#define INFO_ABOUT_ZERO_OPTION L"\"0\" – вывод текста после первичной обязательной обработки."
#define INFO_ABOUT_ONE_OPTION L"\"1\" - Заменить в тексте все подстроки “high noon” на “полдень” и “полночь” на “midnight”."
#define INFO_ABOUT_TWO_OPTION L"\"2\" - Найти и вывести все даты в тексте заданные в виде “ DD/MM/YYYY ” или “ YYYY-MM-DD ” в порядке возрастания этих дат."
#define INFO_ABOUT_THREE_OPTION L"\"3\" - Удалить все предложения, которые начинаются и заканчиваются на одно и то же слово."
#define INFO_ABOUT_FOUR_OPTION L"\"4\" - Для всех вхождений дат в тексте вида “<day> <month> <year>, вывести эти даты в виде “DD.MM.YYYY” и строку “Happened” если эта дата была до текущей и “Not Happened” в противном случае. Например, для даты “03 Jan 1666” вывести “03.01.1666\tHappened”."
#define INFO_ABOUT_FIVE_OPTION L"\"5\" - Вывод информации о доступных действиях."
#define INFO_ABOUT_EXIT L"\"-\" - Для выхода из программы."
#define INFO_ABOUT_INVALID_OPTION L"Такого действия не существует."

#define MESSAGE_FOR_EXIT L"Программа успешно завершена."
#define MESSAGE_FOR_INVALID_ACTION L"Несуществующее действие."

#endif // _INFORMATION_H
