/**
 * @file SimulEngine.cpp
 * @author Vadim Lapchinskiy
 * @brief SimulEngine class definition - Simulation logic implementation
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "SimulEngine.h"
#include "Signal.h"
#include "Train.h"
#include "TrackJunction.h"
#include "EventLogger.h"

using namespace std;

/**
 * @brief train logic implementation
 *
 * @param train - train visitor object
 * @return void
 */
void SimulEngine::visit_train(Train &train)
{
	auto curr_state = train.get_state();
	//no need to update state if train is stopped or crashed
	if (curr_state == Train::STATE_STOPPED
			|| curr_state == Train::STATE_CRASHED)
	{
		return;
	}
	auto curr_train_point = train.get_current_point();
	auto next_move_point =
			(train.get_dir() == Train::DIR_FORWARD) ?
					curr_train_point->get_next() : curr_train_point->get_prev();
	//checking if the train is about to go to the terminator
	if (next_move_point)
	{
		auto next_point_signal = next_move_point->get_signal();
		//checking if the next point
		if (!next_point_signal
				|| next_point_signal->get_state() == Signal::STATE_GREEN)
		{
			// checking if any other train had arrived to this point except us
			if (curr_train_point->get_occupancy() == 1)
			{
				// moving to the next track point
				train.move();
				if (next_move_point->get_occupancy() > 1)
				{
					train.set_state(Train::STATE_CRASHED);
				}
				else
				{
					train.set_state(Train::STATE_RUNNING);
				}
			}
			else
			{
				train.set_state(Train::STATE_CRASHED);
			}
		}
		else
		{
			train.set_state(Train::STATE_WAITING);
		}
	}
	//check if there is signal placed in this point and it is a connected point or it is a terminator
	else if (auto curr_point_signal = curr_train_point->get_signal())
	{
		auto signal_state = curr_point_signal->get_state();
		if (signal_state == Signal::STATE_RED)
		{
			// train is waiting at the red stop
			train.set_state(Train::STATE_WAITING);
		}
		else
		{
			//junction did not switched properly
			train.set_state(Train::STATE_CRASHED);
		}
	}
	else
	{
		//stopping at the terminator
		train.set_state(Train::STATE_STOPPED);
	}
	EventLogger::log_train(train);
}

/**
 * @brief junction logic implementation
 *
 * @param junction - junction visitor object
 * @return void
 */
void SimulEngine::visit_junction(TrackJunction &junction)
{
	static auto junction_last_switch_pos = TrackJunction::SWITCH_POS_MAIN;
	auto next_secondary_signal = junction.get_next_secondary()->get_signal();
	auto next_primary_signal = junction.get_next()->get_signal();
	//if there are signals place on each ends of junctions
	if (next_primary_signal && next_secondary_signal)
	{
		auto point_a = make_shared<TrackPoint>(junction);
		auto point_b = junction.get_next();
		auto point_c = junction.get_next_secondary();
		// checking if there is a train on the line before junction (<--a)
		if (!is_line_clear(point_a, Train::DIR_REVERSE))
		{
			// if line a-->b is free
			if (is_line_clear(point_b, Train::DIR_FORWARD))
			{
				// switching to primary
				junction.make_switch(TrackJunction::SWITCH_POS_MAIN);
				if (next_secondary_signal)
				{
					next_secondary_signal->set_state(Signal::STATE_RED);
				}
				if (next_primary_signal)
				{
					next_primary_signal->set_state(Signal::STATE_GREEN);
				}
			}
			// if line a-->c is free
			else if (is_line_clear(point_c, Train::DIR_FORWARD))
			{
				// switching to secondary
				junction.make_switch(TrackJunction::SWITCH_POS_SECONDARY);
				if (next_primary_signal)
				{
					next_primary_signal->set_state(Signal::STATE_RED);
				}
				if (next_secondary_signal)
				{
					next_secondary_signal->set_state(Signal::STATE_GREEN);
				}
			}
			else
			{
				//Nowhere to go waiting till cleared
				next_primary_signal->set_state(Signal::STATE_RED);
				next_secondary_signal->set_state(Signal::STATE_RED);
			}
		}
		// if line a-->b is busy
		else if (!is_line_clear(point_b, Train::DIR_FORWARD))
		{
			// switching to primary
			junction.make_switch(TrackJunction::SWITCH_POS_MAIN);
			if (next_secondary_signal)
			{
				next_secondary_signal->set_state(Signal::STATE_RED);
			}
			if (next_primary_signal)
			{
				next_primary_signal->set_state(Signal::STATE_GREEN);
			}
		}
		// if line a-->c is busy
		else if (!is_line_clear(point_c, Train::DIR_FORWARD))
		{
			// switching to secondary
			junction.make_switch(TrackJunction::SWITCH_POS_SECONDARY);
			if (next_primary_signal)
			{
				next_primary_signal->set_state(Signal::STATE_RED);
			}
			if (next_secondary_signal)
			{
				next_secondary_signal->set_state(Signal::STATE_GREEN);
			}
		}
		else
		{
			// switching to primary
			junction.make_switch(TrackJunction::SWITCH_POS_MAIN);
			if (next_secondary_signal)
			{
				next_secondary_signal->set_state(Signal::STATE_RED);
			}
			if (next_primary_signal)
			{
				next_primary_signal->set_state(Signal::STATE_GREEN);
			}
		}
	}
// logging the state update
	if (junction_last_switch_pos != junction.get_switch_pos())
	{
		junction_last_switch_pos = junction.get_switch_pos();
		if (next_primary_signal)
		{
			EventLogger::log_signal(*next_primary_signal);
		}
		if (next_secondary_signal)
		{
			EventLogger::log_signal(*next_secondary_signal);
		}
		EventLogger::log_junction(junction);
	}
}

/**
 * @brief checks if the line is clear of trains starting from the given point
 *
 * @param signal - junction visitor object
 * @return void
 */
bool SimulEngine::is_line_clear(const std::shared_ptr<TrackPoint> start_point,
		Train::Direction dir)
{
	auto track_point = start_point;
	// going till terminator or till next junction
	while (track_point && (!dynamic_pointer_cast<TrackJunction>(track_point)))
	{
		auto next_point =
				(dir == Train::DIR_FORWARD) ?
						track_point->get_next() : track_point->get_prev();
		// line if clear if the is no train on it's point except terminals
		if (track_point->get_occupancy() > 0 && next_point)
		{
			return false;
		}
		track_point = next_point;
	}
	return true;
}

/**
 * @brief signal logic implementation
 *
 * @param signal - junction visitor object
 * @return void
 */
void SimulEngine::visit_signal(Signal &signal)
{
}
