#include "common.h"

int main() {
	hittable_list world;

	world.objects.push_back(std::make_unique<sphere>(point(0.0f, 0.0f, -1.0f), 0.5f));
	world.objects.push_back(std::make_unique<sphere>(point(0.0f, -100.5f, -1.0f), 100.0f));

	camera cam;

	cam.aspect_ratio = 16.0f / 9.0f;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;

	cam.render(world);
}