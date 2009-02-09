#include <common.h>
#include <Controller.h>
#include <Game.h>

int main(int argc, char* argv[])
{
    Game g;
    g.run();

    WebCamController c;
    c.test();

	return 0;
}
