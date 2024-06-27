int is_date_correct(int day, int month, int year)
{   
    if (year < 0) return 0;

    if (month == 3 || month == 5 || month == 8 || month == 10)
    {
        if (day <= 30) return 1;
    }
    else if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
    {
        if (day <= 31) return 1;
    }
    else if (month == 1)
    {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        {
            if (day <= 29) return 1;
        }
        else
        {
            if (day <= 28) return 1;
        }
    }
    return 0;
}