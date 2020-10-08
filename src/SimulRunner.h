/**
 * @file SimulRunner.h
 * @author Vadim Lapchinskiy
 * @brief Simulation Runner class declaration
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SIMULRUNNER_H_
#define SIMULRUNNER_H_

#include <memory>
#include <map>
#include <vector>
#include "TrackPoint.h"
#include "Train.h"
#include "Signal.h"
#include "TrackJunction.h"

class SimulRunner
{
public:
	SimulRunner(const std::basic_string<char>& in_file_path);
	void run(void);
	virtual ~SimulRunner() = default;
private:
	void AddPointLine(const std::vector<int> &point_ids);
	void AddTrain(int id, Train::Direction dir, int start_point_id);
	void AddSignal(int id, int point_id);
	bool check_all_trains_stopped(void);
	HeartBeatSubject _heartbeat_subj;
	std::map<int, std::shared_ptr<TrackPoint>> _track_points;
	std::map<int, std::shared_ptr<Train>> _trains;
	std::map<int, std::shared_ptr<Signal>> _signals;
};

#endif /* SIMULRUNNER_H_ */
