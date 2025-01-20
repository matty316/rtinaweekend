#pragma once

struct hit_record {
	point p;
	glm::vec3 normal;
	float t;
	bool front_face;

	void set_face_normal(const ray& r, const glm::vec3& outward_normal) {
		front_face = glm::dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

struct hittable {
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

struct sphere : public hittable {
public:
	sphere(const point center, float radius) : center(center), radius(glm::max<float>(0.0f, radius)) {}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		glm::vec3 oc = center - r.origin;
		auto a = length_square(r.direction);
		auto h = glm::dot(r.direction, oc);
		auto c = length_square(oc) - radius * radius;
		auto discriminant = h * h - a * c;
		if (discriminant < 0.0f)
			return false;

		auto sqrtd = glm::sqrt(discriminant);

		auto root = (h - sqrtd) / a;
		if (!ray_t.surrounds(root)) {
			root = (h + sqrtd) / a;
			if (!ray_t.surrounds(root))
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		glm::vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
private:
	point center;
	float radius;
};

struct hittable_list : public hittable {
public:
	std::vector<std::unique_ptr<hittable>> objects;

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		auto closest_so_far = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
	
		return hit_anything;
	}
};