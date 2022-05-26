#include <iostream>
#include <vector>
#pragma once


#include"Cards.hpp"
#include"Camera.hpp"
#include"Deck.hpp"

#ifdef _WIN32
# include "raylib/src/raylib.h"
#elif __linux__
# include "raylib.h"
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Development"
#define DEFAULT_RES_PATH "res/"

#define CARDS_NUMBER 10
#define MAX_CARDS_ROWS 1
#define MAX_CARDS_COLUMNS 5
#define MAX_DECKS_ROWS 1
#define MAX_DECKS_COLUMNS 6
#define MIN_CARDS_IN_DECK 4

enum States{
    MENU,
    GAME,
    DECKSCREEN,
    DECKCREATINGSCREEN,
};

States gameState = MENU;
bool isDeckLoop = false;
bool chosingDeck = false;

std::vector<Card> Cards = DefineCards();

class game {
public:
    void Draw()
    {
        DrawText("In Game", 300, 300, 33, WHITE);
    }
};

class CreatingDeckMenu{
private:
    Rectangle CButton = {1500,400,90,90};
    bool InLoop = true;
public:
    void Draw()
    {
        DrawLine(0, 160, 1800, 160, WHITE);
        DrawLine(800, 160, 800, 1150, WHITE);
        DrawLine(0,1150,1900,1150, WHITE);
        DrawText("-", CButton.x, CButton.y, 90, WHITE);

    }
    void Listener(){
        if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), CButton) && IsMouseButtonPressed(0)){
            gameState=DECKSCREEN;
        }
    }
};


/* Setting player inventory !!! */

/* Create the player deck list. This will be modified when the games has database */
std::vector<Deck> PlayerDecks;

class menuPrincipal {
private:
    Rectangle play = {10, 5, 120, 50};
    Rectangle Decks = {145, 5, 120, 50};
    Rectangle botao2 = {145 + 135,5, 120, 50};
public:
    void Draw()
    {
        DrawRectangle(play.x, play.y + 20, play.width, play.height, WHITE);
        DrawRectangle(Decks.x, Decks.y + 20, Decks.width, Decks.height, WHITE);
        DrawRectangle(botao2.x,botao2.y + 20, botao2.width, botao2.height, WHITE);
        /* Draw Options */
        DrawText("Play", 42, 40, 30, BLACK);
        DrawText("Coleção", 147, 40, 30, BLACK);
        DrawText("Otro", 287, 40, 30,BLACK);
    }
    /* Listening to menu */
    void Listener()
    {
            /* Check if "Deck" button was pressed */
            if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), Decks)
            && IsMouseButtonPressed(0)) {
                /* Set the gameState DeckScreen */
                gameState = DECKSCREEN;
                isDeckLoop = true;
            }
            /* Check if "Play" button was pressed */
            if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), play)
            && IsMouseButtonPressed(0)) {
                /* Set the gameState Game */
                gameState = GAME;
            }
    };
};


class deckscreen {
private:
    /* Create the button rectangles */
    Rectangle FinalizeButton = {500, 500, 140, 40};
    Rectangle CreateButton = {790, 260, 100, 60};
public:
    void Draw()
    {
        if(gameState==DECKSCREEN)
        {
        DrawText("+", CreateButton.x, CreateButton.y, 50, WHITE);
        }
        if (chosingDeck && gameState == DECKSCREEN) {
            /* Draw text to finalize the deck*/
            DrawText("Finalize", 500, 500, 30, GRAY);
        }
    }
    void Listener()
    {
        if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), CreateButton)
        && IsMouseButtonPressed(0)) {
            if (chosingDeck) {
                chosingDeck = false;
            }
            chosingDeck = true;
            switch(gameState) {
            case DECKSCREEN:
                gameState=DECKCREATINGSCREEN;
                break;
            case DECKCREATINGSCREEN:
                AddToDeck.clear();
                gameState = DECKSCREEN;
                break;
            default:
                break;
            }
        }

        /* Check if button to create deck was pressed */
        if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), FinalizeButton)
        && IsMouseButtonPressed(0)) {
            /* Check if deck have the Min_Cards_Quantity */
            if (AddToDeck.size()>MIN_CARDS_IN_DECK){
                /* Create the deck */
                auto thisDeck = Deck("NoName", AddToDeck, PlayerDecks.size());
                /* Set the deck info */
                /* Clean the cards will be added in deck */
                AddToDeck.clear();
                /* Add the deck to player decklist */
                PlayerDecks.push_back(thisDeck);
                printf("Deck added to wallet. This is your %ld deck", PlayerDecks.size());
            }
        }
    }
};

class button {
public:
    /* Drawing card buttons */
    Rectangle button;
    std::vector<Rectangle> Rectangles;
    void Draw(float x, float y){
        Rectangle button = {x, y, 50, 50};
        if (chosingDeck) {
            DrawText("+",x, y, 50, WHITE);
        }
        DrawRectangle(x, y, 50, 50, WHITE);
        Rectangles.push_back(button);
    }
    void Listener(){
        /* Checking who card is pressed*/
        if (IsMouseButtonPressed(0)) {
            for (size_t i = 0; i < Cards.size(); ++i) {
                if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), Rectangles[i])
                && IsMouseButtonPressed(0)) 
                {
                    printf("\n\n%d\n\n", Cards[i].Id);
            }
        }
    }
    }
};

int main(void) {
    /* Initialize Window */
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    /* Classes */
    Camera_cfg Camera;
    menuPrincipal Menu;
    game Game;
    button Button;
    deckscreen DeckScreen;
    CreatingDeckMenu CDM;
    button Button2;

    /*Camera Config*/
    camera.target = Vector2 {Camera.GetXTarget(), Camera.GetYTarget()};
    camera.rotation = Camera.GetRotation();

    /* Texture Declaration*/
    std::vector<Texture2D> CardList;
    for (size_t i = 0; i < Cards.size(); ++i) {
        Image thisCarde = LoadImage(Cards[i].fileName.c_str());
        ImageResize(&thisCarde, 150, 150);
        Texture2D thisCard = LoadTextureFromImage(thisCarde);
        CardList.push_back(thisCard);
        printf("[ CardList ] - Loading Cards \n%ld/%ld \nwith file %s\n", i,
        Cards.size(),
        Cards[i].fileName.c_str());
        UnloadImage(thisCarde);
    }
    bool inLoop = true;


    Image BkScreen = LoadImage("biosystem-tcg.png");
    ImageResize(&BkScreen, WINDOW_WIDTH, WINDOW_HEIGHT);
    Texture2D BackScreen = LoadTextureFromImage(BkScreen);
    UnloadImage(BkScreen);

    while(!WindowShouldClose()) {
        BeginDrawing();
            BeginMode2D(camera);
                DrawFPS(600,40);

                /* Decks listener */
                /* Updating Camera */
                camera.target = Vector2 {Camera.GetXTarget(), Camera.GetYTarget()};
                Camera.AddY(GetMouseWheelMove() * 100);
                camera.zoom = Camera.GetZoom();


                switch(gameState){
                case DECKCREATINGSCREEN:
                    if(inLoop){
                        for(int i = 0; i<Cards.size();i++){
                            for(size_t l = 0; l < MAX_CARDS_ROWS+2; ++l) {
                                for (size_t c = 0; c < MAX_CARDS_COLUMNS-2; ++c) {
                                    DrawTexture(CardList[i], 40 + l * 270,150+c * 280, WHITE);
                                    Button2.Draw(40+l*270,150+c*280);
        }
            }
                }
                    }
                    CDM.Draw();
                    Camera.SetZoom(0.5);
                    Button2.Listener();
                    CDM.Listener();
                    
                    break;
                case DECKSCREEN:
                    DeckScreen.Draw();
                    Button.Listener();
                    DeckScreen.Listener();
                    Camera.SetZoom(1.0);
                    break;
                case MENU:
                    DrawTexture(BackScreen, 0, 0, WHITE);
                    Menu.Draw();
                    Menu.Listener();
                    Camera.SetZoom(1.0);
                    break;
                case GAME:
                    Game.Draw();
                    Camera.SetZoom(1.0);
                    break;
                default:
                    printf("Unable to get current state");
                    break;
                }

                /* Drawing Decks Menu cards */
                if (gameState == DECKSCREEN) {
                    if (isDeckLoop) {
                        for(int i = 0; i<Cards.size(); ++i){
                            for (size_t l = 0; l < MAX_CARDS_ROWS; ++l) {
                                for (size_t c = 0; c < MAX_CARDS_COLUMNS; ++c) {
                                    DrawTexture(CardList[i], 20 + l * 110,c * 130, WHITE);
                                    Button.Draw(20 + l * 110, c * 130);
                            }
                        }
                    }
                } else {
                        for (size_t l = 0; l < MAX_DECKS_ROWS; ++l) {
                            for (size_t c = 0; c < MAX_DECKS_COLUMNS; ++c) {
                                for (size_t i = 0; i < PlayerDecks.size(); ++i) {
                                    DrawRectangle(600 + l * 110, i * 130, 100, 120, WHITE);
                                }
                            }
                        }
                    }
                }

                ClearBackground(BLACK);
            EndMode2D();
        EndDrawing();
    }
}