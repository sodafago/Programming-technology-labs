#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/assert.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const nigmatullin::Rectangle TEST_RECTANGLE({ {228.0, 47.0, }, 8800.0, 5553535.0, });
const nigmatullin::Circle TEST_CIRCLE({ 47.0, 228.0, }, 42.0);
const long long CONST_VAL = 17;
const double EPS = 1e-9;

nigmatullin::CompositeShape getFilledCompositeShape()
{
  nigmatullin::CompositeShape res;
  for (size_t i = 0; i < CONST_VAL; ++i)
  {
    res.pushBack(std::make_shared<nigmatullin::Rectangle>(TEST_RECTANGLE));
    res.pushBack(std::make_shared<nigmatullin::Circle>(TEST_CIRCLE));
  }
  return res;
}

BOOST_AUTO_TEST_CASE(invalidIndexForOperatorSquareBrackets)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  BOOST_CHECK_THROW(testCompositeShape[2 * CONST_VAL], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(notPositiveMagnificationForScale)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  BOOST_CHECK_THROW(testCompositeShape.scale(-CONST_VAL), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalidIndexForEraseByIndex)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  BOOST_CHECK_THROW(testCompositeShape.eraseByIndex(2 * CONST_VAL), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(checkingPushBackFunction)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  size_t oldSize = testCompositeShape.getSize();
  testCompositeShape.pushBack(std::make_shared<nigmatullin::Circle>(TEST_CIRCLE));
  size_t newSize = testCompositeShape.getSize();
  BOOST_CHECK(oldSize + 1 == newSize);
}

BOOST_AUTO_TEST_CASE(checkingEraseByIndex)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  size_t oldSize = testCompositeShape.getSize();
  testCompositeShape.eraseByIndex(0);
  size_t newSize = testCompositeShape.getSize();
  BOOST_CHECK(oldSize - 1 == newSize);
}

BOOST_AUTO_TEST_CASE(checkingGetArea)
{
  nigmatullin::CompositeShape testCompositeShape = getFilledCompositeShape();
  double area = 0.0;
  for (size_t i = 0; i < 2 * CONST_VAL; ++i)
  {
    area += testCompositeShape[i]->getArea();
  }
  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), area, EPS);
}
