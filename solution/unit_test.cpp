#include "CommandCenter.h"
#include "gtest/gtest.h"

using namespace mars_rover;

namespace mars_rover
{
bool
operator==( const MarsRoverState& lh, const MarsRoverState& rh )
{
    return lh.position.x == rh.position.x && lh.position.y == rh.position.y
           && lh.direction == rh.direction;
}
}  // namespace mars_rover

class CommandCenterTest : public ::testing::Test
{
protected:
    static const auto L = eCommand::TurnLeft;
    static const auto R = eCommand::TurnRight;
    static const auto M = eCommand::MoveForward;

    // CommandCenter command_center;
};

TEST_F( CommandCenterTest, basic_provided_input )
{
    CommandCenter command_center;
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
