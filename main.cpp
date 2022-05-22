#include <iostream>
#include"raylib/src/raylib.h"
#include"raygui/src/raygui.h"
#include<vector>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Development"
#define CARDS_NUMBER 10
#define MAX_ROWS 7
#define MAX_COLUMNS 5

bool InMenu = true;
bool InGame = false;
bool InDecks = false;
bool isDeckLoop = false;

class game{
public:
    void Draw(){
        DrawText("In Game",300,300,33,WHITE);
    }
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
            if(CheckCollisionPointRec(GetMousePosition(), Decks) && IsMouseButtonPressed(0)){
                    InDecks = true;
                    isDeckLoop=true;
                    InMenu=false;
                    InGame=false;
            }
            if(CheckCollisionPointRec(GetMousePosition(), play) && IsMouseButtonPressed(0)){
                InGame = true;
                InMenu = false;
                InDecks = false;
                };
    };
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

class deck{
private:
public:
    void MenuDraw(){
        DrawText("hi",40,40,10,WHITE);
    }
    void CreateDeck(int Deck[52]){
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

std::vector<Card> Cards;

int main(){
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE);

    //Setting UP
    Camera_cfg Camera;
    Camera.SetXTarget(20.0f);
    Camera.SetYTarget(20.0f);
    Camera.SetRotation(0.0f);
    Camera.SetZoom(1.0f);
    //Cards
    Card Lion; Lion.SetCard("Lion", 0, 32,32,"card.png"); Cards.push_back(Lion);
    Card raiko; raiko.SetCard("raiko", 1, 230,23,"card.png"); Cards.push_back(raiko);
    Card oio; oio.SetCard("a", 2, 230,23,"card.png"); Cards.push_back(oio);
    Card oi; oi.SetCard("s", 3, 230,23,"card.png"); Cards.push_back(oi);
    Card five; five.SetCard("d", 4, 230,23,"card.png"); Cards.push_back(five);

    //
    menuPrincipal Menu;
    game Game;
    deck Deck;
    Camera2D camera = { 0 };
    camera.target = (Vector2){Camera.GetXTarget(),Camera.GetYTarget()};
    camera.rotation = Camera.GetRotation();
    camera.zoom = Camera.GetZoom();
    std::vector< Texture2D > CardList;
    for(int i=0;i<Cards.size();i++){
        Image thisCarde = LoadImage(Cards[i].fileName.c_str());
        ImageResize(&thisCarde,150,150);
        Texture2D thisCard = LoadTextureFromImage(thisCarde);
        CardList.push_back(thisCard);
    }


    while(!WindowShouldClose()){
        BeginDrawing();
            BeginMode2D(camera);
                camera.target = (Vector2){Camera.GetXTarget(),Camera.GetYTarget()};
                Camera.AddY(GetMouseWheelMove()* 100);
                Menu.Listener();
                if(InDecks){Deck.MenuDraw();
                }
                if(InMenu){Menu.Draw();}
                if(InGame){Game.Draw();}
                if(InDecks&&isDeckLoop){
                    for (int l=0; l<MAX_ROWS;l++){
                        for(int c=0;c<MAX_COLUMNS;c++){
                        DrawTexture(CardList[c],20+l*110,c*130,WHITE);
                        }
                    }
                }
                

                ClearBackground(BLACK);
            EndMode2D();
        EndDrawing();
                
                }}