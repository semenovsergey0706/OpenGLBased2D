#pragma once

struct NonCopyable
{
    NonCopyable() = default;

    NonCopyable(NonCopyable&&) noexcept = default;
    NonCopyable& operator = (NonCopyable&&) noexcept = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator = (const NonCopyable&) = delete;
};