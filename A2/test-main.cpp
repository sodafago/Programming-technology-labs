#define BOOST_TEST_MAIN
#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPS = 1e-9;
const double TEST_MAGNIFICATION = 7;

const nigmatullin::point_t TEST_POS = { 0.0, 0.0, };
const nigmatullin::point_t TEST_NEW_POS = { 100.0, 100.0, };
const double TEST_HEIGHT = 228;
const double TEST_WIDTH = 47;

BOOST_AUTO_TEST_CASE(rectangleConstAreaAndSidesAtMoving)
{
    nigmatullin::Rectangle testRectangle({ TEST_POS, TEST_WIDTH, TEST_HEIGHT, });

    testRectangle.move(TEST_NEW_POS);

    BOOST_CHECK_CLOSE(testRectangle.getFrameRect().height, TEST_HEIGHT, EPS);
    BOOST_CHECK_CLOSE(testRectangle.getFrameRect().width, TEST_WIDTH, EPS);
    BOOST_CHECK_CLOSE(testRectangle.getArea(), TEST_HEIGHT * TEST_WIDTH, EPS);
}

BOOST_AUTO_TEST_CASE(rectangleSquareChangeInArea)
{
    nigmatullin::Rectangle testRectangle({ TEST_POS, TEST_WIDTH, TEST_HEIGHT, });

    testRectangle.scale(TEST_MAGNIFICATION);

    BOOST_CHECK_CLOSE(testRectangle.getArea(), std::pow(TEST_MAGNIFICATION, 2) * TEST_HEIGHT * TEST_WIDTH, EPS);
}

BOOST_AUTO_TEST_CASE(rectangleNotPositiveScaleParameter)
{
    nigmatullin::Rectangle testRectangle({ TEST_POS, TEST_WIDTH, TEST_HEIGHT, });

    BOOST_CHECK_THROW(testRectangle.scale(-TEST_MAGNIFICATION), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangleNotPositiveHeight)
{
    BOOST_CHECK_THROW(nigmatullin::Rectangle testRectangle({ TEST_POS, TEST_WIDTH, -TEST_HEIGHT, }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangleNotPositiveWidth)
{
    BOOST_CHECK_THROW(nigmatullin::Rectangle testRectangle({ TEST_POS, -TEST_WIDTH, TEST_HEIGHT, }), std::invalid_argument);
}

const double TEST_RADIUS = 19;

BOOST_AUTO_TEST_CASE(circleConstAreaAndRadiusAtMoving)
{
    nigmatullin::Circle testCircle(TEST_POS, TEST_RADIUS);

    testCircle.move(TEST_NEW_POS);

    BOOST_CHECK_CLOSE(testCircle.getRadius(), TEST_RADIUS, EPS);
    BOOST_CHECK_CLOSE(testCircle.getArea(), M_PI * std::pow(TEST_RADIUS, 2), EPS);
}

BOOST_AUTO_TEST_CASE(circleSquareChangeInArea)
{
    nigmatullin::Circle circle(TEST_POS, TEST_RADIUS);

    circle.scale(TEST_MAGNIFICATION);

    BOOST_CHECK_CLOSE(circle.getArea(), std::pow(TEST_MAGNIFICATION, 2) * M_PI * std::pow(TEST_RADIUS, 2), EPS);
}

BOOST_AUTO_TEST_CASE(circleNotPositiveRadius)
{
    BOOST_CHECK_THROW(nigmatullin::Circle circle({ TEST_POS, -TEST_RADIUS }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(circleNotPositiveScaleParameter)
{
    nigmatullin::Circle circle({ TEST_POS, TEST_RADIUS });
    BOOST_CHECK_THROW(circle.scale(-TEST_MAGNIFICATION), std::invalid_argument);
}
