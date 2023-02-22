#pragma once
#include <utilities/Includes/commonIncludes.hpp>

struct BaseApp
{
    BaseApp() = default;
    ~BaseApp() = default;

    virtual void run() = 0;
};