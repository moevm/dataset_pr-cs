int sum_before_even_and_after_odd(int array []) {
    int first_even = index_first_even(array);
    int last_odd = index_last_odd(array);
    int sum = 0;
    int i;
    for (i = 0; i < first_even; i++) {
            sum += abs(array[i]);
    }

    for (i = last_odd; i < 100; i++) {
        sum += abs(array[i]);
    }

    return sum;
}
