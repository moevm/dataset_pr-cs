#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "cwio/cwio.h" 
#include "structures/structures.h"
#include "processing/processing.h"

int main() {
    setlocale(LC_CTYPE, LOCALE);
    print_program_info();
    
    int cmd = get_cmd();
    switch (cmd)
    {
        case 0: {
            wchar_t * input = read_stdin();
            Text * text = Text_from_string(input);
            Text * initial_text = initial_processing(text);
            print_text(initial_text);
            break;
        }
        case 1: {
            wchar_t * input = read_stdin();
            Text * text = Text_from_string(input);
            Text * initial_text = initial_processing(text);
            print_text(process_1(initial_text));
            break;
        }
        case 2: {
            wchar_t * input = read_stdin();
            Text * text = Text_from_string(input);
            Text * initial_text = initial_processing(text);
            print_text(process_2(initial_text));
            break;
        }
            
        case 3: {
            wchar_t * input = read_stdin();
            Text * text = Text_from_string(input);
            Text * initial_text = initial_processing(text) ;
            print_text(process_3(initial_text));
            break;
        }
            
        case 4: {
            wchar_t * input = read_stdin();
            Text * text = Text_from_string(input);
            Text * initial_text = initial_processing(text);
            print_text(process_4(initial_text));
            break;
        }
            
        case 5: {
            print_program_help();
            break;
        }

        case 8: {
            wchar_t * input = read_stdin();
            Text * in = Text_from_string(input);
            Text * text = initial_processing(in);
            Text * result = process_9(text);
            print_text(result)  ;
            break;
        }
            
        default: {
            wprintf(L"Error: Unknown command [%d]\n", cmd);
            break;
        }
            
    }

    return 0;
}