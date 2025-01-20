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
	metal(const color& albedo) : albedo(albedo) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		glm::vec3 reflected = glm::reflect(r_in.direction, rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};