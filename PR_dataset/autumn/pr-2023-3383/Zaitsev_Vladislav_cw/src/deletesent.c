#include "deletesent.h"
void Delete_sent(char **text, int len, int ind){
        for (int i = ind; i < len - 1; i++){
                text[i] = text[i+1];
        }
}
