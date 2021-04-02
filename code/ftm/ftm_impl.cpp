// ftm
// Copyright (c) 2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#include "system_clock.hpp"
#include "test_time.hpp"

#include <atomic>

namespace ftm
{

namespace
{
std::atomic_int64_t test_time_now_ns;
ns_i64 load_test_time()
{
    return ns_i64(test_time_now_ns.load(std::memory_order_relaxed));
}
}

system_clock::time_point system_clock::test_now()
{
    return system_clock::time_point{std::chrono::duration_cast<system_clock::duration>(load_test_time())};
}
system_clock::time_point system_clock::real_now()
{
    return system_clock::time_point{std::chrono::duration_cast<system_clock::duration>(std::chrono::system_clock::now().time_since_epoch())};
}
system_clock::now_func system_clock::now = system_clock::real_now;

void test_time::setup_time_point(system_clock::time_point start)
{
    test_time_now_ns = std::chrono::duration_cast<ns_i64>(start.time_since_epoch()).count();
}

int test_time::setup_clock(system_clock&)
{
    system_clock::now = system_clock::test_now;
    return 1;
}

int test_time::undo_setup_clock(system_clock&)
{
    system_clock::now = system_clock::real_now;
    return 1;
}

void test_time::elapse(ns_i64 duration)
{
    test_time_now_ns.fetch_add(duration.count(), std::memory_order_relaxed);
}

}
