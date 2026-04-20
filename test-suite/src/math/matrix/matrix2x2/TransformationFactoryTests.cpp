/**
 * @file TransformationFactoryTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2D transformation factory function (E.g: MakeRotation, MakeScale, etc.) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"
#include <utility>


// TODO: Add static tests

template <typename T>
class Matrix2DRotation: public ::testing::Test
{
protected:
    using FP_T = T::first_type;   // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix2D<COM_T> _expectedMat;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FMG_LEFT_HANDED
        _expectedMat = { fgm::Vector2D{ COM_T(0), COM_T(-1) }, fgm::Vector2D { COM_T(1), COM_T(0) } };
#else
        _expectedMat = { fgm::Vector2D{ COM_T(0), COM_T(1) }, fgm::Vector2D{ COM_T(-1), COM_T(0) } };
#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix2DRotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Matrix2DUniformScale: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;
    T _scale;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector2D{ T(5.3821839321), T(0) }, fgm::Vector2D{ T(0), T(5.3821839321) } };
        _scale = T(5.3821839321);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DUniformScale, SupportedArithmeticTypes);


template <typename T>
class Matrix2DNonUniformScale: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;
    T _scaleX, _scaleY;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector2D{ T(5.3821839321), T(0) }, fgm::Vector2D{ T(0), T(8.1234921348) } };
        _scaleX = T(5.3821839321);
        _scaleY = T(8.1234921348);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D non-uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DNonUniformScale, SupportedArithmeticTypes);


template <typename T>
class Matrix2DNoReflection: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vector2D{ T(1), T(0) }, fgm::Vector2D{ T(0), T(1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DNoReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2DXAxisReflection: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector2D{ T(-1), T(0) }, fgm::Vector2D{ T(0), T(1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DXAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2DYAxisReflection: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vector2D{ T(1), T(0) }, fgm::Vector2D{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D reflection along y-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DYAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2DOriginReflection: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vector2D{ T(-1), T(0) }, fgm::Vector2D{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D reflection along the origin(0, 0), parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2DOriginReflection, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

/**************************************
 *                                    *
 *         COMPILE TIME TESTS         *
 *                                    *
 **************************************/
namespace
{
    // TODO: Add tests
}



/**************************************
 *                                    *
 *           ROTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory returns a rotation matrix. */
TYPED_TEST(Matrix2DRotation, ReturnsRotationMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<typename TypeParam::first_type>::makeRotation(this->_angle));
}



/**************************************
 *                                    *
 *            SCALE TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Matrix2DUniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeScale(this->_scale));
}


/** @brief Verify that non-uniform scale transformation factory returns a non-uniform scale matrix. */
TYPED_TEST(Matrix2DNonUniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeScale(this->_scaleX, this->_scaleY));
}



/**************************************
 *                                    *
 *          REFLECTION TESTS          *
 *                                    *
 **************************************/

/** 
 * @brief Verify that reflection transformation factory for no reflection along any axis 
 *        returns a reflection matrix. 
 */
TYPED_TEST(Matrix2DNoReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeReflection(false, false));
}


/** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
TYPED_TEST(Matrix2DXAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeReflection(true, false));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Matrix2DYAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeReflection(false, true));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Matrix2DOriginReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeReflection(true, true));
}

/** @} */
