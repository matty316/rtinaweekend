#pragma once

float length_square(glm::vec3 vec) {
	return vec.x * vec.x + vec.g * vec.g + vec.b * vec.b;
}

static glm::vec3 random_vec() {
	return { random_float(), random_float(), random_float() };
}

static glm::vec3 random_vec(float min, float max) {
	return { random_float(min, max), random_float(min, max), random_float(min, max) };
}

inline glm::vec3 random_unit_vector() {
	while (true) {
		auto p = random_vec(-1.0f, 1.0f);
		auto lensq = length_square(p);
		if (1e-7 < lensq && lensq <= 1)
			return p / glm::sqrt(lensq);
	}
}

inline glm::vec3 random_on_hemisphere(const glm::vec3 normal) {
	glm::vec3 on_unit_sphere = random_unit_vector();
	if (glm::dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

bool near_zero(glm::vec3 v) {
	auto s = 1e-8;
	return (glm::abs<float>(v.x) < s) && (glm::abs<float>(v.y) < s) && (glm::abs<float>(v.z) < s);
}