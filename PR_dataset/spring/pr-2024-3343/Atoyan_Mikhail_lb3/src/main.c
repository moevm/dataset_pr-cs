#include <stdio.h>
#include <string.h>
#include <dirent.h>

int sumFile(FILE *file) //возвращает сумму чисел в файле
{
    int sum = 0;
    int n;
    while (fscanf(file, "%d", &n) == 1)
    {
        sum += n;
    }
    return sum;
}

int mulFile(FILE *file) //возвращает произведение чисел в файле
{
    int prod = 1;
    int n;
    while (fscanf(file, "%d", &n) == 1)
    {
        prod *= n;
    }
    return prod;
}

int sumValues(int *values, int valuesLen) //возвращает сумму чисел в массиве
{
    int sum = 0;
    for (int i = 0; i < valuesLen; i++)
    {
        sum += values[i];
    }
    return sum;
}

int mulValues(int *values, int valuesLen) //возвращает произведение чисел в массиве
{
    int prod = 1;
    for (int i = 0; i < valuesLen; i++)
    {
        prod *= values[i];
    }
    return prod;
}

int calculate(const char *dirPath)
{
    DIR *dir = opendir(dirPath);
    FILE *file;
    struct dirent *entry;
    char filePath[1000];
    int values[100]; //для хранения результатов вычислений в файлах текущей директории
    int valuesLen = 0;

    if (dir)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            sprintf(filePath, "%s/%s", dirPath, entry->d_name); 
            if (entry->d_type == DT_DIR) //проверяем, является ли файл директорией
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
                    values[valuesLen++] = calculate(filePath);
            }
            else //иначе обрабатываем текстовый файл
            {
                file = fopen(filePath, "r");
                
                if (strcmp(dirPath + strlen(dirPath) - 3, "add") == 0) //если директория называется add, то складываем числа в файле
                    values[valuesLen++] = sumFile(file);
                else // иначе перемножаем
                    values[valuesLen++] = mulFile(file);
                
                fclose(file);
            }
        }
    }

    int res = values[0];

    if (strcmp(dirPath + strlen(dirPath) - 3, "add") == 0) //если директория называется add, то складываем полученные в ней значения 
        res = sumValues(values, valuesLen);
    else //иначе перемножаем
        res = mulValues(values, valuesLen);

    return res;
}

int main()
{
    char *dirPath = "./tmp";
    FILE *result = fopen("result.txt", "w+");
    int n = calculate(dirPath);
    fprintf(result, "%d", n);
    fclose(result);
    return 0;
}