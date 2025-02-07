////////////////////////////////////////////////////////////////////////////
//	Created		: 31.10.2011
//	Author		: Nikolay Partas
//	Copyright (C) GSC Game World - 2011
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "moon_position.h"

namespace vostok {
namespace render {

//http://www.stjarnhimlen.se/comp/tutorial.html#5

void calculate_moon_position(time_parameters const& params, double in_latitude, double in_longitude, double& out_azimuth, double& out_zenith)
{
	vostok::math::float3 result;
	
	// Calc the day number.
	s32	d	= 367 * params.year - (7 * (params.year + ((params.month + 9) / 12))) / 4 + (275 * params.month) / 9 + params.day - 730530;
	
	double dJulianDate;
	double dElapsedJulianDays;
	double dDecimalHours;

	// Auxiliary variables
	double dY;
	double dX;
	// Calculate difference in days between the current Julian Day 
	// and JD 2451545.0, which is noon 1 January 2000 Universal Time
	{
		long int liAux1;
		long int liAux2;
		// Calculate time of the day in UT decimal hours
		dDecimalHours = params.hours + (params.minutes 
			+ params.seconds / 60.0 ) / 60.0;
		// Calculate current Julian Day
		liAux1 =(params.month-14)/12;
		liAux2=(1461*(params.year + 4800 + liAux1))/4 + (367*(params.month 
			- 2-12*liAux1))/12- (3*((params.year + 4900 
			+ liAux1)/100))/4+params.day-32075;
		dJulianDate=(double)(liAux2)-0.5+dDecimalHours/24.0;
		// Calculate difference between current Julian Day and JD 2451545.0 
		dElapsedJulianDays = dJulianDate-2451545.0;

		d = dJulianDate;
	}

    double	N	= 125.1228 - 0.0529538083 * d;		// (Long asc. node)
    double	i	= 5.1454;							// (Inclination)
    double	w	= 318.0634 + 0.1643573223 * d;		// (Arg. of perigee)
    double	a	= 60.2666;							// (Mean distance)
    double	e	= 0.054900;							// (Eccentricity)
    double	M	= 115.3654 + 13.064992950 * d;		// (Mean anomaly)
	
	double	E0	= M + (180.0 / vostok::math::pi) * e * vostok::math::sin(M) * (1 + e * vostok::math::cos(M));
	
	double	E	= E0 - (E0 - (180.0 / vostok::math::pi) * e * vostok::math::sin(E0) - M) / (1 - e * vostok::math::cos(E0));
	
	double	x = a * (vostok::math::cos(E) - e);
	double	y = a * vostok::math::sqrt(1 - e*e) * vostok::math::sin(E);
	
    double	r = vostok::math::sqrt(x*x + y*y);
    double	v = vostok::math::atan2(y, x);
	
    double	xeclip = r * ( vostok::math::cos(N) * vostok::math::cos(v+w) - vostok::math::sin(N) * vostok::math::sin(v+w) * vostok::math::cos(i) );
    double	yeclip = r * ( vostok::math::sin(N) * vostok::math::cos(v+w) + vostok::math::cos(N) * vostok::math::sin(v+w) * vostok::math::cos(i) );
    double	zeclip = r * vostok::math::sin(v+w) * vostok::math::sin(i);
	
	double RA   = vostok::math::atan2( yeclip, xeclip );
    double Decl = vostok::math::atan2( zeclip, vostok::math::sqrt( xeclip * xeclip + yeclip * yeclip ) );
	
//	out_azimuth		= RA;
//	out_zenith		= Decl;


#define dEarthMeanRadius     6371.01	// In km
#define dAstronomicalUnit    384000.0	// In km


	// Calculate local coordinates ( azimuth and zenith angle ) in degrees
	{
		double dGreenwichMeanSiderealTime;
		double dLocalMeanSiderealTime;
		double dLatitudeInRadians;
		double dHourAngle;
		double dCos_Latitude;
		double dSin_Latitude;
		double dCos_HourAngle;
		double dParallax;
		
		double dDecimalHours = params.hours + (params.minutes + params.seconds / 60.0 ) / 60.0;
		
		dGreenwichMeanSiderealTime = 6.6974243242 + 
			0.0657098283 * d 
			+ dDecimalHours;
		dLocalMeanSiderealTime = (dGreenwichMeanSiderealTime*15 + in_longitude) * vostok::math::pi / 180.0;
		dHourAngle = dLocalMeanSiderealTime - RA;
		dLatitudeInRadians = in_latitude * vostok::math::pi / 180.0;
		
		dCos_Latitude = vostok::math::cos( dLatitudeInRadians );
		dSin_Latitude = vostok::math::sin( dLatitudeInRadians );
		dCos_HourAngle= vostok::math::cos( dHourAngle );
		
		out_zenith = (vostok::math::acos( dCos_Latitude*dCos_HourAngle
			*vostok::math::cos(Decl) + vostok::math::sin( Decl )*dSin_Latitude));
		
		double dY = -vostok::math::sin( dHourAngle );
		double dX = vostok::math::tan( Decl )*dCos_Latitude - dSin_Latitude*dCos_HourAngle;
		
		out_azimuth = vostok::math::atan2( dY, dX );
		
		if ( out_azimuth < 0.0 ) 
			out_azimuth = out_azimuth + math::pi_d2;
		
		out_azimuth = out_azimuth / (vostok::math::pi / 180.0);
		
		// Parallax Correction
		dParallax = (dEarthMeanRadius/dAstronomicalUnit)
			*vostok::math::sin(out_zenith);
		
		out_zenith = (out_zenith 
			+ dParallax) / (vostok::math::pi / 180.0);
	}
}

} // namespace render
} // namespace vostok