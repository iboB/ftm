// ftm
// Copyright (c) 2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <ftm/test_time.hpp>

TEST_SUITE_BEGIN("test time");

TEST_CASE("test")
{
    ftm::test_time::setup();

    auto sysnow = ftm::system_clock::now();
    CHECK(sysnow.time_since_epoch().count() == 0);

    ftm::test_time::elapse(ftm::sec_i32(1));

    sysnow = ftm::system_clock::now();
    CHECK(sysnow.time_since_epoch().count() == 1000);
}
