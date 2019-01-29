#include "MarsRover.h"
#include "MarsPlateau.h"

#include <cstdint>

namespace mars_rover
{
namespace
{
struct PositionIncrements
{
    int x_inc;
    int y_inc;
};

const PositionIncrements position_increments[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

inline eDirection
turn( eDirection direction, int clockwise_inc )
{
    using DirectionVal = uint8_t;

    const auto modified_direction = 0x3 & static_cast< DirectionVal >( direction ) + clockwise_inc;

    return static_cast< eDirection >( modified_direction );
}

inline eDirection
turn_right( eDirection direction )
{
    return turn( direction, 1 );
}

inline eDirection
turn_left( eDirection direction )
{
    return turn( direction, -1 );
}

}  // namespace

void
MarsRover::do_action( eCommand cmd )
{
    switch ( cmd )
    {
    case eCommand::TurnRight:
        m_state.direction = turn_right( m_state.direction );
        break;
    case eCommand::TurnLeft:
        m_state.direction = turn_left( m_state.direction );
        break;
    case eCommand::MoveForward:
        move_forward( );
        break;
    }
}

void
MarsRover::move_forward( )
{
    const auto& direction_increments
        = position_increments[ static_cast< size_t >( m_state.direction ) ];
    auto new_position = Coordinates{m_state.position.x + direction_increments.x_inc,
                                    m_state.position.y + direction_increments.y_inc};
    if ( m_plateau.is_possible_move( new_position ) )
    {
        m_state.position = std::move( new_position );
    }
}

}  // namespace mars_rover
