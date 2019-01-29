#pragma once

#include "MarsRoverTypes.h"

#include <memory>

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

/**
 * @brief Mars Plateau interface definition
 *
 * Represents @ref MarsPlateau which could be navigated by Mars Rovers.
 */
class MarsPlateau
{
public:
    virtual ~MarsPlateau( ) = default;

    /**
     * @brief Check whenever supplied coordinates are in plateau' bounding boxes.
     * @param coords: coordinates to be tested.
     * @retval true if coordinates inside bounding boxes, false otherwise
     */
    virtual bool is_possible_move( const Coordinates& coords ) const = 0;
};

/** @}*/

}  // namespace mars_rover
