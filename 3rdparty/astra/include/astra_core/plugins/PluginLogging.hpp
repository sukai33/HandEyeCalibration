// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015-2017 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef ASTRA_PLUGIN_LOGGING_HPP
#define ASTRA_PLUGIN_LOGGING_HPP

#include <astra_core/plugins/PluginServiceProxy.hpp>
#include <cstdarg>

#if defined(_MSC_VER)  // Visual C++
#   define LOG_FUNC __FUNCSIG__
#elif defined(__GNUC__)  // GCC
#   define LOG_FUNC __PRETTY_FUNCTION__
#elif defined(__INTEL_COMPILER)  // Intel C++
#   define LOG_FUNC __PRETTY_FUNCTION__
#elif defined(__clang__)  // Clang++
#   define LOG_FUNC __PRETTY_FUNCTION__
#else
#   if defined(__func__)
#      define LOG_FUNC __func__
#   else
#      define LOG_FUNC ""
#   endif  // defined(__func__)
#endif  // defined(_MSC_VER)

#define LOG_TRACE(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_TRACE, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

#define LOG_INFO(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_INFO, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

#define LOG_DEBUG(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_DEBUG, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

#define LOG_ERROR(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_ERROR, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

#define LOG_FATAL(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_FATAL, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

#define LOG_WARN(channel, format, ...) \
    ::astra::plugins::log(channel, ASTRA_SEVERITY_WARN, __FILE__, __LINE__, LOG_FUNC, format, ##__VA_ARGS__)

extern astra::PluginServiceProxy* __g_serviceProxy;

namespace astra { namespace plugins {

    inline void log(const char* channel,
                    astra_log_severity_t logLevel,
                    const char* fileName,
                    int lineNo,
                    const char* func,
                    const char* format,
                    ...)
    {
        va_list args;
        va_start(args, format);
        __g_serviceProxy->log(channel, logLevel, fileName, lineNo, func, format, args);
        va_end(args);
    }

    inline void vlog(const char* channel,
                     astra_log_severity_t logLevel,
                     const char* fileName,
                     int lineNo,
                     const char* func,
                     const char* format,
                     va_list args)
    {
        __g_serviceProxy->log(channel, logLevel, fileName, lineNo, func, format, args);
    }
}}
#endif /* ASTRA_PLUGIN_LOGGING_HPP */
