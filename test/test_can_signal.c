#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__has_include)
#  if __has_include("unity.h")
#    include "unity.h"
#  else
#    define UNITY_BEGIN() 0
#    define UNITY_END() 0
#    define RUN_TEST(test) do { (test)(); } while (0)
#    define TEST_ASSERT_EQUAL_UINT8(expected, actual) do { \
        if ((uint8_t)(expected) != (uint8_t)(actual)) { \
            fprintf(stderr, "ASSERTION FAILED: %s:%d expected %u, got %u\n", __FILE__, __LINE__, (unsigned)(expected), (unsigned)(actual)); \
            exit(1); \
        } \
    } while (0)
#    define TEST_ASSERT_EQUAL_HEX8(expected, actual) TEST_ASSERT_EQUAL_UINT8((expected), (actual))
#    define TEST_ASSERT_EQUAL_UINT32(expected, actual) do { \
        if ((uint32_t)(expected) != (uint32_t)(actual)) { \
            fprintf(stderr, "ASSERTION FAILED: %s:%d expected %u, got %u\n", __FILE__, __LINE__, (unsigned)(expected), (unsigned)(actual)); \
            exit(1); \
        } \
    } while (0)
#    define TEST_ASSERT_EQUAL_HEX32(expected, actual) TEST_ASSERT_EQUAL_UINT32((expected), (actual))
#    define TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, length) do { \
        size_t i; \
        for (i = 0u; i < (size_t)(length); ++i) { \
            if ((expected)[i] != (actual)[i]) { \
                fprintf(stderr, "ASSERTION FAILED: %s:%d array mismatch at index %zu expected %u, got %u\n", __FILE__, __LINE__, i, (unsigned)(expected)[i], (unsigned)(actual)[i]); \
                exit(1); \
            } \
        } \
    } while (0)
#  endif
#else
#  include "unity.h"
#endif

#include "can_signal.h"

#ifndef E_OK
#define E_OK 0u
#endif
#ifndef E_NOT_OK
#define E_NOT_OK 1u
#endif
#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

static uint8_t frame[8];

void setUp(void)
{
    uint8_t i;
    for (i = 0u; i < 8u; i++) { frame[i] = 0u; }
}

void tearDown(void) { }

/* ---------- Unpack ---------- */

void test_Unpack_Speed16bit_AlignedAtByte0(void)
{
    uint32_t raw = 0u;
    frame[0] = 0xC8u; frame[1] = 0x32u;                 /* 0x32C8 = 13000 */

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_UnpackIntel(frame, 8u, 0u, 16u, &raw));
    TEST_ASSERT_EQUAL_UINT32(13000u, raw);
}

void test_Unpack_Signal_NotByteAligned(void)
{
    uint32_t raw = 0u;
    frame[0] = 0xA0u; frame[1] = 0x05u;                 /* bit 4..11 = 0x5A */

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_UnpackIntel(frame, 8u, 4u, 8u, &raw));
    TEST_ASSERT_EQUAL_HEX32(0x5Au, raw);
}

void test_Unpack_SingleBit_Bit7(void)
{
    uint32_t raw = 0u;
    frame[0] = 0x80u;

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_UnpackIntel(frame, 8u, 7u, 1u, &raw));
    TEST_ASSERT_EQUAL_UINT32(1u, raw);
}

void test_Unpack_LastBitOfFrame_Valid(void)
{
    uint32_t raw = 0u;
    frame[7] = 0x80u;

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_UnpackIntel(frame, 8u, 63u, 1u, &raw));
    TEST_ASSERT_EQUAL_UINT32(1u, raw);
}

void test_Unpack_ExceedsFrame_ReturnsNotOk(void)
{
    uint32_t raw = 1234u;

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_UnpackIntel(frame, 8u, 60u, 8u, &raw));
    TEST_ASSERT_EQUAL_UINT32(1234u, raw);               /* output không bị ghi đè */
}

void test_Unpack_InvalidLength_ReturnsNotOk(void)
{
    uint32_t raw = 0u;

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_UnpackIntel(frame, 8u, 0u, 0u, &raw));
    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_UnpackIntel(frame, 8u, 0u, 33u, &raw));
}

void test_Unpack_NullPointers_ReturnNotOk(void)
{
    uint32_t raw = 0u;

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_UnpackIntel(NULL_PTR, 8u, 0u, 8u, &raw));
    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_UnpackIntel(frame, 8u, 0u, 8u, NULL_PTR));
}

/* ---------- Pack ---------- */

void test_Pack_Speed16bit_WritesCorrectBytes(void)
{
    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_PackIntel(frame, 8u, 0u, 16u, 13000u));
    TEST_ASSERT_EQUAL_HEX8(0xC8u, frame[0]);
    TEST_ASSERT_EQUAL_HEX8(0x32u, frame[1]);
    TEST_ASSERT_EQUAL_HEX8(0x00u, frame[2]);            /* byte khác không bị đụng tới */
}

void test_Pack_DoesNotChangeNeighbourBits(void)
{
    uint8_t expected[8] = { 0x0Fu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu };
    uint8_t i;
    for (i = 0u; i < 8u; i++) { frame[i] = 0xFFu; }

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_PackIntel(frame, 8u, 4u, 4u, 0u));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, frame, 8);
}

void test_Pack_ValueTooLargeForLength_ReturnsNotOk_FrameUnchanged(void)
{
    frame[0] = 0xAAu;

    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_PackIntel(frame, 8u, 0u, 4u, 16u));  /* 16 cần 5 bit */
    TEST_ASSERT_EQUAL_HEX8(0xAAu, frame[0]);
}

void test_Pack_MaxValueFor4Bits_Valid(void)
{
    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_PackIntel(frame, 8u, 0u, 4u, 15u));
    TEST_ASSERT_EQUAL_HEX8(0x0Fu, frame[0]);
}

void test_Pack_NullFrame_ReturnsNotOk(void)
{
    TEST_ASSERT_EQUAL_UINT8(E_NOT_OK, Can_PackIntel(NULL_PTR, 8u, 0u, 8u, 1u));
}

/* ---------- Pack rồi Unpack phải ra giá trị ban đầu ---------- */

void test_PackThenUnpack_RoundTrip(void)
{
    uint32_t raw = 0u;

    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_PackIntel(frame, 8u, 11u, 13u, 0x1ABCu));
    TEST_ASSERT_EQUAL_UINT8(E_OK, Can_UnpackIntel(frame, 8u, 11u, 13u, &raw));
    TEST_ASSERT_EQUAL_HEX32(0x1ABCu, raw);
}

/* ---------- Runner ---------- */

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Unpack_Speed16bit_AlignedAtByte0);
    RUN_TEST(test_Unpack_Signal_NotByteAligned);
    RUN_TEST(test_Unpack_SingleBit_Bit7);
    RUN_TEST(test_Unpack_LastBitOfFrame_Valid);
    RUN_TEST(test_Unpack_ExceedsFrame_ReturnsNotOk);
    RUN_TEST(test_Unpack_InvalidLength_ReturnsNotOk);
    RUN_TEST(test_Unpack_NullPointers_ReturnNotOk);
    RUN_TEST(test_Pack_Speed16bit_WritesCorrectBytes);
    RUN_TEST(test_Pack_DoesNotChangeNeighbourBits);
    RUN_TEST(test_Pack_ValueTooLargeForLength_ReturnsNotOk_FrameUnchanged);
    RUN_TEST(test_Pack_MaxValueFor4Bits_Valid);
    RUN_TEST(test_Pack_NullFrame_ReturnsNotOk);
    RUN_TEST(test_PackThenUnpack_RoundTrip);
    return UNITY_END();
}