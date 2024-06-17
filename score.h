#include<ncurses.h>

class Score
{
    public:
    int len;
    int maxLen;
    int usePortal;
    int usePlus;
    int useMinus;

    int finLen;
    int finPortal;
    int finPlus;
    int finMinus;
    void Init()
    {
        len = 3;
        maxLen = 3;
        usePortal = 0;
        usePlus = 0;
        useMinus = 0;
    }
    void SetMission(int len, int portal, int plus, int minus)
    {
        finLen = len;
        finPortal = portal;
        finPlus = plus;
        finMinus = minus;
    }
    void NextStage(int a)
    {
        refresh();
        clear();
        box(stdscr, 0, 0);
        mvprintw(10, 10, "Next Stage : %d Stage..!",a);
        refresh();
        sleep(3);
        mvprintw(10, 10, "                            ");
    }
    void GameOver()
    {
        refresh();
        clear();
        box(stdscr, 0, 0);
        mvprintw(10, 10, "Game Over..!");
        refresh();
        sleep(3);
        mvprintw(10, 10, "                            ");
    }
    void GameClear()
    {
        refresh();
        clear();
        box(stdscr, 0, 0);
        mvprintw(10, 10, "Game Clear..!");
        refresh();
        sleep(3);
        mvprintw(10, 10, "                            ");
        exit(0);
    }
    void Draw()
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(i == 0 || i == 9 || j == 0 || j == 19)
                {
                    mvprintw(i+2, j+2, "#");
                }
                else
                {
                    mvprintw(i+2, j+2, " ");
                }
            }
        }

        mvprintw(4, 4, "ScoreBorad");
        mvprintw(5, 4, "B : %d / %d", len, maxLen);
        mvprintw(6, 4, "+ : %d", usePlus);
        mvprintw(7, 4, "- : %d", useMinus);
        mvprintw(8, 4, "G : %d", usePortal);

        for(int i=0;i<10;i++)
        {
            for(int j=0;j<20;j++)
            {
                if(i == 0 || i == 9 || j == 0 || j == 19)
                {
                    mvprintw(i+13, j+2, "#");
                }
                else
                {
                    mvprintw(i+13, j+2, " ");
                }
            }
        }

        mvprintw(15, 4, "Mission");
        mvprintw(16, 4, "B : %d  (%c)", finLen, finLen<=len?'v':' ');
        mvprintw(17, 4, "+ : %d  (%c)", finPlus, finPlus<=usePlus?'v':' ');
        mvprintw(18, 4, "- : %d  (%c)", finMinus, finMinus<=useMinus?'v':' ');
        mvprintw(19, 4, "G : %d  (%c)", finPortal, finPortal<=usePortal?'v':' ');


        
    }
    void AddLen()
    {
        len++;
        if(len > maxLen)
        {
            maxLen = len;
        }
    }
    void MinusLen()
    {
        len--;
    }
    void AddPortal()
    {
        usePortal++;
    }
    void AddPlus()
    {
        usePlus++;
    }
    void AddMinus()
    {
        useMinus++;
    }
    bool CheckMission()
    {
        if(len >= finLen && usePortal >= finPortal && usePlus >= finPlus && useMinus >= finMinus)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};