#pragma once

#include "loguru.hpp"

namespace blitz
{
    class Logger
    {
    public:
        static void init(int argc, char** argv)
        {
            loguru::init(argc, argv);
            // Put every log message in "everything.log":
            loguru::add_file("/var/log/blitz/renderer-core.log", loguru::Append, loguru::Verbosity_MAX);
            // Only show most relevant things on stderr:
            loguru::g_stderr_verbosity = 1;
            // Turn off writing err/warn in red:
            loguru::g_colorlogtostderr = false;
        }
    };
}