#pragma once

#ifdef _DEBUG
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include "spdlog/spdlog.h"
#include "spdlog/common.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"


class KrkrLogger
{
public:
    static void Start()
    {
        set_default_logger(spdlog::basic_logger_mt<spdlog::async_factory>("version", "version.log", true));
        spdlog::set_level(spdlog::level::info);
        spdlog::flush_every(std::chrono::seconds(5));
    }

    static void Stop()
    {
        spdlog::default_logger()->flush();
        spdlog::shutdown();
    }
};
#endif
