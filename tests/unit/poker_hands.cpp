#include <catch2/catch.hpp>

#include <string>

#include <poker_hands.c>

SCENARIO("High Card: Hands which do not fit any higher category are ranked by the value of their highest card. If the highest cards have the same value, the hands are ranked by the next highest, and so on.", "[poker_hands]") {
    std::string output = std::string(128, 'a');
    GIVEN("Two poker hands with high cards") {
        WHEN("the cards are \"Black: 2H 3D 5S 9C KD  White: 2C 3H 4S 8C AH\"") {
            THEN("the output is \"White wins. - with high card: Ace\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D 5S 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 3H 4S 8C AH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "White wins. - with high card: Ace");
            }
        }

        WHEN("the cards are \"Black: 2H 3D 5S 9C KD  White: 2C 3H 4S 8C KH\"") {
            THEN("the output is \"Black wins. - with high card: 9\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D 5S 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 3H 4S 8C KH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "Black wins. - with high card: 9");
            }
        }
    }
}

SCENARIO("Pair: 2 of the 5 cards in the hand have the same value. Hands which both contain a pair are ranked by the value of the cards forming the pair. If these values are the same, the hands are ranked by the values of the cards not forming the pair, in decreasing order.", "[poker_hands]") {
    std::string output = std::string(128, 'a');
    GIVEN("Two poker hands with a pair") {
        WHEN("the cards are \"Black: 2H 3D KS 9C KD  White: 2C 3H AC 8C AH\"") {
            THEN("the output is \"White wins. - with pair: Ace\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D KS 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 3H AC 8C AH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "White wins. - with pair: Ace");
            }
        }

        WHEN("the cards are \"Black: 2H 3D KS 9C KD  White: 2C 3H KC 8C KH\"") {
            THEN("the output is \"Black wins. - with high card: 9\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D KS 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 3H KC 8C KH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "Black wins. - with high card: 9");
            }
        }

        WHEN("the cards are \"Black: 2H 3D KS 9C KD  White: 2C 3H 4C 8C AH\"") {
            THEN("the output is \"Black wins. - with high card: 9\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D KS 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 3H 4C 8C AH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "Black wins. - with pair: King");
            }
        }
    }
}

SCENARIO("Two Pairs: The hand contains 2 different pairs. Hands which both contain 2 pairs are ranked by the value of their highest pair. Hands with the same highest pair are ranked by the value of their other pair. If these values are the same the hands are ranked by the value of the remaining card.", "[poker_hands]") {
    std::string output = std::string(128, 'a');
    GIVEN("Two poker hands with two pair") {
        WHEN("the cards are \"Black: 2H 9D KS 9C KD  White: 2C KH AC KC AH\"") {
            THEN("the output is \"White wins. - with two pairs: Ace over King\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 9D KS 9C KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C KH AC KC AH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "White wins. - with two pairs: Ace over King");
            }
        }

        WHEN("the cards are \"Black: 2H 3D KS AC KD  White: 2C 8H KC 8C KH\"") {
            THEN("the output is \"White wins. - with two pairs: King over 8\"") {
                struct Player *black = Player_Init(PLAYER_1, "Black", "2H 3D KS AC KD");
                struct Player *white = Player_Init(PLAYER_2, "White", "2C 8H KC 8C KH");
                size_t written = Player_PrettyCompare(black, white, &output[0], output.size());
                output.resize(written);
                REQUIRE(output == "White wins. - with two pairs: King over 8");
            }
        }
    }
}

