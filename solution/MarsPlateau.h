#pragma once

#include "MarsRoverTypes.h"

#include <memory>

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

/**
 * @brief Mars Plateau class definition
 *
 * Represents @ref MarsPlateau class which could be navigated by Mars Rovers.
 */
class MarsPlateau
{
public:
    /**
     * @brief @ref MarsPlateau constructor which accepts upper right corner coordinates.
     *
     * @param upper_right_corner: coordinates of plateau' upper right corner
     */
    explicit MarsPlateau( Coordinates upper_right_corner )
        : m_upper_right_corner( std::move( upper_right_corner ) )
    {
    }

    /**
     * @brief Check whenever supplied ccordinates are in plateau' bounding boxes.
     * @param coords: coordinates to be tested.
     * @retval true if coordines inside bounding boxes, false otherwise
     */
    inline bool
    is_possible_move( Coordinates coords ) const
    {
        return coords.x >= 0 && coords.y >= 0 && coords.x <= m_upper_right_corner.x
               && coords.y <= m_upper_right_corner.y;
    }

private:
    const Coordinates m_upper_right_corner; /*!< upper right corner of plateau' grid. */
};

/** @}*/

}  // namespace mars_rover
