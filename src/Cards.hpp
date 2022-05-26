#include<iostream>
#include<vector>
#pragma once
#define DEFAULT_RES_PATH "res/"

using namespace std;

class Card{
public:
    std::string name;
    std::string fileName;
    int Id;
    int HP;
    Card() = default;
    Card(std::string _name, std::string _fileName, int _Id, int _HP)
     :name(_name), fileName(DEFAULT_RES_PATH + _fileName), Id(_Id), HP(_HP){}
};

std::vector<Card> DefineCards(){
    auto Carta1 = Card("a", "card.png", 0, 60);
    auto Carta2 = Card("a", "card.png", 1, 60);
    auto Carta3 = Card("a", "card.png", 2, 60);
    auto Carta4 = Card("a", "card.png", 3, 60);
    auto Carta5 = Card("a", "card.png", 4, 60);
    auto Carta6 = Card("a", "card.png", 5, 60);
    std::vector<Card> CardList;
    CardList.push_back(Carta1);
    CardList.push_back(Carta2);
    CardList.push_back(Carta3);
    CardList.push_back(Carta4);
    CardList.push_back(Carta5);
    CardList.push_back(Carta6);
    return CardList;
}