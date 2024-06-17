class Input
{
public:
    int dir;

void Init()
{
    dir = 1;
}
void processInput(){

    int ch;

    ch = getch();

    if(ch == KEY_LEFT)
    {
      dir = 3;
    }
    if(ch == KEY_RIGHT)
    {
      dir = 1;
    }
    if(ch == KEY_UP)
    {
      dir = 0;
    }
    if(ch == KEY_DOWN)
    {
      dir = 2;
    }
 
}
};