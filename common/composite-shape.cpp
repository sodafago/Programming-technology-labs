#include "composite-shape.hpp"

#include <stdexcept>

const std::shared_ptr<nigmatullin::Shape>& nigmatullin::CompositeShape::operator[](size_t index) const
{
  return content_[index];
}

std::ostream& nigmatullin::operator<<(std::ostream& outStream, const nigmatullin::CompositeShape& forOut)
{
  outStream << "TypeShape: " << forOut.getTypeShape() << "; Summarised area: " << forOut.getArea() << "\n\n";
  for (size_t i = 0; i < forOut.getSize(); ++i)
  {
    outStream << "\tInfo about #" << i << " shape in CompositeShape:\n\n"
        << "\t\tTypeShape: " << forOut[i]->getTypeShape() << "; Area: " << forOut[i]->getArea() << '\n';
  }

  return outStream;
}

const char* nigmatullin::CompositeShape::getTypeShape() const noexcept
{
  return "CompositeShape";
}

nigmatullin::rectangle_t nigmatullin::CompositeShape::getFrameRect() const
{
  if (content_.getSize() == 0)
  {
    return { { 0, 0 }, 0, 0 };
  }
  point_t leftDownPt = content_[0]->getFrameRect().pos;
  point_t rightUpPt = content_[0]->getFrameRect().pos;

  for (size_t i = 0; i < getSize(); ++i)
  {
    rectangle_t nowRect = content_[i]->getFrameRect();

    leftDownPt.x = std::min(leftDownPt.x, nowRect.pos.x - nowRect.width / 2.0);
    leftDownPt.y = std::min(leftDownPt.y, nowRect.pos.y - nowRect.height / 2.0);

    rightUpPt.x = std::max(rightUpPt.x, nowRect.pos.x + nowRect.width / 2.0);
    rightUpPt.y = std::max(rightUpPt.y, nowRect.pos.y + nowRect.height / 2.0);
  }

  return { { (leftDownPt.x + rightUpPt.x) / 2.0, (leftDownPt.y + rightUpPt.y) / 2.0 },
      rightUpPt.x - leftDownPt.x, rightUpPt.y - leftDownPt.y };
}

double nigmatullin::CompositeShape::getArea() const noexcept
{
  double resultArea = 0.0;
  for (size_t i = 0; i < getSize(); ++i)
  {
    resultArea += content_[i]->getArea();
  }

  return resultArea;
}

void nigmatullin::CompositeShape::move(double deltXCenter, double deltYCenter) noexcept
{
  for (size_t i = 0; i < getSize(); ++i)
  {
    content_[i]->move(deltXCenter, deltYCenter);
  }
}

void nigmatullin::CompositeShape::move(const point_t& newCenter) noexcept
{
  point_t centerCompShape = getFrameRect().pos;
  move(centerCompShape.x - newCenter.x, centerCompShape.y - newCenter.y);
}

void nigmatullin::CompositeShape::scale(double magnification)
{
  if (magnification <= 0.0)
  {
    throw std::invalid_argument("Invalid argument for function \"scale\"");
  }
  point_t centerCompShape = getFrameRect().pos;
  for (size_t i = 0; i < getSize(); ++i)
  {
    point_t centerNow = content_[i]->getFrameRect().pos;
    content_[i]->move((magnification - 1) * (centerNow.x - centerCompShape.x),
        (magnification - 1) * (centerNow.y - centerCompShape.y));
    content_[i]->scale(magnification);
  }
}

void nigmatullin::CompositeShape::rotate(double angleInDegrees) noexcept
{
  point_t frameRectCenter = getFrameRect().pos;
  for (size_t i = 0; i < getSize(); ++i)
  {
    content_[i]->move(getEndOfRotatedVector(frameRectCenter,
        content_[i]->getFrameRect().pos, angleInDegrees));
  }
}

size_t nigmatullin::CompositeShape::getSize() const noexcept
{
  return content_.getSize();
}

nigmatullin::CompositeShape& nigmatullin::CompositeShape::pushBack(const std::shared_ptr<Shape>& forAdd)
{
  if (forAdd == nullptr)
  {
    throw std::invalid_argument("Shape is equal nullptr!");
  }
  content_.pushBack(forAdd);

  return *this;
}

nigmatullin::CompositeShape& nigmatullin::CompositeShape::eraseByIndex(size_t index)
{
  content_.eraseByIndex(index);

  return *this;
}
