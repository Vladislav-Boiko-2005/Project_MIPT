#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <vector>



using namespace std;



int line_to_x=25;
int line_to_y=25;
char mas[25][25];
int chet_time_bonus=0;
int speed=0;
int time_no_bonus=0;




void MoveXY (int x, int y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}




class bonus
{
    public:
    bonus ()
    {
        do{
        x_cord=rand()%(line_to_x-2)+1;
        y_cord=rand()%(line_to_y-2)+1;
        }
        while (mas[y_cord][x_cord]!=' ');
    }
    void new_bon ()
    {
        do{
        x_cord=rand()%(line_to_x-2)+1;
        y_cord=rand()%(line_to_y-2)+1;
        }
        while (mas[y_cord][x_cord]!=' ');
    }
    void create_bonus ()
    {
        mas[y_cord][x_cord]=ch_bonus;
    }
    int x_cord;
    int y_cord;
    char ch_bonus;
};



void create_pole (bonus&bon)
{
    MoveXY(0,0);
    for (int i=0;i<line_to_x;i++)
    {
        mas[0][i]='#';
        mas[line_to_y-1][i]='#';
    }
    for (int i=0;i<line_to_y;i++)
    {
        mas[i][0]='#';
        mas[i][line_to_x-1]='#';
    }
    for (int i=1;i<line_to_y-1;i++)
    {
        for (int j=1;j<line_to_x-1;j++)
            mas[i][j]=' ';
    }
    if (chet_time_bonus>0)
    {
        bon.create_bonus();
    }
}





void create_pole ()
{
    MoveXY(0,0);
    for (int i=0;i<line_to_x;i++)
    {
        mas[0][i]='#';
        mas[line_to_y-1][i]='#';
    }
    for (int i=0;i<line_to_y;i++)
    {
        mas[i][0]='#';
        mas[i][line_to_x-1]='#';
    }
    for (int i=1;i<line_to_y-1;i++)
    {
        for (int j=1;j<line_to_x-1;j++)
            mas[i][j]=' ';
    }
}



void print ()
{
    for (int i=0;i<line_to_y;i++)
    {
        for (int j=0;j<line_to_x;j++)
        {
            cout<<mas[i][j]<<' ';
        }
        cout<<'\n';
    }
    MoveXY(0,0);
}



struct part_snake
{
    part_snake ()
    {
        this_x=1;
        this_y=1;
        proh_x=1;
        proh_y=1;
    }
    void moving_part( part_snake&pred)
    {
        proh_x=this_x;
        proh_y=this_y;
        this_x=pred.proh_x;
        this_y=pred.proh_y;
    }
    int this_x;
    int this_y;
    int proh_x;
    int proh_y;
};



class snake
{
public:
    snake()
    {
        vect.resize(8);
    }
    void moving_snake (int n);
    void print_snake();
    void kill_snake();
    void long_snake ();
    void size_long_smol();
    vector <part_snake> vect;
private:
    char char_snake='*';
};

void::snake::size_long_smol()
{
    vect.resize(vect.size()-1);
    if (vect.size()==0)
        exit(0);
}

void snake:: long_snake ()
{
    part_snake n;
    n.this_x=vect[vect.size()-1].proh_x;
    n.this_y=vect[vect.size()-1].proh_y;
    vect.push_back(n);
}


void snake::kill_snake()
{
    vect.resize(0);
    vect.resize(8);
    create_pole();
    print_snake();
    print();
}


void snake:: moving_snake (int n)
    {
        vect[0].proh_x=vect[0].this_x;
        vect[0].proh_y=vect[0].this_y;
        bool flag=0;
        switch (n)
        {
        case 72://///////////   лево
        {
            vect[0].this_y--;
            flag=1;
            break;
        }
        case 75 : ////////////////  вверх
        {
            vect[0].this_x--;
            flag=1;
            break;
        }
        case 80://////////////////   вниз
        {
            vect[0].this_y++;
            flag=1;
            break;
        }
        case 77: //////////////  вправо
        {
            vect[0].this_x++;
            flag=1;
            break;
        }
        }
        if ((mas[vect[0].this_y][vect[0].this_x]=='#')||(mas[vect[0].this_y][vect[0].this_x]=='*'))
        {
            kill_snake();
            return;
        }
        if (mas[vect[0].this_y][vect[0].this_x]=='+')
        {
            long_snake();
            chet_time_bonus=0;
        }
        if (mas[vect[0].this_y][vect[0].this_x]=='@')
        {
            if (speed<100)
                speed+=10;
            chet_time_bonus=0;
        }
        if (flag)
        {
            for (int i=1;i<vect.size();i++)
            {
                vect[i].moving_part(vect[i-1]);
            }
        }
        return;
    }


void snake::print_snake()
{
    MoveXY(0,line_to_y+1);
    for (int i=0;i<vect.size();i++)
    {
        mas[vect[i].this_y][vect[i].this_x]=char_snake;
    }
    MoveXY(0,0);
}


void random_bonus (bonus& bon)
{
    if (time_no_bonus>25)
    {
        time_no_bonus=0;
        bon.new_bon();
        int random =rand()%2;
        switch (random)
        {
            case 0:
                bon.ch_bonus='+';
                break;
            case 1:
                bon.ch_bonus='@';
                break;
        }
        chet_time_bonus=25;
    }
}



int main ()
{
    int time_kill_long=250;
    srand(time(NULL));
    create_pole();
    snake sn;
    sn.print_snake();
    print();
    int c=getch();;
    bonus bon;
    while (true)
    {
        if (_kbhit())
        {
            c=getch();
        }
        else
        {
            if (c==27)
            {
                exit(0);
            }
            random_bonus(bon);
            create_pole(bon);
            sn.print_snake();
            print();
            sn.moving_snake(c);
            Sleep(100-speed);
            time_no_bonus++;
            time_kill_long--;
            MoveXY(0,line_to_y);
            cout<<time_kill_long<<'\n';
            MoveXY(0,0);
            if (time_kill_long<1)
            {
                time_kill_long=250;
                sn.size_long_smol();
            }
        }

    }
}
