#include "answer.h"

int answer(int arr[], int size, int operation, int id_max, int id_min) {
	        switch (operation) {
                case 0:
                        printf("%d\n", arr[abs_max(arr, size)]);
                        break;
                case 1:
                        printf("%d\n", arr[abs_min(arr, size)]);
                        break;
                case 2:
                        id_max = abs_max(arr, size);
                        id_min = abs_min(arr, size);
                        printf("%d\n", diff(arr, size, id_max, id_min));
                        break;
                case 3:
                        id_max = abs_max(arr, size);
                        printf("%d\n", sum(arr, size, id_max));
                        break;
                default:
                        printf("%s\n", ERROR_STRING_OUTPUT);
                        break;
        }
}	
