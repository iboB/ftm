// ftm
// Copyright (c) 2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

namespace ftm
{
struct year_month_day
{
    int16_t year  = 1970;
    uint8_t month = 0; // 0-11
    uint8_t day   = 1; // 1-31

    enum month_t { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
    static constexpr uint8_t days_per_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // convert to/from human-readable integers
    // assume valid
    int to_h_i() const
    {
        auto y = (year < 0) ? -year : year;
        auto ret = int(y) * 10'000 + int(month+1) * 100 + int(day);
        return year < 0 ? -ret : ret;
    }
    static year_month_day from_h_i(int ni)
    {
        auto i = ni < 0 ? -ni : ni;
        year_month_day ret;
        ret.year = uint16_t(i / 10'000);
        if (ni < 0) ret.year = -ret.year;
        i %= 10'000;
        ret.month = uint8_t(i / 100);
        ret.month -= 1;
        ret.day = i % 100;
        return ret;
    }

    bool leap() const
    {
        if (year % 4 != 0) return false;
        if (year % 25 != 0) return true;
        if (year % 16 != 0) return false;
        return true;
    }

    // days from sunday
    // 0-6
    int wday() const
    {
        // Sakamoto
        if (!valid()) return -1;
        auto y = year;
        const auto m = month;
        const auto d = day;
        static constexpr int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        y -= m < 2;
        return (y + y / 4 - y / 100 + y / 400 + t[m] + d) % 7;
    }

    bool valid() const
    {
        if (month > 11) return false;
        if (day == 0) return false;
        if (month == 1 && leap()) return day < 30;
        return day <= days_per_month[month];
    }

    friend bool operator==(const year_month_day& a, const year_month_day& b) { return a.year == b.year && a.month == b.month && a.day == b.day; }
    friend bool operator!=(const year_month_day& a, const year_month_day& b) { return a.year != b.year || a.month != b.month || a.day != b.day; }
    friend bool operator>(const year_month_day& a, const year_month_day& b) { return a.year > b.year || a.month > b.month || a.day > b.day; }
    friend bool operator>=(const year_month_day& a, const year_month_day& b) { return a > b || a == b; }
    friend bool operator<(const year_month_day& a, const year_month_day& b) { return a.year < b.year || a.month < b.month || a.day < b.day; }
    friend bool operator<=(const year_month_day& a, const year_month_day& b) { return a < b || a == b; }
};

}
