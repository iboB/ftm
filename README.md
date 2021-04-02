# ftm

**ftm** (or Fun Times) is a C++ time utilities library which wraps `std::chrono` to provide:

* A shorter namespace: `ftm` as opposed to `std::chrono`
* Some strictly defined types for durations in terms of underlying data type: byte size and whether it's integral or floating point
* Clock types which:
    * Use strictly defined time point types from above
    * Can have their behavior changed for testing purposes, replacing the time measurement from "real" (from the physical system) to "test" (where the time needs to be manually advanced by the user)
* A `year_month_day` type, somewhat similar to the one from C++20, but:
    * With a stricly defined size: 32 bits
    * Using regular integers for year, month, and day 
    * With helper methods like conversion to/from a human-readable integer, leap check, and weekday calculation

*Although usable for the most part, ftm is still under development and things may drastically change in the near future*

## Building

You can use CMake. There is no special configuration involved to simply build the library.

## Contributing

All contributions in the form of issues and pull requests are welcome.

## Copying

The library is distributed under the MIT Software License. See LICENSE for further details or copy here.

Copyright &copy; 2021 Borislav Stanimirov.
