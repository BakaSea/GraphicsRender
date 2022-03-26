#define STB_IMAGE_IMPLEMENTATION
#include "ImageTexture.h"
#include "stb_image.h"

ImageTexture::ImageTexture(const string& path) {
	data = stbi_load(path.c_str(), &width, &height, &channel, 0);
}

ImageTexture::~ImageTexture() {
	stbi_image_free(data);
}

Vector3f ImageTexture::value(float u, float v, const Vector3f& p) const {
	int i = u * width;
	int j = (1 - v) * height - 0.001;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > width - 1) i = width - 1;
	if (j > height - 1) j = height - 1;
	float r = int(data[channel * (i + j * height)]) / 255.0f;
	float g = int(data[channel * (i + j * height) + 1]) / 255.0f;
	float b = int(data[channel * (i + j * height) + 2]) / 255.0f;
	return Vector3f(r, g, b);
}
