#define _USE_MATH_DEFINES
#define BOOST_TEST_MAIN

#include <cmath>
#include <boost/test/included/unit_test.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"
#include "static-polygon.hpp"
#include "dynamic-polygon.hpp"


const double EPS = 1e-9;

BOOST_AUTO_TEST_SUITE(checkValidRotate)

  const double ANGLE_IN_DEGREES = 90;

  BOOST_AUTO_TEST_CASE(forRectangle)
  {
    const double WIDTH = 4.0;
    const double HEIGHT = 5.0;
    nigmatullin::Rectangle testRect({ { 0, 0, }, WIDTH, HEIGHT });
    testRect.rotate(ANGLE_IN_DEGREES);
    BOOST_CHECK_CLOSE(WIDTH * HEIGHT, testRect.getArea(), EPS);
    BOOST_CHECK_CLOSE(WIDTH, testRect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(HEIGHT, testRect.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(forCircle)
  {
    const double RADIUS = 228;
    nigmatullin::Circle testCircle({ 0, 0, }, RADIUS);
    testCircle.rotate(ANGLE_IN_DEGREES);
    BOOST_CHECK_CLOSE(RADIUS, testCircle.getRadius(), EPS);
    BOOST_CHECK_CLOSE(M_PI * RADIUS * RADIUS, testCircle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(forCompositeShape)
  {
    nigmatullin::CompositeShape testCompShape;
    const double WIDTH = 5;
    const double HEIGHT = 6;
    const double RADIUS = 228;
    testCompShape.pushBack
        (std::make_shared<nigmatullin::Rectangle>(nigmatullin::rectangle_t{ { 0, 0, },  WIDTH, HEIGHT, }));
    testCompShape.pushBack(std::make_shared<nigmatullin::Circle>(nigmatullin::point_t{ 0, 0, }, RADIUS));
    nigmatullin::rectangle_t frameRectBeforeRotate = testCompShape.getFrameRect();
    testCompShape.rotate(ANGLE_IN_DEGREES);
    nigmatullin::rectangle_t frameRectAfterRotate = testCompShape.getFrameRect();
    BOOST_CHECK_CLOSE(frameRectBeforeRotate.width, frameRectAfterRotate.height, EPS);
    BOOST_CHECK_CLOSE(frameRectBeforeRotate.height, frameRectAfterRotate.width, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(checkMatrixShape)

  BOOST_AUTO_TEST_CASE(checkPushBackEmptyShape)
  {
    nigmatullin::MatrixShape testMatrix;
    BOOST_CHECK_THROW(testMatrix.insert(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(checkIndexOutOfRange)
  {
    nigmatullin::MatrixShape testMatrix;
    const double WIDTH = 100;
    const double HEIGHT = 100;
    std::shared_ptr<nigmatullin::Shape> testRect
        = std::make_shared<nigmatullin::Rectangle>(nigmatullin::rectangle_t{ { 0, 0, },  WIDTH, HEIGHT, });
    for (size_t i = 0; i < 5; ++i)
    {
      testMatrix.insert(testRect);
    }
    for (size_t i = 5; i < 10; ++i)
    {
      BOOST_CHECK_THROW(testMatrix[i], std::out_of_range);
      BOOST_CHECK_THROW(testMatrix[0][i], std::out_of_range);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(checkPolygon)

  BOOST_AUTO_TEST_CASE(checkConvex)
  {
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<2> testStaticPolygon({ { 0, 0, }, { 0, 0, }, }),
        std::invalid_argument);
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<4> testStaticPolygon({ { 0, 0, }, { 0, 1, }, { 1, 0, }, { 1, 1, } }),
        std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(checkLowerParametersForStaticPolygon)
  {
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<2> testStaticPolygon({ { 0, 0, }, }), std::invalid_argument);
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<4> testStaticPolygon({ { 0, 0, }, { 0, 1, }, { 1, 1, }, }),
        std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(checkGreaterParametersForStaticPolygon)
  {
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<2> testStaticPolygon({ { 0, 0, }, { 0, 1, }, { 1, 1, } }),
        std::invalid_argument);
    BOOST_CHECK_THROW(nigmatullin::StaticPolygon<4> testStaticPolygon({
        { 0, 0, },
        { 0, 1, },
        { 0, 2, },
        { 1, 2, },
        { 1, 1, }, }),
        std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
