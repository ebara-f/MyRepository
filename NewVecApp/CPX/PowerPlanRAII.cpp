// ChatGptê∂ê¨ÉRÅ[Éh(2026.2.15yori)
#define INITGUID
#include "PowerPlanRAII.h"

DEFINE_GUID(GUID_HIGH_PERFORMANCE,
    0x8c5e7fda, 0xe8bf, 0x4a96, 0x9a, 0x85, 0xa6, 0xe2, 0x3a, 0x8c, 0x63, 0x5c);

DEFINE_GUID(GUID_BALANCED,
    0x381b4222, 0xf694, 0x41f0, 0x96, 0x85, 0xff, 0x5b, 0xb2, 0x60, 0xdf, 0x2e);

DEFINE_GUID(GUID_POWER_SAVER,
    0xa1841308, 0x3541, 0x4fab, 0xbc, 0x81, 0xf7, 0x15, 0x56, 0xf2, 0x0b, 0x4a);

PowerPlanGUID::PowerPlanGUID(const GUID& target)
{
    GUID* pCurrent = nullptr;

    if (PowerGetActiveScheme(nullptr, &pCurrent) != ERROR_SUCCESS)
        return;

    m_original = *pCurrent;
    LocalFree(pCurrent);

    if (!IsEqualGUID(m_original, target))
    {
        if (PowerSetActiveScheme(nullptr, &target) == ERROR_SUCCESS)
            m_changed = true;
    }
}

PowerPlanGUID::~PowerPlanGUID()
{
    if (m_changed)
        PowerSetActiveScheme(nullptr, &m_original);
}