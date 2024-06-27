int index_last_negative(int arr[], int num_of_arr_elements){
    int last_index = num_of_arr_elements - 1;
    int res = 0;
    for(int i = last_index; i>=0; i--){
        if(arr[i] < 0){
            res = i;
            break;
        }
    }
    return res;
}