int index_first_negative(int arr[], int num_of_arr_elements){
    int res = 0;
    for(int i =0; i < num_of_arr_elements; i++){
        if(arr[i] < 0){
            res = i;
            break;
        }
    }
    return res;
}