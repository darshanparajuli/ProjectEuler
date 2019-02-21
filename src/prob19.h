#ifndef PE_PROB19_H
#define PE_PROB19_H

/*
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

SolveProblemFunc(19)
{
    u32 result = 0;

    u32 daysInMonthTable[] = {
        31,  // Jan
        28,  // *Feb
        31,  // Mar
        30,  // Apr
        31,  // May
        30,  // Jun
        31,  // Jul
        31,  // Aug
        30,  // Sep
        31,  // Oct
        30,  // Nov
        31,  // Dec
    };

    // 0 => Sunday
    // start off on Monday => 1
    u32 dayIndex = 1;

    for (u32 year = 1900; year <= 2000; ++year)
    {
        b32 canHaveLeapYear = year % 100 != 0 || year % 400 == 0;

        for (u32 month = 0; month < 12; ++month)
        {
            u32 days = daysInMonthTable[month];
            if (month == 1 && year % 4 == 0 && canHaveLeapYear)
            {
                ++days;
            }

            if (dayIndex == 0 && year >= 1901)
            {
                ++result;
            }

            dayIndex = (dayIndex + days) % 7;
        }
    }

    WriteSolution("%d", result);
}

#endif
