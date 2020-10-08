/**
 * @file HeartBeatSubject.cpp
 * @author Vadim Lapchinskiy
 * @brief HeartBeatObserver class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "HeartBeatSubject.h"
#include "SimulEngine.h"

using namespace std;

/**
 * @brief Notifies all registered observers about the heart beat event
 *
 * @param visitors - list of visitors to be visiting registered observers
 * @return void
 */
void HeartBeatSubject::notify_all(list<shared_ptr<AbstractVisitor>> visitors)
{
	for (auto &visitor : visitors)
	{
		for (auto &observer : _observers)
		{
			observer->accept(visitor);
		}
	}
}

