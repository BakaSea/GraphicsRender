#include "Scene.h"
#include <iostream>
#include <fstream>

#include "BVHNode.h"
#include "FlipNormalObject.h"
#include "Rectangle.h"
#include "Disk.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Lambertian.h"
#include "DiffuseLight.h"
#include "Metal.h"
#include "ConstantTexture.h"
#include "ObjectPdf.h"
#include "MixturePdf.h"
#include "Dielectric.h"
#include "Triangle.h"
#include "TriPyramid.h"
#include "MeshTriangle.h"
#include "ImageTexture.h"
using namespace std;

void Scene::build() {
	width = 400;
	height = 400;
	spp = 400;

	Material* red = new Lambertian(new ConstantTexture(Vector3f(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture(Vector3f(0.73f, 0.73f, 0.73f)));
	Material* green = new Lambertian(new ConstantTexture(Vector3f(0.12f, 0.45f, 0.15f)));
	Material* mLight = new DiffuseLight(new ConstantTexture(Vector3f(15, 15, 15)));
	Material* alu = new Metal(new ConstantTexture(Vector3f(0.8f, 0.85f, 0.88f)), 0);
	Material* glass = new Dielectric(1.5f);
	Material* gold = new Metal(new ConstantTexture(Vector3f(1, 0.84f, 0)), 0.1f);
	materials.push_back(red);
	materials.push_back(white);
	materials.push_back(green);
	materials.push_back(mLight);
	materials.push_back(alu);
	materials.push_back(glass);
	materials.push_back(gold);

	light.add(new DiskXZ(Vector3f(278, 554, 278), 100, mLight));

	world.add(new FlipNormalObject(new DiskXZ(Vector3f(278, 554, 278), 100, mLight)));

	world.add(new FlipNormalObject(new RectangleYZ(0, 555, 0, 555, 555, green)));
	world.add(new RectangleYZ(0, 555, 0, 555, 0, red));
	world.add(new FlipNormalObject(new RectangleXZ(0, 555, 0, 555, 555, white)));
	world.add(new RectangleXZ(0, 555, 0, 555, 0, white));
	world.add(new FlipNormalObject(new RectangleXY(0, 555, 0, 555, 555, white)));
	
	world.add(new Sphere(Vector3f(100, 50, 100), 50, alu));
	world.add(new CylinderXZ(Vector3f(450, 0, 200), 50, 150, white));
	world.add(new Sphere(Vector3f(450, 200, 200), 50, glass));

	world.add(new TriPyramid(Vector3f(450, 400, 150), Vector3f(410, 300, 0), Vector3f(390, 250, 200), Vector3f(550, 280, 200), gold));

	world.add(new MeshTriangle("bunny.obj", Vector3f(200, -10, 278), Vector3f(500, 500, 500), white));

	string pKokomi = "kokomi/";
	string pClothes = "tex/clothes.png";
	string pFace = "tex/face.png";
	string pHair = "tex/hair.png";
	string pHairsph = "tex/hairsph+.png";
	string pSkin1 = "tex/skin1.png";
	string pSkin2 = "tex/skin2.png";
	Texture* tClothes = new ImageTexture(pKokomi + pClothes);
	Texture* tFace = new ImageTexture(pKokomi + pFace);
	Texture* tHair = new ImageTexture(pKokomi + pHair);
	Texture* tHairsph = new ImageTexture(pKokomi + pHairsph);
	Texture* tSkin1 = new ImageTexture(pKokomi + pSkin1);
	Texture* tSkin2 = new ImageTexture(pKokomi + pSkin2);
	Material* mClothes = new Lambertian(tClothes);
	Material* mFace = new Lambertian(tFace);
	Material* mHair = new Lambertian(tHair);
	Material* mHairsph = new Lambertian(tHairsph);
	Material* mSkin1 = new Lambertian(tSkin1);
	Material* mSkin2 = new Lambertian(tSkin2);
	materials.push_back(mClothes);
	materials.push_back(mFace);
	materials.push_back(mHair);
	materials.push_back(mHairsph);
	materials.push_back(mSkin1);
	materials.push_back(mSkin2);
	map<string, Material*> materialMap;
	materialMap[pClothes] = mClothes;
	materialMap[pFace] = mFace;
	materialMap[pHair] = mHair;
	materialMap[pHairsph] = mHairsph;
	materialMap[pSkin1] = mSkin1;
	materialMap[pSkin2] = mSkin2;

	world.add(new MeshTriangle("kokomi/kokomi.obj", Vector3f(278, 0, 400), Vector3f(20, 20, 20), materialMap));

	bvh = new BVHNode(world.getList(), world.size(), 0, 0);

	camera = new Camera(Vector3f(278, 278, -800), Vector3f(278, 278, 0), Vector3f(0, 1, 0), 40.0f, float(width) / float(height));
}

void Scene::render() {
	buffer = vector<Vector3f>(width * height);

	int num = thread::hardware_concurrency();
	//int num = 1;
	int lines = height / num + 1;
	cout << "Thread nums: " << num << endl;
	cout << "Lines per cpu: " << lines << endl;
	cout << "Distrubute works..." << endl;
	vector<thread> work;
	for (int i = 0; i < num; ++i) {
		cout << "Distrubte cpu " << i << endl;
		int y0 = i * lines;
		int y1 = min(y0 + lines, height);
		work.push_back(thread(Scene::renderThread, this, y0, y1));
		if (y1 == height) break;
	}
	cout << "Works start..." << endl;
	for (int i = 0; i < work.size(); ++i) {
		work[i].join();
	}

	ofstream img("result.ppm");
	img << "P3\n" << width << " " << height << "\n255\n";
	for (int i = height - 1; i >= 0; --i) {
		for (int j = 0; j < width; ++j) {
			int index = i * width + j;
			int r = int(255.99 * buffer[index][0]);
			int g = int(255.99 * buffer[index][1]);
			int b = int(255.99 * buffer[index][2]);
			img << r << " " << g << " " << b << endl;
		}
	}
	img.close();
}

Vector3f Scene::color(const Ray3f& ray, int depth) {
	HitRecord hrec;
	if (bvh->hit(ray, 0.001f, FLT_MAX, hrec)) {
	//if (world.hit(ray, 0.001f, FLT_MAX, hrec)) {
		ScatterRecord srec;
		Vector3f emitted = hrec.material->emitted(hrec.u, hrec.v, hrec.p);
		if (depth < 50 && hrec.material->scatter(ray, hrec, srec)) {
			if (srec.isSpecular) {
				return srec.attenuation * color(srec.ray, depth + 1);
			} else {
				ObjectPdf pLight(&light, hrec.p);
				MixturePdf pMix(&pLight, srec.pdf);
				Ray3f scattered = Ray3f(hrec.p, pMix.generate());
				float pdfVal = pMix.value(scattered.direction());
				return emitted + srec.attenuation * hrec.material->scatteringPdf(ray, hrec, scattered) * color(scattered, depth + 1) / pdfVal;
			}
		} else {
			return emitted;
		}
	} else return Vector3f(0, 0, 0);
}

void Scene::renderThread(Scene* scene, int y0, int y1) {
	for (int i = y0; i < y1; ++i) {
		for (int j = 0; j < scene->width; ++j) {
			Vector3f col(0, 0, 0);
			for (int s = 0; s < scene->spp; ++s) {
				float u = (float(j) + frand()) / float(scene->width);
				float v = (float(i) + frand()) / float(scene->height);
				Ray3f ray = scene->camera->getRay(u, v);
				col += solveNaN(scene->color(ray, 0));
			}
			col /= float(scene->spp);
			col = Vector3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int index = i * scene->width + j;
			scene->buffer[index] = col;
			
		}
		scene->mut.lock();
		scene->total++;
		cout << scene->total << endl;
		cout.flush();
		scene->mut.unlock();
	}
}
