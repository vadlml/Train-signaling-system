/**
 * @file TrackPoint.h
 * @author Vadim Lapchinskiy
 * @brief Track Point class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TRACKPOINT_H_
#define TRACKPOINT_H_
#include <memory>

class Signal;

class TrackPoint: public std::enable_shared_from_this<TrackPoint>
{
public:
	TrackPoint(int id) :
			_id(id)
	{
	}

	void set_next(std::shared_ptr<TrackPoint> next)
	{
		_next = next;
		if (_next)
		{
			_next->set_prev(shared_from_this());
		}
	}

	void set_prev(std::shared_ptr<TrackPoint> prev)
	{
		_prev = prev;
	}
	virtual const std::shared_ptr<TrackPoint> get_next() const
	{
		return _next;
	}
	const std::shared_ptr<TrackPoint> get_prev() const
	{
		return _prev;
	}

	int get_occupancy(void) const
	{
		return _occupancy_counter;
	}

	void occupy(void)
	{
		_occupancy_counter++;
	}

	void release(void)
	{
		if (_occupancy_counter--)
		{
		}
	}

	int get_id() const
	{
		return _id;
	}

	const std::shared_ptr<Signal>& get_signal() const
	{
		return _signal;
	}

	void set_signal(const std::shared_ptr<Signal> signal)
	{
		_signal = signal;
	}

	virtual ~TrackPoint() = default;

protected:
	int _id;
	int _occupancy_counter = 0;
	std::shared_ptr<Signal> _signal = nullptr;
	std::shared_ptr<TrackPoint> _next = nullptr;
	std::shared_ptr<TrackPoint> _prev = nullptr;
};

#endif /* TRACKPOINT_H_ */
