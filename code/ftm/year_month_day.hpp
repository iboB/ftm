// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#pragma once

namespace ftm
{
class month_t
{
    uint8_t m_i;
    static constexpr uint8_t days_of[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
public:
    explicit constexpr month_t(uint8_t i) noexcept : m_i(i) {}
    constexpr uint8_t to_i() const noexcept { return m_i; }
    constexpr bool valid() const noexcept { return m_i > 0 && m_i < 13; }
    constexpr uint8_t days() const noexcept { return days_of[m_i - 1]; }
    bool operator==(month_t other) const { return m_i == other.m_i; }
    bool operator!=(month_t other) const { return m_i != other.m_i; }
    bool operator<(month_t other) const { return m_i < other.m_i; }
    bool operator>(month_t other) const { return m_i > other.m_i; }
    bool operator<=(month_t other) const { return m_i <= other.m_i; }
    bool operator>=(month_t other) const { return m_i >= other.m_i; }
};

class weekday_t
{
    uint8_t m_i;
public:
    explicit constexpr weekday_t(uint8_t d_since_sun) : m_i(d_since_sun) {}

    static constexpr weekday_t day_from_monday(uint8_t d) { return weekday_t(d == 6 ? 0 : d + 1); };
    static constexpr weekday_t day_from_sunday(uint8_t d) { return weekday_t(d); };
    static constexpr weekday_t day_invalid() { return weekday_t(255); };

    constexpr uint8_t days_since_sun() const noexcept { return m_i; }
    constexpr uint8_t days_since_mon() const noexcept { return m_i == 0 ? 6 : m_i - 1; }
    constexpr bool valid() const noexcept { return m_i < 7; }

    bool operator==(weekday_t other) const { return m_i == other.m_i; }
    bool operator!=(weekday_t other) const { return m_i != other.m_i; }
};

struct year_month_day
{
    static inline constexpr month_t jan{1};
    static inline constexpr month_t feb{2};
    static inline constexpr month_t mar{3};
    static inline constexpr month_t apr{4};
    static inline constexpr month_t may{5};
    static inline constexpr month_t jun{6};
    static inline constexpr month_t jul{7};
    static inline constexpr month_t aug{8};
    static inline constexpr month_t sep{9};
    static inline constexpr month_t oct{10};
    static inline constexpr month_t nov{11};
    static inline constexpr month_t dec{12};

    static inline constexpr weekday_t sun{0};
    static inline constexpr weekday_t mon{1};
    static inline constexpr weekday_t tue{2};
    static inline constexpr weekday_t wed{3};
    static inline constexpr weekday_t thu{4};
    static inline constexpr weekday_t fri{5};
    static inline constexpr weekday_t sat{6};

    int16_t year  = 1970;
    month_t month = jan;
    uint8_t day   = 1; // 1-31

    // convert to/from human-readable integers
    // assume valid
    constexpr int to_h_i() const noexcept
    {
        auto y = (year < 0) ? -year : year;
        auto ret = int(y) * 10'000 + month.to_i() * 100 + int(day);
        return year < 0 ? -ret : ret;
    }
    static year_month_day from_h_i(int ni)
    {
        auto i = ni < 0 ? -ni : ni;
        year_month_day ret;
        ret.year = uint16_t(i / 10'000);
        if (ni < 0) ret.year = -ret.year;
        i %= 10'000;
        ret.month = month_t(i / 100);
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
    weekday_t wday() const
    {
        // Sakamoto
        if (!valid()) return weekday_t::day_invalid();
        auto y = year;
        const auto m = month.to_i() - 1;
        const auto d = day;
        static constexpr int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
        y -= m < 2;
        return weekday_t::day_from_sunday((y + y / 4 - y / 100 + y / 400 + t[m] + d) % 7);
    }

    // day of the year 0-365
    int yday() const
    {
        int ret = day - 1;
        for (uint8_t m = 1; m < month.to_i(); ++m)
        {
            ret += month_t(m).days();
        }
        return ret + (month > feb && leap());
    }

    bool valid() const
    {
        if (!month.valid()) return false;
        if (day == 0) return false;
        if (month == feb && leap()) return day < 30;
        return day <= month.days();
    }

    friend bool operator==(const year_month_day& a, const year_month_day& b) { return a.year == b.year && a.month == b.month && a.day == b.day; }
    friend bool operator!=(const year_month_day& a, const year_month_day& b) { return a.year != b.year || a.month != b.month || a.day != b.day; }
    friend bool operator>(const year_month_day& a, const year_month_day& b)
    {
        if (a.year != b.year) return a.year > b.year;
        if (a.month != b.month) return a.month > b.month;
        return a.day > b.day;
    }
    friend bool operator>=(const year_month_day& a, const year_month_day& b)
    {
        if (a.year != b.year) return a.year > b.year;
        if (a.month != b.month) return a.month > b.month;
        return a.day >= b.day;
    }
    friend bool operator<(const year_month_day& a, const year_month_day& b)
    {
        if (a.year != b.year) return a.year < b.year;
        if (a.month != b.month) return a.month < b.month;
        return a.day < b.day;
    }
    friend bool operator<=(const year_month_day& a, const year_month_day& b)
    {
        if (a.year != b.year) return a.year < b.year;
        if (a.month != b.month) return a.month < b.month;
        return a.day <= b.day;
    }
};

}
