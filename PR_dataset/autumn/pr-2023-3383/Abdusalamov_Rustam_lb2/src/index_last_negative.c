int index_last_negative(int list[],int length){
    int index;
    for(int q = length - 1;q>-1;q--){
        if(list[q]<0){
            index = q;
            break;
        }
    }
    return index;
}
