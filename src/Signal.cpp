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
 * @brief Get accepts the visitor object and runs on needed visiting method
 *
 * @param visitor - visitor object
 * @return void
 */
void Signal::accept(const shared_ptr<AbstractVisitor> visitor)
{
	visitor->visit_signal(*this);
}
