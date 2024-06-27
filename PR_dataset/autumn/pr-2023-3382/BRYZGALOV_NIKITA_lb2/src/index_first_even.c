int index_first_even(int array[], int length){
    int i;
    for(i = 0; i < length; i++){
        if((array[i]%2) == 0){
            return i;
        }
    }
}