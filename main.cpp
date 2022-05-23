#include <iostream>
#include<vector>

#ifdef _WIN32
#include "raylib/src/raylib.h"
#elif __linux__
#include"raylib.h"
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Development"
#define CARDS_NUMBER 10
#define MAX_CARDS_ROWS 1
#define MAX_CARDS_COLUMNS 5
#define MAX_DECKS_ROWS 1
#define MAX_DECKS_COLUMNS 6
#define MIN_CARDS_IN_DECK 4
enum States{
    MENU,GAME,DECKSCREEN, DECKCREATINGSCREEN
};
States gameState = MENU;
bool isDeckLoop = false;
bool ChosingDeck = false;
Camera2D camera = {0};

class Card {
public:
    std::string name;
    std::string fileName;
    std::vector<int> Attacks;
    int Id;
    Card(std::string name, int Id, int atk1, int atk2, std::string fileNameFunc)
    {
        name = name;
        Id = Id;
        Attacks.push_back(atk1);
        Attacks.push_back(atk2);
        fileName = fileNameFunc;
    }
};
std::vector<Card> AddToDeck;
std::vector<Card> Cards;

class game {
public:
    void Draw() {
        DrawText("In Game", 300, 300, 33, WHITE);
    }
};

class Camera_cfg {
private:
    Vector2 target;
    float rotation;
    float zoom;
public:
    float GetXTarget() { return target.x; }
    float GetYTarget() { return target.y; }
    float GetRotation() { return rotation; }
    float GetZoom() { return zoom; }

    void SetXTarget(float element) { target.x = element; }
    void SetYTarget(float element) { target.y = element; }
    void SetRotation(float element) { rotation = element; }
    void SetZoom(float element) { zoom = element; }
    
    void AddX(float element) { target.x += element;};
    void RemoveX(float element) { target.x -= element;};
    void AddY(float element) { target.y += element;};
    void RemoveY(float element) {target.y -= element;};
    void AddZoom(float element){zoom += element;};
    void RemoveZoom(float element){zoom -= element;};
};
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
    /*Listening to menu*/
    void Listener()
    {
            /*Check if "Deck" button was pressed*/
            if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), Decks)
            && IsMouseButtonPressed(0)) {  
                /*Set the gameState DeckScreen*/
                gameState = DECKSCREEN;
                isDeckLoop=true;
            }
            /*Check if "Play" button was pressed*/
            if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), play)
            && IsMouseButtonPressed(0)) {
                /*Set the gameState Game*/
                gameState = GAME;
            }
    };
};

class CreatingDeckMenu{
private:
    
public:
    void Draw(){
        DrawLine(0, 100, 1800, 100, WHITE);
        DrawLine(300, 100, 300, 1800, WHITE);
    }
};

class deck {
public:
    std::string Name;
    std::vector<Card> deck;
    int DeckId;
    void SetDeck(std::string DeckName, std::vector<Card> DeckCards, int Id){
        deck = DeckCards;
        DeckId = Id;
    }
};

/* Setting player inventory !!! */

/* Create the player deck list. This will be modified when the games has database */
std::vector<deck> PlayerDecks;

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
        if(gameState==DECKCREATINGSCREEN){
        CreateButton.x = 1500;
        DrawText("-", CreateButton.x, CreateButton.y, 90, WHITE);
        }
        if (ChosingDeck && gameState == DECKSCREEN) {
            /* Draw text to finalize the deck */
            DrawText("Finalize", 500, 500, 30, GRAY);
        }
    }
    void Listener()
    {
        if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), CreateButton)
        && IsMouseButtonPressed(0)) {
            if(ChosingDeck){
                ChosingDeck=false;
            }
            ChosingDeck = true;
            switch(gameState){
                case DECKSCREEN:
                gameState=DECKCREATINGSCREEN;
                break;
                case DECKCREATINGSCREEN:
                AddToDeck.clear();
                gameState=DECKSCREEN;
                break;
            }
        }

        /* Check if button to create deck was pressed */
        if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), FinalizeButton)
        && IsMouseButtonPressed(0)) {
            /* Check if deck have the Min_Cards_Quantity */
            if (AddToDeck.size()>MIN_CARDS_IN_DECK){
                /* Create the deck */
                deck thisDeck;
                /* Set the deck info */
                thisDeck.SetDeck("Deck1", AddToDeck, PlayerDecks.size());
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
        if (ChosingDeck) {
            DrawText("+",x, y, 50, WHITE);
        }
        DrawRectangle(x, y, 50, 50, WHITE);
        Rectangles.push_back(button);
    }
    void Listener(){
        /* Checking who card is pressed */
        if (IsMouseButtonPressed(0)) {
            for (size_t i = 0; i < Cards.size(); ++i) {
                if (CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), Rectangles[i])
                && IsMouseButtonPressed(0)) {
                    if (ChosingDeck) {
                        AddToDeck.push_back(Cards[i]);
                        printf("Card Loaded sucessfully: %s\n", Cards[i].fileName.c_str());
                        printf("Deck cards: %ld\n", AddToDeck.size());
                    }
                }
            }
        }
    }
};

int main(void) {
    /* Initialize Window */
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    /* Camera Config */
    Camera_cfg Camera;
    Camera.SetXTarget(20.0f);
    Camera.SetYTarget(20.0f);
    Camera.SetRotation(0.0f);
    Camera.SetZoom(1.0f);
    camera.target = (Vector2) {Camera.GetXTarget(), Camera.GetYTarget()};
    camera.rotation = Camera.GetRotation();

    /* Cards */
    auto Lion = Card("Lion", 0, 32, 32, "card.png");
    auto Raiko = Card("raiko", 1, 230, 23, "card2.png");
    auto Ave = Card("Ave", 1, 230, 23, "card2.png");
    auto Mula = Card("Mula", 1, 230,23, "card2.png");
    auto Dilma = Card("Dilma", 1, 230,23, "card2.png");
    Cards.push_back(Lion);
    Cards.push_back(Raiko);
    Cards.push_back(Ave);
    Cards.push_back(Mula);
    Cards.push_back(Dilma);

    /* Classes */
    menuPrincipal Menu;
    game Game;
    deck Deck;
    button Button;
    deckscreen DeckScreen;
    CreatingDeckMenu CDM;

    /* Texture Declaration */
    std::vector<Texture2D> CardList;
    for (size_t i = 0; i < Cards.size(); ++i) {
        Image thisCarde = LoadImage(Cards[i].fileName.c_str());
        ImageResize(&thisCarde, 150, 150);
        Texture2D thisCard = LoadTextureFromImage(thisCarde);
        CardList.push_back(thisCard);
        UnloadImage(thisCarde);
    }

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
                camera.target = (Vector2) {Camera.GetXTarget(), Camera.GetYTarget()};
                Camera.AddY(GetMouseWheelMove() * 100);
                camera.zoom = Camera.GetZoom();


                switch(gameState){
                    case DECKCREATINGSCREEN:
                        CDM.Draw();
                        Camera.SetZoom(0.5);
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
                        for (size_t l = 0; l < MAX_CARDS_ROWS; ++l) {
                            for (size_t c = 0; c < MAX_CARDS_COLUMNS; ++c) {
                                DrawTexture(CardList[c], 20 + l * 110,c * 130, WHITE);
                                Button.Draw(20 + l * 110, c * 130);
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
