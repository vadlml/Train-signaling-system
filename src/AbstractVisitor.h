/**
 * @file AbstractVisitor.h
 * @author Vadim Lapchinskiy
 * @brief Visitor interface definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef ABSTRACTVISITOR_H_
#define ABSTRACTVISITOR_H_

#include <memory>

class Train;
class Signal;
class TrackJunction;

class AbstractVisitor
{
public:
	AbstractVisitor() = default;
	virtual void visit_train(Train &train) = 0;
	virtual void visit_signal(Signal &signal) = 0;
	virtual void visit_junction(TrackJunction &junction) = 0;
	virtual ~AbstractVisitor() = default;
};

#endif /* ABSTRACTVISITOR_H_ */
