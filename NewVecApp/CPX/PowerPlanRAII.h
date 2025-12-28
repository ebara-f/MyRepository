// ChatGpt生成コード(2025.12.27yori)
#pragma once
#include <windows.h>
#include <powrprof.h>

#pragma comment(lib, "PowrProf.lib")

// ---------- GUID extern宣言のみ（実体はcppへ）----------
extern const GUID GUID_HIGH_PERFORMANCE;
extern const GUID GUID_ULTIMATE_PERFORMANCE;
extern const GUID GUID_PROCESSOR_PERF_ENERGY_PREF;

// ---------- RAIIクラス宣言 ----------
class PowerPlanRAII
{
private:
    GUID originalPlan{};
    bool restored = false;

public:
    PowerPlanRAII(bool useUltimate = true);
    ~PowerPlanRAII();

    void Restore();
};