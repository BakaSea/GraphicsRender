#include <time.h>
#include <random>
#include "MathHelper.h"
#include "Scene.h"

extern default_random_engine randEngine;

int main() {
	randEngine.seed(time(0));
	Scene scene;
	scene.build();
	scene.render();
	return 0;
}