int index_first_zero(int m[], int lenm) {
        for (int i = 0; i < lenm; i++){
                if (m[i]== 0)
                        return i;
        }
        return -1;
}

