#include<iostream>
#include<vector>
#include"raylib.h"
#pragma once
#define DEFAULT_RES_PATH "res/"

using namespace std;

class Card
{
public:
    std::string name;
    std::string fileName;
    int Id;
    int HP;
    Image mainImage;
    Card() = default;
    Card(std::string _name, std::string _fileName, int _Id, int _HP);
};

std::vector<Card> DefineCards();
std::vector<Texture2D> TexLoader(std::vector<Card> Cards); 