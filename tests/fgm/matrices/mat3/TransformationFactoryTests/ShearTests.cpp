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
        T _shearFactor;
        fgm::Mat3<T> _shearX2D, _shearY2D;


        void SetUp() override
        {
            _shearFactor = T(22.58923191238);
            _shearX2D    = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ _shearFactor, T(1), T(0) },
                             fgm::Vec3{ T(0), T(0), T(1) } };
            _shearY2D    = {
                fgm::Vec3{ T(1), _shearFactor, T(0) },
                fgm::Vec3{ T(0), T(1), T(0) },
                fgm::Vec3{ T(0), T(0), T(1) },
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
        constexpr auto SHEAR_FACTOR = 22;

        /// @test Verify that @ref Mat3 makeShear2DX by x-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR_X_MAT = fgm::Mat3<int>::makeShear2DX(SHEAR_FACTOR);
        static_assert(SHEAR_X_MAT[0] == fgm::Vec3{ 1, 0,  0 });
        static_assert(SHEAR_X_MAT[1] == fgm::Vec3{ 22, 1, 0 });
        static_assert(SHEAR_X_MAT[2] == fgm::Vec3{ 0, 0, 1 });

        /// @test Verify that @ref Mat3 makeShear2DY by y-axis returns a valid 3D shear matrix at compile time.
        constexpr auto SHEAR_Y_MAT = fgm::Mat3<int>::makeShear2DY(SHEAR_FACTOR);
        static_assert(SHEAR_Y_MAT[0] == fgm::Vec3{ 1, 22,  0 });
        static_assert(SHEAR_Y_MAT[1] == fgm::Vec3{ 0, 1, 0 });
        static_assert(SHEAR_Y_MAT[2] == fgm::Vec3{ 0, 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat3ShearTests, Shear2DX_ReturnsAValid2DMatrix)
{ EXPECT_MAT_EQ(this->_shearX2D, fgm::Mat3<TypeParam>::makeShear2DX(this->_shearFactor)); }


TYPED_TEST(Mat3ShearTests, Shear2DY_ReturnsAValid2DMatrix)
{ EXPECT_MAT_EQ(this->_shearY2D, fgm::Mat3<TypeParam>::makeShear2DY(this->_shearFactor)); }

/** @} */
