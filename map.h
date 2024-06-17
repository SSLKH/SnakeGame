#include <ncurses.h>
#include <vector>
#include <time.h>
#include <queue>
#include "obj.h"
#define MAP_SIZE_X 40
#define MAP_SIZE_Y 21

using namespace std;

char mapSprite[7] = {' ','W', 'P', 'M', 'X', '#', 'O'};

class Map
{
  public:
  vector<vector<ObjType>> map;

  pair<int,int> plusItem;
  pair<int,int> minusItem;

  pair<int,int> portal1;
  pair<int,int> portal2;

  void mapInit()
  {
    plusItem = {-1, -1};
    minusItem = {-1, -1};
    portal1 = {-1, -1};
    portal2 = {-1, -1};
}

void drawMap(queue<pair<int,int>> q)
{
  PlayerSet(q);
  //refresh();
  for(int i = 0; i < MAP_SIZE_Y; i++)
  {
    for(int j = 0; j < MAP_SIZE_X; j++)
    {
      mvprintw(i+2, j+35, "%c", mapSprite[(int)map[i][j]]);
    }
  }
}

void AddPortal()
{
  if(portal1.first != -1)
  {
    map[portal1.second][portal1.first] = ObjType::Wall;
  }
  if(portal2.first != -1)
  {
    map[portal2.second][portal2.first] = ObjType::Wall;
  }
  vector<pair<int,int>> walls;
  for(int i = 0; i < MAP_SIZE_Y; i++)
  {
    for(int j = 0; j < MAP_SIZE_X; j++)
    {
      if(map[i][j] == ObjType::Wall)
      {
        walls.push_back({j, i});
      }
    }
  }
  if(walls.size() <= 1)
  {
    return;
  }
  int idx = rand() % walls.size();
  portal1 = walls[idx];
  map[portal1.second][portal1.first] = ObjType::Portal;
  walls.erase(walls.begin() + idx);

  idx = rand() % walls.size();
  portal2 = walls[idx];
  map[portal2.second][portal2.first] = ObjType::Portal;
}
  void AddItem()
  {
    if(plusItem.first != -1)
    {
      map[plusItem.second][plusItem.first] = ObjType::Air;
    }
    if(minusItem.first != -1)
    {
      map[minusItem.second][minusItem.first] = ObjType::Air;
    }

    vector<pair<int,int>> air;
    for(int i = 0; i < MAP_SIZE_Y; i++)
    {
      for(int j = 0; j < MAP_SIZE_X; j++)
      {
        if(map[i][j] == ObjType::Air)
        {
          air.push_back({j, i});
        }
      }
    }
    if(air.size() <= 1)
    {
      return;
    }
    int idx = rand() % air.size();
    plusItem = air[idx];
    map[plusItem.second][plusItem.first] = ObjType::Plus;
    air.erase(air.begin() + idx);

    idx = rand() % air.size();
    minusItem = air[idx];
    map[minusItem.second][minusItem.first] = ObjType::Minus;
  } 


  void PlayerSet(queue<pair<int,int>> q)
  {
    for(int i = 0; i < MAP_SIZE_Y; i++)
    {
      for(int j = 0; j < MAP_SIZE_X; j++)
      {
        if(map[i][j] == ObjType::Player)
        map[i][j] = ObjType::Air;
      }
    }
    for(int i = 0; i < q.size(); i++)
    {
      pair<int, int> temp = q.front();
      q.pop();
      map[temp.second][temp.first] = ObjType::Player;
      q.push(temp);
    }
  }



  void InitDraw(vector<vector<int>> temp)
  {
    map.clear();
    
    for(int i = 0; i < MAP_SIZE_Y; i++)
    {
      map.push_back(vector<ObjType>());
      for(int j = 0; j < MAP_SIZE_X; j++)
      {
        map[i].push_back((ObjType)temp[i][j]);
      }
    }
  }
};
