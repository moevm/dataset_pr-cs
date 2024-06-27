#include <stdio.h>
#include "general_information.h"

void general_information()
{
    puts(
        "Receives input from stdin\n"
        "stdin:\n"
        "  COMMAND\n"
        "  TEXT...\n"
        "  ...\n"
        "\n"
        "List of commands:\n"
        "  0 - text output with primary processing.\n"
        "  1 - checking for the number of palindromes.\n"
        "  2 - replacing all special characters with “>special symbol<”.\n"
        "  3 - sort proposals by reucing the number of Latin letters.\n"
        "  4 - delete all applications in which Latin Cyrillic letters appear in one word.\n"
        "  5 - print help message.\n"
        "\n"
        "The text is sentences separated by a dot. Sentences are a set of words separated by a space or comma, words are a set of Latin or Cyrillic letters, numbers and other symbols other than a dot, space or comma.");
}
