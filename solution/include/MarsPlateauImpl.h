#pragma once

#include "MarsPlateau.h"

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

/**
 * @brief Mars Plateau implementation
 *
 * Implements @ref MarsPlateau which could be navigated by Mars Rovers.
 */
class MarsPlateauImpl : public MarsPlateau
{
public:
    /**
     * @brief @ref MarsPlateauImpl constructor which accepts upper right corner coordinates.
     *
     * @param upper_right_corner: coordinates of plateau' upper right corner
     */
    explicit MarsPlateauImpl( Coordinates upper_right_corner )
        : m_upper_right_corner( std::move( upper_right_corner ) )
    {
    }

    /**
     * @brief Interface method implementation of @ref MarsPlateau
     */
    bool
    is_possible_move( const Coordinates& coords ) const override
    {
        return coords.x >= 0 && coords.y >= 0 && coords.x <= m_upper_right_corner.x
               && coords.y <= m_upper_right_corner.y;
    }

private:
    const Coordinates m_upper_right_corner; /*!< upper right corner of plateau' grid. */
};

/** @}*/

}  // namespace mars_rover
