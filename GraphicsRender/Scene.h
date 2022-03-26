#pragma once
#include <mutex>
#include "ObjectList.h"
#include "BVHNode.h"
#include "Camera.h"

class Scene {
public:
	Scene() : bvh(nullptr), camera(nullptr), width(0), height(0), spp(0), total(0) {}
	~Scene() {
		delete bvh;
		delete camera;
		for (Material* material : materials) {
			delete material;
		}
		materials.clear();
	}
	void build();
	void render();
	Vector3f color(const Ray3f& ray, int depth);

private:
	ObjectList world;
	ObjectList light;
	BVHNode* bvh;
	Camera* camera;
	vector<Vector3f> buffer;
	vector<Material*> materials;
	int width, height, spp;
	mutex mut;
	int total;

	static void renderThread(Scene* scene, int y0, int y1);
};
