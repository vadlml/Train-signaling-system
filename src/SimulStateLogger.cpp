/**
 * @file SimulStateLogger.cpp
 * @author Vadim Lapchinskiy
 * @brief Simulation State Logger class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "SimulStateLogger.h"
#include "Signal.h"
#include "Train.h"
#include "TrackJunction.h"
#include <iostream>

using namespace std;

/**
 * @brief train logger visit method implementation
 *
 * @param train - train visitor object
 * @return void
 */
void SimulStateLogger::visit_train(Train &train)
{
	switch (train.get_state())
	{
	case Train::STATE_RUNNING:
		_out_stream << "Train#" << train.get_id() << " moved to point#"
				<< train.get_current_point()->get_id() << endl;

		break;
	case Train::STATE_STOPPED:
		_out_stream << "Train#" << train.get_id() << " stopped at point#"
				<< train.get_current_point()->get_id() << endl;

		break;
	case Train::STATE_CRASHED:
		_out_stream << "Train#" << train.get_id() << " crashed at point#"
				<< train.get_current_point()->get_id() << endl;

		break;
	case Train::STATE_WAITING:
		_out_stream << "Train#" << train.get_id() << " waiting at point#"
				<< train.get_current_point()->get_id() << endl;

		break;
	default:
		_out_stream << "Train#" << train.get_id() << " state unknown!" << endl;
		break;
	}
}

/**
 * @brief signal logger visit method implementation
 *
 * @param junction - signal visitor object
 * @return void
 */
void SimulStateLogger::visit_signal(Signal &signal)
{
	switch (signal.get_state())
	{
	case Signal::STATE_GREEN:
		_out_stream << "Signal#" << signal.get_id() << " is green" << endl;
		break;
	case Signal::STATE_RED:
		_out_stream << "Signal#" << signal.get_id() << " is red" << endl;
		break;
	default:
		_out_stream << "Signal#" << signal.get_id() << " state unknown!"
				<< endl;
		break;

	}
}

/**
 * @brief junction logger visit method implementation
 *
 * @param junction - junction visitor object
 * @return void
 */
void SimulStateLogger::visit_junction(TrackJunction &junction)
{
	int switch_point_id =
			(junction.get_switch_pos() == TrackJunction::SWITCH_POS_MAIN) ?
					junction.get_next()->get_id() :
					junction.get_next_secondary()->get_id();
	_out_stream << "Junction#" << junction.get_id() << " is set to point "
			<< switch_point_id << endl;
}

