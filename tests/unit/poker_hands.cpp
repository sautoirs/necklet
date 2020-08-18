#include <catch2/catch.hpp>

#include <string>

#include <poker_hands.c>

SCENARIO("High Card: Hands which do not fit any higher category are ranked by the value of their highest card. If the highest cards have the same value, the hands are ranked by the next highest, and so on.", "[poker_hands]") {
    std::string output = std::string(128, 'a');
    GIVEN("Two poker hands with high cards") {
        WHEN("the cards are \"Black: 2H 3D 5S 9C KD  White: 2C 3H 4S 8C AH\"") {
            THEN("the output is \"White wins. - with high card: Ace\"") {
                struct PokerHand *black = PokerHand_Init(PLAYER_1, "Black", "2H 3D 5S 9C KD");
                struct PokerHand *white = PokerHand_Init(PLAYER_2, "White", "2C 3H 4S 8C AH");
                size_t written = PokerHand_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "White wins. - with high card: Ace");
            }
        }
    }
}
