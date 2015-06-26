#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <boost/cstdint.hpp> 

namespace Robotics { namespace Mathematics {
/**
* Contains commonly used precalculated values
*/
class MathUtil
{
private:
	static const double SIN[];
	static const double TAN[];
	static const double ASIN[];
	static const double ACOS[];
public:
	/**
	* Represents the mathematical constant e.
	*/
	static const double E; //			2.7182818284590452353602874713527;
	/**
	* Represents the log base ten of e. 
	*/
	static const double Log10E; //		0.43429448190325182765112891891661;
	/**
	* Represents the log base two of e. 
	*/
	static const double Log2E; //		1.4426950408889634073599246810019;
	/**
	* Represents the value of pi. 
	*/
	static const double Pi; //			3.1415926535897932384626433832795;
	/**
	* Represents the value of pi divided by two. 
	*/
	static const double PiOver2; //		1.5707963267948966192313216916398;
	/**
	* Represents the value of pi divided by four. 
	*/
	static const double PiOver4; //		0.78539816339744830961566084581988;
	/**
	* Represents the value of pi divided by six. 
	*/
	static const double PiOver6; //		0.52359877559829887307710723054658;
	/**
	* Represents the value of pi times two. 
	*/
	static const double TwoPi; //		6.283185307179586476925286766559;

	/**
	* Returns the absolute value of a Double number. 
	* @param value A number in the range System.Double.MinValue = value = System.Double.MaxValue. 
	* @return A Double, x, such that 0 = x = System.Double.MaxValue. 
	*/
	static double abs(double value);

	/**
	* Returns the absolute value of a Int16 number. 
	* @param value A number in the range System.Int16.MinValue = value = System.Int16.MaxValue. 
	* @return A Double, x, such that 0 = x = System.Int16.MaxValue. 
	*/
	static boost::int16_t abs(boost::int16_t value);

	/**
	* Returns the absolute value of a Int32 number. 
	*
	* @param value A number in the range System.Int32.MinValue = value = System.Int32.MaxValue. 
	* @return A Double, x, such that 0 = x = System.Int32.MaxValue. 
	*/
	static boost::int32_t abs(boost::int32_t value);

	/**
	* Returns the absolute value of a Int64 number. 
	*
	* @param value A number in the range System.Int64.MinValue = value = System.Int64.MaxValue. 
	* @return A Double, x, such that 0 = x = System.Int64.MaxValue. 
	*/
	static boost::int64_t abs(boost::int64_t value);

	/**
	* Returns the absolute value of a SByte number. 
	*
	* @param value A number in the range System.SByte.MinValue = value = System.SByte.MaxValue. 
	* @return A Double, x, such that 0 = x = System.SByte.MaxValue. 
	*/
	static boost::int8_t abs(boost::int8_t value) ;

	/**
	* Returns the absolute value of a Single number. 
	*
	* @param value A number in the range System.Single.MinValue = value = System.Single.MaxValue. 
	* @return A Double, x, such that 0 = x = System.Single.MaxValue. 
	*/
	static float abs(float value);

	/**
	* Restricts a value to be within a specified range.
	*
	* @param value The value to clamp.
	* @param min The minimum value.
	* @param max The maximum value.
	* @return The clamped value.
	*/
	static double clamp(double value, double min, double max) ;

	/**
	* Restricts a value to be within a specified range.
	*
	* @param value The value to clamp.
	* @param min The minimum value.
	* @param max The maximum value.
	* @return The clamped value.
	*/
	static float clamp(float value, float min, float max) ;

	/**
	* Restricts a value to be within a specified range.
	*
	* @param value The value to clamp.
	* @param min The minimum value.
	* @param max The maximum value.
	* @return The clamped value.
	*/
	static boost::int16_t clamp(boost::int16_t value, boost::int16_t min, boost::int16_t max) ;

	/**
	* Restricts a value to be within a specified range.
	*
	* @param value The value to clamp.
	* @param min The minimum value.
	* @param max The maximum value.
	* @return The clamped value.
	*/
	static boost::int32_t clamp(boost::int32_t value, boost::int32_t min, boost::int32_t max) ;

	/**
	* Restricts a value to be within a specified range.
	*
	* @param value The value to clamp.
	* @param min The minimum value.
	* @param max The maximum value.
	* @return The clamped value.
	*/
	static float clamp(boost::int64_t value, boost::int64_t min, boost::int64_t max) ;

	/**
	* Calculates the absolute value of the difference of two values. 
	* @param value1 Source value.
	* @param value2 Source value.
	* @return Distance between the two values.
	*/
	static double distance(double value1, double value2);

	/**
	* Linearly interpolates between two values
	* This method performs the linear interpolation based on the following formula.
	* value1 + (value2 - value1) * amount
	* Passing amount a value of 0 will cause value1 to be returned, a value of 1 will cause value2 to be returned.
	* @param value1 Source value
	* @param value2 Source value
	* @param amount Value between 0 and 1 indicating the weight of value2
	* @return Interpolated value
	*/
	static double lerp(double value1, double value2, double amount);

	static float correctAngle(const float& aRad);
	static double correctAngle(const double& aRad);
	static double round(const double& value);
	/**
	* Converts radians to degrees. 
	*
	* @param aRad The angle in radians.
	* @return The angle in degrees.
	*/
	static double toDegrees(const double& aRad);
	/**
	* Converts degrees to radians.
	*
	* @param aDeg The angle in degrees.
	* @return The angle in radians.	
	*/
	static double toRadians(const double& aDeg);

	/**
	* Returns the angle whose cosine is the specified number.
	* Values returned by this method are precalculated.
	*
	* @param d A number representing a cosine, where -1 = d = 1.
	* @return An angle, ?, measured in radians, such that 0 = ? = p -or- NaN if d &lt; -1 or d &gt; 1.
	*/
	static double acos(double d);

	/**
	* Returns the angle whose sine is the specified number.
	* Values returned by this method are precalculated.
	* @param d A number representing a sine, where -1 = d = 1. 
	* @return An angle, ?, measured in radians, such that -p/2 = ? =p /2 -or- NaN if d &lt; -1 or d &gt; 1.
	*/
	static double asin(double d);

	/**
	* Returns the cosine of the specified angle.
	* Values returned by this method are precalculated.
	*
	* @param radians An angle, measured in radians. 
	* @return The cosine of  the provided angle. If a is equal to NaN, NegativeInfinity, or PositiveInfinity, this method returns NaN
	*/
	static double cos(double radians);

	/**
	* Returns the sine of the specified angle.
	* Values returned by this method are precalculated.
	*
	* @param radians An angle, measured in radians. 
	* @return The sine of the provided angle. If a is equal to NaN, NegativeInfinity, or PositiveInfinity, this method returns NaN
	*/
	static double sin(double radians);

	/**
	* Returns the tangent of the specified angle
	* Values returned by this method are precalculated.
	*
	* @param radians An angle, measured in radians. 
	* @return The sine of the provided angle. If a is equal to NaN, NegativeInfinity, or PositiveInfinity, this method returns NaN
	*/
	static double tan(double radians);


};

} /*Mathematics*/ } /* Robotics */

#endif // __MATH_UTIL_H__