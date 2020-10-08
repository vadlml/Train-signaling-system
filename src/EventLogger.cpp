/**
 * @file EventLogger.cpp
 * @author Vadim Lapchinskiy
 * @brief Event logger class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "EventLogger.h"

using namespace std;

bool EventLogger::_log_enabled = false;

/**
 * @brief logs the trains's object state
 *
 * @param train - train object
 * @return void
 */
void EventLogger::log_train(Train &train)
{
	if (EventLogger::_log_enabled)
	{
		switch (train.get_state())
		{
		case Train::STATE_RUNNING:
			cout << "Event--> Train#" << train.get_id() << " moving to point#"
					<< train.get_current_point()->get_id() << endl;

			break;
		case Train::STATE_STOPPED:
			cout << "Event--> Train#" << train.get_id() << " stopping at point#"
					<< train.get_current_point()->get_id() << endl;

			break;
		case Train::STATE_CRASHED:
			cout << "Event--> Train#" << train.get_id() << " crashing at point#"
					<< train.get_current_point()->get_id() << endl;

			break;
		case Train::STATE_WAITING:
			cout << "Event--> Train#" << train.get_id() << " waiting at point#"
					<< train.get_current_point()->get_id() << endl;

			break;
		default:
			cout << "Event--> Train#" << train.get_id() << " state unknown!"
					<< endl;
			break;
		}
	}
}

/**
 * @brief logs the signal's object state
 *
 * @param signal - signal object
 * @return void
 */
void EventLogger::log_signal(Signal &signal)
{
	if (EventLogger::_log_enabled)
	{
		switch (signal.get_state())
		{
		case Signal::STATE_GREEN:
			cout << "Event--> Signal#" << signal.get_id() << " is set to green"
					<< endl;
			break;
		case Signal::STATE_RED:
			cout << "Event--> Signal#" << signal.get_id() << " is set to red"
					<< endl;
			break;
		default:
			cout << "Event--> Signal#" << signal.get_id()
					<< "is set to unknown state!" << endl;
			break;
		}
	}
}

/**
 * @brief logs the junctions's object state
 *
 * @param signal - junction object
 * @return void
 */
void EventLogger::log_junction(TrackJunction &junction)
{
	if (EventLogger::_log_enabled)
	{
		int switch_point_id =
				(junction.get_switch_pos() == TrackJunction::SWITCH_POS_MAIN) ?
						junction.get_next()->get_id() :
						junction.get_next_secondary()->get_id();
		cout << "Event--> Junction#" << junction.get_id()
				<< " is switching to point " << switch_point_id << endl;
	}
}
