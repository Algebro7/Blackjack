#ifndef BLACKJACK_DECK_H
#define BLACKJACK_DECK_H

#include <algorithm>
#include <vector>

#include "Card.h"

class Deck {
    std::vector<Card> cards;
    void add_card(int name, char suit, int value);
    void add_card(char name, char suit, int value);

public:
    void init();
    void shuffle(std::default_random_engine engine);
    Card draw();
};


#endif //BLACKJACK_DECK_H