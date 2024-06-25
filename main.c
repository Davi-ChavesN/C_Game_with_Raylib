#include "raylib.h"
#include "header.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


/* Structs para objetos do jogo */
typedef struct Node
{
    void *info;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct List
{
    struct Node *start;
    struct Node *end;
}List;

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

typedef struct Obstacle
{
    int width;
    int height;
    int x;
    int y;
    int paridade;
}Obstacle;

typedef struct Scoreboard
{
    char nome[9];
    int score;
    char jogo[50];
}Scoreboard;


int opc_menu = 1;
int opc_menu_jogo = 1;
int pontuacao = 0;
int speed_up = 0;
int highest = 0;
/* Funções */
List* createList()
{
    List *lista = (List*)malloc(sizeof(List));
    lista->start = lista->end = NULL;

    return lista;
}

Node* createNode(void* info)
{
    Node *no = (Node*)malloc(sizeof(Node));
    no->next = no->prev = NULL;
    no->info = info;

    return no;
}

void addEndList(List *lista, void* info)
{
    Node *novo = createNode(info);
    if(lista->start == NULL)
    {
        lista->start = lista->end = novo;
    }
    else if(lista->start != NULL)
    {
        lista->end->next = novo;
        novo->prev = lista->end;
        lista->end = novo;
    }
}

int menu()
{
    int choice = 0;
    DrawText(TextFormat("Arcade"), 520, 50, 70, BLACK);


    if(opc_menu == 1)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, RED);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Créditos"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Sair"), 50, 620, 30, BLACK);
    }
    else if(opc_menu == 2)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, RED);
        DrawText(TextFormat("Créditos"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Sair"), 50, 620, 30, BLACK);
    }
    else if(opc_menu == 3)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Créditos"), 50, 580, 30, RED);
        DrawText(TextFormat("Sair"), 50, 620, 30, BLACK);
    }
    else if(opc_menu == 4)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Créditos"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Sair"), 50, 620, 30, RED);
    }

    if(IsKeyPressed(KEY_DOWN))
    {
        opc_menu++;
        if(opc_menu > 4)
        {
            opc_menu = 4;
        }
    }
    else if(IsKeyPressed(KEY_UP))
    {
        opc_menu--;
        if(opc_menu < 1)
        {
            opc_menu = 1;
        }
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        choice = opc_menu;
    }
    else
    {
        choice = 0;
    }

    return choice;
}

int menuJogo()
{
    int choice = 0;
    DrawText(TextFormat("Jogos"), 520, 50, 70, BLACK);


    if(opc_menu_jogo == 1)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, RED);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Snake"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, BLACK);
    }
    else if(opc_menu_jogo == 2)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, RED);
        DrawText(TextFormat("Snake"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, BLACK);
    }
    else if(opc_menu_jogo == 3)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Snake"), 50, 580, 30, RED);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, BLACK);
    }
    else if(opc_menu_jogo == 4)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, BLACK);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, BLACK);
        DrawText(TextFormat("Snake"), 50, 580, 30, BLACK);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, RED);
    }


    if(IsKeyPressed(KEY_DOWN))
    {
        opc_menu_jogo++;
        if(opc_menu_jogo > 1)
        {
            opc_menu_jogo = 1;
        }
    }
    else if(IsKeyPressed(KEY_UP))
    {
        opc_menu_jogo--;
        if(opc_menu_jogo < 1)
        {
            opc_menu_jogo = 1;
        }
    }

    if(IsKeyPressed(KEY_SPACE))
    {
        choice = opc_menu_jogo;
    }
    else
    {
        choice = 0;
    }

    return choice;
}

bool checkCollision(Character personagem, Rectangle rec)
{
    Vector2 vec = {
        .x = personagem.x,
        .y = personagem.y,
    };
    
    CheckCollisionCircleRec(vec, personagem.radius, rec);

}

void resetFlappy(List *obstaculos)
{
    Node *aux = obstaculos->start;
    while(aux != NULL)
    {
        ((Obstacle*)aux->info)->x += 1500;

        aux = aux->next;
    }
    if(pontuacao > highest)
    {
        highest = pontuacao;
    }
    pontuacao = 0;
}

void flappyBird(Screen tela, Character *personagem, List *obstaculos, Enviroment *ambiente, int *menu_opc, List *scoreboard, int *opc_jogo)
{
    int rng = 0;
    int up_down_value = 0;
    personagem->y += ambiente->gravity;
    ambiente->gravity += 1;
    if(personagem->y + personagem->radius > tela.height)
    {
        ambiente->gravity = 0;
        personagem->y = tela.height - personagem->radius;
    }

    if(IsKeyPressed(KEY_SPACE))
    {
        ambiente->gravity = -10;
    }

    Node *aux = obstaculos->start;
    while(aux != NULL)
    {
        ((Obstacle*)aux->info)->x -= ambiente->speed;
        if(((Obstacle*)aux->info)->x < 0)
        {
            ((Obstacle*)aux->info)->x += 2080;
            if(((Obstacle*)aux->info)->paridade%2 != 0)
            {
                up_down_value = rand()%100;
                rng = rand()% 3;
                if(rng == 1)
                {                
                    if(((Obstacle*)aux->info)->y + ((Obstacle*)aux->info)->height < tela.height/2)
                    {
                        ((Obstacle*)aux->info)->y -= up_down_value;
                        ((Obstacle*)aux->next->info)->y -= up_down_value;
                    }
                }
                else if(rng == 2)
                {
                    if(((Obstacle*)aux->info)->y + ((Obstacle*)aux->info)->height > tela.height/2)
                    {
                        ((Obstacle*)aux->info)->y += up_down_value;
                        ((Obstacle*)aux->next->info)->y += up_down_value;
                    }
                }
            }
        }

        Rectangle rec = {
            .height = ((Obstacle*)aux->info)->height,
            .width = ((Obstacle*)aux->info)->width,
            .x = ((Obstacle*)aux->info)->x,
            .y = ((Obstacle*)aux->info)->y,
        };
        if(checkCollision(*personagem, rec))
        {
            Scoreboard *novo = (Scoreboard*)malloc(sizeof(Scoreboard));
            // DrawText(TextFormat("Insira seu nome"), 520, 50, 70, BLACK);
            // fflush(stdin);
            // scanf("%s", &novo->nome);
            novo->score = pontuacao;
            addEndList(scoreboard, novo);
            
            *menu_opc = 0;
            *opc_jogo = 0;
            resetFlappy(obstaculos);
        }
        else
        {
            speed_up += ambiente->speed;
            if(speed_up == 500)
            {
                speed_up = 0;
                pontuacao++;
            }
        }

        DrawRectangle(
            ((Obstacle*)aux->info)->x, 
            ((Obstacle*)aux->info)->y, 
            ((Obstacle*)aux->info)->width, 
            ((Obstacle*)aux->info)->height, 
            BLACK);

        aux = aux->next;
    }
    

    DrawCircle(personagem->x, personagem->y, personagem->radius, RED);
    DrawText(TextFormat("Pontuação: %d", pontuacao), 10, 10, 30, BLACK);
    DrawText(TextFormat("High Score: %d", highest), 10, 40, 30, BLACK);
}


/* Código Principal */
int main()
{
    Screen tela = {
        .width = 1280,
        .height = 720,
    };

    Character personagem = {
        .x = tela.width/2 - 250,
        .y = tela.height/2,
        .width = 50,
        .height = 50,
        .radius = 25,
    };

    Enviroment ambiente = {
        .gravity = 0,
        .speed = 5,
    };

    InitWindow(tela.width, tela.height, "Arcade");
    SetTargetFPS(60);

    List *scoreboard = createList();
    List *obstaculos = createList();
    Obstacle *obs1 = (Obstacle*)malloc(sizeof(Obstacle));
    obs1->height = 360;
    obs1->width = 50;
    obs1->x = 1280;
    obs1->y = 0;
    obs1->paridade = 1;
    addEndList(obstaculos, (void*)obs1);

    Obstacle *obs2 = (Obstacle*)malloc(sizeof(Obstacle));
    obs2->height = 360;
    obs2->width = 50;
    obs2->x = 1280;
    obs2->y = 500;
    obs2->paridade = 2;
    addEndList(obstaculos, (void*)obs2);

    Obstacle *obs3 = (Obstacle*)malloc(sizeof(Obstacle));
    obs3->height = 360;
    obs3->width = 50;
    obs3->x = 1680;
    obs3->y = 0;
    obs3->paridade = 1;
    addEndList(obstaculos, (void*)obs3);

    Obstacle *obs4 = (Obstacle*)malloc(sizeof(Obstacle));
    obs4->height = 360;
    obs4->width = 50;
    obs4->x = 1680;
    obs4->y = 500;
    obs4->paridade = 2;
    addEndList(obstaculos, (void*)obs4);

    Obstacle *obs5 = (Obstacle*)malloc(sizeof(Obstacle));
    obs5->height = 360;
    obs5->width = 50;
    obs5->x = 2080;
    obs5->y = 0;
    obs5->paridade = 1;
    addEndList(obstaculos, (void*)obs5);

    Obstacle *obs6 = (Obstacle*)malloc(sizeof(Obstacle));
    obs6->height = 360;
    obs6->width = 50;
    obs6->x = 2080;
    obs6->y = 500;
    obs6->paridade = 2;
    addEndList(obstaculos, (void*)obs6);

    srand(time(NULL));
    int games[5];
    int menu_opc = 0;
    int opc_jogo = 0;
    

    while(!WindowShouldClose() && menu_opc != 4)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(menu_opc == 0)
        {
            menu_opc = menu();
        }

        if(menu_opc == 1)
        {
            if(opc_jogo == 0)
            {
                opc_jogo = menuJogo();
            }
            else if(opc_jogo == 1)
            {
                /* Flappy Bird */
                flappyBird(tela, &personagem, obstaculos, &ambiente, &menu_opc, scoreboard, &opc_jogo);
            }
            else if(opc_jogo == 2)
            {
                /* Asteroids */
                // mainAsteroids();
            }
        }
        else if(menu_opc == 2)
        {
            int posy = 200;
            Node *aux = scoreboard->start;
            DrawText(TextFormat("LeaderBoard"), 420, 50, 70, BLACK);

            while(aux != NULL)
            {   
                DrawText(TextFormat("Player - %d", ((Scoreboard*)aux->info)->score), 10, posy, 30, BLACK);

                aux = aux->next;
                posy += 40;
            }

            if(IsKeyPressed(KEY_SPACE))
            {
                menu_opc = 0;
            }
        }
        else if(menu_opc == 3)
        {
            DrawText(TextFormat("Programa criado utilizando a biblioteca "), 10, 10, 30, BLACK);
            DrawText(TextFormat("Raylib "), 620, 10, 30, BLUE);
            DrawText(TextFormat("em linguagem "), 10, 40, 30, BLACK);
            DrawText(TextFormat("C "), 210, 40, 30, BLUE);
            DrawText(TextFormat("para a matéria de Extensão 3"), 240, 40, 30, BLACK);
            DrawText(TextFormat("Alunos: "), 10, 100, 30, BLACK);
            DrawText(TextFormat("Davi de Oliveira Chaves"), 10, 130, 30, BLUE);
            DrawText(TextFormat("Luiz Alberto Cury Andalécio"), 10, 160, 30, RED);
            
            if(IsKeyPressed(KEY_SPACE))
            {
                menu_opc = 0;
            }
        }

        EndDrawing();
    }

    return 0;
}