#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>

#define WIDTH_OF_SCREEN 100
#define HEIGHT_OF_SCREEN 40
#define WIN 70

using namespace std;
HANDLE console =GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int Y[3];
int X[3];
int F[3];
char car[4][4]={' ','+',' ',
                 '+','+','+','+',
                 ' ','+',' ',
                  '+','+','+','+' };
int carPos = WIN/2;
int score =0;
void gotoxy(int x,int y)
{
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console,CursorPosition);
}
void setCursor(bool visible , DWORD size)
{
    if(size==0)
        size=20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible=visible;
    lpCursor.dwSize=size;
    SetConsoleCursorInfo(console,&lpCursor);

}
void drawBorder(){
for(int i=0; i<HEIGHT_OF_SCREEN; i++){
    for(int j=0; j<17; j++)
    {
        gotoxy(0+j,i); cout<<"+";
        gotoxy(WIN-j,i);
         cout<<"+";

    }
}
for(int i=0; i<HEIGHT_OF_SCREEN;i++){
    gotoxy(WIDTH_OF_SCREEN,i);
    cout<<"+";
}
}
void general(int ind){
    X[ind]=17+rand()%(33);
}
void draw(int ind){
if(F[ind]==true){
    gotoxy(X[ind],Y[ind]);
    cout<<"@@";
    gotoxy(X[ind],Y[ind]+1);
    cout<<"@@";
    gotoxy(X[ind],Y[ind+2]);
    cout<<"@@";
    gotoxy(X[ind],Y[ind+3]);
    cout<<"@@";
}
}
void erase(int ind){
if(F[ind]==true){
    gotoxy(X[ind], Y[ind]);
    cout<<"    ";
    gotoxy(X[ind], Y[ind]+1);
    cout<<"    ";
    gotoxy(X[ind], Y[ind]+2);
    cout<<"    ";
     gotoxy(X[ind], Y[ind]+3);
    cout<<"    ";
}
}
void reset(int ind)
{
    erase(ind);
    Y[ind]+1;
    general(ind);
}
void DrawingCar(){
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gotoxy(j+carPos,i+22);cout<<car[i][j];
        }
    }
}

void erase(){
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        gotoxy(j+carPos,i+22);
        cout<<"  ";
    }
}
}
int collision(){
if(Y[0]+4 >= 23)
{
    if(X[0]+4 - carPos >=0 && X[0]+4 - carPos<9)
    {
        return 1;
    }
}
return 0;
}

void gameover()
{
    system("cls");
    cout<<endl;
    cout<<"\t\t-------------------"<<endl;
    cout<<"\t\t-----Game Over-----"<<endl;
    cout<<"\t\t-------------------"<<endl<<endl;
    cout<<"\t\tPress any key to go to menu.";
    getch();
}
void updatedScore(){
    gotoxy(WIN+7,5);
    cout<<"Score is : "<<score<<endl;
}

void instructions(){
 system("cls");
 cout<<"INSTRUCTIONS";
 cout<<"\n-----------";
 cout<<"\n Avoid cars for moving left or right";
 cout<<"\n\n press 'a' to move left";
  cout<<"\n press 'd' to move right";
   cout<<"\n press 'escape' to exit";
   cout<<"\n\nPress any key to go to menu.";
   getch();
}

void play()
{
    carPos= -1 + WIN_WIDTH;
    score = 0;
    F[0]=1;
    F[1]=0;
    Y[0]= Y[1]=1;
     system("cls");
     drawBorder();
     updateScore();
     general(0);
     general(1);

     gotoxy(WIN +7,2);
     cout<<"Car racing game";
     gotoxy(WIN+6,4);
     cout<<"%%%%%%%%%%%";
     gotoxy(WIN+6,6);
     cout<<"-----------";
     gotoxy(WIN+7,12);
     cout<<"Control";
     gotoxy(WIN+7,13);
     cout<<"------------";
     gotoxy(WIN+2,14);
     cout<<"A Key-LEFT";

     gotoxy(WIN+2,15);
     cout<<"D Key-RIGHT";

     gotoxy(18,5);
     cout<<"Press any key to start";
     getch();
     gotoxy(18,5);
     cout<<"                  ";
     while(1)
     {
         if(kbhit())
         {
             char ch=getch();
             if(ch=='a'||ch=='A')
             {
                 if(carPos>18)
                    carPos-=4;
             }
             if(ch=='d'||ch=='D')
             {
                 if(carPos<50)
                    carPos+4;
             }
             if(ch==27){
                break;
             }
         }
         drawingCar();
         drawEnemy(0);
         drawEnemy(1);
         if(collision()==1){
            gameover();
            return;
         }
         Sleep(50);
         erase();
         eraseEnemy(0);
         eraseEnemy(1);

         if(Y[0]==10)
            if(F[1]==0)
            F[1]=1;
         if(F[0]==1)
            Y[0]+=1;
         if(F[1]==1)
            Y[1]+=1;
         if(Y[0]>HEIGHT_OF_SCREEN-4)
         {
             resetEnemy[0];
             score++;
             updatedScore();
         }
         if(Y[1]>HEIGHT_OF_SCREEN-4){
            resetEnemy(1);
            score++;
            updateScore();
         }
     }

}
    int main()
    {
        setCursor(0,0);
        srand((unsigned)time(NULL));

        do{
            system("cls");
            gotoxy(10,5);
            cout<<"------------";
            gotoxy(10,6);
            cout<<"@@        Car Racing Game      @@";
            gotoxy(10,7);
            cout<<"-------------";
            gotoxy(10,9);
            cout<<"1.Start";
            gotoxy(10,10);
            cout<<"2.Instructions";
            gotoxy(10,11);
            cout<<"3.Quit the game";
            gotoxy(10,13);
            cout<<"select option";
            char op=getche();
            if(op=='1') play();
            else if(op=='2') instructions();
            else if(op=='3') exit(0);
        }while(1);
        return 0;
        }

