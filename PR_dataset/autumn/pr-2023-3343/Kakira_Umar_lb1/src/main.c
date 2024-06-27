#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int index_first_even (int array[], int array_size) {
  for (int i = 0; i < array_size; i++)
    {
      if (array[i] % 2 == 0)
	{
	  return i;
	}
    }
  return -1;
}

int index_last_odd (int array[], int array_size) {
  for (int i = array_size - 1; i >= 0; i--)
    {
      if (array[i] % 2 != 0)
	{
	  return i;
	}
    }
  return -1;
}

int sum_between_even_odd (int array[], int array_size) {
  int first_even_index = index_first_even (array, array_size);
  int last_odd_index = index_last_odd (array, array_size);
  if (first_even_index == -1 || last_odd_index == -1
      || first_even_index >= last_odd_index)
    {
      return 0;
    }
  int sum = 0;
  for (int i = first_even_index; i < last_odd_index; i++)
    {
      sum += abs (array[i]);
    }
  return sum;
}

int sum_before_even_and_after_odd (int array[], int array_size) {
  int first_even_index = index_first_even (array, array_size);
  int last_odd_index = index_last_odd (array, array_size);
  int sum_before = 0;
  int sum_after = 0;
  for (int i = 0; i < array_size; i++)
    {
      if (i < first_even_index)
	{
	  sum_before += abs (array[i]);
	}
      if (i >= last_odd_index)
	{
	  sum_after += abs (array[i]);
	}
    }
  return sum_before + sum_after;
}

int main () {
  int operation_number;
  scanf ("%d", &operation_number);

  int array[100];
  int array_size = 0;
  int number;

  while (scanf ("%d", &number) == 1)
    {
      array[array_size] = number;
      array_size++;
    }

  if (array_size == 0 || array_size > 100
      || (index_first_even (array, array_size) == -1
	  || index_last_odd (array, array_size) == -1))
    {
      printf ("Данные некорректны\n");
      return 0;
    }

  switch (operation_number)
    {
    case 0:
      printf ("%d", index_first_even (array, array_size));
      break;
    case 1:
      printf ("%d", index_last_odd (array, array_size));
      break;
    case 2:
      printf ("%d", sum_between_even_odd (array, array_size));
      break;
    case 3:
      printf ("%d", sum_before_even_and_after_odd (array, array_size));
      break;
    default:
      printf ("Данные некорректны\n");
      break;
    }
  return 0;
}

