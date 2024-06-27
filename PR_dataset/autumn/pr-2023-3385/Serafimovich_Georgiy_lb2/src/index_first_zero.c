int index_first_zero(int* arr, int l){
    int i=0;
    while(arr[i]!=0 && i<l)
        i++;
        return i;
}
