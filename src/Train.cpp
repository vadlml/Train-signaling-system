/**
 * @file Train.cpp
 * @author Vadim Lapchinskiy
 * @brief Train class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Train.h"

using namespace std;

/**
 * @brief accepts the visitor object and runs the needed visiting method on it
 *
 * @param visitor - visitor object
 * @return void
 */
void Train::accept(const shared_ptr<AbstractVisitor> visitor)
{
	visitor->visit_train(*this);
}

/**
 * @brief moves train to next track point
 *
 * @param void
 * @return void
 */
void Train::move(void)
{
	auto next_move_point =
			(this->get_dir() == Train::DIR_FORWARD) ?
					_curr_point->get_next() : _curr_point->get_prev();
	// moving to the next track point
	_curr_point->release();
	if(next_move_point)
	{
		next_move_point->occupy();
	}
	this->set_curr_point(next_move_point);
}
