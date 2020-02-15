#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

void homeScreen();
void startGame(int);
void inGrid();
void printGrid();
void delay(int);
void move();
void copy(int, int);
void switchDir(int);
void food();
int kbhit();
void gameOver();

char a[27][27];
int dir = 'd', len = 3, score = 0, speed = 200, acc;

struct coord{
    int x;
    int y;
}s[20], head = {13, 3}, f;

int main(){
    
    srand(time(0));
    
    inGrid();
    homeScreen();
    
    return 0;
}


void homeScreen(){
    
    int choice, ch;
    
    system("clear");
    
    printf("\v\vTic-Tac-Toe");
    printf("\n1. New Game\n2. Quit\n\nEnter Choice : ");
    scanf(" %d", &choice);
    
    system("clear");
    
    if(choice == 1){
        printf("\vDificulty level\n1.Easy\n2.Medium\n3.Difficult");
        scanf("%d", &ch);
        system("clear");
        startGame(ch);
    }
    
 //   else if(choice == 2)
  //      howToPlay();
    
    else
        exit(0);
}

void startGame(int s){
    
    int prevDir;
    
    switch(s){
            
        case 1:
            acc = 3;
            break;
            
        case 2:
            acc = 5;
            break;
            
        case 3:
            acc = 10;
            break;
    }
    
    while(1){
        
        prevDir = dir;
        
        if(kbhit())
            dir = getchar();
        
        switchDir(prevDir);
        move();
        printGrid();
        delay(speed);
    }
}

void switchDir(int prevDir){
    
    switch(dir){
        case 'a':
            head.y--;
            break;
            
        case 's':
            head.x++;
            break;
            
        case 'd':
            head.y++;
            break;
            
        case 'w':
            head.x--;
            break;
            
        default:
            dir = prevDir;
            switchDir(prevDir);
    }

}


void delay(int mSec){
    
    int sec = mSec*1000;
    
    clock_t time = sec + clock();
    
    while (time > clock());
    
}

void move(){
    
    if(a[head.x][head.y] == 'o' || a[head.x][head.y] == 'X')
        gameOver();
    
    else if(a[head.x][head.y] == '*'){
        f = head;
        len++; score++;
        food();
        speed = speed - acc;
    }
    
    a[head.x][head.y] = 'O';
    a[s[0].x][s[0].y] = 'o';
    a[s[len-1].x][s[len-1].y] = ' ';
    
    for(int i = len-2; i >= 0; i--)
        copy(i+1, i);
    
    s[0].x = head.x;
    s[0].y = head.y;
    
    if(f.x == s[len-1].x && f.y == s[len-1].y){
        f.x = 0;
        f.y = 0;
    }
    
    a[f.x][f.y] = 'O';

  //  for(int i = 0; i <= len; i++)
   //     printf("\n%d. %d %d %c", i, s[i].x, s[i].y, a[s[i].x][s[i].y]);
    
    
    
   /* a[tail.x][tail.y] = ' ';
    
    if(a[tail.x][tail.y-1] == 'o')
        tail.y--;
    
    else if(a[tail.x-1][tail.y] == 'o')
        tail.x--;
    
    else if(a[tail.x+1][tail.y] == 'o')
        tail.x++;
    
    else if(a[tail.x][tail.y+1] == 'o')
        tail.y++;*/
}


void copy(int i, int j){
    
    s[i].x = s[j].x;
    s[i].y = s[j].y;
    
}

void food(){
    
    int x, y;
    
    x = 1 + rand()%25;
    y = 1 + rand()%25;
    
    if(a[x][y] == 'o')
        food();
    
    a[x][y] = '*';
}


void printGrid(){
    
    system("clear");
    printf("\v\v\v\v\v");
    
    for(int i = 0; i < 27; i++){
        
        printf("\t\t\t\t\t");
        
        for(int j = 0; j < 27; j++)
            printf("%c ", a[i][j]);
        
        printf("\n");
    }
}

void inGrid(){
    
    for(int i = 0; i < 27; i ++){
        for(int j = 0; j < 27; j++){
            if(i == 0 || j == 0 || i == 26 || j == 26)
                a[i][j] = 'X';
            
            else
                a[i][j] = ' ';
        }
    }
    
    for(int i = 1, j = 13; i < 4; i++){
        a[j][i] = 'o';
        s[len-i].x = j;
        s[len-i].y = i;
    }
    
    a[13][3] = 'O';
    
    food();
}



int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

void gameOver(){
    
    system("clear");
    
    printf("\v\v\v\v\v\t\t\t\tGame Over\n\t\t\t\t\tYour Score : %d\v\v\v\v\v\nc", score);
    
    
    exit(0);
}






















