int index_first_even(int array[], int size_array){ // Индекс первого чётного элемента
    for(int i = 0; i < size_array; i++){
        if(array[i] % 2 == 0){
            return i;
            break;
        }
    }
}
