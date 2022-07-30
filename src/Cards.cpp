#include"Cards.hpp"
#include"raylib.h"

Card::Card(std::string _name, std::string _fileName, int _Id, int _HP):
name(_name), fileName(DEFAULT_RES_PATH + _fileName), Id(_Id), HP(_HP)
{}
        
std::vector<Card> DefineCards()
{
    auto Carta1 = Card("Cadu", "card.png", 0, 60);
    auto Carta2 = Card("Fibertero", "card.png", 1, 60);
    auto Carta3 = Card("Wanonz", "card.png", 2, 60);
    auto Carta4 = Card("fiberter", "card.png", 3, 60);
    auto Carta5 = Card("guioss", "card.png", 4, 60);
    auto Carta6 = Card("teste6", "card.png", 5, 60);
    std::vector<Card> CardList;
    CardList.push_back(Carta1);
    CardList.push_back(Carta2);
    CardList.push_back(Carta3);
    CardList.push_back(Carta4);
    CardList.push_back(Carta5);
    CardList.push_back(Carta6);
    return CardList;
}

/* Texture Declaration*/
std::vector<Texture2D> TexLoader(std::vector<Card> Cards)
{
    std::vector<Texture2D> CardList;

    for (size_t i = 0; i < Cards.size(); ++i) {
        /*Create the card image*/
        Image cardImg = LoadImage(Cards[i].fileName.c_str());
        /**Resize the card image to default size**/
        ImageResize(&cardImg, 150, 200);
        /*Draws the card name*/
        ImageDrawText(&cardImg, Cards[i].name.c_str(), 17, 6, 17, GREEN);
        /*Transform to texture*/
        Texture2D thisCard = LoadTextureFromImage(cardImg);
        /*Add to cardlist*/
        CardList.push_back(thisCard);

        printf("[ CardList ] - Loading Cards \n%ld/%ld \nwith file %s\n\n", i,
        Cards.size(),
        Cards[i].fileName.c_str());
        UnloadImage(cardImg);
    }
    return CardList;
}
