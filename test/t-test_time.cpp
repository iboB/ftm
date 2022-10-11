// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#include <doctest/doctest.h>

#include <ftm/test_time.hpp>

TEST_SUITE_BEGIN("test time");

TEST_CASE("setup")
{
    CHECK(ftm::system_clock::now == ftm::system_clock::real_now);
    ftm::test_time::setup();
    CHECK(ftm::system_clock::now == ftm::system_clock::test_now);
    ftm::test_time::undo_setup();
    CHECK(ftm::system_clock::now == ftm::system_clock::real_now);
}

TEST_CASE("elapse")
{
    ftm::test_time::setup();

    auto sysnow = ftm::system_clock::now();
    CHECK(sysnow.time_since_epoch().count() == 0);

    ftm::test_time::elapse(ftm::sec_i32(1));

    sysnow = ftm::system_clock::now();
    CHECK(sysnow.time_since_epoch().count() == 1'000'000);
}
