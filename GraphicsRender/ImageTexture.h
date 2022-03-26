#pragma once
#include "Texture.h"
#include <string>
using namespace std;

class ImageTexture : public Texture {
public:
	ImageTexture(const string& path);
	~ImageTexture();
	Vector3f value(float u, float v, const Vector3f& p) const override;

private:
	unsigned char* data;
	int width, height, channel;
};

