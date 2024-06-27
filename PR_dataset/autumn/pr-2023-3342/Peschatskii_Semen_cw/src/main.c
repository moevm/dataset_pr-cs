#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 15
typedef struct Text Text;
typedef struct Sentence Sentence;
typedef struct Word Word;
struct Text{
    struct Sentence* sents;
    int txt_len;
};
struct Sentence{
    struct Word* words;
    int word_count;
    int * first_num;
    int * last_num;
};
struct Word{
    char* word;
    int len;
    int caps;
    int num_sum;
};
int caps_comparator(const void* a, const void* b){
    Word *f=(Word*)a;
    Word *s=(Word*)b;
    if(f->caps<s->caps) return -1;
    if(f->caps>s->caps) return 1;
    return 0;
}
int numsrt_comp(const void* f, const void* s){int flen=0; int slen=0;
    Sentence *a=(Sentence*)f;
    Sentence *b=(Sentence*)s;
    for(int i=a->first_num[0];i<=a->last_num[0];i++){
        if(i==a->first_num[0]){for(int j=a->first_num[1];j<a->words[i].len;j++){flen++;}}
        if(i>a->first_num[0] && i<a->last_num[0]){for(int j=0;j<a->words[i].len;j++){flen++;}}
        if(i==a->last_num[0]){for(int j=0;j<a->last_num[1];j++){flen++;}}
    }
    for(int i=b->first_num[0];i<=b->last_num[0];i++){
        if(i==b->first_num[0]){for(int j=b->first_num[1];j<b->words[i].len;j++){slen++;}}
        if(i>b->first_num[0] && i<b->last_num[0]){for(int j=0;j<b->words[i].len;j++){slen++;}}
        if(i==b->last_num[0]){for(int j=0;j<b->last_num[1];j++){slen++;}}
    }
    if(flen>slen) return -1;
    if(slen>flen) return 1;
    return 0;
}
int num_sum_comp(const void*f,const void* s){
    Word *a=(Word*)f;
    Word* b=(Word*)s;
    return ((a->num_sum)-(b->num_sum));
}
Word get_word(int* stop_sign,int *stop_sent, int w_num){char curr_char=0; char prev_char=curr_char; int wrd_len=BUFFER;
    Word word;word.caps=0; word.num_sum=0;
    word.len=0;
    word.word=(char*)calloc(BUFFER, sizeof(char));
    while(1){curr_char=getchar();
        if(curr_char=='\n' && prev_char=='\n'){*stop_sign=1;word.word='\0';return word;}
        if(curr_char=='.'){*stop_sent=1;word.word[word.len]='\0'; return word;}
        if(curr_char==' '){if(prev_char!=0){word.word[word.len]='\0'; return word;}} 
        if(curr_char==','){curr_char=getchar();word.word[word.len]='\0'; return word;}
        if(word.len>=wrd_len){
            wrd_len+=5;
            word.word=(char*) realloc(word.word, sizeof(char)*(wrd_len+1));
        }
        if(curr_char>='0' && curr_char<='9'){word.num_sum+=(curr_char-48);}
        if(curr_char-64>0 && curr_char-91<0){word.caps++;} 
        if(curr_char!='\n' && curr_char!=' '){word.word[word.len++]=curr_char;}
        prev_char=curr_char;
    }
}
Sentence get_sent(int *stop_sign){
    int num_pose=-1;
    Sentence Sentence; 
    int stop_sent=0; 
    Sentence.word_count=0;
    Sentence.words=(Word*) malloc(sizeof(Word)*3);
    Sentence.first_num=(int*)malloc(sizeof(int)*2); Sentence.first_num[0]=-1;
    Sentence.last_num=(int*)malloc(sizeof(int)*2); Sentence.last_num[0]=-1;
    while(*stop_sign==0 && stop_sent==0){
        Sentence.words[Sentence.word_count]=get_word(stop_sign, &stop_sent, Sentence.word_count);
        Sentence.word_count++;
        if(Sentence.word_count>=1){
            Sentence.words=(Word*) realloc(Sentence.words, sizeof(Word)*(Sentence.word_count+1));}
        }if(stop_sent==1)
    for(int i=0;i<Sentence.word_count;i++){num_pose=-1;
        for(int j=0; j<Sentence.words[i].len;j++){
            if(Sentence.words[i].word[j]<='9' && Sentence.words[i].word[j]>='0'){num_pose=j;break;}
        }
        if(num_pose!=-1){Sentence.first_num[0]=i; Sentence.last_num[1]=num_pose;break;}
    }
    for(int i=Sentence.word_count-1;i>0;i--){num_pose=-1;
        for(int j=Sentence.words[i].len; j>0;j--){
            if(Sentence.words[i].word[j]<='9' && Sentence.words[i].word[j]>='0'){num_pose=j;break;}
        }
        if(num_pose!=-1){Sentence.last_num[0]=i; Sentence.last_num[1]=num_pose;break;}
    }
    if(Sentence.first_num[0]==-1 && Sentence.last_num[0]==-1){Sentence.last_num[0]=0;Sentence.last_num[1]=0;Sentence.first_num[0]=Sentence.word_count;Sentence.first_num[1]=Sentence.words[Sentence.word_count].len;}
    return Sentence;
}
Text get_text(){Text text; text.txt_len=0;
    int stop_sign=0;
    text.sents=(Sentence*) malloc(sizeof(Sentence));
    while(stop_sign==0){
        text.sents[text.txt_len]=get_sent(&stop_sign); text.txt_len++;
        if(text.txt_len>=1){
            text.sents=(Sentence*) realloc(text.sents,(text.txt_len+1)*sizeof(Sentence));}
    }text.sents[text.txt_len].word_count=0;
    return text;
}
Text base_proces(Text text){
    for(int i=0; i<text.txt_len-1; i++){
        for(int j=i+1;j<text.txt_len; j++){
            int checker=0;
            if(text.sents[i].word_count==text.sents[j].word_count){
                for(int k=0; k<text.sents[i].word_count;k++){
                    int mini_check=0;
                    if(text.sents[i].words[k].len==text.sents[j].words[k].len){
                        for(int z=0; z<text.sents[i].words[k].len; z++){
                            if(text.sents[i].words[k].word[z]==text.sents[j].words[k].word[z] || (abs(text.sents[i].words[k].word[z]-text.sents[j].words[k].word[z])==22)){
                                mini_check++;
                            }
                        }
                        if(text.sents[i].words[k].len==mini_check){
                            checker++;
                        }
                    }
                }
                if(checker==text.sents[i].word_count){
                text.sents[j].word_count=0;
                }
           }
        }
    }
    return text;
}
Text even_word_count_del(Text text){
    for(int i=1;i<text.txt_len; i+=2){
        if(text.sents[i].word_count%2==0){
            text.sents[i].word_count=0;
        }
    }

    return text;
}
Text word_sort(Text text){
    for (int i = 0; i < text.txt_len; i++)
    {
        qsort(text.sents[i].words, text.sents[i].word_count, sizeof(Word), caps_comparator);
    }

return text;
}
Text num_sum_sort(Text text){
    for(int i = 0;i < text.txt_len; i++)
    {
        qsort(text.sents[i].words, text.sents[i].word_count, sizeof(Word), num_sum_comp);
    }
    return text;   
}
Text small_word_rep(Text text){
    for(int i=0; i<text.txt_len;i++){
        for(int j=0; j<text.sents[i].word_count;j++){
            if(text.sents[i].words[j].len<=3){text.sents[i].words[j].word="Less Then 3";}
        }
    }
return text;
}
Text numstr_length_sort(Text text){
    qsort(text.sents, text.txt_len, sizeof(Sentence), numsrt_comp);
    return text;
}

void output(Text text, int command){
    if((command>=0 && command<=3) || command==9){
        for(int i=0;i<text.txt_len-1;i++){
            for(int j=0; j<text.sents[i].word_count;j++){
                if(j>0){printf(" ");}
                printf("%s",text.sents[i].words[j].word);
                
            }
            if(text.sents[i].word_count!=0){printf(".\n");}
        }
    }
    if(command==4){
        for(int i=0;i<text.txt_len-1;i++){
            if((text.sents[i].last_num[0]==0 && text.sents[i].first_num[0]!=0) || (text.sents[i].first_num[0]==text.sents[i].last_num[0]&& text.sents[i].first_num[1]==text.sents[i].last_num[1])){continue;}
            for(int j=text.sents[i].first_num[0]; j<text.sents[i].last_num[0]+1; j++){
                if(text.sents[i].first_num[0]!=text.sents[i].last_num[0]){
                if(j==text.sents[i].first_num[0]){
                    for(int k=text.sents[i].first_num[1];k<text.sents[i].words[j].len;k++){
                        printf("%c",text.sents[i].words[j].word[k]);}printf(" ");}}
                if(j==text.sents[i].last_num[0]){
                    for(int k=0; k<text.sents[i].last_num[1]+1;k++){
                        printf("%c",text.sents[i].words[j].word[k]);}
                    }
                if(text.sents[i].first_num[0]<j && j<text.sents[i].last_num[0]){
                    printf("%s ",text.sents[i].words[j].word);
                }

            }if(text.sents[i].first_num[0]==text.sents[i].last_num[0] && text.sents[i].first_num[1]==text.sents[i].last_num[1]-1){continue;}
            else{printf(".\n");}
            
        }
    }
    if(command==5){
        printf("0-Ouptup after base processing\n1-Delete even numberd sentences with even number of words\n2-Sort words in each sentence by number of capital letters\n3-Replace words shorter then 3 symbols with line Less Then 3\n4-Find longest line between digits in each sentence and output them sorted by length\n");
    }
    if((command<0 || command>5) && command!=9){
        printf("ERORR: <некоректный номер команды>\n");
    }

}
void comm_exec(Text text, int command){
        if((command>=0 && command<=4) || command==9){
        text=get_text();
        text=base_proces(text);
        switch (command)
        {
        case 1:
            text=even_word_count_del(text);
            break;
        case 2:
            text=word_sort(text);
            break;
        case 3:
            text=small_word_rep(text);
            break;
        case 4:
            text=numstr_length_sort(text);
            break;
        case 9:
            text=num_sum_sort(text);
        default:
            break;
        }}
    output(text, command);
}

int main(){int command;
    Text text={0};   
    printf("Course work for option 4.23, created by Semen Peschatskii\n");
    command=getchar()-48;
    comm_exec(text, command);
    return 0;
}
