#include "App.h"
#include "enumerations.h"


int main(int argc, char* argv[])
{
	App app;
	app.Setup();

	while (app.IsRunning())
	{
		app.Input();
		app.Update();
		app.Render();
	}

	app.Destroy();

	return 0;

}


/////////////////// GLOBAL TODO ///////////////////
#if 0

1) [x] Create Vertex Buffer Object
2) [x] Create Index Buffer Object
3) [x] Create Vertex Array Object
4) [x] Create Vertex Layout Object
5) [ ] Create Mesh Class
6) [ ] Init a mesh and draw it
7) [ ] Check destruction of objects and verify with print statements

8) [ ] Rule of 5 for my existing render classes (vbuf, ibuf, varray, vlayout, mesh)


#endif

