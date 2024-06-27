#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sent_before=0;
    int sent_after;
    int len_sent=0;
    int sent_555=0;
    int fl=0;
    char **outpt=malloc(sizeof(char*));
    char *sent=malloc(sizeof(char));
    char symbol;

    while(symbol!='!')
    {
        symbol=getchar();
        
        if((symbol=='\n')||((symbol=='\t')&&(len_sent==0))||((symbol==' ')&&(len_sent==0)))
        {
            continue;
        }
        
        len_sent++;
        sent=realloc(sent, sizeof(char)*len_sent);
        sent[len_sent-1]=symbol;

        if((len_sent>=4)&&((sent[len_sent-2]=='5')&&(sent[len_sent-3]=='5')&&(sent[len_sent-4]=='5')))
        {
            if(((sent[len_sent-1]==' ')||(sent[len_sent-1]=='.')||(sent[len_sent-1] == ';')||(sent[len_sent-1]=='?')||(sent[len_sent-1]=='!'))&&((len_sent==4)||(sent[len_sent-5]==' ')))
            {
                fl=1;
            }
        }
        
        if((symbol=='.')||(symbol==';')||(symbol=='?')||(symbol=='!'))
        {
            sent_before+=1;
            
            if(fl==1)
            {
                sent_555++;
            } 
            else
            {
                sent_after=sent_before-sent_555;
                outpt=realloc(outpt, sizeof(char*)*sent_after);
                outpt[sent_after-1]=malloc(sizeof(char)*(len_sent+1));
                for(int i=0; i<len_sent; i++)
                {
                    outpt[sent_after-1][i]=sent[i];
                }
                outpt[sent_after-1][len_sent]='\0';
            }
            
            free(sent);
            sent=malloc(sizeof(char));
            len_sent=0;
            fl=0;
        }
    }

    for(int i=0; i<sent_after; i++)
    {
        printf("%s\n", outpt[i]);
        free(outpt[i]);
    }
    
    sent_before--;
    sent_after--;
    printf("Количество предложений до %d и количество предложений после %d",sent_before,sent_after);
    free(outpt);
    free(sent);
    return 0;
}