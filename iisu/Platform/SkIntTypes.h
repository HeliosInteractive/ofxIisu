#pragma once

// provide default basic implementation of <stdint.h>
typedef signed __int8		int8_t;
typedef signed __int16		int16_t;
typedef signed __int32		int32_t;
typedef signed __int64		int64_t;

typedef unsigned __int8		uint8_t;
typedef unsigned __int8		uchar;
typedef unsigned __int16	uint16_t;
typedef unsigned __int16	ushort;
typedef unsigned __int32	uint32_t;
typedef unsigned __int32	uint;
typedef unsigned __int64	uint64_t;

#define	INT8_MIN		int8_t(-128)
#define	INT8_MAX		int8_t(127)

#define	UINT8_MIN		uint8_t(0)
#define	UINT8_MAX		uint8_t(255)

#define	INT16_MIN		int16_t(-32768)
#define	INT16_MAX		int16_t(32767)

#define	UINT16_MIN		uint16_t(0)
#define	UINT16_MAX		uint16_t(65535)

#define	INT32_MIN		int32_t(0x80000000)
#define	INT32_MAX		int32_t(0x7FFFFFFF)

#define	UINT32_MIN		uint32_t(0)
#define	UINT32_MAX		uint32_t(0xFFFFFFFF)

#define	INT64_MIN		int64_t(0x8000000000000000)
#define	INT64_MAX		int64_t(0x7FFFFFFFFFFFFFFF)

#define	UINT64_MIN		uint64_t(0)
#define	UINT64_MAX		uint64_t(0xFFFFFFFFFFFFFFFF)