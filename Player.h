#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"

class Player {
    std::vector<Card> hand;
    std::vector<int> aces;

public:
    std::string name;
    int hand_value;
    int money;
    bool playing;
    bool busted;

    Player ();
    void hit(Deck *deck);
    int calc_hand_value();
    void print_hand_value();
    void adjust_aces();
    void stay();
    void lose(int bet);
    void win(int bet);
    void discard_hand();
};


#endif //BLACKJACK_PLAYER_H
