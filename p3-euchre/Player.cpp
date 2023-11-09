// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include <algorithm>
#include <cassert>
class Simple : public Player {
private:
	std::string player_name;
	std::vector<Card> hand{};

public:
	Simple(std::string simple_player) : player_name(simple_player) {
	}
	virtual const std::string& get_name() const {
		return player_name;
	}

	virtual void add_card(const Card& c) {
		hand.push_back(c);
		std::sort(hand.begin(), hand.end());
	}


	//REQUIRES round is 1 or 2
	//MODIFIES order_up_suit
	//EFFECTS If Player wishes to order up a trump suit then return true and
	//  change order_up_suit to desired suit.  If Player wishes to pass, then do
	//  not modify order_up_suit and return false.
	virtual bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const {
		int trump_count = 0;
		if (round == 1) {
			for (int i = 0; i < hand.size(); i++) {
				if (hand[i].is_face_or_ace() && hand[i].is_trump(upcard.get_suit())) {
					trump_count++;
				}
			}
			if (trump_count > 1) {
				order_up_suit = upcard.get_suit();
				return true;
			}
		}
		else if (round == 2) {
			for (int i = 0; i < hand.size(); i++) {
				if (hand[i].is_face_or_ace() && hand[i].is_trump(Suit_next(upcard.get_suit()))) {
					trump_count++;
				}
			}
			if (trump_count > 0) {
				order_up_suit = Suit_next(upcard.get_suit());
				return true;
			}
			if (is_dealer) {
				order_up_suit = Suit_next(upcard.get_suit());
				return true;
			}
		}
		return false;
	}

	//REQUIRES Player has at least one card
	//EFFECTS  Player adds one card to hand and removes one card from hand.
	virtual void add_and_discard(const Card& upcard) {
		add_card(upcard);
		std::string current_trump = upcard.get_suit();
		int low_card = 0;
		for (int i = 0; i < hand.size(); i++) {
			if (Card_less(hand[i], hand[low_card], current_trump)) {
				low_card = i;
			}
		}
		hand.erase(hand.begin() + low_card);
		std::sort(hand.begin(), hand.end());
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Leads one Card from Player's hand according to their strategy
	//  "Lead" means to play the first Card in a trick.  The card
	//  is removed the player's hand.

	/* When a Simple Player leads a trick, they play the highest
	non-trump card in their hand. If they have only trump cards,
	they play the highest trump card in their hand. */

	virtual Card lead_card(const std::string& trump) {

		// When a Simple Player leads a trick, they play the 
		// // highest non-trump card in their hand. 
		// If they have only trump cards, they play the highest 
		// trump card in their hand.
		std::sort(hand.begin(), hand.end());
		int return_id = 0;
		bool only_trump = true;

		for (int i = 0; i < hand.size(); i++) {
			if (!hand[i].is_trump(trump)) {
				only_trump = false;
				return_id = i;
			}
		}

		for (int i = 0; i < hand.size(); i++) {
			if (only_trump == true) {
				if (Card_less(hand[return_id], hand[i], trump)) {
					return_id = i;
				}
			}
			else {
				if (!hand[i].is_trump(trump)
					&& Card_less(hand[return_id], hand[i], trump)) {
					return_id = i;
				}
			}
		}

		Card return_card = hand[return_id];
		hand.erase(hand.begin() + return_id);
		return return_card;
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Plays one Card from Player's hand according to their strategy.
	//  The card is removed from the player's hand.
	virtual Card play_card(const Card& led_card, const std::string& trump) {
		std::sort(hand.begin(), hand.end());

		// When playing a card, Simple Players use a simple strategy 
		// that considers only the suit that was led
		int selected = 0;
		bool can_follow_suit = false;

		for (int i = 0; i < hand.size(); i++) {
			if ((hand[i].is_trump(trump) && led_card.is_trump(trump)) ||
				((hand[i].get_suit() == led_card.get_suit())
					&& !hand[i].is_trump(trump) && !led_card.is_trump(trump))) {
				can_follow_suit = true;
				selected = i;
			}
		}

		std::sort(hand.begin(), hand.end());
		// If a Simple Player can follow suit, they play the highest 
		// card that follows suit.
		if (can_follow_suit == true) {
			for (int j = 0; j < hand.size(); j++) {
				if (((hand[j].is_trump(trump) && led_card.is_trump(trump)) ||
					((hand[j].get_suit() == led_card.get_suit()) &&
						!hand[j].is_trump(trump) && !led_card.is_trump(trump)))
					&& (Card_less(hand[selected], hand[j], trump))) {
						selected = j;
				}
			}
		}
		std::sort(hand.begin(), hand.end());
		//  Otherwise, they play the lowest card in their hand.
		if (can_follow_suit == false) {
			for (int k = 0; k < hand.size(); k++) {
				if (Card_less(hand[k], hand[selected], trump)) {
					selected = k;
				}
			}
		}
		std::sort(hand.begin(), hand.end());
		Card return_card = hand[selected];
		hand.erase(hand.begin() + selected);
		return return_card;
	}
};

class Human : public Player {
private:
	std::string player_name;
	std::vector<Card> hand{};

	void print_hand() const {
		for (int i = 0; i < hand.size(); ++i) {
			std::cout << "Human player " << player_name << "'s hand: "
				<< "[" << i << "] " << hand[i] << "\n";
		}
	}

public:
	Human(std::string human_player) : player_name(human_player) {
	}

	//EFFECTS returns player's name
	virtual const std::string& get_name() const {
		return player_name;
	};

	//REQUIRES player has less than MAX_HAND_SIZE cards
	//EFFECTS  adds Card c to Player's hand
	virtual void add_card(const Card& c) {
		hand.push_back(c);
		std::sort(hand.begin(), hand.end());
	}


	//REQUIRES round is 1 or 2
	//MODIFIES order_up_suit
	//EFFECTS If Player wishes to order up a trump suit then return true and
	//  change order_up_suit to desired suit.  If Player wishes to pass, then do
	//  not modify order_up_suit and return false.
	virtual bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const {
		std::string choice;

		//std::sort(hand.begin(), hand.end());
		print_hand();

		std::cout << "Human player " << player_name
			<< ", please enter a suit, or \"pass\":\n";
		std::cin >> choice;
		if (choice == "pass") {
			//std::cout << player_name << " passes \n";
			return false;
		}
		else if (choice == "Diamonds" || choice == "Hearts"
			|| choice == "Clubs" || choice == "Spades") {
			order_up_suit = choice;
			//std::cout << player_name << " orders up " << choice << "\n";
			return true;
		}
		return false;
	}

	//REQUIRES Player has at least one card
	//EFFECTS  Player adds one card to hand and removes one card from hand.
	virtual void add_and_discard(const Card& upcard) {
		std::sort(hand.begin(), hand.end());
		bool to_add_upcard = false;
		print_hand();
		std::cout << "Discard upcard: [-1]\n";
		std::cout << "Human player " << player_name << ", please select a card to discard:\n";
		int discard_id = 0;
		std::cin >> discard_id;
		if (discard_id >= 0 && discard_id < 5) {
			hand.erase(hand.begin() + discard_id);
			std::sort(hand.begin(), hand.end());
			to_add_upcard = true;
			std::sort(hand.begin(), hand.end());
		}
		if (to_add_upcard == true) {
			add_card(upcard);
			std::sort(hand.begin(), hand.end());
		}
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Leads one Card from Player's hand according to their strategy
	//  "Lead" means to play the first Card in a trick.  The card
	//  is removed the player's hand.

	virtual Card lead_card(const std::string& trump) {
		std::sort(hand.begin(), hand.end());
		print_hand();
		std::cout << "Human player " << player_name << ", please select a card:\n";
		int choice;
		std::cin >> choice;
		Card return_card = hand[choice];
		hand.erase((hand.begin() + choice));
		return return_card;
	}


	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Plays one Card from Player's hand according to their strategy.
	//  The card is removed from the player's hand.
	virtual Card play_card(const Card& led_card, const std::string& trump) {
		std::sort(hand.begin(), hand.end());
		print_hand();
		std::cout << "Human player " << player_name << ", please select a card:\n";
		int choice;
		std::cin >> choice;
		Card return_card = hand[choice];
		hand.erase((hand.begin() + choice));
		return return_card;
	}
};
Player* Player_factory(const std::string& name, const std::string& strategy) {
	if (strategy == "Simple") {
		return new Simple(name);
	}
	if (strategy == "Human") {
		return new Human(name);
	}
	assert(false);
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.get_name();
	return os;
}