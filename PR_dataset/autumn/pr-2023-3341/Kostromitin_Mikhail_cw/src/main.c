 #include <locale.h>
 #include "structures.h"
 #include "output.h"
 #include "input.h"
 
 int main()
{
    setlocale(LC_CTYPE, "");

    Text* text = (Text*)malloc(sizeof(Text));
    text->sizeOfBuf = TEXTSIZE;
    text->size = 0;
    text->sentences = (Sentence*)malloc(sizeof(Sentence) * (text->sizeOfBuf));

    firstInputOutput(text);

    output(text);

    freeMem(&text);
    return 0;
}
