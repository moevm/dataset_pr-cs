int index_first_zero(int arr[], int CNT_ARR){
    int ind_first = 0;
    for (int i = 0; i < CNT_ARR; i++){
        if (arr[i] == 0) {
            ind_first = i;
            return ind_first;
        }
    }
    return ind_first;
}
