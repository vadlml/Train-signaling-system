/**
 * @file TrackJunction.h
 * @author Vadim Lapchinskiy
 * @brief Track Junction class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TRACKJUNCTION_H_
#define TRACKJUNCTION_H_

#include <memory>
#include "TrackPoint.h"
#include "HeartBeatObserver.h"

class TrackJunction: public TrackPoint, public HeartBeatObserver
{
public:
	enum SwitchPosition
	{
		SWITCH_POS_MAIN, SWITCH_POS_SECONDARY
	};

	/**
	 * @brief instantiates a junction object and subscribes it to an observer subject
	 *
	 * @param subject - subject to subscribe this junction to
	 * @param  id - junction's id
	 * @return std::shared_ptr<TrackJunction> - a pointer to created object
	 */
	static std::shared_ptr<TrackJunction> create(HeartBeatSubject &subject,
			int id)
	{
		auto ptr = std::shared_ptr<TrackJunction>(new TrackJunction(subject, id));
		subject.attach(ptr);
		return ptr;
	}

	void set_next_secondary(std::shared_ptr<TrackPoint> next_switched)
	{
		_next_secondary = next_switched;
		// assigning the next one's previous point value to the current point
		_next_secondary->set_prev(shared_from_this());
	}

	void make_switch(SwitchPosition switch_pos)
	{
		_switch_pos = switch_pos;
		//Allowing to move both directions from forked points for now
		//Disabling the unplugged  and enabling connected point in reverse direction by "removing"
		//or adding it's previous point
		auto disabled_point =
				(_switch_pos == SWITCH_POS_MAIN) ? _next_secondary : _next;
		auto enabled_point =
				(_switch_pos == SWITCH_POS_MAIN) ? _next : _next_secondary;
		disabled_point->set_prev(nullptr);
		enabled_point->set_prev(shared_from_this());
	}

	const std::shared_ptr<TrackPoint>& get_next_secondary() const
	{
		return _next_secondary;
	}

	void accept(const std::shared_ptr<AbstractVisitor> visitor);
	virtual ~TrackJunction() = default;

	SwitchPosition get_switch_pos() const
	{
		return _switch_pos;
	}

private:
	/**
	 * @brief track junction constructor
	 *
	 * @param subject - subject to subscribe this junction to
	 * @param  id - junction's id
	 */
	TrackJunction(HeartBeatSubject &subject, int id) :
			TrackPoint(id), HeartBeatObserver(subject)
	{
	}
	SwitchPosition _switch_pos = SWITCH_POS_MAIN;
	std::shared_ptr<TrackPoint> _next_secondary = nullptr;
};

#endif /* TRACKJUNCTION_H_ */
