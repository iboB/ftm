// ftm
// Copyright (c) 2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "types.hpp"

namespace ftm
{
class system_clock
{
public:
    using duration = ms_i64;
    using time_point = std::chrono::time_point<system_clock>;

    using now_func = time_point(*)();
    static now_func now;

    static time_point test_now();
    static time_point real_now();
};
}
