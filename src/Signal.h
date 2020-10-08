/**
 * @file Signal.h
 * @author Vadim Lapchinskiy
 * @brief Signal class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <memory.h>
#include "TrackPoint.h"
#include "AbstractVisitor.h"
#include "HeartBeatObserver.h"

class Signal: public HeartBeatObserver
{
public:

	enum State
	{
		STATE_RED, STATE_GREEN
	};

	/**
	 * @brief instantiates a Signal object and subscribes it to an observer subject
	 *
	 * @param subject - subject to subscribe this signal to
	 * @param id - signal's id
	 * @param track_point - a pointer to the associated with this signal track point object
	 * @return std::shared_ptr<Signal> - a pointer to created object
	 */
	static std::shared_ptr<Signal> create(HeartBeatSubject &subject, int id,
			std::shared_ptr<TrackPoint> track_point)
	{
		auto ptr = std::shared_ptr<Signal>(new Signal(subject, id, track_point->get_id()));
		subject.attach(ptr);
		track_point->set_signal(ptr);
		return ptr;
	}

	const State get_state(void) const
	{
		return _state;
	}

	void set_state(State state)
	{
		_state = state;
	}

	void accept(const std::shared_ptr<AbstractVisitor> visitor) override;

	const  int get_track_point_id() const
	{
		return _track_point_id;
	}

	int get_id() const
	{
		return _id;
	}

	virtual ~Signal() = default;
private:

	/**
	 * @brief Signal class constructor
	 *
	 * @param subject - subject to subscribe this signal to
	 * @param id - signal's id
	 * @param track_point_id - track point id this signal is placed on
	 */
	Signal(HeartBeatSubject &subject, int id,
			int track_point_id) :
			HeartBeatObserver(subject), _id(id), _track_point_id(track_point_id)
	{
	}
	int _id;
	int _track_point_id;
	State _state = STATE_GREEN;
};

#endif /* SIGNAL_H_ */
