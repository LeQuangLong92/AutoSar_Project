#include "unity.h"
#include "swc_overspeed.h"
#include "rte_swc.h"

/* ---------- Stub RTE ---------- */
static Std_ReturnType Stub_ReadRet;
static uint16_t       Stub_Speed;
static boolean        Stub_Warn;
static uint8_t        Stub_WriteCnt;

Std_ReturnType Rte_Read_VehSpeed(uint16_t *speed)
{
    *speed = Stub_Speed;
    return Stub_ReadRet;
}

Std_ReturnType Rte_Write_OverSpeedWarn(boolean warn)
{
    Stub_Warn = warn;
    Stub_WriteCnt++;
    return E_OK;
}

static void RunCycles(uint16_t speed, uint8_t n)
{
    uint8_t i;
    Stub_Speed = speed;
    for (i = 0u; i < n; i++) { Swc_Run_OverSpeedWarning(); }
}

void setUp(void)
{
    Stub_ReadRet  = RTE_E_OK;
    Stub_Speed    = 0u;
    Stub_Warn     = FALSE;
    Stub_WriteCnt = 0u;
    Swc_OverSpeed_Init();
}

void tearDown(void) { }

/* ---------- Test ---------- */

void test_Speed_BelowThreshold_NoWarning(void)
{
    RunCycles(100u, 5u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_Speed_ExactlyThreshold_NoWarning(void)
{
    RunCycles(120u, 5u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_Speed_AboveThreshold_WarnOnlyAfter3Cycles(void)
{
    RunCycles(121u, 2u);
    TEST_ASSERT_FALSE(Stub_Warn);
    RunCycles(121u, 1u);
    TEST_ASSERT_TRUE(Stub_Warn);
}

void test_Speed_DropsBelowThreshold_ClearsWarning(void)
{
    RunCycles(150u, 3u);
    TEST_ASSERT_TRUE(Stub_Warn);
    RunCycles(100u, 1u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_Speed_InterruptedByNormalValue_DebounceRestarts(void)
{
    RunCycles(150u, 2u);
    RunCycles(100u, 1u);                 /* làm đứt chuỗi 3 chu kỳ liên tiếp */
    RunCycles(150u, 2u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_RteReadFails_WarningOff_FailSafe(void)
{
    RunCycles(150u, 3u);
    TEST_ASSERT_TRUE(Stub_Warn);

    Stub_ReadRet = RTE_E_MAX_AGE_EXCEEDED;
    RunCycles(150u, 1u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_RteReadFails_ResetsDebounce(void)
{
    RunCycles(150u, 2u);
    Stub_ReadRet = RTE_E_INVALID;
    RunCycles(150u, 1u);
    Stub_ReadRet = RTE_E_OK;
    RunCycles(150u, 2u);
    TEST_ASSERT_FALSE(Stub_Warn);
}

void test_EachCycle_WritesOutputExactlyOnce(void)
{
    RunCycles(100u, 4u);
    TEST_ASSERT_EQUAL_UINT8(4u, Stub_WriteCnt);
}

void test_Speed_StaysAbove_ManyCycles_WarningStaysOn(void)
{
    RunCycles(150u, 10u);                /* vượt nhiều hơn 3 chu kỳ liên tiếp */
    TEST_ASSERT_TRUE(Stub_Warn);

    RunCycles(100u, 1u);                 /* một chu kỳ bình thường phải tắt ngay */
    TEST_ASSERT_FALSE(Stub_Warn);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Speed_BelowThreshold_NoWarning);
    RUN_TEST(test_Speed_ExactlyThreshold_NoWarning);
    RUN_TEST(test_Speed_AboveThreshold_WarnOnlyAfter3Cycles);
    RUN_TEST(test_Speed_DropsBelowThreshold_ClearsWarning);
    RUN_TEST(test_Speed_InterruptedByNormalValue_DebounceRestarts);
    RUN_TEST(test_RteReadFails_WarningOff_FailSafe);
    RUN_TEST(test_RteReadFails_ResetsDebounce);
    RUN_TEST(test_EachCycle_WritesOutputExactlyOnce);
    RUN_TEST(test_Speed_StaysAbove_ManyCycles_WarningStaysOn);
    return UNITY_END();
}