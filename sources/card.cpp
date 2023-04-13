#include "card.hpp"
#include <iostream>
namespace ariel {

    ///-----Ctor by type instance and value
    Card::Card(Type type, int value) {
        if(value > 14 || value < 2){
            throw std::runtime_error("Invalid value supplied, value should be in range (2, 14)") ;
        }
        this->type = type;
        this->value = value;
    }

    ///-----Ctor by an integer associated with the type enum and a value-----
    Card::Card(int type, int value) {
        if(value > 14 || value < 2){
            throw std::runtime_error("Invalid value supplied, value should be in range (2, 14)") ;
        }
        if(type < -1 || type > 3){
            throw std::runtime_error("Invalid type supplied, type value should be in range (-1, 3)") ;
        }
        this->type = static_cast<Type>(type);
        this->value = value;
    }

    ///-----Copy Ctor-----
    Card::Card(const Card &other) {
        this->type = other.type ;
        this->value = other.value ;
    }

    ///-----Returns the type of the card-----
    Type Card::getType() {
        return this->type;
    }

    ///-----Returns the value of the card-----
    int Card::getValue() {
        return this->value;
    }

    ///-----Returns a string representation of a type instance provided-----
    std::string getStringByType(Type type) {
        switch (type) {
            case HEARTS:
                return "Hearts";
            case DIAMONDS:
                return "Diamonds";
            case SPADES:
                return "Spades";
            case CLUBS:
                return "Clubs";

            default:
                return "";
        }
    }

    ///-----Return a string represents the card, shows the card's value and type-----
    std::string Card::toString() {
        std::string cardStr = "";
        switch (this->value) {
            case 11:
                cardStr += "Jack ";
                break;
            case 12:
                cardStr += "Queen ";
                break;
            case 13:
                cardStr += "King ";
                break;
            case 14:
                cardStr += "Ace ";
                break;
            default:
                cardStr += std::to_string(this->value) + " ";
        }
        cardStr += "of " + getStringByType(this->type);
        return cardStr;
    }

    ///-----Compare the current card to another instance, return 0 if the both cards are equal, 1 if the current value
    ///-----is bigger then the other, and -1 otherwise-----
    int Card::compare(Card *c){
        this->getValue() ;
        c->getValue() ;
        if(this->getValue() > c->getValue()){
            return 1 ;
        }else if(this->getValue() < c->getValue()){
            return -1 ;
        }
        return 0 ;
    }
}