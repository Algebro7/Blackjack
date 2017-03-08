#include "Deck.h"
#include <iostream>

void Deck::init() {
    std::string suits = "CDHS";
    for (char suit : suits) {
        for (int i = 2; i < 11; i++)
            add_card(i, suit, i);

        std::string face_cards = "JQK";
        for (char face_card : face_cards)
            add_card(face_card, suit, 10);

        add_card('A', suit, 11);
    }

}

void Deck::shuffle(std::default_random_engine engine) {
    std::shuffle(std::begin(cards), std::end(cards), engine);
}

// 2-10 Card
void Deck::add_card(int name, char suit, int value) {
    Card card = Card();
    card.name.int_name = name;
    card.suit = suit;
    card.value = value;
    card.is_facecard = false;

    cards.push_back(card);
}

// Face card
void Deck::add_card(char name, char suit, int value) {
    Card card = Card();
    card.name.char_name = name;
    card.suit = suit;
    card.value = value;
    card.is_facecard = true;

    cards.push_back(card);
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back();

    return card;
}