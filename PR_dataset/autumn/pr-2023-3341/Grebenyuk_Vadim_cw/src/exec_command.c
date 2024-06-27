#include "exec_command.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "regex_task.h"
#include "sorts.h"
#include "util/config.h"
#include "util/error.h"
#include "util/io.h"
#include "util/vector.h"

#define REGEX_MAX 256

static void print_help();

inline void exec_command() {
    wchar_t* regex;
    Text* text;
    int command;

    if (!wscanf(L"%d", &command))
        ERROR("Command should be a number", 2);
    getwchar();  // skip newline

    if (command == 5) {
        print_help();
        return;
    }
    switch (command) {
        case 0:
            text = read_text();
            break;
        case 1:
            regex = calloc(REGEX_MAX, sizeof(wchar_t));
            if (regex == NULL)
                ERROR("Failed to allocate regex string", 1);
            wscanf(L"%ls ", regex);
            text = read_text();
            regex_task(text, regex);
            free(regex);
            break;
        case 2:
            text = read_text();
            sort_avgwordlen(text);
            break;
        case 3:
            text = read_text();
            sort_text_all(text);
            break;
        case 4:
            text = read_text();
            for (unsigned int i = 0; i < text->len; i++)
                if (text->body[i]->words < 2 || text->body[i]->words > 5)
                    clear(&text->body[i]);
            break;
        case 9:
            text = read_text();
            sort_text_by_words(text);
            break;
        default:
            ERROR("Wrong command", 2);
            exit(0); // fix linter warning
            break;
    }
    output_text(text);
    free_text(text);
}

static void print_help() {
    puts(
        "commands:\n"
        " - 0  | remove duplicates\n"
        " - 1  | filter by regex\n"
        " - 2  | sort by avg word len\n"
        " - 3  | sort words by len (descending)\n"
        " - 4  | remove sentences with less than 2\n"
        "      | or more than 5 words\n"
        " - 5  | this message\n");
}
