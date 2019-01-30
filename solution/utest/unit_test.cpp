/*
 * Copyright (c) 2019 PE Lubenets. All rights reserved.
 * Licensed under the MIT License.
 */

#include <CommandCenter.h>
#include <MarsPlateauImpl.h>
#include <MarsRover.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>

using namespace mars_rover;

namespace mars_rover
{
bool
operator==( const Coordinates& lh, const Coordinates& rh )
{
    return lh.x == rh.x && lh.y == rh.y;
}

bool
operator==( const MarsRoverState& lh, const MarsRoverState& rh )
{
    return lh.position == rh.position && lh.direction == rh.direction;
}

std::ostream&
operator<<( std::ostream& os, const Coordinates& coords )
{
    os << "(" << coords.x << "," << coords.y << ")";
    return os;
}

std::ostream&
operator<<( std::ostream& os, const MarsRoverState& state )
{
    static const auto directions = "NESW";
    os << directions[ static_cast< int >( state.direction ) ] << state.position;
    return os;
}
}  // namespace mars_rover

class BaseTest : public ::testing::Test
{
protected:
    static const auto L = eCommand::TurnLeft;
    static const auto R = eCommand::TurnRight;
    static const auto M = eCommand::MoveForward;
};

class MarsPlateauTest : public BaseTest
{
protected:
    class MockMarsPlateau : public MarsPlateau
    {
    public:
        MOCK_CONST_METHOD1( is_possible_move, bool( const Coordinates& ) );
        MOCK_CONST_METHOD1( is_ok, bool( const bool& ) );
    };

    void
    SetUp( ) final
    {
        plateau = std::unique_ptr< MarsPlateau >( new MarsPlateauImpl( {10, 10} ) );
    }

    std::unique_ptr< MarsPlateau > plateau;
};

class MarsRoverTest : public MarsPlateauTest
{
};

class CommandCenterTest : public BaseTest
{
protected:
    CommandCenter command_center;
};

TEST_F( MarsPlateauTest, test_possible_move )
{
    SCOPED_TRACE( "Tests plateau' possible moves calculation" );

    EXPECT_TRUE( plateau->is_possible_move( {5, 5} ) );
    EXPECT_TRUE( plateau->is_possible_move( {0, 0} ) );
    EXPECT_TRUE( plateau->is_possible_move( {10, 10} ) );
    EXPECT_FALSE( plateau->is_possible_move( {-1, 0} ) );
    EXPECT_FALSE( plateau->is_possible_move( {0, -1} ) );
    EXPECT_FALSE( plateau->is_possible_move( {11, 0} ) );
    EXPECT_FALSE( plateau->is_possible_move( {0, 11} ) );
}

TEST_F( MarsRoverTest, turn_360_degrees )
{
    SCOPED_TRACE( "Tests MarsRover' turns for 360 degrees" );

    MarsRoverState expected_state{eDirection::North, Coordinates{1, 2}};
    MarsRover rover( *plateau, expected_state );

    // Turn left four times
    for ( const auto cmd : CommandCenterInput::CommandSequence{L, L, L, L} )
    {
        rover.do_action( cmd );
    }
    EXPECT_EQ( expected_state, rover.get_state( ) );

    // Turn right four times
    for ( const auto cmd : CommandCenterInput::CommandSequence{R, R, R, R} )
    {
        rover.do_action( cmd );
    }

    EXPECT_EQ( expected_state, rover.get_state( ) );
}

TEST_F( MarsRoverTest, move_to_invalid_position )
{
    SCOPED_TRACE( "Tests moving MarsRover to invalid position" );

    MarsRoverState expected_state{eDirection::East, Coordinates{10, 10}};
    MarsRover rover( *plateau, {eDirection::North, Coordinates{9, 9}} );

    for ( const auto cmd : CommandCenterInput::CommandSequence{M, M, M, R, M, M, M} )
    {
        rover.do_action( cmd );
    }
    EXPECT_EQ( expected_state, rover.get_state( ) );
}

TEST_F( MarsRoverTest, test_position_check_invocation )
{
    SCOPED_TRACE( "Ensuring Plateau' possible position calculation was invoked" );

    using ::testing::Return;

    MockMarsPlateau mock_plateau;

    EXPECT_CALL( mock_plateau, is_possible_move( Coordinates{7, 8} ) )
        .Times( 1 )
        .WillRepeatedly( Return( true ) );

    MarsRover rover( mock_plateau, {eDirection::North, Coordinates{7, 7}} );

    rover.do_action( M );
}

TEST_F( CommandCenterTest, basic_provided_input )
{
    SCOPED_TRACE( "Test overall solution with supplied data" );

    Coordinates upper_left{5, 5};
    MarsRoverState rover1_state{eDirection::North, Coordinates{1, 2}};
    CommandCenterInput::CommandSequence rover1_sequence{L, M, L, M, L, M, L, M, M};
    MarsRoverState rover2_state{eDirection::East, Coordinates{3, 3}};
    CommandCenterInput::CommandSequence rover2_sequence{M, M, R, M, M, R, M, R, R, M};

    const CommandCenterInput input_data{
        upper_left,
        {CommandCenterInput::RoverData{std::move( rover1_state ), std::move( rover1_sequence )},
         CommandCenterInput::RoverData{std::move( rover2_state ), std::move( rover2_sequence )}}};

    const CommandCenterOutput expected_output{MarsRoverState{eDirection::North, Coordinates{1, 3}},
                                              MarsRoverState{eDirection::East, Coordinates{5, 1}}};

    const auto output_data = command_center.process( input_data );

    EXPECT_TRUE( expected_output == output_data );
}
