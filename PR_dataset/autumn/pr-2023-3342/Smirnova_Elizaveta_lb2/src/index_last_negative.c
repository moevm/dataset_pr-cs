int index_last_negative(int numbers[], int size){
    int last_negative = 0;

    for(int i = 0;i < size; i++){

        if(numbers[i]<0){
            last_negative = i;
        }
    }

    return last_negative;
}
