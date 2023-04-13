#ifndef CARD_H
#define CARD_H
#include <string>
namespace ariel {
    enum Type {
        HEARTS = 0,
        DIAMONDS = 1,
        SPADES = 2,
        CLUBS = 3,
        NONE = -1
    };

    class Card {
    private:
        Type type;
        int value;
    public:
        Card();

        Card(Type type, int value) ;

        Card(int type, int value) ;

        Card(const Card& other) ;
        Card& operator=(const Card& other) = default;
        ~Card() = default ;
        Card(Card&& other) = default;
        Card& operator=(Card&& other) noexcept = default;

        Type getType() ;

        int getValue() ;

        int compare(Card *c) ;

        std::string toString() ;
    };


}
#endif //CARD_H
