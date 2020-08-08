#include <iostream>
#include <ctime>

int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 1000 == 0;
}

int leap_year_count_till(int year) 
{
    int count = 0;
    count += year / 4;
    count -= year / 100;
    count += year / 1000;
    return count;
}

int days_in_month (int month, int year)
{
    switch(month)
    {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            return 31;
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
            break;
        case 1:
            return is_leap_year(year) ? 29 : 28;
            break;
    }
    return 0;
}

int diff_dates_in_year(tm large, tm small)
{
    // if same month, then return the date diff.
    if(large.tm_mon == small.tm_mon)
    {
        return large.tm_mday - small.tm_mday;
    }
    int days_count = 0;
    for(int i = small.tm_mon + 1; i < large.tm_mon; i++) 
    {
        days_count += days_in_month(i, small.tm_year);
    }  
    days_count += days_in_month(small.tm_mon, small.tm_year) - small.tm_mday;
    days_count += large.tm_mday;
    return days_count;
}

int diff_dates(tm a, tm b)
{
    int large_first = a.tm_year > b.tm_year ? 1 : -1;
    if(a.tm_year == b.tm_year)
    {
        large_first = a.tm_mon > b.tm_mon ? 1 : -1;
        if(a.tm_mon == b.tm_mon)
        {
            large_first = a.tm_mday > b.tm_mday ? 1 : -1;
            if(a.tm_mday == b.tm_mday)
            {
                return 0;
            }
        }
    }
    tm large = a;
    tm small = b;
    if(large_first == -1){
        large = b;
        small = a;
    }

    int largeY = large.tm_year + 1900;
    int smallY = small.tm_year + 1900;
    int days_between = 0;
    // If years are same, then find days between 2 dates.
    if(largeY == smallY)
    {
        days_between = diff_dates_in_year(large, small);
        return days_between * large_first;
    }
    // find count of leap years and normal years bewteen the years.
    int small_leap_count = leap_year_count_till(smallY);
    int large_leap_count = leap_year_count_till(largeY - 1);
    int total_leap_years_count = large_leap_count - small_leap_count;
    int non_leap_years_count = largeY - smallY - 1 - total_leap_years_count;
    days_between += total_leap_years_count * 366;
    days_between += non_leap_years_count * 365;
    days_between += days_in_month(small.tm_mon, smallY) - small.tm_mday;
    for(int i = small.tm_mon + 1; i <= 11; i++){
        days_between += days_in_month(i, smallY);
    }
    for(int i = 0; i < large.tm_mon; i++){
        days_between += days_in_month(i, largeY);
    }
    days_between += large.tm_mday;
    return days_between * large_first;
}

int main()
{
    struct std::tm start;
    struct std::tm end;
    std::time_t endT;
    std::time_t nowT;
    double difference;

    start = (tm){0,0,0,1,0,120}; 
    end = (tm){0,0,0,2,0,120}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,1,0,120}; 
    end = (tm){0,0,0,3,1,120}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,1,0,120}; 
    end = (tm){0,0,0,8,8,120}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,8,8,120}; 
    end = (tm){0,0,0,1,1,120}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,8,8,120}; 
    end = (tm){0,0,0,1,5,121}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,8,8,99}; 
    end = (tm){0,0,0,1,5,150}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,1,5,150}; 
    end = (tm){0,0,0,8,8,99}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,1,0,120}; 
    end = (tm){0,0,0,1,0,120}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;

    start = (tm){0,0,0,6,7,120}; 
    end = (tm){0,0,0,4,6,141}; 
    endT = std::mktime(&end);
    nowT = std::mktime(&start);
    difference = std::difftime(endT, nowT) / (60 * 60 * 24);
    std::cout << std::ctime(&endT);
    std::cout << std::ctime(&nowT);
    std::cout << "difference by system = " << difference << " days" << std::endl;
    std::cout << "difference by me     = " << diff_dates(end, start) << " days" << std::endl << std::endl << std::endl;
    return 0;
}