/**
 * @file ShearTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 29, 2026
 *
 * @brief Verify @ref fgm::Mat2 shear factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat2x2_Transforms
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
     * @brief Test fixture for @ref Mat2 shear transform factories.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2ShearTests: public testing::Test
    {
    protected:
        T _shearFactor;
        fgm::Mat2<T> _shearX, _shearY;


        void SetUp() override
        {
            _shearFactor = T(22.58923191238);
            _shearX      = {
                fgm::Vec2{ T(1), T(0) },
                fgm::Vec2{ _shearFactor, T(1) },
            };
            _shearY = {
                fgm::Vec2{ T(1), _shearFactor },
                fgm::Vec2{ T(0), T(1) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat2ShearTests, SupportedArithmeticTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/
    namespace static_tests
    {
        constexpr auto SHEAR_FACTOR = 22;

        /// @test Verify that @ref Mat2 makeShear by x-axis returns a valid shear matrix at compile time.
        constexpr auto SHEAR_X_MAT = fgm::Mat2<int>::makeShearX(SHEAR_FACTOR);
        static_assert(SHEAR_X_MAT[0] == fgm::Vec2{ 1, 0 });
        static_assert(SHEAR_X_MAT[1] == fgm::Vec2{ 22, 1 });

        /// @test Verify that @ref Mat2 makeShear by y-axis returns a valid shear matrix at compile time.
        constexpr auto SHEAR_Y_MAT = fgm::Mat2<int>::makeShearY(SHEAR_FACTOR);
        static_assert(SHEAR_Y_MAT[0] == fgm::Vec2{ 1, 22 });
        static_assert(SHEAR_Y_MAT[1] == fgm::Vec2{ 0, 1 });
    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat2ShearTests, ShearX_ReturnsAValid2DMatrix)
{ EXPECT_MAT_EQ(this->_shearX, fgm::Mat2<TypeParam>::makeShearX(this->_shearFactor)); }


TYPED_TEST(Mat2ShearTests, ShearY_ReturnsAValid2DMatrix)
{ EXPECT_MAT_EQ(this->_shearY, fgm::Mat2<TypeParam>::makeShearY(this->_shearFactor)); }

/** @} */
