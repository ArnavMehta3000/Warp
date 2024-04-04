#pragma once
#include <cstdint>
#include <limits>
namespace Warp
{
    using i8  = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	using u8  = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

    constexpr u64 u64max = std::numeric_limits<u64>::max();
	constexpr u32 u32max = std::numeric_limits<u32>::max();
	constexpr u16 u16max = std::numeric_limits<u16>::max();
	constexpr u8  u8max  = std::numeric_limits<u8>::max();

	constexpr i64 i64max = std::numeric_limits<i64>::max();
	constexpr i32 i32max = std::numeric_limits<i32>::max();
	constexpr i16 i16max = std::numeric_limits<i16>::max();
	constexpr i8  i8max  = std::numeric_limits<i8>::max();

	using f32 = float;
	using f64 = double;

	using byte = uint8_t;
}
