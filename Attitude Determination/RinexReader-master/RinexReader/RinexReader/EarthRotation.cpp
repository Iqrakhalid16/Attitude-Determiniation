#include "pch.h"
#include "EarthRotation.h"


Cart EarthRotation(double transit_time, Cart SatPos)
{
    double rot_angle, mEarthRotation[3][3];
    Cart SatXYZ;

    rot_angle = transit_time * rot_rate;

    //Rotation matrix
    mEarthRotation[0][0] = cos(rot_angle);
    mEarthRotation[0][1] = sin(rot_angle);
    mEarthRotation[0][2] = 0;
    mEarthRotation[1][0] = -sin(rot_angle);
    mEarthRotation[1][1] = cos(rot_angle);
    mEarthRotation[1][2] = 0;
    mEarthRotation[2][0] = 0;
    mEarthRotation[2][1] = 0;
    mEarthRotation[2][2] = 1;

    //Rotate the coordinate
    SatXYZ.X = cos(rot_angle) * SatPos.X + sin(rot_angle) * SatPos.Y + 0;
    SatXYZ.Y = -sin(rot_angle) * SatPos.X + cos(rot_angle) * SatPos.Y + 0;
    SatXYZ.Z = 0 + 0 + 1 * SatPos.Z;

    return SatXYZ;
}