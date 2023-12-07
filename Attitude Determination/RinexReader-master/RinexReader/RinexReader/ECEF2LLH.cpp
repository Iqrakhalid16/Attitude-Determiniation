#include "pch.h"
#include "ECEF2LLH.h"


llh ECEF2LLH(Cart XYZ)
{
	llh Out;
    double a, b, e2, e_2, p, theta, lat, lon, N, h;

    // Earth radius in meters
        a = Earth_R;
    // Earth semiminor in meters
        b = semi_minor;

    // Following the procedure proposed by the text book
    e2 = (a * a - b * b) / (a * a);
    p = sqrt(XYZ.X * XYZ.X + XYZ.Y * XYZ.Y);
    e_2 = (a * a - b * b) / (b * b);
    theta = atan(XYZ.Z * a / p / b);
    lat = atan((XYZ.Z + e_2 * b * pow(sin(theta), 3.0)) / (p - e2 * a * pow(cos(theta), 3.0)));
    lon = atan(XYZ.Y / XYZ.X);
    N = a * a / sqrt(a * a * pow(cos(lat), 2.0) + b * b * pow(sin(lat), 2.0));
    h = p / cos(lat) - N;

    // Format the longitude value
    if ((XYZ.X < 0) && (XYZ.Y > 0))
    {
        lon = pi + lon;
    }

    else if ((XYZ.X < 0) && (XYZ.Y < 0))
    {
        lon = lon - pi;
    }

        Out.lat = lat;
        Out.lon = lon;
        Out.alt = h;
       

    return Out;
}