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
    int vidas;
    int speed;
    float speedX;
    float speedY;
    int start;
    int moving;
    int facing_up_down;
    int facing_right_left;
    int pontos;
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
    char nome[20];
    int score;
    char jogo[50];
}Scoreboard;

typedef struct Block
{
    int width;
    int height;
    int x;
    int y;
    int vidas;
    int alive;
}Block;

typedef struct Vehicle
{
    int width;
    int height;
    int x;
    int y;
    int speed;
}Vehicle;


int opc_menu = 1;
int opc_menu_jogo = 1;
int pontuacao = 0;
int speed_up = 0;
int cont = 0;
int highest = 0;
int qtd_blocos = 80;
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

void createBlocks(List *blocos)
{
    for(int i = 0; i < qtd_blocos; i++)
    {
        Block *bloco = (Block*)malloc(sizeof(Block));
        bloco->height = 30;
        bloco->width = 60;
        bloco->x = 0;
        bloco->y = 0;
        bloco->vidas = 3;

        addEndList(blocos, (void*)bloco);
    }
}

int menu()
{
    int choice = 0;
    DrawText(TextFormat("Arcade"), 520, 50, 70, WHITE);


    if(opc_menu == 1)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, GREEN);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Créditos"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Sair"), 50, 620, 30, WHITE);
    }
    else if(opc_menu == 2)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, GREEN);
        DrawText(TextFormat("Créditos"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Sair"), 50, 620, 30, WHITE);
    }
    else if(opc_menu == 3)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Créditos"), 50, 580, 30, GREEN);
        DrawText(TextFormat("Sair"), 50, 620, 30, WHITE);
    }
    else if(opc_menu == 4)
    {
        DrawText(TextFormat("Start"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Leaderboard"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Créditos"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Sair"), 50, 620, 30, GREEN);
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
    DrawText(TextFormat("Jogos"), 520, 50, 70, WHITE);


    if(opc_menu_jogo == 1)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, GREEN);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Racing"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, WHITE);
    }
    else if(opc_menu_jogo == 2)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, GREEN);
        DrawText(TextFormat("Racing"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, WHITE);
    }
    else if(opc_menu_jogo == 3)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Racing"), 50, 580, 30, GREEN);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, WHITE);
    }
    else if(opc_menu_jogo == 4)
    {
        DrawText(TextFormat("Flappy Bird"), 50, 500, 30, WHITE);
        DrawText(TextFormat("Asteroids"), 50, 540, 30, WHITE);
        DrawText(TextFormat("Racing"), 50, 580, 30, WHITE);
        DrawText(TextFormat("Block Breaker"), 50, 620, 30, GREEN);
    }


    if(IsKeyPressed(KEY_DOWN))
    {
        opc_menu_jogo++;
        if(opc_menu_jogo > 4)
        {
            opc_menu_jogo = 4;
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

/* Flappy Bird */
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
            if(((Obstacle*)aux->info)->paridade%2 == 0)
            {
                up_down_value = rand()%100;
                rng = rand()% 3;
                if(rng == 1)
                {                
                    if(((Obstacle*)aux->info)->y >= 220)
                    {
                        ((Obstacle*)aux->info)->y -= up_down_value;
                        ((Obstacle*)aux->prev->info)->y -= up_down_value;
                        if(((Obstacle*)aux->info)->y < 220)
                        {
                            ((Obstacle*)aux->info)->y = 220;
                            ((Obstacle*)aux->prev->info)->y = ((Obstacle*)aux->info)->y - ((Obstacle*)aux->info)->height - 160;
                        }
                    }
                }
                else if(rng == 2)
                {
                    if(((Obstacle*)aux->info)->y <= 520)
                    {
                        ((Obstacle*)aux->info)->y += up_down_value;
                        ((Obstacle*)aux->prev->info)->y += up_down_value;
                        if(((Obstacle*)aux->info)->y > 520)
                        {
                            ((Obstacle*)aux->info)->y = 520;
                            ((Obstacle*)aux->prev->info)->y = ((Obstacle*)aux->info)->y - ((Obstacle*)aux->info)->height - 160;
                        }
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
            strcpy(novo->nome, "Flappy Bird");
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

/* Block Breaker */
resetBlocks(List *blocos, Screen tela)
{
    Node *aux = blocos->start;
    int posX = 10;
    int posY = 70;
    for(int i = 0; i < qtd_blocos; i++)
    {
        ((Block*)aux->info)->x = posX;
        ((Block*)aux->info)->y = posY;
        ((Block*)aux->info)->vidas = 1;
        ((Block*)aux->info)->alive = 1;
        if(posX + ((Block*)aux->info)->width + 63 < tela.width)
        {
            posX += 63;
        }
        else
        {
            posX = 10;
            posY += 32;
        }
        aux = aux->next;
    }
}

bool checkBallPlayer(Character *personagem, Character *ball)
{
    Vector2 vec = {
        .x = ball->x,
        .y = ball->y,
    };

    Rectangle rec = {
        .height = personagem->height,
        .width = personagem->width,
        .x = personagem->x,
        .y = personagem->y,
    };

    if(ball->x <= personagem->width*0.3)
    {
        ball->speedX = 5*0.3;
    }
    else if(ball->x > personagem->width*0.3 && ball->x < personagem->width*0.45 )
    {
        ball->speedX = 5*0.7;
    }
    else if(ball->x >= personagem->width*0.45 && ball->x <= personagem->width*0.55 )
    {
        ball->speedX = 5;
    }
    else if(ball->x > personagem->width*0.55 && ball->x < personagem->width*0.7 )
    {
        ball->speedX = 5*0.7;
    }
    else if(ball->x >= personagem->width*0.7)
    {
        ball->speedX = 5*0.3;
    }
    CheckCollisionCircleRec(vec, ball->radius, rec);
}

bool checkBallBlock(Character *ball, Node *aux, int *total_blocos, Character *personagem)
{
    Vector2 vec = {
        .x = ball->x,
        .y = ball->y,
    };

    Rectangle rec1 = {
        .height = 0,
        .width = ((Block*)aux->info)->width,
        .x = ((Block*)aux->info)->x,
        .y = ((Block*)aux->info)->y,
    };
    if(CheckCollisionCircleRec(vec, ball->radius, rec1))
    {
        ball->facing_up_down = 1;
        ((Block*)aux->info)->vidas--;
    }

    Rectangle rec2 = {
        .height = 0,
        .width = ((Block*)aux->info)->width,
        .x = ((Block*)aux->info)->x,
        .y = ((Block*)aux->info)->y + ((Block*)aux->info)->height,
    };
    if(CheckCollisionCircleRec(vec, ball->radius, rec2))
    {
        ball->facing_up_down = 2;
        ((Block*)aux->info)->vidas--;
    }

    Rectangle rec3 = {
        .height = ((Block*)aux->info)->height,
        .width = 0,
        .x = ((Block*)aux->info)->x + ((Block*)aux->info)->width,
        .y = ((Block*)aux->info)->y,
    };
    if(CheckCollisionCircleRec(vec, ball->radius, rec3))
    {
        ball->facing_right_left = 1;
        ((Block*)aux->info)->vidas--;
    }

    Rectangle rec4 = {
        .height = ((Block*)aux->info)->height,
        .width = 0,
        .x = ((Block*)aux->info)->x,
        .y = ((Block*)aux->info)->y,
    };
    if(CheckCollisionCircleRec(vec, ball->radius, rec4))
    {
        ball->facing_right_left = 2;
        ((Block*)aux->info)->vidas--;
    }

    if(((Block*)aux->info)->vidas == 0)
    {
        ((Block*)aux->info)->y = -100;
        if(((Block*)aux->info)->alive == 1)
        {
            total_blocos--;
            personagem->pontos += 1;
            ((Block*)aux->info)->alive = 0;
        }
    }
}

void blockBreaker(int *menu_opc, int *opc_jogo, Character *personagem, Screen tela, Character *ball, List *blocos, int *total_blocos, List *scoreboard)
{
    Node *aux = blocos->start;

    if(personagem->start == 1)
    {
        resetBlocks(blocos, tela);
        *total_blocos = qtd_blocos;
        personagem->speedX = 5;
        personagem->vidas = 3;
        personagem->y = 650;
        personagem->pontos = 0;
        ball->x = personagem->x + personagem->width/2;
        ball->y = personagem->y - personagem->height;
        ball->moving = 0;
        ball->facing_up_down = 1;
        ball->facing_right_left = 1;
        personagem->start = 0;
    }

    /*
        1 = Up
        2 = Down
        1 = Right
        2 = Left
    */

    if(ball->moving == 1)
    {
        if(ball->facing_up_down == 1)
        {
            ball->y -= ball->speedY;
        }
        else if(ball->facing_up_down == 2)
        {
            ball->y += ball->speedY;
        }

        if(ball->facing_right_left == 1)
        {
            ball->x += ball->speedX;
        }
        else if(ball->facing_right_left == 2)
        {
            ball->x -= ball->speedX;
        }

        if(ball->x <= 0)
        {
            ball->facing_right_left = 1;
        }
        else if(ball->x >= tela.width)
        {
            ball->facing_right_left = 2;
        }

        if(ball->y <= 0)
        {
            ball->facing_up_down = 2;
        }
        else if(ball->y >= tela.height)
        {
            ball->moving = 0;
            ball->x = personagem->x + personagem->width/2;
            ball->y = personagem->y - personagem->height;
            personagem->vidas--;
        }

        if(checkBallPlayer(personagem, ball))
        {
            ball->facing_up_down = 1;
            if(personagem->facing_right_left == 1)
            {
                ball->facing_right_left = 1;
            }
            else if(personagem->facing_right_left == 2)
            {
                ball->facing_right_left = 2;
            }
        }
    }

    

    if(IsKeyDown(KEY_RIGHT))
    {
        personagem->x += personagem->speed;
        if(ball->moving == 0)
        {
            ball->x += personagem->speed;
        }
        personagem->facing_right_left = 1;
    }
    else if(IsKeyDown(KEY_LEFT))
    {
        personagem->x -= personagem->speed;
        if(ball->moving == 0)
        {
            ball->x -= personagem->speed;
        }
        personagem->facing_right_left = 2;
    }

    if(personagem->x <= 0)
    {
        personagem->x = 0;
        if(ball->moving == 0)
        {
            ball->x = personagem->x + personagem->width/2;
        }
    }
    else if(personagem->x + personagem->width > tela.width)
    {
        personagem->x = tela.width - personagem->width;
        if(ball->moving == 0)
        {
            ball->x = personagem->x + personagem->width/2;
        }
    }

    if(IsKeyPressed(KEY_SPACE) && ball->moving == 0)
    {
        ball->moving = 1;
    }

    if(personagem->vidas == 0 || total_blocos == 0)
    {
        personagem->start = 1;
        *menu_opc = 0;
        *opc_jogo = 0;
        Scoreboard *novo = (Scoreboard*)malloc(sizeof(Scoreboard));
        novo->score = personagem->pontos;
        strcpy(novo->nome, "Block Breaker");
        addEndList(scoreboard, novo);
    }

    int blocos_vivos = 0;
    while(aux != NULL)
    {
        DrawRectangle(
            ((Block*)aux->info)->x,
            ((Block*)aux->info)->y,
            ((Block*)aux->info)->width,
            ((Block*)aux->info)->height,
            BLACK);

        checkBallBlock(ball, aux, total_blocos, personagem);
        
        aux = aux->next;
    }
    
    DrawRectangle(personagem->x, personagem->y, personagem->width, personagem->height, BLACK);
    DrawCircle(ball->x, ball->y, ball->radius, RED);
    DrawText(TextFormat("Vidas: %d", personagem->vidas), 10, tela.height-60, 30, BLACK);
    DrawText(TextFormat("Pontuação: %d", personagem->pontos), 10, tela.height-30, 30, BLACK);
}

/* Racing */
void createLines(List *lines)
{
    int posX = 30;
    int qtd = 1;
    for(int i = 0; i < 20; i++)
    {
        Vehicle *line = (Vehicle*)malloc(sizeof(Vehicle));
        line->height = 30;
        line->width = 90;
        line->x = posX;
        line->speed = 3;

        addEndList(lines, (void*)line);

        if(qtd%2 == 0)
        {
            posX += 140;
        }
        qtd++;
    }
}

void createVeiculos(List *veiculos)
{
    int posX = 1280;
    int rng;
    for(int i = 0; i < 7; i++)
    {
        Vehicle *veiculo = (Vehicle*)malloc(sizeof(Vehicle));
        veiculo->height = 50;
        veiculo->width = 90;
        veiculo->x = posX;
        veiculo->speed = 10;
        
        rng = rand()%3 + 1;
        if(rng == 1)
        {
            veiculo->y = 210;
        }
        else if(rng == 2)
        {
            veiculo->y = 350;
        }
        else if(rng == 3)
        {
            veiculo->y = 490;
        }

        addEndList(veiculos, (void*)veiculo);
        posX += 250;
    }
}

bool checkCarCrash(Vehicle *carro, Node *aux)
{
    Rectangle rec1 = {
        .height = carro->height,
        .width = carro->width,
        .x = carro->x,
        .y = carro->y,
    };
    Rectangle rec2 = {
        .height = ((Vehicle*)aux->info)->height,
        .width = ((Vehicle*)aux->info)->width,
        .x = ((Vehicle*)aux->info)->x,
        .y = ((Vehicle*)aux->info)->y,        
    };

    CheckCollisionRecs(rec1, rec2);
}

void resetVeiculos(List *veiculos)
{
    int posX = 1280;
    int rng;
    Node *aux = veiculos->start;
    while(aux != NULL)
    {
        ((Vehicle*)aux->info)->x = posX;
        
        rng = rand()%3 + 1;
        if(rng == 1)
        {
            ((Vehicle*)aux->info)->y = 210;
        }
        else if(rng == 2)
        {
            ((Vehicle*)aux->info)->y = 350;
        }
        else if(rng == 3)
        {
            ((Vehicle*)aux->info)->y = 490;
        }

        posX += 250;
        aux = aux->next;
    }
}

void racing(List *veiculos, Vehicle *carro, Screen tela, int *menu_opc, int *opc_jogo, List *scoreboard, Enviroment *ambiente, List *lines)
{
    if(IsKeyPressed(KEY_UP))
    {
        if(carro->y > 210)
        {
            carro->y -= 140;
        }
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        if(carro->y < 490)
        {
            carro->y += 140;
        }
    }
    if(IsKeyDown(KEY_RIGHT))
    {
        carro->x += carro->speed;
        if(carro->x >= tela.width)
        {
            carro->x = tela.width - carro->width;
        }
    }
    if(IsKeyDown(KEY_LEFT))
    {
        carro->x -= carro->speed;
        if(carro->x <= 0)
        {
            carro->x = 0;
        }
    }

    /*
        Lanes
        1 = 210
        2 = 350
        3 = 490
    */
    int rng;
    Node *aux = veiculos->start;
    while(aux != NULL)
    {
        ((Vehicle*)aux->info)->x -= ((Vehicle*)aux->info)->speed;

        rng = rand()%3 + 1;
        if(((Vehicle*)aux->info)->x + ((Vehicle*)aux->info)->width <= 0)
        {
            if(rng == 1)
            {
                ((Vehicle*)aux->info)->y = 210;
            }
            else if(rng == 2)
            {
                ((Vehicle*)aux->info)->y = 350;
            }
            else if(rng == 3)
            {
                ((Vehicle*)aux->info)->y = 490;
            }
            ((Vehicle*)aux->info)->x = 1440;
        }
        
        DrawRectangle(
            ((Vehicle*)aux->info)->x,
            ((Vehicle*)aux->info)->y,
            ((Vehicle*)aux->info)->width,
            ((Vehicle*)aux->info)->height,
            DARKGREEN);

        if(checkCarCrash(carro, aux))
        {
            *menu_opc = 0;
            *opc_jogo = 0;
            carro->x = 70;
            carro->y = 350;
            resetVeiculos(veiculos);

            Scoreboard *novo = (Scoreboard*)malloc(sizeof(Scoreboard));
            novo->score = pontuacao;
            strcpy(novo->nome, "Racing");
            addEndList(scoreboard, novo);

            cont = 0;
            pontuacao = 0;
        }
        else
        {
            cont += ambiente->speed;
            if(cont == 500)
            {
                cont = 0;
                pontuacao++;
            }
        }

        aux = aux->next;
    }    

    DrawRectangle(
        carro->x,
        carro->y,
        carro->width,
        carro->height,
        RED);
    DrawRectangle(0, 150, 1280, 30, BLACK);
    DrawRectangle(0, 570, 1280, 30, BLACK);
    
    Node *aux_line = lines->start;
    while(aux_line != NULL)
    {
        DrawRectangle(
            ((Vehicle*)aux_line->info)->x,
            290,
            ((Vehicle*)aux_line->info)->width,
            ((Vehicle*)aux_line->info)->height,
            GOLD);
        ((Vehicle*)aux_line->info)->x -= ((Vehicle*)aux_line->info)->speed;
        if(((Vehicle*)aux_line->info)->x + ((Vehicle*)aux_line->info)->width <= 0)
        {
            ((Vehicle*)aux_line->info)->x = tela.width + 30;
        }

        aux_line = aux_line->next;
        DrawRectangle(
            ((Vehicle*)aux_line->info)->x,
            430,
            ((Vehicle*)aux_line->info)->width,
            ((Vehicle*)aux_line->info)->height,
            GOLD);
        ((Vehicle*)aux_line->info)->x -= ((Vehicle*)aux_line->info)->speed;
        if(((Vehicle*)aux_line->info)->x + ((Vehicle*)aux_line->info)->width <= 0)
        {
            ((Vehicle*)aux_line->info)->x = tela.width + 30;
        }

        aux_line = aux_line->next;
    }
    DrawText(TextFormat("Pontuação: %d", pontuacao), 10, 10, 30, BLACK);
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
        .width = 100,
        .height = 10,
        .radius = 25,
        .vidas = 3,
        .speed = 10,
        .start = 1,
    };

    Character ball = {
        .radius = 10,
        .x = 0,
        .y = 0,
        .speed = 5,
        .speedX = 5,
        .speedY = 10,
    };

    Enviroment ambiente = {
        .gravity = 0,
        .speed = 5,
    };

    Vehicle carrinho = {
        .height = 50,
        .width = 70,
        .x = 70,
        .y = 350,
        .speed = 5,
    };

    InitWindow(tela.width, tela.height, "Arcade");
    SetTargetFPS(60);

    List *scoreboard = createList();
    List *obstaculos = createList();
    List *blocos = createList();
    List *veiculos = createList();
    List *lines = createList();

    createLines(lines);

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

    createBlocks(blocos);
    createVeiculos(veiculos);

    Image logo_iftm = LoadImage("assets/logoIFTM.png");
    ImageResize(&logo_iftm, 200, 200);
    Texture2D texture = LoadTextureFromImage(logo_iftm);
    UnloadImage(logo_iftm);

    Image wallpaper = LoadImage("assets/Arcade.png");
    ImageResize(&wallpaper, 1280, 720);
    Texture2D background = LoadTextureFromImage(wallpaper);
    UnloadImage(wallpaper);

    srand(time(NULL));
    int games[5];
    int menu_opc = 0;
    int opc_jogo = 0;
    int total_blocos;
    
    float timePlayed = 0.0f;
    InitAudioDevice();
    Music music = LoadMusicStream("assets/PrayerInC_8bit.mp3");
    PlayMusicStream(music);

    while(!WindowShouldClose() && menu_opc != 4)
    {
        UpdateMusicStream(music);
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
        if (timePlayed > 1.0f)
        {
            timePlayed = 1.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(menu_opc == 0)
        {
            DrawTexture(background, 0, 0, RAYWHITE);
            DrawRectangle(860, 700, 400, 12, LIGHTGRAY);
            DrawRectangle(860, 700, (int)(timePlayed*400.0f), 12, RED);
            DrawRectangleLines(860, 700, 400, 12, GRAY);
            DrawTexture(texture, 10, 10, RAYWHITE);
            menu_opc = menu();
        }

        if(menu_opc == 1)
        {
            if(opc_jogo == 0)
            {
                DrawTexture(background, 0, 0, RAYWHITE);
                DrawRectangle(860, 700, 400, 12, LIGHTGRAY);
                DrawRectangle(860, 700, (int)(timePlayed*400.0f), 12, RED);
                DrawRectangleLines(860, 700, 400, 12, GRAY);
                DrawTexture(texture, 10, 10, RAYWHITE);
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
            else if(opc_jogo == 3)
            {
                /* Racing */
                racing(veiculos, &carrinho, tela, &menu_opc, &opc_jogo, scoreboard, &ambiente, lines);
            }
            else if(opc_jogo == 4)
            {
                /* Block Breaker */
                blockBreaker(&menu_opc, &opc_jogo, &personagem, tela, &ball, blocos, &total_blocos, scoreboard);
            }
        }
        else if(menu_opc == 2)
        {
            DrawTexture(background, 0, 0, RAYWHITE);
            int posy = 200;
            Node *aux = scoreboard->start;
            DrawText(TextFormat("LeaderBoard"), 420, 50, 70, WHITE);

            while(aux != NULL)
            {   
                DrawText(TextFormat("Player - %s: %d", ((Scoreboard*)aux->info)->nome, ((Scoreboard*)aux->info)->score), 10, posy, 30, WHITE);

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
            DrawTexture(background, 0, 0, RAYWHITE);
            DrawText(TextFormat("Programa criado utilizando a biblioteca "), 10, 10, 30, WHITE);
            DrawText(TextFormat("Raylib "), 620, 10, 30, BLUE);
            DrawText(TextFormat("em linguagem "), 10, 40, 30, WHITE);
            DrawText(TextFormat("C "), 210, 40, 30, BLUE);
            DrawText(TextFormat("para a matéria de Extensão 3"), 240, 40, 30, WHITE);
            DrawText(TextFormat("Alunos: "), 10, 100, 30, WHITE);
            DrawText(TextFormat("Davi de Oliveira Chaves"), 10, 130, 30, BLUE);
            DrawText(TextFormat("Luiz Alberto Cury Andalécio"), 10, 160, 30, RED);
            
            if(IsKeyPressed(KEY_SPACE))
            {
                menu_opc = 0;
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}