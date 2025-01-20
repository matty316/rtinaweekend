#pragma once

using point = glm::vec3;

struct ray {
	const point origin;
	const glm::vec3 direction;

	point at(float t) const {
		return origin + t * direction;
	}
};