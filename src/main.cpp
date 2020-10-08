/**
 * @file main.cpp
 * @author Vadim Lapchinskiy
 * @brief program's entry point
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "SimulRunner.h"
#include "EventLogger.h"

using namespace std;

void print_usage(int argc, char *argv[])
{
	std::cerr << "Usage: " << argv[0] << " [FILE]... [OPTION]... " << std::endl;
	std::cerr << "Options: " << std::endl;
	std::cerr << "         -v - verbose output with event log messages;"
			<< std::endl;
	std::cerr << "Example: " << argv[0] << " input.json" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
	{
		print_usage(argc, argv);
		return 1;
	}
	try
	{
		if (argc == 2)
		{
			SimulRunner runner(argv[1]);
			runner.run();
		}
		else if (std::string(argv[2]) == "-v")
		{
			EventLogger::set_log_enabled(true);
			SimulRunner runner(argv[1]);
			runner.run();
		}
		else
		{
			print_usage(argc, argv);
			return -1;
		}
	} catch (invalid_argument &e)
	{
		cerr << "Invalid argument: " << e.what() << endl;
		return -1;
	} catch (nlohmann::detail::type_error &e)
	{
		cerr << "error in json file format: " << e.what() << endl;
		return -1;
	}
	return 0;
}
