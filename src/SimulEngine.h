/**
 * @file SimulEngine.h
 * @author Vadim Lapchinskiy
 * @brief SimulEngine class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SIMULENGINE_H_
#define SIMULENGINE_H_

#include "AbstractVisitor.h"
#include "TrackPoint.h"
#include "Train.h"

class SimulEngine: public AbstractVisitor
{
public:
	SimulEngine() = default;
	bool is_line_clear(const std::shared_ptr<TrackPoint> start_point, Train::Direction dir);
	void visit_train(Train &train) override;
	void visit_signal(Signal &signal);
	void visit_junction(TrackJunction &junction) override;
	~SimulEngine() = default;
private:
};

#endif /* SIMULENGINE_H_ */
