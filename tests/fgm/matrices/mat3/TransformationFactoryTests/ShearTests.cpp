/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 29, 2026
 *
 * @brief Verify @ref fgm::Mat3 shear factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */

namespace
{
    /**************************************
     *                                    *
     *             TEST SETUP             *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref Mat3 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3ShearTests: public testing::Test
    {
    protected:
        T _shearFactor1, _shearFactor2;
        fgm::Mat3<T> _shearX2D, _shearY2D, _shearX3D, _shearY3D, _shearZ3D;


        void SetUp() override
        {
            _shearFactor1 = T(22.58923191238);
            _shearFactor1 = T(3.16);

            _shearX2D = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ _shearFactor1, T(1), T(0) },
                          fgm::Vec3{ T(0), T(0), T(1) } };
            _shearY2D = {
                fgm::Vec3{ T(1), _shearFactor1, T(0) },
                fgm::Vec3{ T(0), T(1), T(0) },
                fgm::Vec3{ T(0), T(0), T(1) },
            };

            _shearX3D = {
                fgm::Vec3{ T(1), _shearFactor1, _shearFactor2 },
                fgm::Vec3{ T(0), T(1), T(0) },
                fgm::Vec3{ T(0), T(0), T(1) },
            };

            _shearY3D = {
                fgm::Vec3{ T(1), T(0), T(0) },
                fgm::Vec3{ _shearFactor2, T(1), _shearFactor1 },
                fgm::Vec3{ T(0), T(0), T(1) },
            };

            _shearZ3D = {
                fgm::Vec3{ T(1), T(0), T(0) },
                fgm::Vec3{ T(0), T(1), T(0) },
                fgm::Vec3{ _shearFactor1, _shearFactor2, T(1) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat3ShearTests, SupportedArithmeticTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/
    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR1 = 22;
        constexpr auto SHEAR_FACTOR2 = 316;

        /// @test Verify that @ref Mat3 makeShearX2D by x-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR2D_X_MAT = fgm::Mat3<int>::makeShearX2D(SHEAR_FACTOR1);
        static_assert(SHEAR2D_X_MAT[0] == fgm::Vec3{ 1, 0, 0 });
        static_assert(SHEAR2D_X_MAT[1] == fgm::Vec3{ SHEAR_FACTOR1, 1, 0 });
        static_assert(SHEAR2D_X_MAT[2] == fgm::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearY2D by y-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR2D_Y_MAT = fgm::Mat3<int>::makeShearY2D(SHEAR_FACTOR1);
        static_assert(SHEAR2D_Y_MAT[0] == fgm::Vec3{ 1, SHEAR_FACTOR1, 0 });
        static_assert(SHEAR2D_Y_MAT[1] == fgm::Vec3{ 0, 1, 0 });
        static_assert(SHEAR2D_Y_MAT[2] == fgm::Vec3{ 0, 0, 1 });


        /// @test Verify that @ref Mat3 makeShearX3D by x-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_X_MAT = fgm::Mat3<int>::makeShearX3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_X_MAT[0] == fgm::Vec3{ 1, SHEAR_FACTOR1, SHEAR_FACTOR2 });
        static_assert(SHEAR3D_X_MAT[1] == fgm::Vec3{ 0, 1, 0 });
        static_assert(SHEAR3D_X_MAT[2] == fgm::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearY3D by y-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_Y_MAT = fgm::Mat3<int>::makeShearY3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_Y_MAT[0] == fgm::Vec3{ 1, 0, 0 });
        static_assert(SHEAR3D_Y_MAT[1] == fgm::Vec3{ SHEAR_FACTOR2, 1, SHEAR_FACTOR1 });
        static_assert(SHEAR3D_Y_MAT[2] == fgm::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShearZ3D by z-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR3D_Z_MAT = fgm::Mat3<int>::makeShearZ3D(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR3D_Z_MAT[0] == fgm::Vec3{ 1, 0, 0 });
        static_assert(SHEAR3D_Z_MAT[1] == fgm::Vec3{ 0, 1, 0 });
        static_assert(SHEAR3D_Z_MAT[2] == fgm::Vec3{ SHEAR_FACTOR1, SHEAR_FACTOR2, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat3ShearTests, ShearX2D_ReturnsAValid3DAffineShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX2D, fgm::Mat3<TypeParam>::makeShearX2D(this->_shearFactor1)); }


TYPED_TEST(Mat3ShearTests, ShearY2D_ReturnsAValid3DAffineShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY2D, fgm::Mat3<TypeParam>::makeShearY2D(this->_shearFactor1)); }


TYPED_TEST(Mat3ShearTests, ShearX3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX3D, fgm::Mat3<TypeParam>::makeShearX3D(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat3ShearTests, ShearY3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY3D, fgm::Mat3<TypeParam>::makeShearY3D(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat3ShearTests, ShearZ3D_ReturnsAValid3DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearZ3D, fgm::Mat3<TypeParam>::makeShearZ3D(this->_shearFactor1, this->_shearFactor2)); }


/** @} */
