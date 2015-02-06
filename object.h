
#pragma once
#ifndef h_object
#define h_object
#include <iostream>

std::object<int,std::string> objects = boost::assign::object
    (map,"map")
	(item_carpet, "item_carpet")
	(item_spot, "item_spot")
	(item_popcorn, "item_popcorn")
	(item_cup, "item_cup")
	(item_stand_yellow, "item_stand_yellow")
	(item_stand_green, "item_stand_green")
	(item_clap_yellow, "item_clap_yellow")
	(item_clap_green, "item_clap_green")
	(item_popcorn_machine, "item_popcorn_machine")

	(area_building, "area_building")
	(area_platform, "area_platform")
	(area_step_yellow, "area_step_yellow")
	(area_step_green, "area_step_green")
	(area_starting_yellow, "area_starting_yellow")
	(area_starting_green, "area_starting_green")
	(area_cinema_yellow, "area_cinema_yellow")
	(area_cinema_green, "area_cinema_green")

	(wall, "wall")

	(robot_main, "robot_main")
	(robot_secondary,"robot_secondary");

typedef enum object {

	map,

	item_carpet,
	item_spot,
	item_popcorn,
	item_cup,
	item_stand_yellow,
	item_stand_green,
	item_clap_yellow,
	item_clap_green,
	item_popcorn_machine,

	area_building,
	area_platform,
	area_step_yellow,
	area_step_green,
	area_starting_yellow,
	area_starting_green,
	area_cinema_yellow,
	area_cinema_green,

	wall,

	robot_main,
	robot_secondary

} object_t;

#endif
