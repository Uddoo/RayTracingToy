//
// Created by yw_li on 2022/9/13.
//

#ifndef RAYTRACINGTOY_HITTABLELIST_H
#define RAYTRACINGTOY_HITTABLELIST_H

#include "hittable.h"
#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
    hittable_list() {}

    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;

    virtual bool bounding_box(double t0, double t1, aabb &output_box) const;

public:
    std::vector<std::shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closet_so_far = t_max;

    // 对hitable list中的所有元素进行hit检测，并将最近的hit信息存入rec中
    for (const auto &object: objects) {
        // 每次只对[t_min, closet_so_far]范围内的检测hit，即
        if (object->hit(r, t_min, closet_so_far, temp_rec)) {
            hit_anything = true;
            closet_so_far = temp_rec.t; // 更新closet_so_far信息，closet_so_far只会越来越小
            rec = temp_rec;
        }
    }
    return hit_anything;
}

bool hittable_list::bounding_box(double t0, double t1, aabb &output_box) const {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    // Box整合
    for (const auto &object: objects) {
        if (!object->bounding_box(t0, t1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

#endif //RAYTRACINGTOY_HITTABLELIST_H
