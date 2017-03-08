#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <string>


struct Card {
    union {
        int int_name;
        char char_name;
    } name;
    char suit;
    int value;
    bool is_facecard;
};

#endif //BLACKJACK_CARD_H