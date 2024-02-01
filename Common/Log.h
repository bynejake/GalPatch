#pragma once

#include <format>

#ifdef _DEBUG
#define LOG(fmt, ...) OutputDebugString(std::format(fmt, __VA_ARGS__).c_str())
#else
#define LOG(fmt, ...)
#endif
