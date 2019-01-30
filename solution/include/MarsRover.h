/*
 * Copyright (c) 2019 PE Lubenets. All rights reserved.
 * Licensed under the MIT License.
 */

#pragma once

#include "MarsRoverTypes.h"

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

class MarsPlateau;

/**
 * @brief Mars Rover class definition
 *
 * Represents MarsRover class which navigates the Mars plateau.
 */
class MarsRover
{
public:
    /**
     * @brief @ref MarsRover constructor which accepts initial state.
     *
     * @param plateau: plateau to be navigated by Mars Rover
     * @param state: initial state of Mars Rover
     */
    MarsRover( const MarsPlateau& plateau, MarsRoverState state )
        : m_plateau( plateau )
        , m_state( std::move( state ) )
    {
    }

    /**
     * @brief Perform instruction
     * @param cmd: instruction value to be performed
     */
    void do_action( eCommand cmd );

    /**
     * @brief Returns the actual state of Mars Rover
     * @retval const reference to the actual state
     */
    inline const MarsRoverState&
    get_state( ) const
    {
        return m_state;
    }

private:
    MarsRover( const MarsRover& ) = delete;
    MarsRover& operator=( const MarsRover& ) = delete;

    void move_forward( );

private:
    const MarsPlateau& m_plateau;
    MarsRoverState m_state;
};

/** @}*/

}  // namespace mars_rover
