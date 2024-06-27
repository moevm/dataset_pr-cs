int index_last_odd(int array[], int size_array){ // Индекс последнего нечётного элемента
    for(int i = size_array - 1; i >= 0; i--){
        if(array[i] % 2 != 0){
            return i;
            break;
        }
    }
}
