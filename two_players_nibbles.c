#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

#define N 28
#define M 80

FILE* f;
int i, j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs, a, b, var, dir, score, HighScore, Speed;
int x2, y2, Gy2, Head2, Tail2, var2, dir2, score2;

void snakeInitialization()
{

    f = fopen("highscore.txt", "r");
    if (f == NULL)
        printf("fopen failed :(\n\nlotfan yek file ba name 'highscore.txt' besazid");
    else
        fscanf(f, "%d", &HighScore);

    fclose(f);


    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            Field[i][j] = 0;
        }
    }

    x = N / 4; y = M / 2; Gy = y; Head = 5; Tail = 1;  Game = 0, Frogs = 0, dir = 'd', score = 0, Speed = 99, dir2 = 'd';
    x2 = N / 1.5; y2 = M / 2; Gy2 = y2; Head2 = 1005; Tail2 = 1001; score2 = 0;
    for (i = 0; i < Head; i++)
    {
        Gy++;
        Field[x][Gy - Head] = i + 1;
    }

    for (i = 1000; i < Head2; i++)
    {
        Gy2++;
        Field[x2][Gy2 - 5] = i + 1;
    }
}

void print()
{
    //Frame
    for (i = 0; i <= M + 1; i++)  
    {
        if (i == 0)
        {
            printf("%c", 201);
        }
        else if (i == M + 1)
        {
            printf("%c", 187);
        }
        else
        {
            printf("%c", 205);
        }
    }

    printf("   Score1:%d"  RED " Score2:%d" COLOR_RESET " HighScore: %d", score,score2, HighScore);
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%c", 186);
        // note this place

        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == 0) printf(" "); //printing game space

            if (Field[i][j] > 0 && Field[i][j] != Head && Field[i][j] < 1000) printf("%c", 176); //badane snake
            if (Field[i][j] == Head) printf("%c", 178); //head-e snake

           if (Field[i][j] > 1000 && Field[i][j] != Head2) printf(RED "%c" COLOR_RESET, 176); //badane snake dovom
           if (Field[i][j] == Head2) printf(RED "%c" COLOR_RESET, 178); //head-e snake dovom


            if (Field[i][j] == -1) printf(GREEN "%c" COLOR_RESET, 15); // priting frogs
            if (j == M - 1) printf("%c\n", 186);
        }
    }
    //edn frame
    for (i = 0; i <= M + 1; i++) {
        if (i == 0) {
            printf("%c", 200);
        }
        else if (i == M + 1) {
            printf("%c", 188);
        }
        else {
            printf("%c", 205);
        }
    }

}

ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

Random()
{
    srand(time(0));
    a = 1 + rand() % 28;
    b = 1 + rand() % 78;
    if (Frogs == 0 && Field[a][b] == 0)
    {
        Field[a][b] = -1;
        Frogs = 1;
        if (Speed > 10 && score != 0)
            Speed -= 5;
    }

}

int getch_noblock()
{
    if (_kbhit())

        return (_getch());
       
    else
        return (-1);
}

void endgame()
{
    printf("\a");
    Sleep(1500);
    system("Cls");

    if (score > HighScore)
    {
        printf("\t\t\tNew recordes %d!!!!!!\n\n", score);
        system("puse");
        f = fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }
    if (score2 > HighScore)
    {
        printf("\t\t\tNew recordes %d!!!!!!\n\n", score2);
        system("puse");
        f = fopen("highscore.txt", "w");
        fprintf(f, "%d", score2);
        fclose(f);
    }
    system("Cls");

    printf("\t\t\t\tGAME OVER!\n\n");
    printf("\t\t\t   Score1:%d"  RED " Score2:%d" COLOR_RESET " Last HighScore: %d", score, score2, HighScore);
    printf("\n\nPress ENTER to play agin and ESC to exit...");

    while (1)
    {
        var = getch_noblock();
        if (var == 13) //code askie-e enter
        {
            Game = 0;
            snakeInitialization();
            break;
        }
        else if (var == 27)
        {
            Game = 1;
            break;
        }

    }
    system("Cls");
}

void movment()
{
    var = getch_noblock();
    var = tolower(var); //ba in dastur khamush ya roshan budan capslock mohem nist

    if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5))
        dir = var;

    if (dir == 'd')
    {
        y++;

        if (Field[x][y] != 0 && Field[x][y] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (y == M - 1)  //hale moshkele biroon raftan az safhe va vared shodan az tarafe moghabel
            y = 0;

        if (Field[x][y] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail -= 2;  // afzayeshe toole dome maar
            score += 5; //afzayeshe emtiaz
        }

        Head++;
        Field[x][y] = Head;
    }

    if (dir == 'a')
    {
        y--;

        if (Field[x][y] != 0 && Field[x][y] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (y == 0)
            y = M - 1;

        if (Field[x][y] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail -= 2;  // afzayeshe toole dome maar
            score += 5; //afzayeshe emtiaz
        }


        Head++;
        Field[x][y] = Head;
    }

    if (dir == 'w')
    {
        x--;

        if (Field[x][y] != 0 && Field[x][y] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (x == 0)
            x = N - 1;

        if (Field[x][y] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail -= 2;  // afzayeshe toole dome maar
            score += 5; //afzayeshe emtiaz
        }

        Head++;
        Field[x][y] = Head;
    }

    if (dir == 's')
    {
        x++;

        if (Field[x][y] != 0 && Field[x][y] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }
        if (x == N - 1)
            x = 0;

        if (Field[x][y] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail -= 2;  // afzayeshe toole dome maar
            score += 5; //afzayeshe emtiaz
        }

        Head++;
        Field[x][y] = Head;
    }

}

void movment2()
{
    var2 = getch_noblock();
    //var2 = tolower(var2); //ba in dastur khamush ya roshan budan capslock mohem nist

    //if (((var2 == 'd' || var2 == 52) || (var2 == 56 || var2 == 53)) && (abs(dir2 - var2) > 2))
    
        switch (var2)
        {
        case -32: //This value is returned by all arrow key. So, we don't want to do something.
            break;
        case 72:
            if (dir2 != 's')
            dir2 = 'w';
            break;
        case 75:
            if (dir2 != 'd')
            dir2 = 'a';
            break;
        case 77:
            if (dir2 != 'a')
            dir2 = 'd';
            break;
        case 80:
            if (dir2 != 'w')
            dir2 = 's';
            break;
            // default:
            //  printf("INVALID INPUT!");
            // break;
        }
         

    if (dir2 == 'd')
    {
        y2++;

        if (Field[x2][y2] != 0 && Field[x2][y2] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (y2 == M - 1)  //hale moshkele biroon raftan az safhe va vared shodan az tarafe moghabel
            y2 = 0;

        if (Field[x2][y2] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail2 -= 2;  // afzayeshe toole dome maar
            score2 += 5; //afzayeshe emtiaz
        }

        Head2++;
        Field[x2][y2] = Head2;
    }

    if (dir2 == 'a')
    {
        y2--;

        if (Field[x2][y2] != 0 && Field[x2][y2] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (y2 == 0)
            y2 = M - 1;

        if (Field[x2][y2] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail2 -= 2;  // afzayeshe toole dome maar
            score2 += 5; //afzayeshe emtiaz
        }


        Head2++;
        Field[x2][y2] = Head2;
    }

    if (dir2 == 'w')
    {
        x2--;

        if (Field[x2][y2] != 0 && Field[x2][y2] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }

        if (x2 == 0)
            x2 = N - 1;

        if (Field[x2][y2] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail2 -= 2;  // afzayeshe toole dome maar
            score2 += 5; //afzayeshe emtiaz
        }

        Head2++;
        Field[x2][y2] = Head2;
    }

    if (dir2 == 's')
    {
        x2++;

        if (Field[x2][y2] != 0 && Field[x2][y2] != -1) //na dar fazaye khali hast na roye frog pas roye badane khodash ast
        {
            endgame();
        }
        if (x2 == N - 1)
            x2 = 0;

        if (Field[x2][y2] == -1) //chek kardan baraye khorde shodane ghourbaghe
        {
            Frogs = 0;  //sakhtane yek ghurbagheye digar
            Tail2 -= 2;  // afzayeshe toole dome maar
            score2 += 5; //afzayeshe emtiaz
        }

        Head2++;
        Field[x2][y2] = Head2;
    }

}

void TailRemove()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == Tail)
                Field[i][j] = 0;
        }
    }
    Tail++;
}

void TailRemove2()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == Tail2)
                Field[i][j] = 0;
        }
    }
    Tail2++;
}


int main()
{
    snakeInitialization();

    while (Game == 0)
    {
        print();
        ResetScreenPosition();
        Random();
        movment();
        TailRemove();
        movment2();
        TailRemove2();
        Sleep(Speed);
    }
    return 0;
}