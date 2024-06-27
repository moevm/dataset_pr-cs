#include "my_lib.h"

void find_no_reg(struct Text* text, ch* str){
    ch* find_st = wcsdup(str);
    //find_st = _wcslwr(find_st);
    ch**arr = malloc(sizeof(ch*)*200);
  //  wprintf(L"%ls\n",find_st);
    ch*pt;
    ch *iter = wcstok(find_st,L" ,.\n",&pt);
    ch*it;

    int k = 0;
        while(iter!=NULL){
            it = iter;
            //wprintf(L"%ls\n",it);
            arr[k++] = wcsdup(it);
            iter = wcstok(NULL,L" ,.\n",&pt);
        }
//    for(int i=0;i<k;++i){
//        wprintf(L"%ls\n",arr[i]);
//    }
    for(int i=0;i<text->cnt_sen;++i){
        int flag =1;
        ch *st = wcsdup(text->txt[i].snt);
        //st = _wcslwr(st);
        iter = wcstok(st,L" ,.",&pt);
        while(iter!=NULL){
            it = iter;
            int loc_flag =1;

            for(int j=0;j<k;++j){
                if(wcscasecmp(it,arr[j])==0)loc_flag = 0;
                //wprintf(L"%ls %ls %d\n",it,arr[j],wcscmp(it,arr[j]));
            }
            if(loc_flag)flag=0;
            iter = wcstok(NULL,L" ,.",&pt);
        }
        if(flag){
            wprintf(L"%ls\n",text->txt[i].snt);
        }
    }
//    wprintf(find_st);
}
//hello my friend
//ab cd. friend my, hello. Hello, hello.
