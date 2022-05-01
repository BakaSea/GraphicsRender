#pragma once
#include <mutex>
#include "ObjectList.h"
#include "BVHNode.h"
#include "Camera.h"
#include "Sampler.h"

class Scene {
public:
	Scene() : samplerLight(nullptr), samplerUniform(nullptr), samplerRandom(nullptr), samplerBlueNoise(nullptr),
		bvh(nullptr), camera(nullptr), width(0), height(0), spp(0), total(0) {}
	~Scene() {
		delete samplerUniform;
		delete samplerRandom;
		delete samplerBlueNoise;
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
	Sampler* samplerLight;
	Sampler* samplerUniform;
	Sampler* samplerRandom;
	Sampler* samplerBlueNoise;
	vector<Vector3f> buffer;
	vector<Material*> materials;
	int width, height, spp;
	mutex mut;
	int total;

	void buildCornellBox();
	void buildSampler();
	static void renderThread(Scene* scene, int y0, int y1);
};
