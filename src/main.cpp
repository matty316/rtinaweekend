#include "common.h"

int main() {
	hittable_list world;

	auto material_ground = std::make_shared<lambertian>(color(0.8f, 0.8f, 0.0f));
	auto material_center = std::make_shared<lambertian>(color(0.1f, 0.2f, 0.5f));
	auto material_left = std::make_shared<metal>(color(0.8f, 0.8f, 0.8f));
	auto material_right = std::make_shared<metal>(color(0.8f, 0.6f, 0.2f));

	world.objects.push_back(std::make_shared<sphere>(point(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
	world.objects.push_back(std::make_shared<sphere>(point(0.0f, 0.0f, -1.2f), 0.5f, material_center));
	world.objects.push_back(std::make_shared<sphere>(point(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
	world.objects.push_back(std::make_shared<sphere>(point(1.0f, 0.0f, -1.0f), 0.5f, material_right));

	camera cam;

	cam.aspect_ratio = 16.0f / 9.0f;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	cam.render(world);
}