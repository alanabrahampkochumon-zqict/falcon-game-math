#pragma once

#include <cstddef>

namespace falcon::simd
{
	struct PackedSize
	{
		std::size_t alignedByteSize;
		std::size_t padding;
	};

	constexpr PackedSize calculatePackedSize(std::size_t totalByteSize)
	{
		return PackedSize { totalByteSize, 0 };
	}
}
