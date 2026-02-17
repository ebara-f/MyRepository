// ChatGptê∂ê¨ÉRÅ[Éh(2026.2.15yori)
#pragma once
#include <windows.h>
#include <powrprof.h>

#pragma comment(lib, "PowrProf.lib")

extern const GUID GUID_HIGH_PERFORMANCE;
extern const GUID GUID_BALANCED;
extern const GUID GUID_POWER_SAVER;

class PowerPlanGUID
{
public:
    PowerPlanGUID(const GUID& target);
    ~PowerPlanGUID();

    bool Changed() const { return m_changed; }

private:
    GUID m_original{};
    bool m_changed = false;
};