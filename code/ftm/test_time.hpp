// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#pragma once
#include "api.h"

#include "system_clock.hpp"

namespace ftm
{

class FTM_API test_time
{
public:
    template <typename ...Clocks>
    static void setup(system_clock::time_point start, Clocks... clocks)
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
