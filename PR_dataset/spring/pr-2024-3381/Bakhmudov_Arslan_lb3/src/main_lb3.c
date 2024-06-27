#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>


#define STARTPATH "tmp"
#define SIZE 128
#define ANSDEST "result.txt"


enum neutralelement
{
    ADD,
    MUL
};


int check(char c)
{
    return isdigit(c) || (c == '-');
}


int mathfile(char * path, enum neutralelement nel)
{
    int result = nel;
    char string[SIZE];
    char * sp;
    FILE * fp = fopen(path, "r");
    if (fp)
    {
        while (1)
        {
            sp = fgets(string, SIZE, fp);
            if (string[0] == '\n' || string[0] == '\0' || sp == NULL)
            {
                break;
            }
            while (check(sp[0]) || check(sp[1]))
            {
                switch (nel)
                {
                    case (MUL):
                        result *= strtol(sp, &sp, 10);
                        break;

                    default:
                        result += strtol(sp, &sp, 10);
                        break;
                }
            }
        }
    }
    fclose(fp);
    return result;
}


int mathdirs(char * path, enum neutralelement nel)
{
    int result = nel;
    DIR * dirp = opendir(path);
    struct dirent * de;
    char newpath[SIZE];
    enum neutralelement newnel;

    if (dirp)
    {
        de = readdir(dirp);
        while (de)
        {
            strcpy(newpath, path);
            strcat(newpath, "/");
            strcat(newpath, de->d_name);

            if (strstr(de->d_name, ".txt") != NULL)
            {
                switch (nel)
                {
                    case (MUL):
                        result *= mathfile(newpath, nel);
                        break;

                    default:
                        result += mathfile(newpath, nel);
                        break;
                }
            }
            else if (strchr(de->d_name, '.') == NULL)
            {
                newnel = (strcmp(de->d_name, "mul") == 0) ? MUL : ADD;
                switch (nel)
                {
                    case (MUL):
                        result *= mathdirs(newpath, newnel);
                        break;

                    default:
                        result += mathdirs(newpath, newnel);
                        break;
                }
            }
            de = readdir(dirp);
        }
    }
    closedir(dirp);
    return result;
}


int main()
{
    int answer = mathdirs(STARTPATH, ADD);
    FILE * fp = fopen(ANSDEST, "w");
    fprintf(fp, "%d\n\n", answer);
    fclose(fp);
    return 0;
}
