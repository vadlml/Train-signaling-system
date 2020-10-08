/**
 * @file HeartBeatSubject.h
 * @author Vadim Lapchinskiy
 * @brief HeartBeatObserver class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef HEARTBEATSUBJECT_H_
#define HEARTBEATSUBJECT_H_

#include <iostream>
#include <list>
#include <memory>
#include "AbstractObserver.h"

class HeartBeatSubject
{
public:
	HeartBeatSubject() = default;

	/**
	 * @brief Subscribes observer object to the current subject
	 *
	 * @param obs - observer object to be subscribed
	 * @return void
	 */
	void attach(std::shared_ptr<AbstractObserver> obs)
	{
		_observers.push_back(obs);
	}

	/**
	 * @brief Unsubscribes observer object from the current subject
	 *
	 * @param obs - observer object to be unsubscribed
	 * @return void
	 */
	void detach(std::shared_ptr<AbstractObserver> obs)
	{
		_observers.remove(obs);
	}

	void notify_all(std::list<std::shared_ptr<AbstractVisitor>> visitors);
	virtual ~HeartBeatSubject() =default;
private:
	std::list<std::shared_ptr<AbstractObserver>> _observers;

};

#endif /* HEARTBEATSUBJECT_H_ */
