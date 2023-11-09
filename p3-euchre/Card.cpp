// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
// 

 //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit

Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}


Card::Card(const std::string& rank_in, const std::string& suit_in) {
    rank = rank_in;
    suit = suit_in;
}

std::string Card::get_rank() const {
    return rank;
}

std::string Card::get_suit() const {
    return suit;
}

std::string Card::get_suit(const std::string& trump) const {
    if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) {
        return trump;
    }
    return suit;
}

bool Card::is_face_or_ace() const {
    if (get_rank() == RANK_JACK || get_rank() == RANK_QUEEN ||
        get_rank() == RANK_KING || get_rank() == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_right_bower(const std::string& trump) const {
    if (get_rank() == RANK_JACK && get_suit() == trump) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_left_bower(const std::string& trump) const {
    if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_trump(const std::string& trump) const {
    if (get_suit() == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}

// hopefully these helpers i'm adding are legal

int get_rank_weight(const Card card) {
    for (int i = 0; i < NUM_RANKS; i++) {
        if (card.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            return i;
        }
    }
    assert(false);
    return 0;
}

int get_suit_weight(const Card card) {
    for (int i = 0; i < NUM_SUITS; i++) {
        if (card.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            return i;
        }
    }
    assert(false);
    return 0;
}

//


bool operator<(const Card& lhs, const Card& rhs) {
    if (get_rank_weight(lhs) < get_rank_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) < get_suit_weight(rhs)) {
        return true;
    }
    return false;
}

bool operator<=(const Card& lhs, const Card& rhs) {
    if (get_rank_weight(lhs) < get_rank_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) < get_suit_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) == get_suit_weight(rhs)) {
        return true;
    }
    return false;
}

bool operator>(const Card& lhs, const Card& rhs) {
    if (get_rank_weight(lhs) > get_rank_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) > get_suit_weight(rhs)) {
        return true;
    }
    return false;
}

bool operator>=(const Card& lhs, const Card& rhs) {
    if (get_rank_weight(lhs) > get_rank_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) > get_suit_weight(rhs)) {
        return true;
    }
    else if (get_rank_weight(lhs) == get_rank_weight(rhs)
        && get_suit_weight(lhs) == get_suit_weight(rhs)) {
        return true;
    }
    return false;
}

bool operator==(const Card& lhs, const Card& rhs) {
    return (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit());
}

bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs == rhs);
}

//

std::string Suit_next(const std::string& suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    assert(false);
    return suit;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const std::string& trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.get_rank() == Card::RANK_JACK && a.get_suit() == trump) {
            return false;
        }
        if (b.get_rank() == Card::RANK_JACK && b.get_suit() == trump) {
            return true;
        }
        if (a.get_rank() == Card::RANK_JACK && a.get_suit() == Suit_next(trump)) {
            return false;
        }
        if (b.get_rank() == Card::RANK_JACK && b.get_suit() == Suit_next(trump)) {
            return true;
        }
        return (get_rank_weight(a) < get_rank_weight(b));
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else {
        return (a < b);
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const std::string& trump) {

    if (!a.is_trump(trump) && !b.is_trump(trump)) {
        if (a.get_suit() == led_card.get_suit()
            && b.get_suit() != led_card.get_suit()) {
            return false;
        }
        else if (a.get_suit() != led_card.get_suit()
            && b.get_suit() == led_card.get_suit()) {
            return true;
        }
        else if (get_rank_weight(a) > get_rank_weight(b)) {
            return false;
        }
        else if (a.get_rank() == b.get_rank()) {
            if (get_suit_weight(a) < get_suit_weight(b)) {
                return true;
            }
            return false;
        }
        return true;
    }
    else {
        return Card_less(a, b, trump);
    }
}
