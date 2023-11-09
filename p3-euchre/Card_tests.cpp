// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_get_rank) {
    ASSERT_EQUAL(Card::RANK_NINE, nine_clubs.get_rank());
}

TEST(test_get_suit) {
    string trump = Card::SUIT_DIAMONDS;

    ASSERT_EQUAL(Card::SUIT_DIAMONDS, nine_diamonds.get_suit());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, ace_diamonds.get_suit());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, jack_diamonds.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, nine_hearts.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, ace_hearts.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, jack_hearts.get_suit());
    ASSERT_EQUAL(Card::SUIT_SPADES, jack_spades.get_suit());
    ASSERT_EQUAL(Card::SUIT_CLUBS, jack_clubs.get_suit());
}

TEST(test_get_trump_suit) {
    string trump_suit = Card::SUIT_DIAMONDS;

    ASSERT_EQUAL(Card::SUIT_DIAMONDS, nine_diamonds.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, ace_diamonds.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, jack_diamonds.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_HEARTS, nine_hearts.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_HEARTS, ace_hearts.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, jack_hearts.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_SPADES, jack_spades.get_suit(trump_suit));
    ASSERT_EQUAL(Card::SUIT_CLUBS, jack_clubs.get_suit(trump_suit));
}

TEST(test_face_or_ace) {
    ASSERT_FALSE(nine_spades.is_face_or_ace());
    ASSERT_FALSE(ten_spades.is_face_or_ace());
    ASSERT_TRUE(jack_spades.is_face_or_ace());
    ASSERT_TRUE(queen_spades.is_face_or_ace());
    ASSERT_TRUE(king_spades.is_face_or_ace());
    ASSERT_TRUE(ace_spades.is_face_or_ace());
}

TEST(test_is_right_bower) {
    string trump_suit = Card::SUIT_SPADES;

    ASSERT_FALSE(nine_spades.is_right_bower(trump_suit));
    ASSERT_FALSE(ten_spades.is_right_bower(trump_suit));
    ASSERT_TRUE(jack_spades.is_right_bower(trump_suit));
    ASSERT_FALSE(queen_spades.is_right_bower(trump_suit));
    ASSERT_FALSE(king_spades.is_right_bower(trump_suit));
    ASSERT_FALSE(ace_spades.is_right_bower(trump_suit));

    ASSERT_FALSE(nine_clubs.is_right_bower(trump_suit));
    ASSERT_FALSE(ten_clubs.is_right_bower(trump_suit));
    ASSERT_FALSE(jack_clubs.is_right_bower(trump_suit));
    ASSERT_FALSE(queen_clubs.is_right_bower(trump_suit));
    ASSERT_FALSE(king_clubs.is_right_bower(trump_suit));
    ASSERT_FALSE(ace_clubs.is_right_bower(trump_suit));

    ASSERT_FALSE(nine_diamonds.is_right_bower(trump_suit));
    ASSERT_FALSE(ten_diamonds.is_right_bower(trump_suit));
    ASSERT_FALSE(jack_diamonds.is_right_bower(trump_suit));
    ASSERT_FALSE(queen_diamonds.is_right_bower(trump_suit));
    ASSERT_FALSE(king_diamonds.is_right_bower(trump_suit));
    ASSERT_FALSE(ace_diamonds.is_right_bower(trump_suit));

    ASSERT_FALSE(nine_hearts.is_right_bower(trump_suit));
    ASSERT_FALSE(ten_hearts.is_right_bower(trump_suit));
    ASSERT_FALSE(jack_hearts.is_right_bower(trump_suit));
    ASSERT_FALSE(queen_hearts.is_right_bower(trump_suit));
    ASSERT_FALSE(king_hearts.is_right_bower(trump_suit));
    ASSERT_FALSE(ace_hearts.is_right_bower(trump_suit));
}

TEST(test_is_left_bower) {
    string trump_suit = Card::SUIT_CLUBS;

    ASSERT_FALSE(nine_spades.is_left_bower(trump_suit));
    ASSERT_FALSE(ten_spades.is_left_bower(trump_suit));
    ASSERT_TRUE(jack_spades.is_left_bower(trump_suit));
    ASSERT_FALSE(queen_spades.is_left_bower(trump_suit));
    ASSERT_FALSE(king_spades.is_left_bower(trump_suit));
    ASSERT_FALSE(ace_spades.is_left_bower(trump_suit));

    ASSERT_FALSE(nine_clubs.is_left_bower(trump_suit));
    ASSERT_FALSE(ten_clubs.is_left_bower(trump_suit));
    ASSERT_FALSE(jack_clubs.is_left_bower(trump_suit));
    ASSERT_FALSE(queen_clubs.is_left_bower(trump_suit));
    ASSERT_FALSE(king_clubs.is_left_bower(trump_suit));
    ASSERT_FALSE(ace_clubs.is_left_bower(trump_suit));

    ASSERT_FALSE(nine_diamonds.is_left_bower(trump_suit));
    ASSERT_FALSE(ten_diamonds.is_left_bower(trump_suit));
    ASSERT_FALSE(jack_diamonds.is_left_bower(trump_suit));
    ASSERT_FALSE(queen_diamonds.is_left_bower(trump_suit));
    ASSERT_FALSE(king_diamonds.is_left_bower(trump_suit));
    ASSERT_FALSE(ace_diamonds.is_left_bower(trump_suit));

    ASSERT_FALSE(nine_hearts.is_left_bower(trump_suit));
    ASSERT_FALSE(ten_hearts.is_left_bower(trump_suit));
    ASSERT_FALSE(jack_hearts.is_left_bower(trump_suit));
    ASSERT_FALSE(queen_hearts.is_left_bower(trump_suit));
    ASSERT_FALSE(king_hearts.is_left_bower(trump_suit));
    ASSERT_FALSE(ace_hearts.is_left_bower(trump_suit));
}

TEST(test_is_trump_and_Card_less) {
    string trump_suit = Card::SUIT_CLUBS;

    ASSERT_FALSE(nine_spades.is_trump(trump_suit));
    ASSERT_FALSE(ten_spades.is_trump(trump_suit));
    ASSERT_TRUE(jack_spades.is_trump(trump_suit));
    ASSERT_FALSE(queen_spades.is_trump(trump_suit));
    ASSERT_FALSE(king_spades.is_trump(trump_suit));
    ASSERT_FALSE(ace_spades.is_trump(trump_suit));

    ASSERT_TRUE(nine_clubs.is_trump(trump_suit));
    ASSERT_TRUE(queen_clubs.is_trump(trump_suit));
    ASSERT_TRUE(ace_clubs.is_trump(trump_suit));
    ASSERT_TRUE(jack_clubs.is_trump(trump_suit));

    ASSERT_FALSE(nine_hearts.is_trump(trump_suit));
    ASSERT_FALSE(queen_hearts.is_trump(trump_suit));
    ASSERT_FALSE(ace_hearts.is_trump(trump_suit));
    ASSERT_FALSE(jack_hearts.is_trump(trump_suit));

    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, trump_suit));
    ASSERT_TRUE(Card_less(ace_clubs, jack_spades, trump_suit));
    ASSERT_TRUE(Card_less(ace_spades, ace_clubs, trump_suit));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_clubs, trump_suit));
    ASSERT_TRUE(Card_less(jack_diamonds, nine_clubs, trump_suit));
    ASSERT_TRUE(Card_less(jack_hearts, nine_clubs, trump_suit));
}

TEST(test_Card_less_with_led) {
    string trump_suit = Card::SUIT_CLUBS;

    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, ten_diamonds, trump_suit));

    ASSERT_TRUE(Card_less(ace_clubs, jack_spades, ten_diamonds, trump_suit));

    ASSERT_TRUE(Card_less(ace_spades, nine_diamonds, ten_diamonds, 
        trump_suit));

    ASSERT_TRUE(Card_less(jack_diamonds, jack_spades, ten_diamonds, 
        trump_suit));

    ASSERT_TRUE(Card_less(ace_spades, jack_diamonds, ten_diamonds, 
        trump_suit));

    ASSERT_TRUE(Card_less(jack_diamonds, king_diamonds, ten_diamonds,
        trump_suit));
    ASSERT_TRUE(Card_less(king_diamonds, nine_clubs, ten_diamonds,
        trump_suit));
}

TEST(test_card_other_comparison) {
    Card a(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, a.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit());
    Card b(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_ACE, b.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit());
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit());
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}

TEST(test_card_less) {
    ASSERT_TRUE(Card_less(nine_clubs, king_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_clubs, ace_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_clubs, ace_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(nine_hearts, nine_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(nine_spades, nine_clubs, Card::SUIT_HEARTS));
}

TEST(test_card_exam) {
    Card five_clubs = Card(Card::RANK_FIVE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(five_clubs.get_rank(), Card::RANK_FIVE);
    ASSERT_EQUAL(five_clubs.get_suit(), Card::SUIT_CLUBS);
    ASSERT_FALSE(five_clubs.is_face_or_ace());
    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    ASSERT_TRUE(ace_spades.is_face_or_ace());
}

TEST(test_card_comparisons) {
    ASSERT_FALSE(ten_spades < nine_spades);
    ASSERT_TRUE(ten_spades > nine_spades);
    ASSERT_TRUE(ten_spades < ten_diamonds);
    ASSERT_FALSE(ten_spades > ten_diamonds);
    ASSERT_TRUE(jack_spades <= jack_spades);
    ASSERT_FALSE(nine_spades > ten_spades);
    ASSERT_TRUE(king_diamonds >= jack_diamonds);
    ASSERT_TRUE(king_diamonds >= king_diamonds);
    ASSERT_TRUE(nine_clubs == nine_clubs);
    ASSERT_TRUE(ace_diamonds > ace_clubs);
    ASSERT_TRUE(king_diamonds < ace_diamonds);
    ASSERT_TRUE(king_diamonds > queen_diamonds);
    ASSERT_TRUE(jack_diamonds <= queen_diamonds);
    ASSERT_TRUE(jack_diamonds >= ten_diamonds);
    ASSERT_TRUE(jack_spades >= ten_diamonds);
}

TEST_MAIN()
