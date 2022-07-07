// ftm
// Copyright (c) 2021-2022 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include <chrono>
#include <cstdint>

// strong time units

namespace ftm
{
using sec_t = std::chrono::seconds;
using sec_i32 = std::chrono::duration<int32_t>;
using sec_i64 = std::chrono::duration<int64_t>;

using ms_t = std::chrono::milliseconds;
using ms_i64 = std::chrono::duration<int64_t, std::milli>;
using ms_i32 = std::chrono::duration<int32_t, std::milli>;

using us_t = std::chrono::microseconds;
using us_i64 = std::chrono::duration<int64_t, std::micro>;
using us_i32 = std::chrono::duration<int32_t, std::micro>;

using ns_t = std::chrono::nanoseconds;
using ns_i64 = std::chrono::duration<int64_t, std::nano>;
using ns_i32 = std::chrono::duration<int32_t, std::nano>;
}
