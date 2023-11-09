// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
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


TEST(test_simple_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;

    Player* joe_rogan = Player_factory("Joe Rogan", "Simple");
    ASSERT_EQUAL("Joe Rogan", joe_rogan->get_name());
    delete joe_rogan;
}

TEST(test_simple_add_and_discard_1) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_diamonds);
    bob->add_card(ten_diamonds);
    bob->add_card(ace_diamonds);
    bob->add_card(nine_hearts);
    Card led_card = bob->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(led_card, nine_hearts);
    bob->add_and_discard(jack_diamonds);
    Card led_card_2 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_2, ace_diamonds);
    Card led_card_3 = bob->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(led_card_3, jack_diamonds);
    delete bob;
}

TEST(test_simple_add_and_discard_2) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_diamonds);
    bob->add_card(ten_diamonds);
    bob->add_card(ten_clubs);
    bob->add_card(nine_hearts);
    bob->add_and_discard(ace_spades);
    Card led_card = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card, ace_spades);
    Card led_card_2 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_2, ten_diamonds);
    delete bob;
}

TEST(test_simple_add_and_discard_3) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_clubs);
    bob->add_card(king_clubs);
    bob->add_card(jack_spades);
    bob->add_card(ten_hearts);
    bob->add_and_discard(ace_clubs);
    Card led_card = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card, jack_spades);
    Card led_card_2 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_2, ace_clubs);
    delete bob;
}

TEST(test_simple_add_and_discard_3_2) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_clubs);
    bob->add_card(king_hearts);
    bob->add_card(jack_spades);
    bob->add_card(ten_hearts);
    bob->add_and_discard(ace_clubs);
    Card led_card = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card, king_hearts);
    Card led_card_2 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_2, ace_clubs);
    delete bob;
}

TEST(test_simple_add_and_discard_4) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_diamonds);
    bob->add_card(ten_diamonds);
    bob->add_card(ace_diamonds);
    bob->add_card(jack_diamonds);
    bob->add_and_discard(king_diamonds);
    Card led_card = bob->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(led_card, jack_diamonds);
    delete bob;
}

/*
* 
TEST(test_simple_add_and_discard_5) {
DONT ADD PAST THE MAX!! IDIOT!!!!!!!!
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(king_hearts);
    bob->add_card(nine_diamonds);
    bob->add_card(jack_diamonds);
    bob->add_card(ten_diamonds);
    bob->add_card(queen_spades);
    bob->add_card(ten_hearts);
    Card led_card = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card, queen_spades);
    bob->add_and_discard(queen_diamonds);
    Card led_card_2 = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card_2, king_hearts);
    delete bob;
}
*/

TEST(test_simple_add_and_discard_queens) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(king_hearts); // same suit
    bob->add_card(jack_diamonds); // left bower
    bob->add_card(ten_diamonds); // too low
    bob->add_card(queen_diamonds); // highest non-trump
    bob->add_card(ten_hearts); // same suit
    Card led_card = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card, queen_diamonds);
    delete bob;
}

TEST(test_simple_add_and_discard_queens_isnt_jack) {
    // Bob's hand
    Player* ken = Player_factory("bob", "Simple");
    ken->add_card(king_hearts); // same suit
    ken->add_card(jack_diamonds); // left bower
    ken->add_card(ten_diamonds); // too low
    ken->add_card(queen_diamonds); // highest non-trump
    ken->add_card(ten_hearts); // same suit
    Card led_card = ken->lead_card(Card::SUIT_HEARTS);
    ASSERT_FALSE(led_card == jack_diamonds);
    delete ken;
}

TEST(test_simple_add_and_discard_queens_original) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(king_hearts); // same suit
    bob->add_card(jack_diamonds); // left bower
    bob->add_card(ten_diamonds); // too low
    bob->add_card(queen_diamonds); // highest non-trump
    bob->add_card(ten_hearts); // same suit
    Card led_card = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card, queen_diamonds);
    bob->add_and_discard(queen_diamonds);
    Card led_card_2 = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(led_card_2, king_hearts);
    delete bob;
}

TEST(test_simple_add_and_discard_6) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(ace_hearts);
    bob->add_card(ace_diamonds);
    bob->add_card(ace_spades);
    bob->add_card(king_hearts);
    bob->add_card(ace_clubs);
    bob->add_and_discard(king_spades);
    Card led_card = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card, ace_diamonds);
    delete bob;
}

TEST(test_simple_make_trump_1) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(queen_spades);
    bob->add_card(nine_hearts);
    bob->add_card(jack_hearts);
    bob->add_card(queen_clubs);
    bob->add_card(jack_clubs);

    // Has left bower of next suit
    string trump_1;
    ASSERT_TRUE(bob->make_trump(ten_hearts, true, 2, trump_1));
    ASSERT_TRUE(bob->make_trump(ten_hearts, false, 2, trump_1));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, trump_1);
    //
    string trump_2;
    ASSERT_TRUE(bob->make_trump(ten_clubs, true, 2, trump_2));
    ASSERT_TRUE(bob->make_trump(ten_clubs, false, 2, trump_2));
    ASSERT_EQUAL(Card::SUIT_SPADES, trump_2);
    //
    string trump_3;
    ASSERT_TRUE(bob->make_trump(ten_diamonds, true, 2, trump_3));
    ASSERT_TRUE(bob->make_trump(ten_diamonds, false, 2, trump_3));
    ASSERT_EQUAL(Card::SUIT_HEARTS, trump_3);
    //
    string trump_4;
    ASSERT_TRUE(bob->make_trump(ten_spades, true, 2, trump_4));
    ASSERT_TRUE(bob->make_trump(ten_spades, false, 2, trump_4));
    ASSERT_EQUAL(Card::SUIT_CLUBS, trump_4);

    delete bob;
}

TEST(test_simple_make_trump_2) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(ace_diamonds);
    bob->add_card(nine_hearts);
    bob->add_card(jack_spades);
    bob->add_card(nine_clubs);
    bob->add_card(ace_clubs);

    string trump_1;
    ASSERT_FALSE(bob->make_trump(ace_hearts, true, 1, trump_1));
    ASSERT_FALSE(bob->make_trump(ace_hearts, false, 1, trump_1));
    ASSERT_EQUAL("", trump_1);
    string trump_2;
    ASSERT_TRUE(bob->make_trump(ace_clubs, true, 1, trump_2));
    ASSERT_TRUE(bob->make_trump(ace_clubs, false, 1, trump_2));
    ASSERT_EQUAL(Card::SUIT_CLUBS, trump_2);
    string trump_3;
    ASSERT_FALSE(bob->make_trump(queen_diamonds, true, 1, trump_3));
    ASSERT_FALSE(bob->make_trump(queen_diamonds, false, 1, trump_3));
    ASSERT_EQUAL("", trump_3);
    string trump_4;
    ASSERT_FALSE(bob->make_trump(jack_spades, true, 1, trump_4));
    ASSERT_FALSE(bob->make_trump(jack_spades, false, 1, trump_4));
    ASSERT_EQUAL("", trump_4);

    delete bob;
}

TEST(test_simple_make_trump_3) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(ten_clubs);
    bob->add_card(nine_diamonds);
    bob->add_card(ten_spades);
    bob->add_card(ace_spades);
    bob->add_card(jack_diamonds);

    string trump_1;
    ASSERT_FALSE(bob->make_trump(ace_hearts, true, 1, trump_1));
    ASSERT_FALSE(bob->make_trump(ace_hearts, false, 1, trump_1));
    ASSERT_EQUAL("", trump_1);
    string trump_1_2;
    ASSERT_TRUE(bob->make_trump(ace_hearts, true, 2, trump_1_2));
    ASSERT_TRUE(bob->make_trump(ace_hearts, false, 2, trump_1_2));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, trump_1_2);

    string trump_2;
    ASSERT_FALSE(bob->make_trump(ace_diamonds, true, 1, trump_2));
    ASSERT_FALSE(bob->make_trump(ace_diamonds, false, 1, trump_2));
    ASSERT_EQUAL("", trump_2);
    string trump_2_2;
    ASSERT_TRUE(bob->make_trump(ace_diamonds, true, 2, trump_2_2));
    ASSERT_TRUE(bob->make_trump(ace_diamonds, false, 2, trump_2_2));
    ASSERT_EQUAL(Card::SUIT_HEARTS, trump_2_2);

    string trump_3;
    ASSERT_FALSE(bob->make_trump(ace_clubs, true, 1, trump_3));
    ASSERT_FALSE(bob->make_trump(ace_clubs, false, 1, trump_3));
    ASSERT_EQUAL("", trump_3);
    string trump_3_2;
    ASSERT_TRUE(bob->make_trump(ace_clubs, true, 2, trump_3_2));
    ASSERT_TRUE(bob->make_trump(ace_clubs, false, 2, trump_3_2));
    ASSERT_EQUAL(Card::SUIT_SPADES, trump_3_2);

    string trump_4;
    ASSERT_FALSE(bob->make_trump(ace_spades, true, 1, trump_4));
    ASSERT_FALSE(bob->make_trump(ace_spades, false, 1, trump_4));
    ASSERT_EQUAL("", trump_4);
    string trump_4_2;
    ASSERT_TRUE(bob->make_trump(ace_spades, true, 2, trump_4_2));
    ASSERT_EQUAL(Card::SUIT_CLUBS, trump_4_2);
    string trump_4_3;
    ASSERT_FALSE(bob->make_trump(ace_spades, false, 2, trump_4_3));
    ASSERT_EQUAL("", trump_4_3);

    delete bob;
}

TEST(test_simple_make_trump_4) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(queen_diamonds);
    bob->add_card(nine_diamonds);
    bob->add_card(king_diamonds);
    bob->add_card(nine_hearts);
    bob->add_card(ten_hearts);

    string trump_1_2;
    ASSERT_TRUE(bob->make_trump(queen_diamonds, true, 2, trump_1_2));
    ASSERT_EQUAL(Card::SUIT_HEARTS, trump_1_2);
    string trump_1_3;
    ASSERT_FALSE(bob->make_trump(queen_diamonds, false, 2, trump_1_3));
    ASSERT_EQUAL("", trump_1_3);

    delete bob;
}


TEST(test_simple_add_and_discard_7) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(nine_diamonds);
    bob->add_card(ten_diamonds);
    bob->add_card(king_diamonds);
    bob->add_card(ace_diamonds);
    bob->add_card(jack_diamonds);
    bob->add_and_discard(queen_diamonds);
    Card test = bob->lead_card(Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(test, jack_diamonds);
    delete bob;
}

TEST(test_more_simple_leads) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(nine_spades);
    bob->add_card(ten_spades);
    bob->add_card(queen_spades);
    bob->add_card(king_spades);
    // led with ace
    bob->add_card(ace_spades);
    Card led_card = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card, ace_spades);
    // led with king
    Card led_card_2 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_2, king_spades);
    // led with queen
    Card led_card_3 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_3, queen_spades);
    // led with jerk
    bob->add_card(jack_clubs);
    Card led_card_4 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_4, jack_clubs);
    // led with jack
    bob->add_card(jack_spades);
    Card led_card_5 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_5, jack_spades);
    // led with ten
    Card led_card_6 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_6, ten_spades);
    // led with nine
    Card led_card_7 = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(led_card_7, nine_spades);
    delete bob;
}

TEST(test_more_simple_leads_2) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(nine_spades);
    bob->add_card(ten_spades);
    bob->add_card(queen_spades);
    bob->add_card(king_spades);
    // led with jack
    bob->add_card(jack_spades);
    Card led_card = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card, jack_spades);
    // led with jerk
    bob->add_card(jack_clubs);
    Card led_card_2 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_2, jack_clubs);
    // led with ace
    bob->add_card(ace_spades);
    Card led_card_3 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_3, ace_spades);
    // led with king
    Card led_card_4 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_4, king_spades);
    // led with queen
    Card led_card_5 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_5, queen_spades);
    // led with ten
    Card led_card_6 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_6, ten_spades);
    // led with nine
    Card led_card_7 = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(led_card_7, nine_spades);
    delete bob;
}

TEST(test_simple_play_card) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(nine_spades);
    bob->add_card(ten_spades);
    bob->add_card(queen_spades);
    bob->add_card(king_spades);
    bob->add_card(ace_spades);

    // Bob plays a card
    Card played_card = bob->play_card(nine_diamonds, Card::SUIT_HEARTS);

    // Verify the card Bob played
    ASSERT_EQUAL(played_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
    delete bob;

}

TEST(test_simple_play_card_2) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(king_diamonds);
    bob->add_card(nine_diamonds);
    bob->add_card(jack_clubs);
    bob->add_card(nine_hearts);
    bob->add_card(ace_hearts);

    Card played_card = bob->play_card(ten_diamonds, Card::SUIT_HEARTS);
    ASSERT_EQUAL(played_card, king_diamonds);
    Card played_card_2 = bob->play_card(ten_spades, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_2, jack_clubs);
    bob->add_card(nine_diamonds);
    Card played_card_3 = bob->play_card(ten_spades, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_3, nine_hearts);
    bob->add_card(ten_spades);
    Card played_card_4 = bob->play_card(jack_clubs, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_4, ten_spades);

    delete bob;
}

TEST(test_simple_play_card_3) {
    // Bob's hand
    Player* bob = Player_factory("bob", "Simple");
    bob->add_card(ten_hearts); //
    bob->add_card(queen_diamonds); //
    bob->add_card(ace_spades);
    bob->add_card(king_hearts);
    bob->add_card(jack_clubs); 

    Card played_card = bob->play_card(nine_hearts, Card::SUIT_HEARTS);
    ASSERT_EQUAL(played_card, king_hearts);
    Card played_card_2 = bob->play_card(nine_hearts, Card::SUIT_HEARTS);
    ASSERT_EQUAL(played_card_2, ten_hearts);
    Card played_card_2_2 = bob->play_card(nine_hearts, Card::SUIT_HEARTS);
    ASSERT_EQUAL(played_card_2_2, jack_clubs);
    bob->add_card(jack_clubs);
    bob->add_card(jack_spades);
    Card played_card_3 = bob->play_card(nine_diamonds, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_3, queen_diamonds);
    bob->add_card(jack_hearts);
    Card played_card_3_2 = bob->play_card(nine_diamonds, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_3_2, jack_hearts);
    Card played_card_4 = bob->play_card(nine_diamonds, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_4, ace_spades);
    Card played_card_5 = bob->play_card(nine_diamonds, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_5, jack_clubs);
    Card played_card_6 = bob->play_card(nine_diamonds, Card::SUIT_SPADES);
    ASSERT_EQUAL(played_card_6, jack_spades);

    delete bob;
}





TEST_MAIN()
