#include <ncurses.h>
#include <vector>
#include <unistd.h>
#include <thread>

#include "input.h"
#include "stage.h"
using namespace std;

void InputUpdate();
void AddItemUpdate();
void AddPortalUpdate();
void CheckClear();
void CheckDead();

Player player;
Map map;
Input input;
Score score;



int nowStage = 1;

int main()
{

  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));


	//newwin(MAP_SIZE_Y, MAP_SIZE_X, 1, 1);
  keypad(stdscr,true);
  wbkgd(stdscr, COLOR_PAIR(1));  //윈도우 백그라운드 컬러



  refresh();

  map.mapInit();
  player.playerInit();
  input.Init();

  SetStage(nowStage,map,score);

  thread t1(InputUpdate);
  thread t2(AddItemUpdate);
  thread t3(AddPortalUpdate);
  while(1)
  {
      player.Move(map,score);
      map.drawMap(player.q);
      score.Draw();
      player.DrawPlayer();
      CheckClear();
      CheckDead();
      usleep(150000);
  }

  endwin();
  t1.join();
  t2.join();
  t3.join();

  return 0;
}
void CheckDead()
{
  if(player.dead)
  {
    map.mapInit();
    player.playerInit();
    input.Init();
    Dead(map,score,nowStage);
  }

}
void CheckClear()
{
  if(score.CheckMission())
  {
    map.mapInit();
    player.playerInit();
    input.Init();

    SetStage(++nowStage,map,score);
  }
}
void InputUpdate()
{
  while(1)
  {
  input.processInput();
  player.PlayerTurn(input.dir);
  }
}

void AddItemUpdate()
{
  while (1)
  {
    map.AddItem();
    sleep(5);
  }
  
}

void AddPortalUpdate()
{
  while (1)
  {
    if(player.CheckCanPortal())
    {
      map.AddPortal();
    }
    sleep(10);
  }
  
}