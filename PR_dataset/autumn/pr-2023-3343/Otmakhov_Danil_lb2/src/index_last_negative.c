int index_last_negative(int arr[], int sizeOfArr){
    int index_last;
    int i = sizeOfArr - 1;
    while (i > 0){
        if (arr[i] < 0){
            index_last = i;
            break;
        }
        i--;
    }
    return index_last;
}
