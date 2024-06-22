#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>


/* Structs para objetos do jogo */
typedef struct Screen
{
    int width;
    int height;
}Screen;

typedef struct Character
{
    int x;
    int y;
    int width;
    int height;
    float radius;
}Character;

typedef struct Enviroment
{
    int gravity;
    int speed;
}Enviroment;


/* Funções */
int menu(Screen tela)
{
    DrawText("Arcade", 520, 50, 70, BLACK);

    return 0;
}



/* Código Principal */
int main()
{
    Screen tela = {
        .width = 1280,
        .height = 720,
    };

    Character personagem = {
        .x = tela.width/2,
        .y = tela.height/2,
        .width = 50,
        .height = 50,
        .radius = 25,
    };

    Enviroment ambiente = {
        .gravity = 0,
    };

    InitWindow(tela.width, tela.height, "Nome do jogo");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int menu_opc = menu(tela);



        /*
        personagem.y += ambiente.gravity;
        ambiente.gravity += 1;
        if(personagem.y + personagem.radius > tela.height)
        {
            ambiente.gravity = 0;
            personagem.y = tela.height - personagem.radius;
        }

        if(IsKeyPressed(KEY_SPACE))
        {
            ambiente.gravity = -20;
        }

        DrawCircle(personagem.x, personagem.y, personagem.radius, RED);
        */
        EndDrawing();
    }

    return 0;
}