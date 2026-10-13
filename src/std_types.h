#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

typedef uint8_t Std_ReturnType;

#define E_OK      ((Std_ReturnType)0x00u)
#define E_NOT_OK  ((Std_ReturnType)0x01u)
#define NULL_PTR  ((void *)0)

#endif /* STD_TYPES_H */