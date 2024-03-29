//
// Created by yw_li on 2022/9/20.
//
#ifndef RAYTRACINGTOY_MATERIAL_H
#define RAYTRACINGTOY_MATERIAL_H

struct hit_record; // 不完全声明

#include "ray.h"
#include "hittable.h"
#include "rtweekend.h"

#define random(a, b) (rand()%(b-a+1)+a) //使用rand()的一个后果是，种子相同时每次的随机结果都相同
#define random1 (float((rand() % 100) / 100.f))

/// 求镜面反射出射向量
/// \param v 入射光线向量
/// \param n 平面单位法向量
/// \return 出射光线向量
//vec3 reflect(const vec3 &v, const vec3 &n) {
//    return v - 2 * dot(v, n) * n;
//}

///
/// \param v
/// \param n
/// \param ni_over_nt
/// \param refracted
/// \return
//bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
//    vec3 uv = unit_vector(v);
//    float dt = dot(uv, n);
//    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
//    if (discriminant > 0) {
//        refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
//        return true;
//    } else {
//        return false;
//    }
//}

class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

// 漫反射
class lambertian : public material {
public:
    lambertian(const vec3 &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 scatter_direction = rec.normal + random_unit_vector(); // 散射方向由random_unit_vector()控制
        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo; // attenuation衰减，控制散射后的光纤强度
        return true;
    }

    vec3 albedo; // 反射率
};

// 金属材质
class metal : public material {
public:
    metal(const vec3 &a, double f) : albedo(a), fuzz(f) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0); // dot < 0 认为吸收
    }

    vec3 albedo; // 反射率
    double fuzz;
};

// 电介质
class dielectric : public material {
public:
    dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        attenuation = vec3(1.0, 1.0, 1.0);

        double etai_over_etat;
        if (rec.front_face) {
            etai_over_etat = 1.0 / ref_idx;
        } else {
            etai_over_etat = ref_idx;
        }

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        if (sin_theta * etai_over_etat > 1.0) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);

        return true;
    }

    float ref_idx;
};

#endif //RAYTRACINGTOY_MATERIAL_H
