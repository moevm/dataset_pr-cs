int index_first_even(int arr[], int array_length) {
    for (int r = 0; r < array_length; r++) {

        if (arr[r] % 2 == 0) {

            return r;
        }
    }

}

