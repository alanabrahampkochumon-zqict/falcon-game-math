#include <gtest/gtest.h>
#include <SIMDUtils.h>

struct TestData
{
	std::size_t totalByteSize;
	std::size_t expectedByteSize;
	std::size_t padding;
};

class PackedSizeCalculatorParams: public ::testing::TestWithParam<TestData>{};

TEST_P(PackedSizeCalculatorParams, CalculatesCorrectSize)
{
	// Given an arbitrary data type size and total byte size
	const auto [totalByteSize, expectedByteSize, expectedPadding] = GetParam();

	// When packed size is calculated
	falcon::simd::PackedSize packedSize = falcon::simd::calculatePackedSize(totalByteSize);

	// It gives the nearest packed size and padding
	EXPECT_EQ(expectedByteSize, packedSize.alignedByteSize);
	EXPECT_EQ(expectedPadding, packedSize.padding);
}

INSTANTIATE_TEST_SUITE_P(
	PackedSizeCalculatorTests,
	PackedSizeCalculatorParams,
	::testing::Values(
		TestData {1, 16, 15 }, 
		TestData {4, 16, 12 }, 
		TestData {  8, 16, 8 }, 
		TestData { 12, 16, 4 }, 
		TestData { 16, 16, 0 }, 
		TestData {  20, 32, 12 }, 
		TestData {  24, 32, 8 },
		TestData {  32, 32, 0 },
		TestData {  48, 64, 16 },
		TestData {  56, 64, 8 },
		TestData {  64, 64, 0 },
		TestData {  72, 128, 56 },
		TestData {  80, 128, 48 },
		TestData {  128, 128, 0 },
		TestData {  192, 256, 64 },
		TestData {  256, 256, 0 },
		TestData {  512, 512, 0 },
		TestData {  777, 1024, 247 },
		TestData {  1024, 1024, 0 }
	)

//INSTANTIATE_TEST_SUITE_P(
//	PackedSizeCalculatorTests,
//	PackedSizeCalculatorParams,
//	::testing::Values(
//		TestData{sizeof(float), 4, 16, 12}, // 1d float vec
//		TestData{sizeof(float),  8, 16, 8}, // 2d float vec
//		TestData{sizeof(float), 12, 16, 4}, // 3d float vec
//		TestData{sizeof(float), 16, 16, 0}, // 4d float vec
//		TestData { sizeof(double), 8, 16, 8}, // 1d double vec
//		TestData { sizeof(double), 16, 16, 0}, // 1d double vec
//		TestData { sizeof(double), 24, 32, 8}, // 3d double vec
//		TestData { sizeof(double), 32, 32, 0}, // 4d double vec
//
//		TestData{sizeof(char), 9, 16}, // 3x3 char matrix
//		TestData{sizeof(short), 18, 32}, // 3x3 short matrix
//		TestData{sizeof(float), 36, 64}, // 3x3 float matrix
//		TestData{sizeof(double), 72, 128}, // 3x3 double matrix
//
//		TestData{sizeof(double), 128, 128}, // 4x4 double matrix
//		TestData{sizeof(double), 96, 128}, // 3x4 double matrix
//		TestData{sizeof(unsigned char), 16, 16}, // 4x4 uchar matrix
//		TestData{sizeof(float), 64, 64}, // 4x4 float matrix
//		TestData{sizeof(short), 32, 32}, // 4x4 short matrix
//		TestData{sizeof(char), 17, 32}, // 1 byte over 16 byte limit
//		TestData{sizeof(char), 33, 64}, // 1 byte over 32 byte limit
//		TestData{sizeof(char), 65, 128} // 1 byte over 64 byte limit
//	)
);
