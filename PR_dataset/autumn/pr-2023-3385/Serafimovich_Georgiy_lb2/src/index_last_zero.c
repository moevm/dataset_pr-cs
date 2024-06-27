int index_last_zero(int* arr, int l){
    int i=l-1;
    while(arr[i]!=0 && i>0)
    i--;
        return i;
}
