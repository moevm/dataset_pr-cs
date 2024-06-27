#include <stdio.h>
#include <stdlib.h>

int abs_max(int mas[], int ln)
{	int mx=abs(mas[0]);
	int mxi=0;
	for (int i=1; i<ln; i++)
	{
		if (abs(mas[i])>abs(mx))
		{
			mx=mas[i];
			mxi=i;	
			}
	}
	return mxi;
}

int abs_min(int mas[], int ln)
{
	int mn=abs(mas[0]);
	for (int i=1; i<ln; i++)
	{
		if (abs(mas[i])<abs(mn))
		{
			mn=mas[i]; 	
		}
	}
	return mn;
}

int diff (int mas[],int mxi,int mn)
{
	return mas[mxi]-mn;
}

int sum (int mas[], int ln, int mxi)
{	int s=0;
	for (int i=mxi;i<ln;i++)
	{
		s+=mas[i];
	}
	return s;
}

int main()
{
	int number;
	scanf ("%d",&number);
	int mas[100];
	int i=0;
	int c;
	int ln=0;
	while ((c=getchar())!='\n')
	{
		scanf("%d",&mas[i]);
		if (ln<100)
		{ln=++i;}
		else
		{ puts("Данные некорректны\n");
		return 0; }
	}
	switch (number)
	{
		case 0:
			printf("%d\n", mas[abs_max(mas,ln)]);
			break;
		case 1:
			printf("%d\n", abs_min(mas,ln));
			break;
		case 2:
			printf("%d\n", diff(mas,abs_max(mas,ln),abs_min(mas,ln)));
			break;
		case 3:
			printf("%d\n", sum(mas,ln,abs_max(mas,ln)));
			break;
		default:
			puts("Данные некорректны\n");
	}
	return 0;
}
