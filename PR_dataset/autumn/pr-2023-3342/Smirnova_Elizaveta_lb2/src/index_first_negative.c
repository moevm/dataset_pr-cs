int index_first_negative(int numbers[], int size){
    int first_negative = 0;

    for(int i = 0; i < size; i++){

        if(numbers[i]<0){
            first_negative = i;
            i = size;
        }
    }

    return first_negative;
}
