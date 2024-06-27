int sum_between_even_odd (int array []) {
    int first_even = index_first_even(array);
    int last_odd = index_last_odd(array);
    int sum = 0;
    int i;
    for (i = first_even; i < last_odd; i++){
        sum += abs(array[i]);
    }

    return sum;
}
