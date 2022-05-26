#include<iostream>
#include"raylib.h"
#include"Cards.hpp"
#include<vector>
#pragma once

std::vector<Card> AddToDeck;

class Deck {
public:
    std::string Name;
    std::vector<Card> Cards;
    int Id;
    Deck() = default;
    Deck(std::string _Name, std::vector<Card> _Cards, int _Id)
        :Name(_Name), Cards(_Cards), Id(_Id){}
    Card GetCardByIndex(int index){
        return Cards[index];
    }
};