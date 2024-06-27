#include "../header/input.h"
#include "../header/output.h"
#include "../header/removeDuplicates.h"
#include "../header/errors.h"
#include "../header/allocator.h"
#include "../header/defence.h"


int main() {
    printAuthorInfo();
    char function_id=0;
    getFuncID(&function_id);
    funcIdError(&function_id);
    if (function_id==53){
        help();
        return 0;
    }
    int sentences_number_before_changes=0;
    char* keyword="";
    if (function_id==51) {
        keyword = getKeyWord();
        keywordError(keyword);
    }
    char* keysentence="";
    if (function_id==57){
        keysentence= getKeySentence();
    }
    char* no_split_text=getText(&sentences_number_before_changes);
    errorText(no_split_text);
    char** split_text=split(no_split_text, &sentences_number_before_changes);
    rmDup(split_text, &sentences_number_before_changes);

    output(&function_id, &sentences_number_before_changes, split_text, keyword, keysentence);
    allocator(keyword, no_split_text, split_text, &sentences_number_before_changes);
    return 0;
}
