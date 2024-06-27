#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define STR_SIZE 5000
#define END_OF_STRING '\0'
#define REGEX_STRING "([A-z0-9_]+)@[A-z0-9_-]+\\:[ ]*~[ ]*# (.+)"
#define INPUT_END "Fin."

char **input(size_t *length)
{
    char current_char;
    char *line = NULL;
    char **lines = NULL;
    size_t i;
    size_t input_end_length = strlen(INPUT_END);

    *length = 0;
    i = 0;
    current_char = getchar();
    while (i < input_end_length || strncmp((line + i - input_end_length), INPUT_END, input_end_length))
    {
        line = realloc(line, (i + 1) * sizeof(char));
        if (current_char == '\n')
        {
            line[i++] = END_OF_STRING;
            lines = realloc(lines, sizeof(char *) * ((*length) + 1));
            lines[(*length)++] = strdup(line);
            free(line);
            line = NULL;
            i = 0;
        }
        else
        {
            line[i++] = current_char;
        }

        current_char = getchar();
    }

    free(line);

    return lines;
}

char *regular_func(char *input_string)
{
    char *result = calloc(sizeof(char), STR_SIZE);
    int regex_result;
    int user_start, user_length;
    int user_group = 1;
    int command_group = 2;
    int group_count =3;
    int command_start, command_length;
    regex_t pattern;
    regmatch_t matches[group_count];

    regex_result = regcomp(&pattern, REGEX_STRING, REG_EXTENDED);
    regex_result = regexec(&pattern, input_string,group_count , matches, 0);
    if (regex_result == REG_NOMATCH)
        return result;

    user_start = matches[user_group].rm_so;
    user_length = matches[user_group].rm_eo - user_start;

    command_start = matches[command_group].rm_so;
    command_length = matches[command_group].rm_eo - command_start;

    sprintf(result, "%.*s - %.*s", user_length, input_string + user_start, command_length, input_string + command_start);

    regfree(&pattern);

    return result;
}

void display_func(char **command_array, size_t length)
{
    char *result;
    size_t count = 0;
    for (size_t i = 0; i < length; i++)
    {
        result = regular_func(command_array[i]);
        if (result[0] == END_OF_STRING)
            continue;
        count++;
        if (count == 1)
            printf("%s", regular_func(command_array[i]));
        else
            printf("\n%s", regular_func(command_array[i]));
        free(result);
        free(command_array[i]);
    }
}

void process_commands()
{
    size_t length;
    char **command_array = input(&length);
    display_func(command_array, length);
    free(command_array);
}

int main()
{
    process_commands();
    return 0;
}