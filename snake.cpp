#include <raylib.h>
#include <iostream>
using namespace std;
Color green={173,204,96,255};
Color darkGreen={43,51,24,255};
int cellSize=30;
int cellcount=20;
class Food{
   public:
   Vector2 position;
   Texture2D texture;

   Food(){

       const char* path = "heart.png";
   TraceLog(LOG_INFO, "Exists: %d", FileExists(path));
   Image image = LoadImage(path);
       texture=LoadTextureFromImage(image);
       UnloadImage(image);
       position=GenerateRandomPos();
   }
   ~Food(){
    UnloadTexture(texture);
   }
   void Draw(){
DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);   
}

Vector2 GenerateRandomPos(){
    float x=GetRandomValue(0,cellcount-1);
    float y=GetRandomValue(0,cellcount-1);
    return Vector2{x,y};
}
};
int main(){
    SetTargetFPS(60);
    InitWindow(cellSize*cellcount,cellSize*cellcount,"Snake");
    TraceLog(LOG_INFO, "Working dir: %s", GetWorkingDirectory());
    TraceLog(LOG_INFO, "Exists: %d", FileExists("heart.png"));
       
    GetWorkingDirectory();
    Food food = Food();
    while (!WindowShouldClose()){
         BeginDrawing();
            ClearBackground(green);
            food.Draw();
           EndDrawing();
    }
    
}