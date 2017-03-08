#include <iostream>
#include <random>

#include "Deck.h"
#include "Player.h"

void do_player_turn(Player *human, Deck *deck) {
    char action;
    std::cout << "Hit or Stay? (H/S) ";
    std::cin >> action;

    if (std::tolower(action) == 'h')
        human->hit(deck);
    else if (std::tolower(action) == 's')
        human->stay();
    else
        std::cout << "Not a valid option." << std::endl;
}

void do_computer_turn(Player *computer, Deck *deck) {
    if (computer->hand_value >= 14)
        computer->stay();
    else
        computer->hit(deck);
}

int get_bet(int current_money) {
    std::cout << "Current money: " << current_money << std::endl;
    int bet = 0;
    while (bet <= 0 || bet > current_money) {
        std::cout << "Enter your bet: ";
        std::cin >> bet;
    }

    return bet;
}

void setup_new_round(Player *human, Player *computer, Deck *deck) {
    human->discard_hand();
    computer->discard_hand();

    human->busted = false;
    human->playing = true;
    computer->busted = false;
    computer->playing = true;
}

int main() {
    // Initialize RNG
    std::random_device rd;


    // Initialize player
    Player human = Player();
    std::cout << "Enter player name: ";
    std::cin >> human.name;

    // Initialize computer
    Player computer = Player();
    computer.name = "Pokerbot";

    // Main game loop
    bool playing_game = true;
    while (playing_game) {
        // Get a positive integer starting money from the player
        while (human.money <= 0) {
            std::cout << "Enter starting money (must be greater than zero): ";
            std::cin >> human.money;
        }

        // Get player bet and start hand (round)
        while (human.money > 0) {
            int bet = get_bet(human.money);

            // Initialize and shuffle deck
            Deck deck = Deck();
            deck.init();
            std::default_random_engine engine = std::default_random_engine{rd()};
            deck.shuffle(engine);
            human.hit(&deck);
            human.hit(&deck);

            // Do player's turn
            while (human.playing) {
                human.print_hand_value();
                do_player_turn(&human, &deck);
            }

            // If human busted, skip computer's turn and go to the next round
            if (human.busted) {
                human.lose(bet);
                setup_new_round(&human, &computer, &deck);
                continue;
            }

            computer.hit(&deck);
            computer.hit(&deck);

            // Do computer's turn
            while (computer.playing) {
                computer.print_hand_value();
                do_computer_turn(&computer, &deck);
            }

            if (computer.busted || human.hand_value > computer.hand_value)
                human.win(bet);
            else if (human.hand_value < computer.hand_value)
                human.lose(bet);

            // Clear player state flags and empty hands/deck
            setup_new_round(&human, &computer, &deck);
        }

        std::cout << human.name << " ran out of money!!!" << std::endl;

        char choice;
        std::cout << "Play again? (Y/N): ";
        std::cin >> choice;

        if (std::tolower(choice) == 'n')
            playing_game = false;
    }

    return 0;
}