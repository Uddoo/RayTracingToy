//
// Created by yw_li on 2022/9/12.
//

#ifndef RAYTRACINGTOY_RAY_H
#define RAYTRACINGTOY_RAY_H

#include "vec3.h"

class ray {
public:
	ray() {}

	/// 声明一条射线
	/// \param a 射线起点
	/// \param b 射线终点
	ray(const vec3 &a, const vec3 &b) {
		A = a;
		B = b;
	}

	/// 返回射线起点
	/// \return 射线起点
	vec3 origin() const { return A; }

	/// 返回射线的指向
	/// \return 射线的指向
	vec3 direction() const { return B; }

	/// 返回射线上某一点
	/// \param t
	/// \return
	vec3 point_at_parameter(float t) const { return A + B * t; }

	vec3 A;
	vec3 B;
};

#endif //RAYTRACINGTOY_RAY_H
