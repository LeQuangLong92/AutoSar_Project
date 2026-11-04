#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint8_t   boolean;

#ifndef TRUE
#define TRUE   (1u)
#endif
#ifndef FALSE
#define FALSE  (0u)
#endif

typedef uint8 Std_ReturnType;
#define E_OK      ((Std_ReturnType)0u)
#define E_NOT_OK  ((Std_ReturnType)1u)

typedef uint16 PduIdType;
typedef uint16 PduLengthType;

typedef struct
{
    uint8         *SduDataPtr;
    PduLengthType  SduLength;
} PduInfoType;

typedef uint32 Can_IdType;

#endif