/**
 * @file HeartBeatObserver.h
 * @author Vadim Lapchinskiy
 * @brief HeartBeatObserver interface definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef HEARTBEATOBSERVER_H_
#define HEARTBEATOBSERVER_H_
#include <memory>
#include "AbstractObserver.h"
#include "HeartBeatSubject.h"

class HeartBeatObserver: public AbstractObserver
{
public:
	HeartBeatObserver(HeartBeatSubject &subject) :
			_subject(subject)
	{
	}

	virtual void accept(const std::shared_ptr<AbstractVisitor> visitor) = 0;
	virtual ~HeartBeatObserver() = default;
protected:
	HeartBeatSubject &_subject;
};

#endif /* HEARTBEATOBSERVER_H_ */
