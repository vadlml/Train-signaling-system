/**
 * @file Train.h
 * @author Vadim Lapchinskiy
 * @brief Train class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TRAIN_H_
#define TRAIN_H_

#include <memory.h>
#include "AbstractVisitor.h"
#include "HeartBeatObserver.h"
#include "TrackPoint.h"

class Train: public HeartBeatObserver
{
public:
	enum State
	{
		STATE_WAITING, STATE_RUNNING, STATE_STOPPED, STATE_CRASHED

	};

	enum Direction
	{
		DIR_FORWARD, DIR_REVERSE,
	};

	/**
	 * @brief instantiates a train object and subscribes it to an observer subject
	 *
	 * @param subject - subject to subscribe this train to
	 * @param  id - train's id
	 * @param  dir - train's direction
	 * @param  start_point - a pointer to train's starting point
	 * @return std::shared_ptr<Train> - a pointer to created object
	 */
	static std::shared_ptr<Train> create(HeartBeatSubject &subject, int id,
			Direction dir, std::shared_ptr<TrackPoint> start_point)
	{
		auto ptr = std::shared_ptr<Train>(new Train(subject, id, dir, start_point));
		subject.attach(ptr);
		return ptr;
	}

	const std::shared_ptr<TrackPoint> get_current_point(void) const
	{
		return _curr_point;
	}

	State get_state(void)
	{
		return _state;
	}

	void accept(const std::shared_ptr<AbstractVisitor> visitor) override;

	Direction get_dir() const
	{
		return _dir;
	}

	void set_state(State state)
	{
		_state = state;
	}

	void set_curr_point(const std::shared_ptr<TrackPoint> &currPoint)
	{
		_curr_point = currPoint;
	}

	int get_id() const
	{
		return _id;
	}

	void move(void);
	virtual ~Train() = default;

private:
	/**
	 * @brief Trains class constructor
	 *
	 * @param subject - subject to subscribe this train to
	 * @param  id - train's id
	 * @param  dir - train's direction
	 * @param  start_point - a pointer to train's starting point
	 */
	Train(HeartBeatSubject &subject, int id, Direction dir,
			std::shared_ptr<TrackPoint> start_point) :
			HeartBeatObserver(subject), _id(id), _dir(dir), _curr_point(
					start_point)
	{
		_curr_point->occupy();
	}
	int _id;
	State _state = STATE_RUNNING;
	Direction _dir = DIR_FORWARD;
	std::shared_ptr<TrackPoint> _curr_point;
};

#endif /* TRAIN_H_ */
