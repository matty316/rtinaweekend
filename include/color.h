#pragma once

#include <iostream>

using color = glm::vec3;

void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.r;
	auto g = pixel_color.g;
	auto b = pixel_color.b;

	static const interval intensity(0.000f, 0.999f);
	int rbyte = int(255 * intensity.clamp(r));
	int gbyte = int(255 * intensity.clamp(g));
	int bbyte = int(255 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}