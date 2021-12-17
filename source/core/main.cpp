/** @file main.cpp
 *
 * @description
 * This program implements a bar char race animation.
 *
 * ===========================================================================
 * @license
 *
 * This file is part of BARCHART RACE project.
 *
 * BAR_CHART_RACE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * BAR_CHART_RACE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Copyright (C) 2021 Pedro Costa Aragão
 * ===========================================================================
 *
 * @author	Pedro Costa Aragão, <pedroc_aragao@outlook.com>
 * @date	2021
 *
 * @remark On 2021-09-19 changed ...
 */

#include <cstdlib> // EXIT_SUCCESS

#include "bcr_am.h"

int main( int argc, char ** argv )
{
    bcra::BCRAnimation animation;
    
    animation.read_cli_input(argc, argv);
    animation.display_welcome();
    animation.read_input_file();
    animation.display_input_read();
    animation.begin_animation();

    return EXIT_SUCCESS;
}
