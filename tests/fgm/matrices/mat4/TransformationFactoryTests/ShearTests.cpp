/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref fgm::Mat4 shear factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FGM_Mat4x4_Transforms
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
     * @brief Test fixture for @ref Mat4 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4Shear: public testing::Test
    {
    protected:
        T _shearFactor1, _shearFactor2;
        fgm::Mat4<T> _shearX, _shearY, _shearZ;


        void SetUp() override
        {
            _shearFactor1 = T(22.58923191238);
            _shearFactor2 = T(3.16);
            _shearX = { fgm::Vec4{ T(1), _shearFactor1, _shearFactor2, T(0) }, fgm::Vec4{ T(0), T(1), T(0), T(0) },
                        fgm::Vec4{ T(0), T(0), T(1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
            _shearY = { fgm::Vec4{ T(1), T(0), T(0), T(0) }, fgm::Vec4{ _shearFactor1, T(1), _shearFactor2, T(0) },
                        fgm::Vec4{ T(0), T(0), T(1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
            _shearZ = { fgm::Vec4{ T(1), T(0), T(0), T(0) }, fgm::Vec4{ T(0), T(1), T(0), T(0) },
                        fgm::Vec4{ _shearFactor1, _shearFactor2, T(1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4Shear, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref Mat4 shear transform factory skewing along any arbitrary unit vector.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    // template <typename T>
    // class Mat4ArbitraryShear: public testing::Test
    // {
    // protected:
    //     T _shearAngle;
    //     T _shearFactor;
    //     fgm::Vec4<T> _shearDirection, _shearPlaneNormal;
    //     fgm::Mat4<T> _shear;
    //
    //     void SetUp() override
    //     {
    //         _shearAngle       = T(3.1415 / 4);
    //         _shearFactor      = T(1);
    //         _shearDirection   = fgm::Vec4{ T(0.2672612419124244), T(0.5345224838248488), T(0.8017837257372732) };
    //         _shearPlaneNormal = fgm::Vec4{ T(0.48471791416315496), T(0.5728484440110013), T(0.6609789738588476) };
    //         _shear = fgm::Mat4{ fgm::Vec4{ T(1.1295403103900423), T(0.1530930940973227), T(0.17664587780460309) },
    //                             fgm::Vec4{ T(0.25908062078008454), T(1.3061861881946455), T(0.35329175560920617) },
    //                             fgm::Vec4{ T(0.38862093117012675), T(0.459279282291968), T(1.5299376334138093) } };
    //     }
    // };
    // TYPED_TEST_SUITE(Mat4ArbitraryShear, SupportedFloatingPointTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/
    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR1 = 22;
        constexpr auto SHEAR_FACTOR2 = 316;


        /// @test Verify that @ref Mat4 makeShearX by x-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_X_MAT = fgm::Mat4<int>::makeShearX(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_X_MAT[0] == fgm::Vec4{ 1, SHEAR_FACTOR1, SHEAR_FACTOR2, 0 });
        static_assert(SHEAR4D_X_MAT[1] == fgm::Vec4{ 0, 1, 0, 0 });
        static_assert(SHEAR4D_X_MAT[2] == fgm::Vec4{ 0, 0, 1, 0 });
        static_assert(SHEAR4D_X_MAT[3] == fgm::Vec4{ 0, 0, 0, 1 });

        /// @test Verify that @ref Mat4 makeShearY by y-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_Y_MAT = fgm::Mat4<int>::makeShearY(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_Y_MAT[0] == fgm::Vec4{ 1, 0, 0, 0 });
        static_assert(SHEAR4D_Y_MAT[1] == fgm::Vec4{ SHEAR_FACTOR1, 1, SHEAR_FACTOR2, 0 });
        static_assert(SHEAR4D_Y_MAT[2] == fgm::Vec4{ 0, 0, 1, 0 });
        static_assert(SHEAR4D_Y_MAT[3] == fgm::Vec4{ 0, 0, 0, 1 });

        /// @test Verify that @ref Mat4 makeShearZ by z-axis returns a valid 4D shear matrix at compile time.
        constexpr auto SHEAR4D_Z_MAT = fgm::Mat4<int>::makeShearZ(SHEAR_FACTOR1, SHEAR_FACTOR2);
        static_assert(SHEAR4D_Z_MAT[0] == fgm::Vec4{ 1, 0, 0, 0 });
        static_assert(SHEAR4D_Z_MAT[1] == fgm::Vec4{ 0, 1, 0, 0 });
        static_assert(SHEAR4D_Z_MAT[2] == fgm::Vec4{ SHEAR_FACTOR1, SHEAR_FACTOR2, 1, 0 });
        static_assert(SHEAR4D_Y_MAT[3] == fgm::Vec4{ 0, 0, 0, 1 });

        // /// TODO: Add shear by angle static tests after making tan compile time.
        //
        //
        // /// @test Verify that @ref Mat4 makeShear returns a valid 4D shear matrix at compile time.
        // constexpr auto SHEAR4D_MAT =
        //     fgm::Mat4<float>::makeShear(1.0f, fgm::Vec4{ 1.0f, 0.0f, 0.0f }, fgm::Vec4{ 0.0f, 0.0f, 1.0f });
        // static_assert(SHEAR4D_MAT[0] == fgm::Vec4{ 1, 0, 0 });
        // static_assert(SHEAR4D_MAT[1] == fgm::Vec4{ 0, 1, 0 });
        // static_assert(SHEAR4D_MAT[2] == fgm::Vec4{ 1, 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat4Shear, ShearX4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearX, fgm::Mat4<TypeParam>::makeShearX(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat4Shear, ShearY4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearY, fgm::Mat4<TypeParam>::makeShearY(this->_shearFactor1, this->_shearFactor2)); }


TYPED_TEST(Mat4Shear, ShearZ4D_ReturnsAValid4DShearMatrix)
{ EXPECT_MAT_EQ(this->_shearZ, fgm::Mat4<TypeParam>::makeShearZ(this->_shearFactor1, this->_shearFactor2)); }


// TYPED_TEST(Mat4ArbitraryShear, ShearByAngle_ReturnsAValid4DShearMatrix)
// {
//     EXPECT_MAT_EQ(
//         this->_shear,
//         fgm::Mat4<TypeParam>::makeShearByAngle(this->_shearAngle, this->_shearPlaneNormal, this->_shearDirection));
// }
//
//
// TYPED_TEST(Mat4ArbitraryShear, Shear_ReturnsAValid4DShearMatrix)
// {
//     EXPECT_MAT_EQ(
//         this->_shear,
//         fgm::Mat4<TypeParam>::makeShear(this->_shearFactor, this->_shearPlaneNormal, this->_shearDirection));
// }


/** @} */
