#include <raylib.h>
using namespace std;
Color green={173,204,96,255};
Color darkGreen={43,51,24,255};

int main(){
    SetTargetFPS(60);
    InitWindow(800,600,"Snake");
    while (!WindowShouldClose()){
         BeginDrawing();
            ClearBackground(green);
           EndDrawing();
    }
    
}