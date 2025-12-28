// 設定が変わらないため。現状使用不可(2025.12.27yori)
// ChatGpt生成コード(2025.12.27yori)
// 最適パフォーマンスへ切替→終了時(例外、クラッシュ時も対応)に復帰 (Win10/11対応)
// Windows11では 電源プランを変更してもUI上の「電源モード」は変わらない場合があるため、
// EPP(Energy Performance Preference)も併せて設定しないと「最適なパフォーマンス」にならないことが多いです。
// UIが変わらない＝無効ではなく、EPP優先の挙動）

#define INITGUID
#include "PowerPlanRAII.h"
#include <windows.h>
#include <powrprof.h>
#pragma comment(lib, "PowrProf.lib")

// ===== GUID定義（外部シンボル未解決対策用）=====
DEFINE_GUID(GUID_HIGH_PERFORMANCE,
    0x8c5e7fda, 0xe8bf, 0x4a96, 0x9a, 0x85, 0xa6, 0xe2, 0x96, 0xb0, 0x1f, 0x1f);

DEFINE_GUID(GUID_ULTIMATE_PERFORMANCE,
    0xe9a42b02, 0xd5df, 0x448d, 0xaa, 0x00, 0x03, 0xf1, 0x47, 0x49, 0xeb, 0x61);

DEFINE_GUID(GUID_PROCESSOR_PERF_ENERGY_PREF,
    0x36687f9e, 0xe3a5, 0x4dbf, 0xb1, 0xdc, 0x15, 0xeb, 0x38, 0x6f, 0x5f, 0xb5);


// ===== RAII 実装 =====
PowerPlanRAII::PowerPlanRAII(bool useUltimate)
{
    GUID* pGuid = nullptr;
    if (PowerGetActiveScheme(NULL, &pGuid) == ERROR_SUCCESS)
    {
        originalPlan = *pGuid;
        LocalFree(pGuid);
    }

    const GUID& target = (useUltimate ? GUID_ULTIMATE_PERFORMANCE : GUID_HIGH_PERFORMANCE);

    // プラン切替
    PowerSetActiveScheme(NULL, &target);

    // ---- Windows11でUIに反映されないが内部は切替させる処理 ----
    DWORD epp = 0; // 0=性能最優先（100で省電力）
    PowerWriteACValueIndex(NULL, &target,
        &GUID_PROCESSOR_SETTINGS_SUBGROUP,
        &GUID_PROCESSOR_PERF_ENERGY_PREF, epp);

    PowerWriteDCValueIndex(NULL, &target,
        &GUID_PROCESSOR_SETTINGS_SUBGROUP,
        &GUID_PROCESSOR_PERF_ENERGY_PREF, epp);

    // 変更確定（重要）
    PowerSetActiveScheme(NULL, &target);    
}

PowerPlanRAII::~PowerPlanRAII()
{
    Restore();
}

void PowerPlanRAII::Restore()
{
    if (!restored)
    {
        PowerSetActiveScheme(NULL, &originalPlan);
        restored = true;
    }
}