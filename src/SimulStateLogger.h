/**
 * @file SimulStateLogger.h
 * @author Vadim Lapchinskiy
 * @brief Simulation State Logger class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SIMULSTATELOGGER_H_
#define SIMULSTATELOGGER_H_

#include <iostream>
#include "AbstractVisitor.h"

class SimulStateLogger: public AbstractVisitor
{
public:
	SimulStateLogger(std::ostream &out_stream) :
			_out_stream(out_stream)
	{
	}
	void visit_train(Train &train) override;
	void visit_signal(Signal &signal) override;
	void visit_junction(TrackJunction &junction) override;
	virtual ~SimulStateLogger() = default;
private:
	std::ostream &_out_stream;
};

#endif /* SIMULSTATELOGGER_H_ */
