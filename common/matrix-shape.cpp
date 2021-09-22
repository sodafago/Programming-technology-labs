#include "matrix-shape.hpp"

#include <stdexcept>
#include <cassert>
#include <algorithm>

#include "shape.hpp"
#include "composite-shape.hpp"

const std::shared_ptr<nigmatullin::Shape>&
    nigmatullin::MatrixShape::MatrixShapeRow::operator[](size_t columnIndex) const
{
  if (columnIndex >= size_)
  {
    throw std::out_of_range("ColumnIndex out of range!");
  }

  return matrixShapePtr_->getElement_(rowIndex_ - 1, columnIndex);
}

size_t nigmatullin::MatrixShape::MatrixShapeRow::getColumns() const noexcept
{
  return size_;
}

size_t nigmatullin::MatrixShape::MatrixShapeRow::getCapacity() const noexcept
{
  return sumAllocToCurRow_ - matrixShapePtr_->rows_[rowIndex_ - 1].sumAllocToCurRow_;
}

nigmatullin::MatrixShape::MatrixShapeRow::MatrixShapeRow() :
  matrixShapePtr_(nullptr),
  rowIndex_(0),
  size_(0),
  sumAllocToCurRow_(0) {}

nigmatullin::MatrixShape::MatrixShapeRow::MatrixShapeRow(MatrixShape* matrixShapePtr, size_t rowIndex) :
  matrixShapePtr_(matrixShapePtr),
  rowIndex_(rowIndex),
  size_(0),
  sumAllocToCurRow_(matrixShapePtr_->rows_[rowIndex_ - 1].sumAllocToCurRow_) {}

bool nigmatullin::MatrixShape::MatrixShapeRow::isHasMemory_() const noexcept
{
  return size_ < getCapacity();
}

nigmatullin::MatrixShape::MatrixShape() :
  rows_(1) {}

nigmatullin::MatrixShape::MatrixShape(const MatrixShape& forCopy) :
  MatrixShape()
{
  *this = forCopy;
}

nigmatullin::MatrixShape::MatrixShape(MatrixShape&& forMove) noexcept :
  MatrixShape()
{
  *this = std::move(forMove);
}

nigmatullin::MatrixShape::MatrixShape(const CompositeShape& iniCompShape) :
  MatrixShape()
{
  insert(iniCompShape);
}

nigmatullin::MatrixShape& nigmatullin::MatrixShape::operator=(const MatrixShape& forCopy)
{
  if (this != &forCopy)
  {
    MatrixShape temp;
    temp.content_ = forCopy.content_;
    temp.rows_ = forCopy.rows_;
    for (size_t i = 0; i < temp.rows_.getSize(); ++i)
    {
      temp.rows_[i].matrixShapePtr_ = &temp;
    }
    *this = std::move(temp);
  }

  return *this;
}

nigmatullin::MatrixShape& nigmatullin::MatrixShape::operator=(MatrixShape&& forMove) noexcept
{
  if (this != &forMove)
  {
    content_ = std::move(forMove.content_);
    rows_ = std::move(forMove.rows_);
    for (size_t i = 0; i < rows_.getSize(); ++i)
    {
      rows_[i].matrixShapePtr_ = this;
    }
  }

  return *this;
}

const nigmatullin::MatrixShape::MatrixShapeRow& nigmatullin::MatrixShape::operator[](size_t rowIndex) const
{
  if (rowIndex >= getRows())
  {
    throw std::out_of_range("Row index out of range");
  }

  return rows_[rowIndex + 1];
}

std::ostream& nigmatullin::operator<<(std::ostream& outStream, const nigmatullin::MatrixShape& forOut)
{
  outStream << "MatrixShape have " << forOut.getRows() << " rows\n\n";
  for (size_t i = 0; i < forOut.getRows(); ++i)
  {
    outStream << "\tInfo about " << i + 1 << " row:\n\n";
    for (size_t j = 0; j < forOut[i].getColumns(); ++j)
    {
      outStream << "\t\tType " << j + 1 << " shape: " << forOut[i][j]->getTypeShape() << '\n';
    }
    outStream << '\n';
  }

  return outStream;
}

size_t nigmatullin::MatrixShape::getRows() const noexcept
{
  return rows_.getSize() - 1;
}

nigmatullin::MatrixShape& nigmatullin::MatrixShape::insert(const std::shared_ptr<Shape>& forAdd)
{
  if (forAdd == nullptr)
  {
    throw std::invalid_argument("Shape must exist!");
  }

  size_t rowForAdd = getRows();
  for (size_t i = 0; rowForAdd == getRows() && i < getRows(); ++i)
  {
    bool isSuitableRow = true;
    for (size_t j = 0; isSuitableRow && j < getRow_(i).size_; ++j)
    {
      isSuitableRow = !isIntersect_(forAdd, getElement_(i, j));
    }
    rowForAdd = (isSuitableRow ? i : rowForAdd);
  }

  if (rowForAdd != getRows() && getRow_(rowForAdd).isHasMemory_())
  {
    getElement_(rowForAdd, getRow_(rowForAdd).size_) = forAdd;
    getRow_(rowForAdd).size_++;
  }
  else
  {
    MatrixShape temp(*this);
    if (rowForAdd == temp.getRows())
    {
      temp.pushBackRow_();
    }
    else
    {
      temp.controlRowMemory_(rowForAdd);
    }
    temp.getElement_(rowForAdd, temp.getRow_(rowForAdd).size_) = forAdd;
    temp.getRow_(rowForAdd).size_++;
    *this = std::move(temp);
  }

  return *this;
}

nigmatullin::MatrixShape& nigmatullin::MatrixShape::insert(const CompositeShape& compShape)
{
  MatrixShape temp(*this);
  for (size_t i = 0; i < compShape.getSize(); ++i)
  {
    temp.insert(compShape[i]);
  }
  *this = std::move(temp);

  return *this;
}

std::shared_ptr<nigmatullin::Shape>& nigmatullin::MatrixShape::getElement_(size_t row, size_t column)
{
  assert(row < getRows() && column < rows_[row + 1].getCapacity());

  return content_[rows_[row].sumAllocToCurRow_ + column];
}

nigmatullin::MatrixShape::MatrixShapeRow& nigmatullin::MatrixShape::getRow_(size_t row)
{
  assert(row < getRows());

  return rows_[row + 1];
}

void nigmatullin::MatrixShape::pushBackRow_()
{
  MatrixShape temp(*this);
  temp.rows_.pushBack(MatrixShapeRow(&temp, getRows() + 1));
  temp.content_.resize(content_.getSize() + 1);
  temp.getRow_(temp.getRows() - 1).sumAllocToCurRow_++;
  *this = std::move(temp);
}

void nigmatullin::MatrixShape::controlRowMemory_(size_t row)
{
  if (!getRow_(row).isHasMemory_())
  {
    Vector<std::shared_ptr<Shape>> newContent(2 * getRow_(row).size_ + 1);
    size_t addedAllocation = getRow_(row).size_ + 1;
    for (size_t i = 0; i < getRows(); ++i)
    {
      for (size_t j = 0; j < getRow_(i).size_; ++j)
      {
        newContent[rows_[i].sumAllocToCurRow_ + j + (i > row ? addedAllocation : 0)] = getElement_(i, j);
      }
    }
    content_ = std::move(newContent);
    for (size_t i = row; i < getRows(); ++i)
    {
      getRow_(i).sumAllocToCurRow_ += addedAllocation;
    }
  }
}

bool nigmatullin::MatrixShape::isIntersect_(const std::shared_ptr<nigmatullin::Shape>& firstShape,
    const std::shared_ptr<nigmatullin::Shape>& secondShape)
{
  nigmatullin::rectangle_t firstFrameRect = firstShape->getFrameRect();
  nigmatullin::rectangle_t secondFrameRect = secondShape->getFrameRect();

  return (std::abs(firstFrameRect.pos.x - secondFrameRect.pos.x)
      <= firstFrameRect.width / 2.0 + secondFrameRect.width / 2.0
      && std::abs(firstFrameRect.pos.y - secondFrameRect.pos.y)
      <= firstFrameRect.height / 2.0 + secondFrameRect.height / 2.0);
}
