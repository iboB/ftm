// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#pragma once

#if !defined(FTM_API)
#   if defined(FTM_SHARED)
#       if defined(_WIN32)
#           define FTM_SYM_EXPORT __declspec(dllexport)
#           define FTM_SYM_IMPORT __declspec(dllimport)
#       else
#           define FTM_SYM_EXPORT __attribute__((__visibility__("default")))
#           define FTM_SYM_IMPORT
#       endif

#       if defined(FTM_IMPLEMENT)
#           define FTM_API FTM_SYM_EXPORT
#       else
#           define FTM_API FTM_SYM_IMPORT
#       endif
#   else
#       define FTM_API
#   endif
#endif
