/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_MATHUTIL_H
#define TRINITYCORE_MATHUTIL_H

#include "Util.h"
#include <cmath>

/**
 * @brief Calculate the angle between two points.
 * 
 * @param start_x The x-coordinate of the starting point.
 * @param start_y The y-coordinate of the starting point.
 * @param end_x The x-coordinate of the ending point.
 * @param end_y The y-coordinate of the ending point.
 * @return The angle between the points.
 */
inline float CalculateAngle(float start_x, float start_y, float end_x, float end_y) {
    float delta_x = end_x - start_x;
    float delta_y = end_y - start_y;

    float angle = atan2(delta_y, delta_x);
    angle = (angle >= 0) ? angle : 2 * static_cast<float>(M_PI) + angle;
    return angle;
}

/**
 * @brief Calculate the slope angle between two points in 3D space.
 * 
 * @param start_x The x-coordinate of the starting point.
 * @param start_y The y-coordinate of the starting point.
 * @param start_z The z-coordinate of the starting point.
 * @param end_x The x-coordinate of the ending point.
 * @param end_y The y-coordinate of the ending point.
 * @param end_z The z-coordinate of the ending point.
 * @return The slope angle between the points.
 */
inline float CalculateSlopeAngle(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z) {
    float floor_distance = sqrt(pow(end_y - start_y, 2.0f) + pow(end_x - start_x, 2.0f));
    return atan(abs(end_z - start_z) / abs(floor_distance));
}

/**
 * @brief Calculate the absolute slope angle between two points in 3D space.
 * 
 * @param start_x The x-coordinate of the starting point.
 * @param start_y The y-coordinate of the starting point.
 * @param start_z The z-coordinate of the starting point.
 * @param end_x The x-coordinate of the ending point.
 * @param end_y The y-coordinate of the ending point.
 * @param end_z The z-coordinate of the ending point.
 * @return The absolute slope angle between the points.
 */
inline float CalculateSlopeAngleAbs(float start_x, float start_y, float start_z, float end_x, float end_y, float end_z) {
    return abs(CalculateSlopeAngle(start_x, start_y, start_z, end_x, end_y, end_z));
}

/**
 * @brief Calculate the area of a circle given its radius.
 * 
 * @param radius The radius of the circle.
 * @return The area of the circle.
 */
inline double CalculateAreaByRadius(double radius) {
    return radius * radius * M_PI;
}

/**
 * @brief Calculate the perimeter of a circle given its radius.
 * 
 * @param radius The radius of the circle.
 * @return The perimeter of the circle.
 */
inline double CalculatePerimeterByRadius(double radius) {
    return radius * static_cast<double>(M_PI);
}

/**
 * @brief Calculate the volume of a cylinder given its height and radius.
 * 
 * @param height The height of the cylinder.
 * @param radius The radius of the cylinder.
 * @return The volume of the cylinder.
 */
inline double CalculateCylinderVolume(double height, double radius) {
    return height * CalculateAreaByRadius(radius);
}

/**
 * @brief Calculate the weight of an object.
 * 
 * @param height The height of the object.
 * @param width The width of the object.
 * @param specific_weight The specific weight of the object.
 * @return The weight of the object.
 */
inline float CalculateWeight(float height, float width, float specific_weight) {
    double volume = CalculateCylinderVolume(height, width / 2.0f);
    float weight = static_cast<float>(volume) * specific_weight;
    return weight;
}

/**
 * @brief Get the height immersed in a liquid plane.
 * 
 * @param width The width of the object.
 * @param weight The weight of the object.
 * @param density The density of liquid.
 * @return The height immersed in liquid.
 */
inline float GetHeightAboveLiquidPlane(float width, float weight, float density) {
    double base_area = CalculateAreaByRadius(width / 2.0f);
    return weight / (static_cast<float>(base_area) * density);
}

#endif // TRINITYCORE_MATHUTIL_H
