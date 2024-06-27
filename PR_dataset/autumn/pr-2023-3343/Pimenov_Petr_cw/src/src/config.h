#ifndef CONFIG_H
#define CONFIG_H

#define INFO L"Course work for option 5.5, created by Petr Pimenov.\n"
#define HELP_0 L"Справка о функциях, которые реализует программа:\n"
#define HELP_1 L"0. Вывести текст после первичной обработки.\n"
#define HELP_2 L"1. Распечатать каждое слово (с учётом регистра) и количество его повторений в тексте.\n"
#define HELP_3 L"2. Заменить каждый символ, который не является буквой, на его код.\n"
#define HELP_4 L"3. Отсортировать предложения по количеству латинских букв в предложении.\n"
#define HELP_5 L"4. Удалить все предложения, которые содержат специальные символы и не содержат заглавные буквы. К специальным символам относятся: #$^\%@\n"
#define HELP_6 L"5. Вывести справку о функциях, которые реализует программа.\n"
// базовый размер расширения массива при вводе текста
#define MEMORY_BLOCK_SIZE 10
// символы, которыми может заканчиваться предложение
#define SENTENCE_ENDS L"."
// признак конца текста
#define TEXT_END L"\n\n"
// пробельные символы
#define SPACES L" \f\n\r\t\v"
// разделители между словами (если полностью, то SPACES + TEXT_END + SENTENCE_END + WORD_DELIMITERS)
#define WORD_DELIMITERS L" ,"
// специальные символы
#define SPECIAL_CHARS L"#$^\%@"

#endif
