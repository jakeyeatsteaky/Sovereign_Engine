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
 5) [x] Create Mesh Class
 6) [x] Init a mesh and draw it
		[x] Passing the VertexArray into the Mesh object via pointer works, but try to pass via rvalue reference (RendererApi.cpp, Renderer_GL::Init())
 7) [ ] Check destruction of objects and verify with print statements
 7) [x] Make Texture Class
 8) [ ] Put all that vertex stuff inside a mesh object.  Mesh should have a shader, texture and vertex info

** Copy ctor / assignops and Move ctor / assignops for all existing classes
 9) [ ] Rule of 5 for my existing render classes (vbuf, ibuf, varray, vlayout, mesh)
10) [ ] Make some primitive shapes.

#endif

