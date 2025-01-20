#pragma once

struct material {
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
		return false;
	}
};

struct lambertian : public material {
public: 
	lambertian(const color& albedo) : albedo(albedo) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scatter_direction = rec.normal + random_unit_vector();

		if (near_zero(scatter_direction))
			scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};

struct metal : public material {
public:
	metal(const color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		glm::vec3 reflected = glm::reflect(r_in.direction, rec.normal);
		reflected = glm::normalize(reflected) + (fuzz * random_unit_vector());
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction, rec.normal) > 0);
	}

private:
	color albedo;
	float fuzz;
};

class dielectric : public material {
public:
	dielectric(float refraction_index) : refraction_index(refraction_index) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		attenuation = color(1.0f, 1.0f, 1.0f);
		float ri = rec.front_face ? (1.0f / refraction_index) : refraction_index;
		glm::vec3 unit_direction = glm::normalize(r_in.direction);
		auto cos_theta = glm::min(glm::dot(-unit_direction, rec.normal), 1.0f);
		auto sin_theta = glm::sqrt(1.0f - cos_theta * cos_theta);

		bool cannot_refract = ri * sin_theta > 1.0f;
		glm::vec3 direction;

		if (cannot_refract || reflectance(cos_theta, ri) > random_float())
			direction = glm::reflect(unit_direction, rec.normal);
		else
			direction = glm::refract(unit_direction, rec.normal, ri);

		scattered = ray(rec.p, direction);
		return true;
	}

private:
	float refraction_index;

	static float reflectance(float cosine, float refraction_index) {
		auto r0 = (1 - refraction_index) / (1 + refraction_index);
		r0 = r0 * r0;
		return r0 + (1 - r0) * glm::pow((1 - cosine), 5);
	}
};