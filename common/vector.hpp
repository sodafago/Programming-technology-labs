#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>
#include <stdexcept>
#include <cassert>

namespace nigmatullin
{
  template <class T>
  class Vector
  {
  public:

    Vector();
    Vector(const Vector<T>& forCopy);
    Vector(Vector<T>&& forMove) noexcept;
    Vector(size_t size);
    ~Vector() = default;

    Vector<T>& operator=(const Vector<T>& forCopy);
    Vector<T>& operator=(Vector<T>&& forMove) noexcept;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    Vector<T>& reserve(size_t needAlloc);
    Vector<T>& resize(size_t newSize);
    Vector<T>& shrinkToFit();
    Vector<T>& pushBack(const T& newElem);
    Vector<T>& pushBack(T&& newElem);
    Vector<T>& insertByIndex(const T& newElem, size_t index);
    Vector<T>& insertByIndex(T&& newElem, size_t index);
    Vector<T>& popBack();
    Vector<T>& eraseByIndex(size_t index);
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    T& getBack();
    const T& getBack() const;
    bool isEmpty() const noexcept;
    T* getRawPtr() noexcept;

  private:

    std::unique_ptr<T[]> content_;
    size_t size_;
    size_t allocated_;

    size_t getNeedAlloc_() const noexcept;

    void setAlloc_(size_t newAlloc);
  };
}

template <class T>
nigmatullin::Vector<T>::Vector() :
  content_(nullptr),
  size_(0),
  allocated_(0) {}

template <class T>
nigmatullin::Vector<T>::Vector(const Vector<T>& forCopy) :
  Vector()
{
  *this = forCopy;
}

template <class T>
nigmatullin::Vector<T>::Vector(Vector<T>&& forMove) noexcept :
  Vector()
{
  *this = std::move(forMove);
}

template <class T>
nigmatullin::Vector<T>::Vector(size_t size) :
  content_(std::make_unique<T[]>(size)),
  size_(size),
  allocated_(size) {}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::operator=(const Vector<T>& forCopy)
{
  if (this != &forCopy)
  {
    std::unique_ptr<T[]> newContent = std::make_unique<T[]>(forCopy.size_);
    for (size_t i = 0; i < forCopy.size_; ++i)
    {
      newContent[i] = forCopy.content_[i];
    }
    content_.swap(newContent);
    size_ = allocated_ = forCopy.size_;
  }

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::operator=(Vector<T>&& forMove) noexcept
{
  if (this != &forMove)
  {
    content_ = std::move(forMove.content_);
    size_ = forMove.size_;
    allocated_ = forMove.allocated_;

    forMove.size_ = forMove.allocated_ = 0;
    forMove.content_ = nullptr;
  }

  return *this;
}

template <class T>
T& nigmatullin::Vector<T>::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("\"Index\" in class \"Vector\" out of range!");
  }

  return content_[index];
}

template <class T>
const T& nigmatullin::Vector<T>::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("\"index\" in class \"Vector\" out of range!");
  }

  return content_[index];
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::reserve(size_t needAlloc)
{
  if (needAlloc > allocated_)
  {
    setAlloc_(needAlloc);
  }

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::resize(size_t newSize)
{
  if (newSize < size_)
  {
    for (size_t i = newSize; i < size_; ++i)
    {
      content_[i] = {};
    }
    size_ = newSize;
  }
  else if (newSize > size_)
  {
    Vector<T> temp(newSize);
    for (size_t i = 0; i < size_; ++i)
    {
      temp.content_[i] = content_[i];
    }
    *this = std::move(temp);
  }

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::shrinkToFit()
{
  setAlloc_(size_);

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::pushBack(const T& newElem)
{
  return insertByIndex(newElem, size_);
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::pushBack(T&& newElem)
{
  return insertByIndex(newElem, size_);
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::insertByIndex(const T& newElem, size_t index)
{
  if (index > size_)
  {
    throw std::out_of_range("Vector index out of range!");
  }
  size_t needAlloc = getNeedAlloc_();
  Vector<T> temp(needAlloc);
  temp.content_[index] = newElem;
  for (size_t i = 0; i < index; ++i)
  {
    temp.content_[i] = content_[i];
  }
  for (size_t i = index + 1; i <= size_; ++i)
  {
    temp.content_[i] = content_[i - 1];
  }
  temp.resize(size_ + 1);
  *this = std::move(temp);

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::insertByIndex(T&& newElem, size_t index)
{
  if (index > size_)
  {
    throw std::out_of_range("Vector index out of range!");
  }
  size_t needAlloc = getNeedAlloc_();
  Vector<T> temp(needAlloc);
  temp.content_[index] = std::move(newElem);
  for (size_t i = 0; i < index; ++i)
  {
    temp.content_[i] = std::move(content_[i]);
  }
  for (size_t i = index + 1; i <= size_; ++i)
  {
    temp.content_[i] = std::move(content_[i - 1]);
  }
  temp.resize(size_ + 1);
  *this = std::move(temp);

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::popBack()
{
  if (isEmpty())
  {
    throw std::out_of_range("Vector is empty");
  }
  content_[size_ - 1] = {};
  size_--;

  return *this;
}

template <class T>
nigmatullin::Vector<T>& nigmatullin::Vector<T>::eraseByIndex(size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Vector index out of range!");
  }
  Vector<T> temp(*this);
  for (size_t i = index; i + 1 < temp.getSize(); ++i)
  {
    std::swap(temp.content_[i], temp.content_[i + 1]);
  }
  temp.popBack();
  *this = std::move(temp);

  return *this;
}

template <class T>
size_t nigmatullin::Vector<T>::getSize() const noexcept
{
  return size_;
}

template <class T>
size_t nigmatullin::Vector<T>::getCapacity() const noexcept
{
  return allocated_;
}

template <class T>
T& nigmatullin::Vector<T>::getBack()
{
  if (size_ == 0)
  {
    throw std::out_of_range("Vector is empty!");
  }

  return content_[size_ - 1];
}

template <class T>
const T& nigmatullin::Vector<T>::getBack() const
{
  if (size_ == 0)
  {
    throw std::out_of_range("Vector is empty!");
  }

  return content_[size_ - 1];
}

template <class T>
bool nigmatullin::Vector<T>::isEmpty() const noexcept
{
  return (size_ == 0);
}

template <class T>
T* nigmatullin::Vector<T>::getRawPtr() noexcept
{
  return content_.get();
}

template <class T>
size_t nigmatullin::Vector<T>::getNeedAlloc_() const noexcept
{
  return (2 * size_ + 1);
}

template <class T>
void nigmatullin::Vector<T>::setAlloc_(size_t newAlloc)
{
  assert(newAlloc >= size_);
  if (newAlloc != allocated_)
  {
    std::unique_ptr<T[]> newContent = std::make_unique<T[]>(newAlloc);
    allocated_ = newAlloc;
    for (size_t i = 0; i < size_; ++i)
    {
      newContent[i] = std::move(content_[i]);
    }
    content_.swap(newContent);
  }
}

#endif // !__VECTOR_HPP__
