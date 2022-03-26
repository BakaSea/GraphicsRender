#include <stdlib.h>
#include <time.h>
#include "Scene.h"
using namespace std;

int main() {
	srand(time(0));
	Scene scene;
	scene.build();
	scene.render();
	return 0;
}