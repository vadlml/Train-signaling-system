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
	/**
	 * @brief TrackPoint constructor
	 * @param int id -a pointer id
	 * @return void
	 */
	TrackPoint(int id) :
			_id(id)
	{
	}

	/**
	 * @brief sets next point object to the current one
	 * @param next- a pointer to the next pointer object
	 * @return void
	 */
	void set_next(std::shared_ptr<TrackPoint> next)
	{
		_next = next;
		if (_next)
		{
			_next->set_prev(shared_from_this());
		}
	}
	/**
	 * @brief sets previous point object to the current one
	 * @param prev - a pointer to the previous pointer object
	 * @return void
	 */
	void set_prev(std::shared_ptr<TrackPoint> prev)
	{
		_prev = prev;
	}

	/**
	 * @brief next point getter
	 * @param void
	 * @return std::shared_ptr<TrackPoint> - a pointer to next point
	 */
	virtual const std::shared_ptr<TrackPoint> get_next() const
	{
		return _next;
	}

	/**
	 * @brief previous point getter
	 * @param void
	 * @return std::shared_ptr<TrackPoint> - a pointer to previous point
	 */
	const std::shared_ptr<TrackPoint> get_prev() const
	{
		return _prev;
	}

	/**
	 * @brief point occupancy getter
	 * @param void
	 * @return int - the number of trains that occupies current point
	 */
	int get_occupancy(void) const
	{
		return _occupancy_counter;
	}

	/**
	 * @brief increases occupy counter of the point
	 * @param void
	 * @return void
	 */
	void occupy(void)
	{
		_occupancy_counter++;
	}

	/**
	 * @brief decreases occupy counter of the point
	 * @param void
	 * @return void
	 */
	void release(void)
	{
		if (_occupancy_counter--)
		{
		}
	}

	/**
	 * @brief point id getter
	 * @param void
	 * @return int - the current point id
	 */
	int get_id() const
	{
		return _id;
	}

	/**
	 * @brief returns a pointer to the signal object associated with the current point
	 * @param void
	 * @return std::shared_ptr<Signal>& - a reference to a pointer of the signal object
	 */

	const std::shared_ptr<Signal>& get_signal() const
	{
		return _signal;
	}

	/**
	 * @brief sets a pointer to the signal object associated with the current point
	 * @param std::shared_ptr<Signal>& - a reference to a pointer of the signal object
	 * @return void
	 */
	void set_signal(const std::shared_ptr<Signal>& signal)
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
