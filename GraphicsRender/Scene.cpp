#include "Scene.h"
#include <iostream>
#include <fstream>
#include "BVHNode.h"
#include "FlipNormalObject.h"
#include "Rectangle.h"
#include "Disk.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "DiffuseLight.h"
#include "GGX.h"
#include "ConstantTexture.h"
#include "ObjectPdf.h"
#include "MixturePdf.h"
#include "GGXPdf.h"
#include "Triangle.h"
#include "TriPyramid.h"
#include "MeshTriangle.h"
#include "ImageTexture.h"
#include "SamplerUniform.h"
#include "SamplerRandom.h"
#include "SamplerBlueNoise.h"
#include "SamplerRandomNP.h"
using namespace std;

void Scene::build() {
	cout << "Width: ";
	cin >> width;
	cout << "Height: ";
	cin >> height;
	cout << "Samples per pixel: ";
	cin >> spp;
	cout << "Choose a sampler(1-uniform, 2-random, 3-bluenoise, 4-default): ";
	cin >> cLight;
	if (1 <= cLight && cLight <= 3) {
		cout << "MC Samples in light: ";
		cin >> sLight;
	}
	buildCornellBox();
	//buildSampler();
	//buildSampleLight();
}

void Scene::render() {
	buffer = vector<Vector3f>(width * height);

	int num = thread::hardware_concurrency();
	//int num = 1;
	int lines = height / num + 1;
	if (lines > height) lines = height;
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

Vector3f Scene::color(const Ray3f& ray, int depth, Sampler& samplerLight, Sampler& samplerBrdf) {
	HitRecord hrec;
	if (bvh->hit(ray, 0.001f, FLT_MAX, hrec)) {
		ScatterRecord srec;
		Vector3f emitted = hrec.material->emitted(hrec.u, hrec.v, hrec.p);
		if (depth < 50 && hrec.material->scatter(ray, hrec, srec)) {
			Vector3f c = emitted;
			ObjectPdf lightPdf(&light, hrec.p);
			Vector3f lightDir = lightPdf.generate(samplerLight);
			Ray3f lightRay = Ray3f(hrec.p, lightDir);
			HitRecord lhrec;
			if (bvh->hit(lightRay, 0.001f, FLT_MAX, lhrec)) {
				if (lhrec.p == hrec.p + lightDir && dynamic_cast<DiffuseLight*>(lhrec.material) != nullptr) {
					float cosine = dot(hrec.normal, lightRay.direction());
					if (cosine >= 0) {
						float lightPdfVal = lightPdf.value(lightRay.direction());
						float brdfPdfVal = srec.pdf->value(lightRay.direction());
						Vector3f lightEmited = lhrec.material->emitted(lhrec.u, lhrec.v, lhrec.p);
						//MIS
						c += hrec.material->BRDF(hrec, lightRay.direction(), -ray.direction()) * cosine * lightEmited / (lightPdfVal + brdfPdfVal);
						//Light sampling
						//c += hrec.material->BRDF(hrec, lightRay.direction(), -ray.direction()) * cosine * lightEmited / lightPdfVal;
					}
				}
			}
			Ray3f scattered = Ray3f(hrec.p, srec.pdf->generate(samplerBrdf));
			float cosine = dot(hrec.normal, scattered.direction());
			if (cosine >= 0) {
				float lightPdfVal = lightPdf.value(scattered.direction());
				float brdfPdfVal = srec.pdf->value(scattered.direction());
				//MIS
				c += hrec.material->BRDF(hrec, scattered.direction(), -ray.direction()) * cosine * color(scattered, depth + 1, samplerLight, samplerBrdf) / (lightPdfVal + brdfPdfVal);
				//BRDF sampling
				//c += hrec.material->BRDF(hrec, scattered.direction(), -ray.direction()) * cosine * color(scattered, depth + 1, samplerLight, samplerBrdf) / brdfPdfVal;
			}
			return c;
		} else {
			return emitted;
		}
	} else return Vector3f(0, 0, 0);
}

void Scene::buildCornellBox() {
	Material* red = new GGX((new ConstantTexture(Vector3f(0.65f, 0.05f, 0.05f))), Vector3f(0, 0, 0), 0, 1);
	Material* white = new GGX((new ConstantTexture(Vector3f(0.73f, 0.73f, 0.73f))), Vector3f(0, 0, 0), 0, 1);
	Material* green = new GGX((new ConstantTexture(Vector3f(0.12f, 0.45f, 0.15f))), Vector3f(0, 0, 0), 0, 1);
	Material* alu = new GGX(new ConstantTexture(Vector3f(0.91f, 0.92f, 0.92f)), Vector3f(0.96f, 0.96f, 0.97f), 0.9f, 0.01f);
	Material* gold = new GGX(new ConstantTexture(Vector3f(1, 0.86f, 0.57f)), Vector3f(1.0f, 0.71f, 0.29f), 0.8f, 0.1f);
	Material* copper = new GGX(new ConstantTexture(Vector3f(0.98f, 0.82f, 0.76f)), Vector3f(0.95f, 0.64f, 0.54f), 0.6f, 0.2f);
	Material* silver = new GGX(new ConstantTexture(Vector3f(0.98f, 0.97f, 0.95f)), Vector3f(0.95f, 0.93f, 0.88f), 1.0f, 0.3f);
	Material* mLight = new DiffuseLight(new ConstantTexture(Vector3f(15, 15, 15)));

	materials.push_back(red);
	materials.push_back(white);
	materials.push_back(green);
	materials.push_back(mLight);
	materials.push_back(alu);
	materials.push_back(copper);
	materials.push_back(gold);

	light.add(new DiskXZ(Vector3f(278, 554, 278), 100, mLight));
	world.add(new FlipNormalObject(new DiskXZ(Vector3f(278, 554, 278), 100, mLight)));

	world.add(new FlipNormalObject(new RectangleYZ(0, 555, 0, 555, 555, green)));
	world.add(new RectangleYZ(0, 555, 0, 555, 0, red));
	world.add(new FlipNormalObject(new RectangleXZ(0, 555, 0, 555, 555, white)));
	world.add(new RectangleXZ(0, 555, 0, 555, 0, white));
	world.add(new FlipNormalObject(new RectangleXY(0, 555, 0, 555, 555, white)));

	world.add(new Sphere(Vector3f(100, 50, 100), 50, alu));
	world.add(new CylinderXZ(Vector3f(450, 0, 200), 50, 150, silver));
	world.add(new Sphere(Vector3f(450, 200, 200), 50, copper));

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
	map<string, Texture*> textureMap;
	textureMap[pClothes] = tClothes;
	textureMap[pFace] = tFace;
	textureMap[pHair] = tHair;
	textureMap[pHairsph] = tHairsph;
	textureMap[pSkin1] = tSkin1;
	textureMap[pSkin2] = tSkin2;

	world.add(new MeshTriangle("kokomi/kokomi.obj", Vector3f(278, 0, 400), Vector3f(20, 20, 20), textureMap, materials));
	
	bvh = new BVHNode(world.getList(), world.size(), 0, 0);

	camera = new Camera(Vector3f(278, 278, -800), Vector3f(278, 278, 0), Vector3f(0, 1, 0), 40.0f, float(width) / float(height));
}

void Scene::buildSampler() {
	Material* red = new GGX(new ConstantTexture(Vector3f(0.65f, 0.05f, 0.05f)), Vector3f(0.6f, 0.01f, 0.01f), 0.5f, 0.5f);
	Material* white = new GGX(new ConstantTexture(Vector3f(0.73f, 0.73f, 0.73f)), Vector3f(0.7f, 0.7f, 0.7f), 0.5f, 0.5f);
	Material* green = new GGX(new ConstantTexture(Vector3f(0.12f, 0.45f, 0.15f)), Vector3f(0.08f, 0.4f, 0.1f), 0.5f, 0.5f);
	Material* mLight = new DiffuseLight(new ConstantTexture(Vector3f(10, 10, 10)));
	materials.push_back(red);
	materials.push_back(white);
	materials.push_back(green);
	materials.push_back(mLight);
	light.add(new DiskXZ(Vector3f(278, 554, 278), 100, mLight));
	world.add(new FlipNormalObject(new DiskXZ(Vector3f(278, 554, 278), 100, mLight)));

	world.add(new FlipNormalObject(new RectangleYZ(0, 555, 0, 555, 555, green)));
	world.add(new RectangleYZ(0, 555, 0, 555, 0, red));
	world.add(new FlipNormalObject(new RectangleXZ(0, 555, 0, 555, 555, white)));
	world.add(new RectangleXZ(0, 555, 0, 555, 0, white));
	world.add(new FlipNormalObject(new RectangleXY(0, 555, 0, 555, 555, white)));

	world.add(new CylinderXZ(Vector3f(450, 0, 200), 75, 200, white));

	bvh = new BVHNode(world.getList(), world.size(), 0, 0);

	camera = new Camera(Vector3f(278, 278, -800), Vector3f(278, 278, 0), Vector3f(0, 1, 0), 40.0f, float(width) / float(height));
}

void Scene::buildSampleLight() {
	Material* mLight1 = new DiffuseLight(new ConstantTexture(Vector3f(1, 0, 0)));
	Material* mLight2 = new DiffuseLight(new ConstantTexture(Vector3f(0, 1, 0)));
	Material* mLight3 = new DiffuseLight(new ConstantTexture(Vector3f(0, 0, 1)));
	Material* white = new GGX(new ConstantTexture(Vector3f(1, 1, 1)), Vector3f(0, 0, 0), 0.5f, 0.5f);
	Material* blue = new GGX(new ConstantTexture(Vector3f(0.4f, 0.8f, 0.99f)), Vector3f(0, 0, 0), 0.5f, 0.5f);
	Material* m1 = new GGX(new ConstantTexture(Vector3f(0.91f, 0.92f, 0.92f)), Vector3f(0.96f, 0.96f, 0.97f), 1.0f, 0.01f);
	Material* m2 = new GGX(new ConstantTexture(Vector3f(0.91f, 0.92f, 0.92f)), Vector3f(0.96f, 0.96f, 0.97f), 1.0f, 0.1f);
	Material* m3 = new GGX(new ConstantTexture(Vector3f(0.91f, 0.92f, 0.92f)), Vector3f(0.96f, 0.96f, 0.97f), 1.0f, 0.2f);
	materials.push_back(mLight1);
	materials.push_back(mLight2);
	materials.push_back(mLight3);
	materials.push_back(white);
	materials.push_back(blue);
	materials.push_back(m1);
	materials.push_back(m2);
	materials.push_back(m3);

	light.add(new FlipNormalObject(new MeshTriangle("square.obj", Vector3f(-3, 5, 5), Vector3f(0.5f, 0.5f, 0.5f), mLight1)));
	world.add(new FlipNormalObject(new MeshTriangle("square.obj", Vector3f(-3, 5, 5), Vector3f(0.5f, 0.5f, 0.5f), mLight1)));
	light.add(new FlipNormalObject(new MeshTriangle("pentagon.obj", Vector3f(0, 5, 5), Vector3f(1, 1, 1), mLight2)));
	world.add(new FlipNormalObject(new MeshTriangle("pentagon.obj", Vector3f(0, 5, 5), Vector3f(1, 1, 1), mLight2)));
	light.add(new FlipNormalObject(new MeshTriangle("hexagon.obj", Vector3f(3, 5, 5), Vector3f(1.5f, 1.5f, 1.5f), mLight3)));
	world.add(new FlipNormalObject(new MeshTriangle("hexagon.obj", Vector3f(3, 5, 5), Vector3f(1.5f, 1.5f, 1.5f), mLight3)));

	world.add(new RectangleXY(-100, 100, 0, 5, 3, blue));

	world.add(new RectangleXZ(-100, 100, -100, 100, 0, m1));
	//world.add(new RectangleXZ(-100, 100, -100, 100, 0, m2));
	//world.add(new RectangleXZ(-100, 100, -100, 100, 0, m3));

	bvh = new BVHNode(world.getList(), world.size(), 0, 0);
	camera = new Camera(Vector3f(0, 2.5f, 12), Vector3f(0, 0, 0), Vector3f(0, 1, 0), 90.0f, float(width) / float(height));
}

void Scene::renderThread(Scene* scene, int y0, int y1) {
	Sampler* samplerLight, * samplerDefault;
	switch (scene->cLight) {
	case 1: samplerLight = new SamplerUniform(scene->sLight); break;
	case 2: samplerLight = new SamplerRandom(scene->sLight); break;
	case 3: samplerLight = new SamplerBlueNoise(scene->sLight); break;
	default:
		samplerLight = new SamplerRandomNP();
		break;
	}
	samplerDefault = new SamplerRandomNP();
	for (int i = y0; i < y1; ++i) {
		for (int j = 0; j < scene->width; ++j) {
			Vector3f col(0, 0, 0);
			int debug = 0;
			for (int s = 0; s < scene->spp; ++s) {
				Vector2f uv = samplerDefault->generate2D(1.0f, 1.0f);
				float u = (float(j) + uv.x()) / float(scene->width);
				float v = (float(i) + uv.y()) / float(scene->height);
				Ray3f ray = scene->camera->getRay(u, v);
				//col += scene->color(ray, 0, *samplerLight, *samplerDefault);
				col += solveNaN(scene->color(ray, 0, *samplerLight, *samplerDefault));
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
	delete samplerLight;
	delete samplerDefault;
}
