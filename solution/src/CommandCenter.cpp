/*
 * Copyright (c) 2019 PE Lubenets. All rights reserved.
 * Licensed under the MIT License.
 */

#include "CommandCenter.h"
#include "MarsPlateauImpl.h"
#include "MarsRover.h"

#include <algorithm>

namespace mars_rover
{
CommandCenterOutput
CommandCenter::process( const CommandCenterInput& input_data ) const
{
    const MarsPlateauImpl plateau( input_data.upper_right_corner_of_plateau );

    CommandCenterOutput result;
    result.reserve( input_data.rovers_data.size( ) );

    for ( const auto& rover_data : input_data.rovers_data )
    {
        MarsRover rover( plateau, rover_data.initial_state );
        std::for_each( rover_data.command_sequence.begin( ), rover_data.command_sequence.end( ),
                       [&rover]( eCommand cmd ) { rover.do_action( cmd ); } );
        result.emplace_back( rover.get_state( ) );
    }

    // RVO
    return result;
}

}  // namespace mars_rover
