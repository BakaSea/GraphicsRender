#define TINYOBJLOADER_IMPLEMENTATION
#include "MeshTriangle.h"
#include "tiny_obj_loader.h"
#include <iostream>
#include "Triangle.h"
using namespace tinyobj;

MeshTriangle::MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, Material* material) {
	ObjReader reader;
	ObjReaderConfig config;
	if (!reader.ParseFromFile(objPath, config)) {
		if (!reader.Error().empty()) {
			cerr << "TinyObjReader: " << reader.Error();
		}
		exit(1);
	}
	if (!reader.Warning().empty()) {
		cout << "TinyObjReader: " << reader.Warning();
	}
	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();
	for (int s = 0; s < shapes.size(); ++s) {
		int index = 0;
		for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			vector<Vector3f> vList(fv);
			vector<Vector3f> vnList;
			for (int v = 0; v < fv; ++v) {
				index_t idx = shapes[s].mesh.indices[index + v];
				float vx = attrib.vertices[3 * idx.vertex_index];
				float vy = attrib.vertices[3 * idx.vertex_index + 1];
				float vz = attrib.vertices[3 * idx.vertex_index + 2];
				vList[v] = center + scale * Vector3f(vx, vy, vz);
				if (idx.normal_index >= 0) {
					float vnx = attrib.normals[3 * idx.normal_index];
					float vny = attrib.normals[3 * idx.normal_index + 1];
					float vnz = attrib.normals[3 * idx.normal_index + 2];
					vnList[v] = Vector3f(vnx, vny, vnz);
				}
			}
			index += fv;
			Triangle* tri = new Triangle(vList[0], vList[1], vList[2], material);
			if (!vnList.empty()) {
				tri->setVertexNormal(vnList[0], vnList[1], vnList[2]);
			}
			triangleList.add(tri);
		}
	}
	bvh = new BVHNode(triangleList.getList(), triangleList.size(), 0, 0);
}

MeshTriangle::MeshTriangle(const string& objPath, const Vector3f& center, const Vector3f& scale, map<string, Material*> materialMap) {
	ObjReader reader;
	ObjReaderConfig config;
	if (!reader.ParseFromFile(objPath, config)) {
		if (!reader.Error().empty()) {
			cerr << "TinyObjReader: " << reader.Error();
		}
		exit(1);
	}
	if (!reader.Warning().empty()) {
		cout << "TinyObjReader: " << reader.Warning();
	}
	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();
	for (int s = 0; s < shapes.size(); ++s) {
		int index = 0;
		for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); ++f) {
			int fv = shapes[s].mesh.num_face_vertices[f];
			vector<Vector3f> vList(fv);
			vector<Vector2f> vtList(fv);
			vector<Vector3f> vnList;
			for (int v = 0; v < fv; ++v) {
				index_t idx = shapes[s].mesh.indices[index + v];
				float vx = attrib.vertices[3 * idx.vertex_index];
				float vy = attrib.vertices[3 * idx.vertex_index + 1];
				float vz = attrib.vertices[3 * idx.vertex_index + 2];
				vList[v] = center + scale * Vector3f(vx, vy, vz);
				if (idx.normal_index >= 0) {
					float vnx = attrib.normals[3 * idx.normal_index];
					float vny = attrib.normals[3 * idx.normal_index + 1];
					float vnz = attrib.normals[3 * idx.normal_index + 2];
					vnList.push_back(Vector3f(vnx, vny, vnz));
				}
				if (idx.texcoord_index >= 0) {
					float vtx = attrib.texcoords[2 * idx.texcoord_index];
					float vty = attrib.texcoords[2 * idx.texcoord_index + 1];
					vtList[v] = Vector2f(vtx, vty);
				}
			}
			index += fv;
			int mid = shapes[s].mesh.material_ids[f];
			Material* material = materialMap[materials[mid].diffuse_texname];
			Triangle* tri = new Triangle(vList[0], vList[1], vList[2], vtList[0], vtList[1], vtList[2], material);
			if (!vnList.empty()) {
				tri->setVertexNormal(vnList[0], vnList[1], vnList[2]);
			}
			triangleList.add(tri);
		}
	}
	bvh = new BVHNode(triangleList.getList(), triangleList.size(), 0, 0);
}

MeshTriangle::~MeshTriangle() {
	delete bvh;
}

bool MeshTriangle::hit(const Ray3f& ray, float tMin, float tMax, HitRecord& record) const {
	return bvh->hit(ray, tMin, tMax, record);
}

bool MeshTriangle::getBoundingBox(float t0, float t1, AABB& box) const {
	return bvh->getBoundingBox(t0, t1, box);
}
