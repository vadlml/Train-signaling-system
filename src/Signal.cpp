/**
 * @file Signal.cpp
 * @author Vadim Lapchinskiy
 * @brief Signal class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Signal.h"

using namespace std;

/**
 * @brief accepts the visitor object and runs the needed visiting method on it
 *
 * @param visitor - visitor object
 * @return void
 */
void Signal::accept(const shared_ptr<AbstractVisitor> visitor)
{
	visitor->visit_signal(*this);
}
