/**
 * @file SimulRunner.cpp
 * @author Vadim Lapchinskiy
 * @brief Simulation Runner class definition
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include <memory>
#include <list>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SimulRunner.h"
#include "SimulEngine.h"
#include "SimulStateLogger.h"
#include "EventLogger.h"

const int MAXIMUM_SIMULATION_TICKS = 1e4;

using json = nlohmann::json;
using namespace std;

/**
 * @brief Simulation runner constructor - extracts the simulation data from the input file
 * @param in_file_path - a path to input json file path
 * @return void
 */
SimulRunner::SimulRunner(const basic_string<char> &in_file_path)
{
	ifstream in_file;
	in_file.open(in_file_path, ifstream::in);
	if (!in_file.good())
	{
		throw invalid_argument("cannot open file: "s + in_file_path + "!"s);
	}
	json json_obj;
	in_file >> json_obj;
	for (json::iterator it = json_obj.begin(); it != json_obj.end(); ++it)
	{
		if (it.key() == "lines")
		{
			auto line_arr = it.value();
			for (auto a : line_arr)
			{
				vector<int> v = a;
				AddPointLine(v);
			}
		}
		if (it.key() == "trains")
		{
			auto train_arr = it.value();
			for (auto &el : train_arr)
			{
				int id = el["id"];
				Train::Direction dir =
						(el["dir"] == "Forward") ?
								Train::DIR_FORWARD : Train::DIR_REVERSE;
				int start_point_id = el["start_point id"];
				AddTrain(id, dir, start_point_id);
			}
		}
		if (it.key() == "signals")
		{
			auto sign_arr = it.value();
			for (auto &el : sign_arr)
			{
				int id = el["id"];
				int point_id = el["point id"];
				AddSignal(id, point_id);
			}
		}
	}
}

/**
 * @brief starts simulation
 * @param void
 * @return void
 */
void SimulRunner::run(void)
{
	auto simul_engine = shared_ptr<AbstractVisitor>(new SimulEngine);
	auto state_logger = shared_ptr<AbstractVisitor>(new SimulStateLogger(cout));
	auto visitors =
	{ simul_engine, state_logger };

	int sim_tick = 0;
	while (!check_all_trains_stopped() && sim_tick < MAXIMUM_SIMULATION_TICKS)
	{
		cout << "----------------------Time tick = " << ++sim_tick
				<< "---------------------------" << endl;
		_heartbeat_subj.notify_all(visitors);
		cout << "----------------------Time tick = " << sim_tick
				<< "---------------------------" << endl;
	}
	cout << "Simulation finished!" << endl;
}

/**
 * @brief adds a line of point to the simulation object
 * @param point_ids - a reference to a vector of track ppint ids
 * @return void
 */
void SimulRunner::AddPointLine(const std::vector<int> &point_ids)
{
	shared_ptr<TrackPoint> prev_point = nullptr;
	for (auto it = point_ids.begin(); it != point_ids.end(); ++it)
	{
		// it a point with this id already exists create a junction
		if (_track_points.find(*it) != _track_points.end())
		{
			if (!_track_points[*it]->get_next())
			{
				throw invalid_argument(
						"Wrong point line input. Merging cannot start at the end of existing line!"s);
			}
			if (it == point_ids.begin())
			{
				//checking if existing point is regular point and junction
				if (!dynamic_pointer_cast<TrackJunction>(_track_points[*it]))
				{
					// replacing the existing node with junction
					auto next_tmp = _track_points[*it]->get_next();
					auto prev_tmp = _track_points[*it]->get_prev();
					_track_points[*it] = TrackJunction::create(_heartbeat_subj,
							*it);
					prev_tmp->set_next(_track_points[*it]);
					_track_points[*it]->set_next(next_tmp);
				}
				else
				{
					throw invalid_argument(
							"Wrong point line input. Cannot put junction on existing junction!"s);
				}
			}
			else
			{
				throw invalid_argument(
						"Wrong point line input. Merging allowed only from the beginning of the merging line!"s);
			}
		}
		else
		{
			_track_points[*it] = shared_ptr<TrackPoint>(new TrackPoint(*it));
			if (prev_point)
			{
				// setting to secondary point line for previous junction line
				if (auto junction = dynamic_pointer_cast<TrackJunction>(
						prev_point))
				{
					junction->set_next_secondary(_track_points[*it]);
				}
				else
				{
					prev_point->set_next(_track_points[*it]);
				}
			}
		}
		prev_point = _track_points[*it];
	}
}

/**
 * @brief adds signal object to the simulation object
 * @param id - signal's unique id
 * @param point_id - a point id to associate this signal with
 * @return void
 */
void SimulRunner::AddSignal(int id, int point_id)
{
	auto point = _track_points[point_id];
	//if there is already train with this id
	if (_signals.find(id) != _signals.end())
	{
		throw invalid_argument(
				"signal with id#"s + to_string(id) + " already exists!"s);
	}
	else if (!point)
	{
		throw invalid_argument(
				"cannot place signal on non existing point id#"s
						+ to_string(point_id) + "!"s);
	}
	else if (point->get_signal())
	{
		throw invalid_argument(
				"cannot place more than one signal on point#"s
						+ to_string(point_id) + "!"s);
	}
	else
	{
		if (auto start_point = _track_points[point_id])
		{
			_signals[id] = Signal::create(_heartbeat_subj, id, point);
		}
	}
}

/**
 * @brief adds train object to the simulation object
 * @param id - train's unique id
 * @param dir - train's direction
 * @param start_point_id - a start point id to put this train in
 * @return void
 */
void SimulRunner::AddTrain(int id, Train::Direction dir, int start_point_id)
{
	auto start_point = _track_points[start_point_id];
	//if there is already train with this id
	if (_trains.find(id) != _trains.end())
	{
		throw invalid_argument(
				"train with id#"s + to_string(id) + " already exists!"s);
	}
	else if (!start_point)
	{
		throw invalid_argument(
				"cannot place train on non existing point id#"s
						+ to_string(start_point_id) + "!"s);
	}
	else if (start_point->get_occupancy() > 0)
	{
		throw invalid_argument(
				"cannot place train on the occupied point#"s
						+ to_string(start_point_id) + "!"s);
	}
	else
	{
		_trains[id] = Train::create(_heartbeat_subj, id, dir, start_point);

	}
}

/**
 * @brief chaks if all trains are stopped or crashed
 * @param void
 * @return void
 */
bool SimulRunner::check_all_trains_stopped(void)
{
	for (auto &train_pair : _trains)
	{
		if (train_pair.second->get_state() != Train::STATE_STOPPED
				&& train_pair.second->get_state() != Train::STATE_CRASHED)
		{
			return false;
		}
	}
	return true;
}
