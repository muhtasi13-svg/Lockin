#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>
using namespace std;
Color green={173,204,96,255};
Color darkGreen={43,51,24,255};
float cellSize=30;
float cellcount=20;
double lastUpdateTime=0;
bool ElementInDeque(Vector2 element,deque<Vector2>deque){
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i],element))
        {
           return true;
        }
      
    }
     return false; 
}
bool eventTriggered(double interval){
    double currentTime=GetTime();
    if (currentTime-lastUpdateTime>=interval){
        lastUpdateTime=currentTime;
        return true;
    }
    return false;
}

class Snake{
    public:
    deque<Vector2> body={Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction={1,0};
    bool addsegment = false;
    void Draw(){
        for(unsigned int i=0;i<body.size();i++){
            float x = body[i].x;
            float y= body[i].y;
            Rectangle segment=Rectangle{x*cellSize,y*cellSize,cellSize,cellSize};
            DrawRectangleRounded(segment,0.5,6,darkGreen);
           
        }
    }
    void Update(){ 
        body.push_front(Vector2Add(body[0],direction));
        if (addsegment==true)
        {
         
          addsegment=false;  
        }else{
         body.pop_back();
    
      }
        
        

    }
};
class Food{

   public:
   Vector2 position;
   Texture2D texture;

   Food(deque<Vector2>snakeBody){

       const char* path = "heart.png";
   TraceLog(LOG_INFO, "Exists: %d", FileExists(path));
   Image image = LoadImage(path);
       texture=LoadTextureFromImage(image);
       UnloadImage(image);
       position=GenerateRandomPos(snakeBody);
   }
   ~Food(){
    UnloadTexture(texture);
   }
   void Draw(){
DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);   
}
Vector2 GenerateRandomCell(){
    float x=GetRandomValue(0,cellcount-1);
    float y=GetRandomValue(0,cellcount-1);
    return Vector2{x,y};
}
Vector2 GenerateRandomPos(deque<Vector2>snakeBody){
    
     Vector2 position=GenerateRandomCell();
     while (ElementInDeque(position,snakeBody))
     {
        position =GenerateRandomCell();
     }
    return position; 
}
};
class Game{
    public:
    Snake snake =Snake();
    Food food = Food(snake.body);
    void Draw(){
        food.Draw();
        snake.Draw();
        
    }
    void Update(){
        snake.Update();
        CheckCollisionWithFood();
    }
    void CheckCollisionWithFood(){
        if (Vector2Equals(snake.body[0],food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addsegment = true;
        }
        
    }
};
int main(){
    SetTargetFPS(60);
    InitWindow(cellSize*cellcount,cellSize*cellcount,"Snake");
    TraceLog(LOG_INFO, "Working dir: %s", GetWorkingDirectory());
    TraceLog(LOG_INFO, "Exists: %d", FileExists("heart.png"));
       
    GetWorkingDirectory();
    Game game = Game();
    while (!WindowShouldClose()){
        if(eventTriggered(0.2)){
            game.Update();
        }
        if(IsKeyPressed(KEY_W)&& game.snake.direction.y!=1){
            game.snake.direction={0,-1};
        }
        if(IsKeyPressed(KEY_S)&& game.snake.direction.y!=-1){
            game.snake.direction={0,1};
        }
        if(IsKeyPressed(KEY_A)&& game.snake.direction.x!=1){
            game.snake.direction={-1,0};
        }
        if(IsKeyPressed(KEY_D)&& game.snake.direction.x!=-1){
            game.snake.direction={1,0};
        }
    
         BeginDrawing();
            ClearBackground(green);
            game.Draw();
           EndDrawing();

    }
    
}