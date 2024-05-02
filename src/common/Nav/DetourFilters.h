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

#ifndef TRINITYCORE_DETOURFILTERS_H
#define TRINITYCORE_DETOURFILTERS_H

#include "DetourCommon.h"
#include "DetourNavMeshQuery.h"
#include "MathUtil.h"

class dtCustomCostQueryFilter: public dtQueryFilter
{
public:
    /**
     * @brief Calculates the cost of traversing between two points based on slope and distance.
     * 
     * @param pa The start position on the edge of the previous and current polygon. [(x, y, z)]
     * @param pb The end position on the edge of the current and next polygon. [(x, y, z)]
     * @param prevRef The reference id of the previous polygon.
     * @param prevTile The tile containing the previous polygon.
     * @param prevPoly The previous polygon.
     * @param curRef The reference id of the current polygon.
     * @param curTile The tile containing the current polygon.
     * @param curPoly The current polygon.
     * @param nextRef The refernece id of the next polygon.
     * @param nextTile The tile containing the next polygon.
     * @param nextPoly The next polygon.
     * @return The cost of traversing between the start and destination points.
     */
    float getCost(const float* pa, const float* pb,
        const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly,
        const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly,
        const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const override
    {
        // Extract coordinates from the input arrays
        float start_x = pa[2], start_y = pa[0], start_z = pa[1];
        float dest_x = pb[2], dest_y = pb[0], dest_z = pb[1];

        // Calculate the slope angle between start and destination points
        float slope_angle_rad = CalculateSlopeAngle(start_x, start_y, start_z, dest_x, dest_y, dest_z);
        
        // Convert slope angle from radians to degrees
        float slope_angle_deg = (slope_angle_rad * 180.0f / M_PI);
        
        // Calculate cost based on slope angle
        // If slope angle is positive, increase cost based on angle value
        float cost_factor = slope_angle_deg > 0 ? 1.0f + (1.0f * (slope_angle_deg / 100)) : 1.0f;
        
        // Calculate distance between start and destination points
        float distance = dtVdist(pa, pb);

        // Calculate total cost based on distance, slope angle cost factor, and area cost
        float total_cost = distance * cost_factor * getAreaCost(curPoly->getArea());

        return total_cost;
    }
};

#endif // TRINITYCORE_DETOURFILTERS_H