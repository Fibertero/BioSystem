#include <iostream>
#include"raylib/src/raylib.h"
#include"raygui/src/raygui.h"
#include<vector>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Development"
#define CARDS_NUMBER 10
#define MAX_ROWS 1
#define MAX_COLUMNS 2

bool InMenu = true;
bool InGame = false;
bool InDecks = false;
bool isDeckLoop = false;
Camera2D camera = { 0 };


class game{
public:
    void Draw(){
        DrawText("In Game",300,300,33,WHITE);
    }
};
class Camera_cfg{
private:
    float x_target;
    float y_target;
    float rotation;
    float zoom;
public:
    float GetXTarget(){ return x_target; }
    float GetYTarget(){ return y_target; }
    float GetRotation(){ return rotation; }
    float GetZoom(){ return zoom; }
    void SetXTarget(float element){ x_target = element; }
    void SetYTarget(float element){ y_target = element; }
    void SetRotation(float element){ rotation = element; }
    void SetZoom(float element){ zoom = element; }
    void AddX(float element){x_target = x_target + element;};
    void RemoveX(float element){x_target = x_target - element;};
    void AddY(float element){y_target = y_target + element;};
    void RemoveY(float element){y_target = y_target - element;};

};
class menuPrincipal{
private:
    Rectangle play = {10,5,120,50};
    Rectangle Decks = {145,5,120,50};
    Rectangle botao2 = {145+135,5,120,50};
public:
    void Draw(){
        DrawRectangle(play.x, play.y+20, play.width, play.height, WHITE);
        DrawRectangle(Decks.x, Decks.y+20,Decks.width,Decks.height,WHITE);
        DrawRectangle(botao2.x,botao2.y+20,botao2.width, botao2.height, WHITE);
        DrawText("Play", 42,40,30,BLACK);
        DrawText("Coleção", 147,40,30,BLACK);
        DrawText("Otro", 287,40,30,BLACK);

    }
    void Listener(){
            if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), Decks) && IsMouseButtonPressed(0)){
                    InDecks = true;
                    isDeckLoop=true;
                    InMenu=false;
                    InGame=false;
            }
            if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(),camera), play) && IsMouseButtonPressed(0)){
                InGame = true;
                InMenu = false;
                InDecks = false;
                };
    };
};
class deck{
private:
    deck Deck[52];
public:
    deck SetDeck(std::string name, std::vector<deck> DeckFunc)
    {
        for(int i = 0;i<DeckFunc.size(); i++){
            Deck[i] = DeckFunc[i];
        }
        Decks.push_back(Deck);
    }
};
std::vector<deck> Decks;
class deckscreen{
private:
    Rectangle CreateButton = {790,60,100,60};
public:
    void Draw(){
        DrawText("+", 790,100,50,WHITE);
    }
    void Listener(){
        if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), CreateButton) && IsMouseButtonPressed(0)){
            Deck.SetDeck() 
        }
    }

};
class Card{
public:
    std::string name;
    int Id;
    std::vector< int > Attacks;
    std::string fileName;
    void SetCard(std::string name, int Id, int atk1, int atk2, std::string fileNameFunc){
        name = name;
        Id = Id;
        Attacks.push_back(atk1);
        Attacks.push_back(atk2);
        fileName = fileNameFunc;
    }
};
std::vector<Card> Cards;

class button{
public:
    //Drawing card buttons
    Rectangle button;
    std::vector<Rectangle> Rectangles;
    void Draw(float x, float y){
        Rectangle button={x,y,50,50};
        DrawRectangle(x,y,50,50,WHITE);
        Rectangles.push_back(button);
    }
    void Listener(){
        int i = 0;
        bool cardIsPressed=false;
        //Checking who card is pressed
        if(IsMouseButtonPressed(0)){
            for(i=0;i<Cards.size();i++){
                if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(),camera), Rectangles[i]) && IsMouseButtonPressed(0)){
                    printf("");
                }
            }
        }
    }
};


int main(){
    //Window inicialization
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE);

    //Camera Config
    Camera_cfg Camera;
    Camera.SetXTarget(20.0f);
    Camera.SetYTarget(20.0f);
    Camera.SetRotation(0.0f);
    Camera.SetZoom(1.0f);
    camera.target = (Vector2){Camera.GetXTarget(),Camera.GetYTarget()};
    camera.rotation = Camera.GetRotation();
    camera.zoom = Camera.GetZoom();
    //Cards
    Card Lion; Lion.SetCard("Lion", 0, 32,32,"card.png"); Cards.push_back(Lion);
    Card raiko; raiko.SetCard("raiko", 1, 230,23,"card2.png"); Cards.push_back(raiko);

    //Classes
    menuPrincipal Menu;
    game Game;
    deck Deck;
    button Button;
    deckscreen DeckScreen;
    //Texture Declaration
    std::vector< Texture2D > CardList;
    for(int i=0;i<Cards.size();i++){
        Image thisCarde = LoadImage(Cards[i].fileName.c_str());
        ImageResize(&thisCarde,150,150);
        Texture2D thisCard = LoadTextureFromImage(thisCarde);
        CardList.push_back(thisCard);
    }
    Image BkScreen = LoadImage("biosystem-tcg.png");
    ImageResize(&BkScreen, WINDOW_WIDTH, WINDOW_HEIGHT);
    Texture2D BackScreen = LoadTextureFromImage(BkScreen);
    UnloadImage(BkScreen);
    

    while(!WindowShouldClose()){
        BeginDrawing();
            BeginMode2D(camera);
                //Drawing FPS
                DrawFPS(600,40);
                //Decks listener
                if(InDecks){Button.Listener(); DeckScreen.Listener();}
                //Camera Updates
                camera.target = (Vector2){Camera.GetXTarget(),Camera.GetYTarget()};
                Camera.AddY(GetMouseWheelMove()* 100);
                //Drawing DeckScreen
                if(InDecks){DeckScreen.Draw();
                }
                //Drawing Menu
                if(InMenu){
                    DrawTexture(BackScreen, 0,0,WHITE);
                    Menu.Draw(); 
                    }
                //Listening to menu
                if(InMenu){
                    Menu.Listener();
                }
                //Drawing Game
                if(InGame){
                    Game.Draw();
                    }
                //Drawing Decks Menu cards
                if(InDecks&&isDeckLoop){
                    for (int l=0; l<MAX_ROWS;l++){
                        for(int c=0;c<MAX_COLUMNS;c++){
                        DrawTexture(CardList[c],20+l*110,c*130,WHITE);
                        Button.Draw(20+l*110,c*130);
                        }
                    }
                }
                

                ClearBackground(BLACK);
            EndMode2D();
        EndDrawing();
                
                }}
