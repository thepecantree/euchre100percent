// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

class Game {
private:
	vector <Player*> playas;
	Pack deck;
	Card upcard;
	string trump;
	int dealer_id = 0;
	int leader_id = 1;
	int threshold;
	bool team_1_ordered;
	int round = 1;
	int team_1_points = 0;
	int team_1_tricks = 0;
	int team_2_points = 0;
	int team_2_tricks = 0;
	int hand_num = 0;
	bool to_shizzle;


public:
	/*
	void add_playa(Player* new_playa) {
		playas.push_back(new_playa);
		// probably don't sort players
	}
	*/

	int increment_hand_num() {
		hand_num++;
		return hand_num;
	}

	void pack_set(istream& pack_input) {
		deck = Pack(pack_input);
	}

	void deal_three(int playa_role) {
		for (int i = 0; i < 3; i++) {
			playas[playa_role]->add_card(deck.deal_one());
		}
	}
	void deal_two(int playa_role) {
		for (int i = 0; i < 2; i++) {
			playas[playa_role]->add_card(deck.deal_one());
		}
	}

	void deal() {
		// Announcements made.

		std::cout << "Hand " << hand_num << "\n";
		std::cout << playas[dealer_id]->get_name() << " deals\n";

		deck.reset(); // fix yo stuff
		if (to_shizzle == true) {
			deck.shuffle();
		}

		// first iteration
		deal_three((dealer_id + 1) % 4);
		deal_two((dealer_id + 2) % 4);
		deal_three((dealer_id + 3) % 4);
		deal_two(dealer_id);
		// second iteration
		deal_two((dealer_id + 1) % 4);
		deal_three((dealer_id + 2) % 4);
		deal_two((dealer_id + 3) % 4);
		deal_three(dealer_id);


		upcard = deck.deal_one();
		std::cout << upcard << " turned up\n";
	}

	void make_or_pass() {
		round = 1;
		trump = upcard.get_suit();
		//for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 9; ++j) {
			if (j > 4) {
				round = 2;
			}
			if (playas[(dealer_id + j) % 4]->
				make_trump(upcard, j == 4, round, trump)) {
				if ((dealer_id + j) % 4 == 0 || (dealer_id + j) % 4 == 2) {
					team_1_ordered = true;
				}
				else {
					team_1_ordered = false;
				}
				cout << playas[(dealer_id + j) % 4]->get_name()
					<< " orders up " << trump << "\n";
				if (round == 1) {
					// round 1 stuff
					playas[dealer_id]->add_and_discard(upcard);

				}
				else {
					// round 2 stuff
				}
				cout << endl;
				return;
			}
			else {
				cout << playas[(dealer_id + j) % 4]->get_name() << " passes\n";
			}
		}
		//}
	}

	/* trump = upcard.get_suit();
		for (int i = 1; i < 9; i++) {
			if (i < 5) {
				round = 1;
			}
			else {
				round = 2;
			}
			if (playas[(dealer_id + i) % 4]->make_trump(upcard, (i % 4) == 0, round, trump)) {
				if ((dealer_id + i) % 4 == 0 || (dealer_id + i) % 4 == 2) {
					team_1_ordered = true;
				}
				else {
					team_1_ordered = false;
				}
				cout << playas[(dealer_id + i) % 4]->get_name() << " orders up " << trump << "\n";
				if (round == 2) {
					playas[dealer_id]->add_and_discard(upcard);
				}
				return;
			}
			else {
				cout << playas[(dealer_id + i) % 4]->get_name() << " passes\n";
			}
		} */

	Card compete(vector <Card> in_cards) {
		Card top_card = in_cards[0];
		for (int i = 1; i < in_cards.size(); i++) {
			if (Card_less(top_card, in_cards[i], in_cards[0], trump)) {
				top_card = in_cards[i];
			}
		}
		return top_card;
	}

	void trick() {
		vector <Card> played_cards;

		Card card_1 = playas[(leader_id) % 4]->lead_card(trump);
		cout << card_1 << " led by " << playas[(leader_id) % 4]->get_name() << "\n";

		Card card_2 = playas[(leader_id + 1) % 4]->play_card(card_1, trump);
		cout << card_2 << " played by " << playas[(leader_id + 1) % 4]->get_name() << "\n";

		Card card_3 = playas[(leader_id + 2) % 4]->play_card(card_1, trump);
		cout << card_3 << " played by " << playas[(leader_id + 2) % 4]->get_name() << "\n";

		Card card_4 = playas[(leader_id + 3) % 4]->play_card(card_1, trump);
		cout << card_4 << " played by " << playas[(leader_id + 3) % 4]->get_name() << "\n";


		played_cards.push_back(card_1);
		played_cards.push_back(card_2);
		played_cards.push_back(card_3);
		played_cards.push_back(card_4);
		Card top_card = compete(played_cards);

		if (top_card == card_1 || top_card == card_3) {
			if ((leader_id) % 4 == 0 || (leader_id) % 4 == 2) {
				team_1_tricks++;
			}
			else {
				team_2_tricks++;
			}
		}
		if (top_card == card_2 || top_card == card_4) {
			if ((leader_id + 1) % 4 == 0 || (leader_id + 1) % 4 == 2) {
				team_1_tricks++;
			}
			else {
				team_2_tricks++;
			}
		}

		if (top_card == card_1) {
			cout << playas[(leader_id) % 4]->get_name() << " takes the trick\n";
			leader_id = (leader_id) % 4;
		}
		else if (top_card == card_2) {
			cout << playas[(leader_id + 1) % 4]->get_name() << " takes the trick\n";
			leader_id = (leader_id + 1) % 4;
		}
		else if (top_card == card_3) {
			cout << playas[(leader_id + 2) % 4]->get_name() << " takes the trick\n";
			leader_id = (leader_id + 2) % 4;
		}
		else {
			cout << playas[(leader_id + 3) % 4]->get_name() << " takes the trick\n";
			leader_id = (leader_id + 3) % 4;
		}
		cout << endl;
	}

	int higher_score() {
		if (team_1_points > team_2_points) {
			return team_1_points;
		}
		return team_2_points;
	}

	void print_scores() {
		cout << playas[0]->get_name() << " and " << playas[2]->get_name()
			<< " have " << team_1_points << " points\n";
		cout << playas[1]->get_name() << " and " << playas[3]->get_name()
			<< " have " << team_2_points << " points\n";
		cout << endl;
	}

	void announce_winners() {
		if (team_1_points > team_2_points) {
			cout << playas[0]->get_name() << " and "
				<< playas[2]->get_name() << " win!\n";
		}
		else {
			cout << playas[1]->get_name() << " and "
				<< playas[3]->get_name() << " win!\n";
		}
	}

	void bout() {
		team_1_tricks = 0;
		team_2_tricks = 0;
		for (int i = 0; i < 5; i++) {
			trick();
		}
		if (team_1_tricks > team_2_tricks) {
			cout << playas[0]->get_name() << " and " 
				<< playas[2]->get_name() << " win the hand\n";
			if (!team_1_ordered) {
				team_1_points += 2;
				cout << "euchred!\n";
			}
			else {
				team_1_points++;
				if (team_1_tricks == 5) {
					team_1_points++;
					cout << "march!\n";
				}
			}
		}
		if (team_1_tricks < team_2_tricks) {
			cout << playas[1]->get_name() << " and " 
				<< playas[3]->get_name() << " win the hand\n";
			if (team_1_ordered) {
				team_2_points += 2;
				cout << "euchred!\n";
			}
			else {
				team_2_points++;
				if (team_2_tricks == 5) {
					team_2_points++;
					cout << "march!\n";
				}
			}
		}
		print_scores();
		dealer_id = (dealer_id + 1) % 4;
		leader_id = (dealer_id + 1) % 4;
	}


	Game(vector <Player*> players, string shuf_status, int thrshold) {
		dealer_id = 0;
		playas = players;
		threshold = thrshold;
		if (shuf_status == "shuffle") {
			to_shizzle = true;
		}
		else if (shuf_status == "noshuffle") {
			to_shizzle = false;
		}
		else {
		}
	}

	void play() {
		while (higher_score() < threshold) {
			deal();
			make_or_pass();
			bout();
			increment_hand_num();
		}
		announce_winners();
	}

};

int main(int argc, char** argv) {
	// Read command line args and check for errors
	//Game game(/* game details */);
	//game.play();
	int threshold = 0;
	string shuf_status = "";


	int x = 5;
	int* arr[] = { &x, &x, &x };
	int* ptr = &(arr[2]);

	for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	}
	cout << endl;

	if (2 < argc) {
		if (string(argv[2]) == "shuffle") {
			shuf_status = "shuffle";
		}
		else if (string(argv[2]) == "noshuffle") {
			shuf_status = "noshuffle";
		}
	}

	if (3 < argc) {
		threshold = stoi(argv[3]);
	}

	if (argc != 12 || threshold < 1 || threshold > 100 ||
		(shuf_status != "shuffle" && shuf_status != "noshuffle") 
		|| (string(argv[5]) != "Human" && string(argv[5]) != "Simple")
		|| (string(argv[7]) != "Human" && string(argv[7]) != "Simple")
		|| (string(argv[9]) != "Human" && string(argv[9]) != "Simple")
		|| (string(argv[11]) != "Human" && string(argv[11]) != "Simple")) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 18;
	}
	/*
	if ((string(argv[5]) != "Human" && string(argv[5]) != "Simple")
		|| (string(argv[7]) != "Human" && string(argv[7]) != "Simple")
		|| (string(argv[9]) != "Human" && string(argv[9]) != "Simple")
		|| (string(argv[11]) != "Human" && string(argv[11]) != "Simple")) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 18;
	}
	*/

	Player* player_1 = Player_factory(argv[4], argv[5]);
	Player* player_2 = Player_factory(argv[6], argv[7]);
	Player* player_3 = Player_factory(argv[8], argv[9]);
	Player* player_4 = Player_factory(argv[10], argv[11]);

	vector <Player*> input_playas;
	input_playas.push_back(player_1);
	input_playas.push_back(player_2);
	input_playas.push_back(player_3);
	input_playas.push_back(player_4);

	ifstream pack_in;
	string pack_filename(argv[1]);
	pack_in.open(pack_filename);

	if (!pack_in.is_open()) {
		cout << "Error opening " << pack_filename << endl;
		return 18;
	}

	Game poker(input_playas, shuf_status, threshold);
	poker.pack_set(pack_in);

	/*
	while (poker.higher_score() < threshold) {
		poker.deal();
		poker.make_or_pass();
		poker.bout();
		poker.increment_hand_num();
	}
	poker.announce_winners();
	*/
	poker.play();

	/*
	for (size_t i = 0; i < input_playas.size(); ++i) {
		delete input_playas[i];
	}
	*/

	delete player_1;
	delete player_2;
	delete player_3;
	delete player_4;

	return 0;
}