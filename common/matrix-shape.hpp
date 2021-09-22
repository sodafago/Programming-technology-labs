#ifndef __MATRIX_SHAPE_HPP__
#define __MATRIX_SHAPE_HPP__

#include <iostream>
#include <memory>

#include "vector.hpp"

namespace nigmatullin
{
  class Shape;
  class CompositeShape;

  class MatrixShape
  {
  public:

    class MatrixShapeRow
    {
    public:

      MatrixShapeRow();
      ~MatrixShapeRow() = default;

      const std::shared_ptr<nigmatullin::Shape>& operator[](size_t columnIndex) const;

      size_t getColumns() const noexcept;
      size_t getCapacity() const noexcept;

    private:

      friend class MatrixShape;
      friend class Vector<MatrixShapeRow>;

      MatrixShape* matrixShapePtr_;
      size_t rowIndex_;
      size_t size_;
      size_t sumAllocToCurRow_;

      MatrixShapeRow(const MatrixShapeRow& forCopy) = default;
      MatrixShapeRow(MatrixShapeRow&& forMove) noexcept = default;
      MatrixShapeRow(MatrixShape* matrixShapePtr, size_t rowIndex_);

      MatrixShapeRow& operator=(const MatrixShapeRow& forCopy) = default;
      MatrixShapeRow& operator=(MatrixShapeRow&& forMove) noexcept = default;

      bool isHasMemory_() const noexcept;
    };

    MatrixShape();
    MatrixShape(const MatrixShape& forCopy);
    MatrixShape(MatrixShape&& forMove) noexcept;
    MatrixShape(const CompositeShape& iniCompShape);
    ~MatrixShape() = default;

    MatrixShape& operator=(const MatrixShape& forCopy);
    MatrixShape& operator=(MatrixShape&& forMove) noexcept;

    const MatrixShapeRow& operator[](size_t rowIndex) const;
    friend std::ostream& operator<<(std::ostream& outStream, const MatrixShape& forOut);

    size_t getRows() const noexcept;
    MatrixShape& insert(const std::shared_ptr<nigmatullin::Shape>& forAdd);
    MatrixShape& insert(const CompositeShape& compShape);

  private:

    nigmatullin::Vector<std::shared_ptr<nigmatullin::Shape>> content_;
    nigmatullin::Vector<MatrixShapeRow> rows_;

    std::shared_ptr<nigmatullin::Shape>& getElement_(size_t row, size_t column);
    MatrixShapeRow& getRow_(size_t row);
    void pushBackRow_();
    void controlRowMemory_(size_t row);

    static bool isIntersect_(const std::shared_ptr<nigmatullin::Shape>& firstShape,
        const std::shared_ptr<nigmatullin::Shape>& secondShape);
  };

  std::ostream& operator<<(std::ostream& outStream, const MatrixShape& forOut);
}

#endif // !__MATRIX_SHAPE_HPP__
