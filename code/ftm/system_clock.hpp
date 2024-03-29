// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#pragma once
#include "api.h"
#include "types.hpp"

namespace ftm
{
class FTM_API system_clock
{
public:
    using duration = us_i64;
    using time_point = std::chrono::time_point<system_clock>;

    using now_func = time_point(*)();
    static now_func now;

    static time_point test_now();
    static time_point real_now();
};
}
