#pragma once

#include <stdexcept>
#include <vector>

namespace mars_rover
{
/** \addtogroup MarsRover
 *  @{
 */

/**
 * @brief Base @ref MarsRover exception class
 *
 * Is used as the most base exception class. All other exceptions derive from this exception class.
 */
struct MarsRoverException : public std::logic_error
{
    /**
     * @brief implicit @ref MarsRoverException string constructor.
     *
     * @ref MarsRoverException have a single implicit string constructor. Error description is
     * passed as argument.
     * @param message: error description
     */
    MarsRoverException( std::string const& message )
        : std::logic_error( message )
    {
    }
};

/**
 * @brief @ref eCommand enumeration of all possible @ref MarsRover commands
 */
enum class eCommand
{
    TurnRight = 0,
    TurnLeft = 1,
    MoveForward = 2
};

/**
 * @brief @ref eDirection enumeration of all possible @ref MarsRover directions
 */
enum class eDirection
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

/**
 * @brief @ref CoordinateType type definition for plateau grid
 */
using CoordinateType = int;

/**
 * @brief @ref Coordinates type definition for plateau grid
 */
struct Coordinates
{
    CoordinateType x; /*!< x coordinate. */
    CoordinateType y; /*!< y coordinate. */
};

/**
 * @brief @ref MarsRover state structure
 *
 * Represents @ref MarsRoverState: direction with position.
 */
struct MarsRoverState
{
    eDirection direction;
    Coordinates position;
};

/**
 * @brief @ref CommandCenterInput type definition, which holds all initial data for Plateau and
 * Rovers.
 */
struct CommandCenterInput
{
    /**
     * @brief @ref CommandSequence type definition, which holds the sequence of @ref eCommand for
     * @ref MarsRover
     */
    using CommandSequence = std::vector< eCommand >;

    /**
     * @brief @ref RoverData type definition, which holds initial state and commans sequence for
     * @ref MarsRover
     */
    struct RoverData
    {
        MarsRoverState initial_state;     /*!< initial state for Mars Rover */
        CommandSequence command_sequence; /*!< commands for Mars Rover */
    };

    const Coordinates upper_right_corner_of_plateau;
    const std::vector< RoverData > rovers_data;
};

/**
 * @brief @ref CommandCenterOutput type definition, which holds states of all rovers
 */
using CommandCenterOutput = std::vector< MarsRoverState >;

/** @}*/

}  // namespace mars_rover
