/**
 * @file AbstractObserver.h
 * @author Vadim Lapchinskiy
 * @brief Observer interface definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef ABSTRACTOBSERVER_H_
#define ABSTRACTOBSERVER_H_

#include <memory>
#include "AbstractVisitor.h"

class AbstractObserver
{
public:
	AbstractObserver() = default;
	virtual void accept(const std::shared_ptr<AbstractVisitor> visitor) = 0;
	virtual ~AbstractObserver() = default;
};

#endif /* ABSTRACTOBSERVER_H_ */
