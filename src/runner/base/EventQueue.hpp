/// @file EventQueue.hpp

#pragma once

#include <cstdint>  //  size_t

namespace runner {
namespace base {

/// @class  EventQueue
/// @brief  Interface for a class that serves events in time priority
/// @tparam EventType Type for event, the data to deliver at the given time
/// @tparam TimeType  Type for time, must implement less-than

EventQueue is an abstract class which models storing and serving events in
time order.
template <class EventType, class TimeType>
class EventQueue {
 public:
  EventQueue() = default;
  EventQueue(const EventQueue&) = default;
  EventQueue(EventQueue&&) = default;
  EventQueue& operator=(const EventQueue&) = default;
  EventQueue& operator=(EventQueue&&) = default;
  virtual ~EventQueue() = default;

  /// True if there are no events remaining in the queue
  /// @note Must return false if size() == 0
  bool empty() const noexcept { return (m_size == 0ul); }

  ///
  /// Number of events in the queue.
  /// @note Must return 0 if empty()
  ///
  size_t size() const noexcept { return m_size; }

  ///
  /// Highest priority time value.
  /// @warning  Undefined behaviour if empty()
  ///
  virtual const TimeType& time() const = 0;

  /// Highest priority event.
  /// @warning  Undefined behaviour if empty()
  virtual const EventType& event() const = 0;

  /// Remove the currently highest priority time and event.
  /// @note No op if empty()
  virtual void pop() = 0;

  /// Insert an event and its associated timestamp.
  /// @param  time  Timestamp of the event
  /// @param  event The event
  /// @note No op if the time is of lower priority than that of time()
  virtual void push(TimeType&& time, EventType&& event) = 0;

 protected:
  size_t m_size = 0;
};

}  //  end namespace 'base'
}  //  end namespace 'runner'
