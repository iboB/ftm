// ftm
// Copyright (c) 2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "system_clock.hpp"

namespace ftm
{

class test_time
{
public:
    template <typename ...Clocks>
    static void setup(system_clock::time_point start = {}, Clocks... clocks)
    {
        setup_time_point(start);
        [[maybe_unused]] int u[] = { setup_clock(clocks)... };
    }

    static void setup(system_clock::time_point start = {})
    {
        setup(start, system_clock());
    }

    template <typename ...Clocks>
    static void undo_setup(Clocks... clocks)
    {
        [[maybe_unused]] int u[] = { undo_setup_clock(clocks)... };
    }

    static void undo_setup()
    {
        undo_setup(system_clock());
    }

    static void elapse(ns_i64 duration);

private:
    static void setup_time_point(system_clock::time_point start);
    static int setup_clock(system_clock&);
    static int undo_setup_clock(system_clock&);
};

}
