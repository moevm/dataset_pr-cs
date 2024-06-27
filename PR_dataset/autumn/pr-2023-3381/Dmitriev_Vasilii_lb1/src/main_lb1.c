#include <stdio.h>
#include <stdlib.h>


//получение первого числа
int get_one_int(){
	int el;
	scanf("%d",&el);
	return el;

}

//заполнение массива и получение его длины
int fill_array_and_get_len(int array[]){
	int len = 0;
	do{
		scanf("%d",&array[len++]);
	}
        while (len<100 &&  getchar()!='\n');
	return len;

}


//общая функция по поиску индекса нуля
int search_index_zero(int array[], int start, int end, int step){
         for(int i=start;i!=end;i+=step){
                 if (array[i] == 0){
                          return i;
                  }

         }

         return -1;
	
}


int index_first_zero(int array[],int len){
	 return search_index_zero(array, 0, len, 1);
}

int index_last_zero(int array[], int len){
	 return search_index_zero(array, len-1, -1, -1);

}

//общая функция для суммирование элементов
int sum_elements(int array[], int start, int end){
     int sum_abs = 0;
	 if (start!=-1){ 
        	 for(int i=start;i<end;i++){
         		sum_abs+=abs(array[i]);

         	}
	 }
        return sum_abs;

}


int sum_between(int array[], int len){
	int first = index_first_zero(array,len);
	int last = index_last_zero(array,len);
        return sum_elements(array,first,last);

}

int sum_before_and_after(int array[], int len){
	 int one_summ = sum_elements(array,0,index_first_zero(array,len));
	 int two_summ = sum_elements(array,index_last_zero(array,len),len);

         return one_summ+two_summ;

}

int main(){
	int one_int = get_one_int();
	int array[100];
	int len = fill_array_and_get_len(array);

	switch(one_int){	
		case 0:
			printf("%d\n",index_first_zero(array, len));
			break;
		case 1:
			printf("%d\n",index_last_zero(array, len));
			break;
		case 2: 
			printf("%d\n",sum_between(array,len));
			break;
		case 3:
			printf("%d\n",sum_before_and_after(array,len));
			break;
		default:
			puts("Данные некорректны");
	}


	return 0;
}
	
