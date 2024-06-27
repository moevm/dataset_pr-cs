#include "input.h"
#include "output.h"
#include "text_processing.h"

void free_memory(struct Text *text, int **time_and_sentence_num_array, int size);

int calculate_time(int *time_and_sentence_num_arr, time_t program_start_time);

void command_processing(int command, struct Text *text, time_t program_start_time);

void initial_processing();