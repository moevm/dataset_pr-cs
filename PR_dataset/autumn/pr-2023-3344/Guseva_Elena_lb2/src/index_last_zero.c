int index_last_zero(int array[], int size){
    for (int i=size-1; i>=0; i--){
        if (array[i]==0){
            return i;
        }
    }
    return -1;
}
