#pragma once
#include <cstdint>

namespace Warp
{
    using I8 = int8_t;
	using I16 = int16_t;
	using I32 = int32_t;
	using I64 = int64_t;

	using U8  = uint8_t;
	using U16 = uint16_t;
	using U32 = uint32_t;
	using U64 = uint64_t;

	using U32Max = uintmax_t;
	using I32Max = intmax_t;

    constexpr U64 U64InvalidId = std::numeric_limits<U64>::max();
	constexpr U32 U32InvalidId = std::numeric_limits<U32>::max();
	constexpr U16 U16InvalidId = std::numeric_limits<U16>::max();
	constexpr U8  U8InvalidId  = std::numeric_limits<U8>::max();

	constexpr I64 I64InvalidId = std::numeric_limits<I64>::max();
	constexpr I32 I32InvalidId = std::numeric_limits<I32>::max();
	constexpr I16 I16InvalidId = std::numeric_limits<I16>::max();
	constexpr I8  I8InvalidId  = std::numeric_limits<I8>::max();

	using F32 = float;
	using F64 = double;

	using Byte = uint8_t;
}
