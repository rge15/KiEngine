#include "KiEngine.hpp"

KiEngine::KiEngine(String p_appName, size_t p_w, size_t p_h) noexcept
: driver_ { p_appName, p_w, p_h }
{
}