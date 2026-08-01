/**
 * @file ScaleTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Mat3 scale factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "../Mat3TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */
namespace
{

    /**************************************
     *                                    *
     *              SETUP                 *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 uniform scale factory.
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t, float) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3ScaleFactoryUniform: public testing::Test
    {
    protected:
        fgm::Mat3<T> _expectedMat;
        T _scale;

        void SetUp() override
        {
            _expectedMat = { fgm::Vec3{ T(5.3821839321), T(0), T(0) }, fgm::Vec3{ T(0), T(5.3821839321), T(0) },
                             fgm::Vec3{ T(0), T(0), T(5.3821839321) } };
            _scale       = T(5.3821839321);
        }
    };
    TYPED_TEST_SUITE(Mat3ScaleFactoryUniform, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat3 non-uniform scale factory.
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t, float) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3ScaleFactoryNonUniform: public testing::Test
    {
    protected:
        fgm::Mat3<T> _expectedMat;
        T _scaleX, _scaleY, _scaleZ;

        void SetUp() override
        {
            _expectedMat = { fgm::Vec3{ T(5.3821839321), T(0), T(0) }, fgm::Vec3{ T(0), T(8.1234921348), T(0) },
                             fgm::Vec3{ T(0), T(0), T(0.12348921340) } };
            _scaleX      = T(5.3821839321);
            _scaleY      = T(8.1234921348);
            _scaleZ      = T(0.12348921340);
        }
    };
    TYPED_TEST_SUITE(Mat3ScaleFactoryNonUniform, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat3 scale factory for scaling along any vector direction (Floating Point).
     *
     * @tparam T The floating point scalar type (float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3ScaleFactoryDirectionVectorFP: public testing::Test
    {
    protected:
        fgm::Vec3<T> _direction;
        T _scale;
        fgm::Mat3<T> _expectedMat;

        void SetUp() override
        {
            _scale       = 5;
            _direction   = { T(0.2672612419124244), T(0.5345224838248488), T(0.8017837257372732) };
            _expectedMat = { fgm::Vec3{ T(1.2857142857142858), T(0.5714285714285715), T(0.8571428571428572) },
                             fgm::Vec3{ T(0.5714285714285715), T(2.1428571428571432), T(1.7142857142857144) },
                             fgm::Vec3{ T(0.8571428571428572), T(1.7142857142857144), T(3.5714285714285716) } };
        }
    };
    TYPED_TEST_SUITE(Mat3ScaleFactoryDirectionVectorFP, SupportedFloatingPointTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat3 scale factory for scaling along any vector direction (Integrals).
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3ScaleFactoryDirectionVectorInt: public testing::Test
    {
    protected:
        fgm::Vec3<T> _xAxis, _yAxis, _zAxis;
        T _scale;
        fgm::Mat3<T> _expectedMatX, _expectedMatY, _expectedMatZ;

        void SetUp() override
        {
            _scale = 5;
            _xAxis = { T(1), T(0), T(0) };
            _yAxis = { T(0), T(1), T(0) };
            _zAxis = { T(0), T(0), T(1) };

            _expectedMatX = { fgm::Vec3{ T(5), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                              fgm::Vec3{ T(0), T(0), T(1) } };

            _expectedMatX = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(5), T(0) },
                              fgm::Vec3{ T(0), T(0), T(1) } };

            _expectedMatX = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                              fgm::Vec3{ T(0), T(0), T(5) } };
        }
    };
    TYPED_TEST_SUITE(Mat3ScaleFactoryDirectionVectorInt, SupportedFloatingPointTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    /** @brief Verify that scale transform factory is available at compile time.  */
    namespace static_tests
    {
        /// @test Verify that scale transformation factory for uniform scale is available at compile time.
        constexpr auto UNIFORM_SCALE_MAT = fgm::Mat3<int>::makeScale(2);
        static_assert(UNIFORM_SCALE_MAT[0] == fgm::Vec3(2, 0, 0));
        static_assert(UNIFORM_SCALE_MAT[1] == fgm::Vec3(0, 2, 0));
        static_assert(UNIFORM_SCALE_MAT[2] == fgm::Vec3(0, 0, 2));

        /// @test Verify that scale transformation factory for non-uniform scale is available at compile time.
        constexpr auto NON_UNIFORM_SCALE_MAT = fgm::Mat3<int>::makeScale(2, 3, 4);
        static_assert(NON_UNIFORM_SCALE_MAT[0] == fgm::Vec3(2, 0, 0));
        static_assert(NON_UNIFORM_SCALE_MAT[1] == fgm::Vec3(0, 3, 0));
        static_assert(NON_UNIFORM_SCALE_MAT[2] == fgm::Vec3(0, 0, 4));

        /// @test Verify that scale transformation factory for scaling along any direction is available at compile time.
        /// Tests scaling along x-axis.
        constexpr auto SCALE_ANY_DIR = fgm::Mat3<int>::makeScale(2, fgm::Vec3(1, 0, 0));
        static_assert(SCALE_ANY_DIR[0] == fgm::Vec3(2, 0, 0));
        static_assert(SCALE_ANY_DIR[1] == fgm::Vec3(0, 1, 0));
        static_assert(SCALE_ANY_DIR[2] == fgm::Vec3(0, 0, 1));

    } // namespace static_tests


} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat3ScaleFactoryUniform, ReturnsValidScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::makeScale(this->_scale)); }


TYPED_TEST(Mat3ScaleFactoryNonUniform, ReturnsValidScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::makeScale(this->_scaleX, this->_scaleY, this->_scaleZ)); }


TYPED_TEST(Mat3ScaleFactoryDirectionVectorFP, ArbitraryDirectionVector_ReturnsValidScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::makeScale(this->_scale, this->_direction)); }


TYPED_TEST(Mat3ScaleFactoryDirectionVectorInt, XAxis_ReturnsIdentityMatrixWithScaleAppliedAlongTheFirstRow)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Mat3<TypeParam>::makeScale(this->_scale, this->_xAxis)); }


TYPED_TEST(Mat3ScaleFactoryDirectionVectorInt, YAxis_ReturnsIdentityMatrixWithScaleAppliedAlongTheSecondRow)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Mat3<TypeParam>::makeScale(this->_scale, this->_yAxis)); }


TYPED_TEST(Mat3ScaleFactoryDirectionVectorInt, ZAxis_ReturnsIdentityMatrixWithScaleAppliedAlongTheThirdRow)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Mat3<TypeParam>::makeScale(this->_scale, this->_zAxis)); }

/** @} */
