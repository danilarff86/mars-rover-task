#pragma once

#include "MarsRoverTypes.h"

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

/**
 * @brief Command Center class definition
 *
 * Represents CommandCenter class which control the Mars Rovers.
 */
class CommandCenter
{
public:
    CommandCenter( ) = default;

    /**
     * @brief Performs all actions on rovers
     *
     * Instantiates all rovers from input data. Send actions to them. Collects final states of the
     * rovers and return it as output data.
     *
     * @param input_data: Initial states of entities and commands to be performed on them
     * @return final states of the rovers
     */
    CommandCenterOutput process( const CommandCenterInput& input_data ) const;
};

/** @}*/

}  // namespace mars_rover
