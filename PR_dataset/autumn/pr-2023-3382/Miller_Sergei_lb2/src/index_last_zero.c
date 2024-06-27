int index_last_zero(int m[], int lenm){
        for (int i = lenm - 1; i != 0; i--){
                if (m[i] == 0){
                        return i;
                }
        }
        return -1;
}

