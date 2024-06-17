#include "map.h"
#include "score.h"

int Dir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
class Player{
    public:
    int x, y;
    int dir;

    int len;
    bool dead;

    queue<pair<int, int>> q;
    void playerInit()
    {
        x = 4;
        y = 4;
        dead = false;
        dir = 1;
        len = 3;
        q = queue<pair<int, int>>();
        q.push({x-2, y});
        q.push({x-1, y});
        q.push({x, y});
    }
    bool CheckDead()
    {
        return dead;
    }
    bool CheckCanPortal()
    {
        pair<int,int> undo = {q.front().first, q.front().second};
        bool flag = true;
        for(int i=0;i<q.size();i++)
        {
            pair<int,int> temp = q.front();
            q.pop();
            if(abs(undo.first - temp.first + undo.second - temp.second) > 1)
            {
                flag = false;
            }
            undo = temp;
            q.push(temp);
        }
        return flag;
    }
    void Move(Map map, Score& score)
    {
        int nx = x + Dir[dir][0];
        int ny = y + Dir[dir][1];
        if(map.map[ny][nx] == ObjType::Wall || map.map[ny][nx] == ObjType::Player)
        {
            dead = true;
            return;
        }
        if(map.map[ny][nx] == ObjType::Plus)
        {
            len++;
            map.plusItem = {-1, -1};
            map.map[ny][nx] = ObjType::Air;
            score.AddLen();
            score.AddPlus();
            
        }
        if(map.map[ny][nx] == ObjType::Minus)
        {
            len--;
            map.minusItem = {-1, -1};
            q.pop();
            if(len<3)dead = true;
            map.map[ny][nx] = ObjType::Air;
            score.MinusLen();
            score.AddMinus();
        }
        if(map.map[ny][nx] == ObjType::Air)
        {
            q.push({nx, ny});
            map.map[ny][nx] = ObjType::Player;
            x = nx;
            y = ny;
            if(q.size() > len)
            {
                map.map[q.front().second][q.front().first] = ObjType::Air;
                q.pop();
            }
        }
        if(map.map[ny][nx] == ObjType::Portal)
        {
            for(int i = 0; i < MAP_SIZE_Y; i++)
            {
                for(int j = 0; j < MAP_SIZE_X; j++)
                {
                    if(map.map[i][j] == ObjType::Portal && (i != ny || j != nx))
                    {
                        if(i==0)dir = 2;
                        else if(i==MAP_SIZE_Y-1)dir = 0;
                        else if(j==0)dir = 1;
                        else if(j==MAP_SIZE_X-1)dir = 3;
                        else if(map.map[i+Dir[dir][1]][j+Dir[dir][0]] != ObjType::Wall)
                        {
                        }
                        else if(map.map[i+Dir[(dir+1)%4][1]][j+Dir[(dir+1)%4][0]] != ObjType::Wall)
                        {
                            dir = (dir+1)%4;
                        }
                        else if(map.map[i+Dir[(dir+3)%4][1]][j+Dir[(dir+3)%4][0]] != ObjType::Wall)
                        {
                            dir = (dir+3)%4;
                        }
                        else if(map.map[i+Dir[(dir+2)%4][1]][j+Dir[(dir+2)%4][0]] != ObjType::Wall)
                        {
                            dir = (dir+2)%4;
                        }

                        j += Dir[dir][0];
                        i += Dir[dir][1];

                        x = j;
                        y = i;
                        q.push({x, y});
                        map.map[y][x] = ObjType::Player;
                        if(q.size() > len)
                        {
                            q.pop();
                        }
                        score.AddPortal();
                        return;
                    }
                }
            }
        }
    }
    void PlayerTurn(int _dir)
    {
        dir = _dir;
    }
    void DrawPlayer()
    {
        mvprintw(y+2, x+35, "X");
        refresh();
    }
};