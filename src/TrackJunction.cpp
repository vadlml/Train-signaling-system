/**
 * @file TrackJunction.cpp
 * @author Vadim Lapchinskiy
 * @brief Track Junction class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "TrackJunction.h"

using namespace std;

/**
 * @brief accepts the visitor object and runs the needed visiting method on it
 *
 * @param visitor - visitor object
 * @return void
 */
void TrackJunction::accept(const shared_ptr<AbstractVisitor> visitor)
{
	visitor->visit_junction(*this);
}
