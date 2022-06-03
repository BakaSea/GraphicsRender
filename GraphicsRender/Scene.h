#pragma once
#include <mutex>
#include "ObjectList.h"
#include "BVHNode.h"
#include "Camera.h"
#include "Sampler.h"

class Scene {
public:
	Scene() : bvh(nullptr), camera(nullptr), width(0), height(0), spp(0), sLight(0), cLight(0), total(0) {}
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
	Vector3f color(const Ray3f& ray, int depth, Sampler& samplerLight, Sampler& samplerBrdf);

private:
	ObjectList world;
	ObjectList light;
	BVHNode* bvh;
	Camera* camera;
	vector<Vector3f> buffer;
	vector<Material*> materials;
	int width, height, spp, sLight, cLight;
	mutex mut;
	int total;

	void buildCornellBox();
	void buildSampler();
	void buildSampleLight();
	static void renderThread(Scene* scene, int y0, int y1);
};
