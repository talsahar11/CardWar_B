#ifndef TASK2_GAME_H
#define TASK2_GAME_H
#include "player.hpp"
#include <array>
namespace ariel {
    constexpr int LOG_SIZE = 100 ;
    class Game {
    private:
        Player& p1 ;
        Player& p2 ;
        Player* winner;
        Deck *gameDeck;
        std::array<std::string, LOG_SIZE> log;
        int turnsPlayed;
        int drawNumber;
        std::array<std::string ,LOG_SIZE>::size_type logSize;
        bool isGameOn;

        void gameOver() ;

        void dealCards() ;

        void handleDraw(Card *c1, Card *c2) ;

        void logTurn(Card *c1, Card *c2, Player *p, bool isDraw) ;

    public:

        Game(Player& p1, Player& p2) ;
        Game(const Game& other) = default ;
        Game& operator=(const Game& other) = delete;
        Game(Game&& other) = default;
        Game& operator=(Game&& other) noexcept = delete;
        ~Game() ;
        void playTurn() ;

        void playAll() ;

        void printStats() ;

        void printLastTurn() ;

        void printLog() ;

        void printWiner() ;
    };

}
#endif //TASK2_GAME_H
