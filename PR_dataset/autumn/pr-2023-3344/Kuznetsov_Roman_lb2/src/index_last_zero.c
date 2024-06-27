int index_last_zero(int arr[], int size){    
    int last_zero_index=-1;
    for (int i=0; i<size; i++){
        if (arr[i]==0)
            last_zero_index = i;
    }
    return last_zero_index;
}
