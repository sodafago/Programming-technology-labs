#ifndef __QUEUE_WITH_PRIORITY_HPP__
#define __QUEUE_WITH_PRIORITY_HPP__

#include <list>
#include <stdexcept>

namespace nigmatullin
{
  enum elementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  template <class T>
  class QueueWithPriority
  {
  public:

    QueueWithPriority<T>& putElementToQueue(const T& elem, elementPriority priority);

    T& getElementFromQueue();

    const T& getElementFromQueue() const;

    QueueWithPriority<T>& accelerate() noexcept;

    QueueWithPriority<T>& pop();

    size_t getSize() const noexcept;

    bool isEmpty() const noexcept;

  private:

    static const size_t CNT_PRIORITY = 3;
    std::list<T> content_[CNT_PRIORITY];

    int getLastQueueWithElements_() const noexcept;
  };
}

template <class T>
nigmatullin::QueueWithPriority<T>&
    nigmatullin::QueueWithPriority<T>::putElementToQueue(const T& elem, elementPriority priority)
{
  content_[priority].push_back(elem);

  return *this;
}

template <class T>
T& nigmatullin::QueueWithPriority<T>::getElementFromQueue()
{
  int id = getLastQueueWithElements_();

  if (id == -1)
  {
    throw std::underflow_error("Queue is empty!");
  }

  return content_[id].front();
}

template <class T>
const T& nigmatullin::QueueWithPriority<T>::getElementFromQueue() const
{
  int id = getLastQueueWithElements_();

  if (id == -1)
  {
    throw std::underflow_error("Queue is empty!");
  }

  return content_[id].front();
}

template <class T>
nigmatullin::QueueWithPriority<T>& nigmatullin::QueueWithPriority<T>::accelerate() noexcept
{
  content_[HIGH].splice(content_[HIGH].end(), content_[LOW]);

  return *this;
}

template <class T>
nigmatullin::QueueWithPriority<T>& nigmatullin::QueueWithPriority<T>::pop()
{
  int id = getLastQueueWithElements_();
  if (id == -1)
  {
    throw std::underflow_error("Queue is empty!");
  }
  content_[id].pop_front();

  return *this;
}

template <class T>
int nigmatullin::QueueWithPriority<T>::getLastQueueWithElements_() const noexcept
{
  int retPrior = HIGH;
  while (retPrior >= LOW && content_[retPrior].empty())
  {
    --retPrior;
  }

  return retPrior;
}

template <class T>
size_t nigmatullin::QueueWithPriority<T>::getSize() const noexcept
{
  return content_[LOW].size() + content_[NORMAL].size() + content_[HIGH].size();
}

template <class T>
bool nigmatullin::QueueWithPriority<T>::isEmpty() const noexcept
{
  return (getSize() == 0);
}

#endif
