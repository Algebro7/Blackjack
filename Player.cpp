#include <iostream>
#include "Player.h"

Player::Player() {
    money = 0;
    playing = true;
    busted = false;
}

void Player::hit(Deck *deck) {
    Card card = deck->draw();

    // Keep track of aces so they can be adjusted later
    if (card.is_facecard && card.name.char_name == 'A')
        aces.push_back(hand.size());
    hand.push_back(card);

    if (card.is_facecard) {
        std::cout << name << " draws " << card.name.char_name << card.suit << std::endl;
    } else {
        std::cout << name << " draws " << card.name.int_name << card.suit  << std::endl;
    }

    hand_value = calc_hand_value();
    if (hand_value > 21) {
        std::cout << name << " BUSTS with " << hand_value << "!!!" << std::endl;
        busted = true;
        playing = false;
    }
}

int Player::calc_hand_value() {
    int value = 0;
    for (int i = 0; i < hand.size(); i++)
        value += hand[i].value;

    while (value > 21 && aces.size() > 0) {
        adjust_aces();
        value -= 10;
    }

    return value;
}

void Player::print_hand_value() {
    std::cout << name << "'s current hand is worth " << hand_value << std::endl;
}

void Player::adjust_aces() {
    hand[aces.back()].value = 1;
    aces.pop_back();
}

void Player::stay() {
    playing = false;
    std::cout << name << " stays with " << hand_value << std::endl;
}

void Player::lose(int bet) {
    money -= bet;
    if (money < 0)
        money = 0;
    std::cout << name << " loses $" << bet << " (Money left: $"
              << money << ")" << std::endl;
}

void Player::win(int bet) {
    money += bet;
    std::cout << name << " wins $" << bet << " (New Total: $"
              << money << ")" << std::endl;
}

void Player::discard_hand() {
    hand.clear();
    aces.clear();
}