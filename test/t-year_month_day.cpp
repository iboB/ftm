// ftm
// Copyright (c) 2021-2022 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <ftm/year_month_day.hpp>

using namespace ftm;

TEST_SUITE_BEGIN("year_month_day");

TEST_CASE("default")
{
    year_month_day d;
    CHECK(d.year == 1970);
    CHECK(d.month == 0);
    CHECK(d.day == 1);
}

TEST_CASE("leap")
{
    year_month_day d = {1984, year_month_day::jun, 25};

    CHECK(d.valid());
    CHECK(d.leap());

    d.year = 1900;
    CHECK(d.leap() == false);

    d.year = 2000;
    CHECK(d.leap() == true);
}

TEST_CASE("wday")
{
    year_month_day d;
    d = { 1900, year_month_day::aug, 5 };
    CHECK(d.wday() == 0);

    d = {1984, year_month_day::jun, 25};
    CHECK(d.wday() == 1);

    d = {4801, year_month_day::dec, 25};
    CHECK(d.wday() == 2);

    d = {1813, year_month_day::jan, 20};
    CHECK(d.wday() == 3);

    d = {2000, year_month_day::mar, 2};
    CHECK(d.wday() == 4);

    d = {2021, year_month_day::apr, 2};
    CHECK(d.wday() == 5);

    d = {2020, year_month_day::feb, 29};
    CHECK(d.wday() == 6);
}

TEST_CASE("yday")
{
    year_month_day d;

    d = { 2004, year_month_day::jan, 1 };
    CHECK(d.yday() == 0);
    d = {2004, year_month_day::feb, 1};
    CHECK(d.yday() == 31);
    d = {2004, year_month_day::feb, 29};
    CHECK(d.yday() == 59);
    d = {2004, year_month_day::mar, 1};
    CHECK(d.yday() == 60);
    d = {2004, year_month_day::dec, 31};
    CHECK(d.yday() == 365);

    d = {2003, year_month_day::jan, 1};
    CHECK(d.yday() == 0);
    d = {2003, year_month_day::feb, 1};
    CHECK(d.yday() == 31);
    d = {2003, year_month_day::feb, 28};
    CHECK(d.yday() == 58);
    d = {2003, year_month_day::mar, 1};
    CHECK(d.yday() == 59);
    d = {2003, year_month_day::dec, 31};
    CHECK(d.yday() == 364);
}

TEST_CASE("compare")
{
    year_month_day d = {1984, year_month_day::jun, 25};

    CHECK(d.valid());
    CHECK(d.leap());

    year_month_day d2 = d;
    CHECK(d2 <= d);
    CHECK(d2 >= d);
    CHECK(d == d2);

    d2.year = 1234;
    CHECK(d != d2);
    CHECK(d2 < d);
    CHECK(d2 <= d);
    d2 = d;
    d2.month = year_month_day::feb;
    CHECK(d != d2);
    CHECK(d2 < d);
    CHECK(d2 <= d);
    d2 = d;
    d2.day = 5;
    CHECK(d != d2);
    CHECK(d2 < d);
    CHECK(d2 <= d);

    d2 = d;
    d2.year = 2234;
    CHECK(d != d2);
    CHECK(d2 > d);
    CHECK(d2 >= d);
    d2 = d;
    d2.month = year_month_day::nov;
    CHECK(d != d2);
    CHECK(d2 > d);
    CHECK(d2 >= d);
    d2 = d;
    d2.day = 28;
    CHECK(d != d2);
    CHECK(d2 > d);
    CHECK(d2 >= d);
}

TEST_CASE("human integer")
{
    year_month_day d = {1984, year_month_day::jun, 25};
    int i = d.to_h_i();
    CHECK(i == 19840625);
    CHECK(year_month_day::from_h_i(i) == d);

    d = {-306, year_month_day::jul, 8};
    i = d.to_h_i();
    CHECK(i == -3060708);
    CHECK(year_month_day::from_h_i(i) == d);
}

TEST_CASE("valid")
{
    year_month_day d;
    CHECK(d.valid());
    d = { 2154, year_month_day::jan, 31 };
    CHECK(d.valid());
    d.month = year_month_day::feb;
    CHECK(!d.valid());
    d.month = year_month_day::mar;
    CHECK(d.valid());
    d.month = year_month_day::apr;
    CHECK(!d.valid());
    d.month = year_month_day::may;
    CHECK(d.valid());
    d.month = year_month_day::jun;
    CHECK(!d.valid());
    d.month = year_month_day::jul;
    CHECK(d.valid());
    d.month = year_month_day::aug;
    CHECK(d.valid());
    d.month = year_month_day::sep;
    CHECK(!d.valid());
    d.month = year_month_day::oct;
    CHECK(d.valid());
    d.month = year_month_day::nov;
    CHECK(!d.valid());
    d.month = year_month_day::dec;
    CHECK(d.valid());

    d.month = 12;
    CHECK(!d.valid());
    d.month = year_month_day::feb;
    d.day = 0;
    CHECK(!d.valid());
    d.day = 28;
    CHECK(d.valid());
    d.day = 29;
    CHECK(!d.valid());
    d.year = 2000;
    CHECK(d.valid());
    d.year = 900;
    CHECK(!d.valid());
}
