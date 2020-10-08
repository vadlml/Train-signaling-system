/**
 * @file EventLogger.h
 * @author Vadim Lapchinskiy
 * @brief Event logger class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */


#ifndef EVENTLOGGER_H_
#define EVENTLOGGER_H_

#include <iostream>
#include "Signal.h"
#include "Train.h"
#include "TrackJunction.h"

class EventLogger
{
public:
	static void log_train(Train& train);
	static void log_signal(Signal& signal);
	static void log_junction(TrackJunction& junction);

	static void set_log_enabled(bool log_enabled = false)
	{
		_log_enabled = log_enabled;
	}

private:
	static bool _log_enabled;
};

#endif /* EVENTLOGGER_H_ */
