// usecases_ba.cpp : Bundle Adjustment

#include "stdafx.h"

#include "usecases_ba.h"

Vec2<Real> radial_distort(Vec2<Real> rad_params, Vec2<Real> proj)
{
    Real rsq = sumsq(proj);
    Real L = 1.0 + rad_params[0] * rsq + rad_params[1] * rsq*rsq;
    return proj * L;
}

Vec3<Real> rodrigues_rotate_point(Vec3<Real> rot, Vec3<Real> x)
{
    Real sqtheta = sumsq(rot);
    if (sqtheta != 0.0) {
        Real theta = sqrt(sqtheta);
        Real costheta = cos(theta);
        Real sintheta = sin(theta);
        Real theta_inv = 1. / theta;
        Vec3<Real> w = rot * theta_inv;
        Vec3<Real> w_cross_X = cross(w, x);
        Real tmp = dot(w, x) * (1.0 - costheta);
        Vec3<Real> v1 = x * costheta;
        Vec3<Real> v2 = w_cross_X * sintheta;
        return v1 + v2 + w * tmp;
    }
    else
        return x + cross(rot, x);
}

Vec2<Real> project(Vec<Real, N_CAM_PARAMS> cam, Vec3<Real> x)
{
    Vec3<Real> rot = cam.segment<ROT_IDX, ROT_IDX + 2>();
    Vec3<Real> center = cam.segment<CENTER_IDX, CENTER_IDX + 2>();
    Vec3<Real> Xcam = rodrigues_rotate_point(rot, x - center);
    Vec2<Real> rad_params = cam.segment<RAD_IDX, RAD_IDX + 1>();
    Vec2<Real> distorted = radial_distort(rad_params, Xcam.head<2>() / Xcam[2]);
    return cam.segment<X0_IDX, X0_IDX + 1>() + distorted * cam[FOCAL_IDX];
}

Vec2<Real> compute_reproj_err(Vec<Real, N_CAM_PARAMS> cam, Vec3<Real> x, Real w, Vec2<Real> feat)
{
    return (project(cam, x) - feat) * w;
}
