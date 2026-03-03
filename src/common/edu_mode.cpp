#include "common/edu_mode.h"

namespace Edu
{
    static bool g_enabled = false;

    void SetEnabled(bool enabled) { g_enabled = enabled; }
    bool IsEnabled() { return g_enabled; }
}
