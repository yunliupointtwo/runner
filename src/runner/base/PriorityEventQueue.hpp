#pragma once

#include "EventQueue.hpp"

#include <queue>
#include <tuple>
#include <vector>

namespace runner {
namespace base {

template <class EventType, class TimeType>
class PriorityEventQueue final : public EventQueue<EventType, TimeType> {
 public:
  const TimeType& time() const override;

  const TimeType& event() const override;

  void pop() override;

  void push(TimeType&& time, EventType&& event) override;

 private:
  enum { EVENT = 0, TIME = 1 }; //  for ease of use with std::get
  using DataType = std::tuple<EventType, TimeType>;
  using Container = std::vector<DataType>;

  //  comparator on the time component
  struct Compare {
    bool operator()(const DataType& a, const DataType& b) const noexcept {
      return std::get<TIME>(a) < std::get<TIME>(b);
    }
  };

 private:
  std::priority_queue<DataType> m_queue;
};

}  //  end namespace 'base'
}  //  end namespace 'runner'

//==============================================================================

namespace runner {
namespace base {

template <class EventType, class TimeType>
inline const TimeType& PriorityEventQueue<EventType, Timetype>::time() const {
  return std::get<TIME>(m_queue.top());
}

template <class EventType, class TimeType>
inline const TimeType& PriorityEventQueue<EventType, Timetype>::event() const {
  return std::get<EVENT>(m_queue.top());
}

template <class EventType, class TimeType>
inline void PriorityEventQueue<EventType, Timetype>::pop() {
  if (!empty()) {
    m_queue.pop();
    --m_size;
  }
}

template <class EventType, class TimeType>
inline void PriorityEventQueue<EventType, Timetype>::push(TimeType&& time,
                                                          EventType&& event) {
  //  TODO
  m_queue.push(std::make_tuple(event, time));
}

}  //  end namespace 'base'
}  //  end namespace 'runner'
