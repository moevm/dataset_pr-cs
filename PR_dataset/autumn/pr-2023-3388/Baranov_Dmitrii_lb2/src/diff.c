#include<stdio.h>
#include"diff.h"
#include"min.h"
#include"max.h"

int diff(int masiv[], int s) {

        return max(masiv,s) - min(masiv, s);

        }
