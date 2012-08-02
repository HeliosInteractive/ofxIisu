/* Version: $Id: Maths.h 7299 2010-01-20 15:33:45Z jeremie $ */

//include the standard math library
#include <math.h>
#include <cstdlib> //random generator

namespace SK 
{

	//*************** INTEGER ARITHMETIC *************** 

	SK_FORCE_INLINE int32_t Math::clamp(int32_t val, int32_t low, int32_t high)
	{
		if( val <= low) return low;
		if( val >= high) return high;
		return val;
	}

	SK_FORCE_INLINE int32_t Math::iAbs (int32_t number)
	{
		return ( number >= 0 ? number : -number );
	}

	SK_FORCE_INLINE int32_t Math::iSign (int32_t number)
	{
		return ( number > 0 ? +1 : ( number < 0 ? -1 : 0 ) );
	}

	SK_FORCE_INLINE int32_t Math::iCeil (float number)
	{
		return int32_t(ceil(number));
	}

	SK_FORCE_INLINE int32_t Math::iFloor (float number)
	{
		return int32_t(floor(number));
	}

	//***************  FLOAT ARITHMETIC *************** 

	SK_FORCE_INLINE bool Math::equal( float a, float b, float tolerance )
	{
		return (SK::Math::abs((float)b-a) <= tolerance);
	}

	SK_FORCE_INLINE float Math::abs (float number)
	{
		return (float)abs((double)number);
	}

	SK_FORCE_INLINE double Math::abs (double number)
	{
		return ::fabs(number);
	}

	SK_FORCE_INLINE int32_t Math::abs (int32_t number)
	{
		return ::abs(number);
	}

	SK_FORCE_INLINE float Math::sign (float number)
	{
		return ( number > 0.0f ? +1.0f : ( number < 0.0f ? -1.0f : 0.0f ) );
	}

	//Wow!  What does "ceil(PI_OVER_180*number)"  means ?  --corrected
	SK_FORCE_INLINE float Math::ceil (float number)
	{
		return (float)::ceil(number);
	}

	SK_FORCE_INLINE float Math::floor (float number)
	{
		return (float)::floor(number);
	}

	SK_FORCE_INLINE float Math::fmod (float numerator, float denominator)
	{
		return (float)::fmod(numerator, denominator);
	}

	SK_FORCE_INLINE float Math::clamp(float val, float low, float high)
	{
		if( val <= low) return low;
		if( val >= high) return high;
		return val;
	}

	SK_FORCE_INLINE float Math::lerp(float value1, float value2, float interpolater) 
	{
		return value1 + (value2 - value1) * interpolater;
	}

	SK_FORCE_INLINE float Math::exp (float number)
	{
		return (float)::exp(number);
	}

	SK_FORCE_INLINE float Math::log (float number)
	{
		return (float)::log(number);
	}

	SK_FORCE_INLINE int16_t Math::pow (int16_t baseVal, int16_t exponentVal)
	{
		while( exponentVal > 1 )
		{
			baseVal *= baseVal;
			--exponentVal;
		}
		return baseVal;
	}

	SK_FORCE_INLINE float Math::pow (float fBase, float fExponent)
	{
		return (float)::pow(fBase, fExponent);
	}

	SK_FORCE_INLINE float Math::sqr (float number)
	{
		return number*number;
	}

	SK_FORCE_INLINE float Math::sqrt (float number)
	{
		return (float)sqrt((double)number);
	}

	SK_FORCE_INLINE double Math::sqrt (double number)
	{
		return ::sqrt(number);
	}

	SK_FORCE_INLINE float Math::invSqrt (float number)
	{
		assert(number!=0.0f);
		return 1.0f / sqrt(number);
	}

	//***************  FLOAT TRIGONOMETRY *************** 

	SK_FORCE_INLINE float Math::degreeToRadian(float fDegreeValue)
	{		
		return fDegreeValue*PI_OVER_180;
	}

	SK_FORCE_INLINE float Math::radianToDegree(float fRadianValue)
	{
		return fRadianValue*PI_UNDER_180;
	}

	SK_FORCE_INLINE float Math::cos (float number)
	{
		return (float)::cos(number);
	}

	SK_FORCE_INLINE double Math::cos (double number)
	{
		return (double)::cos(number);
	}

	SK_FORCE_INLINE float Math::sin (float number)
	{
		return (float)::sin(number);
	}

	SK_FORCE_INLINE double Math::sin (double number)
	{
		return (double)::sin(number);
	}

	SK_FORCE_INLINE float Math::tan (float number)
	{
		return (float)::tan(number);
	}

	SK_FORCE_INLINE double Math::tan (double number)
	{
		return (double)::tan(number);
	}

	SK_FORCE_INLINE float Math::aCos (float number)
	{
		if ( -1.0f < number )
		{
			if ( number < 1.0f )
				return (float)::acos(number);
			else
				return 0.0f;
		}
		else
		{
			return PI;
		}
	}

	SK_FORCE_INLINE double Math::aCos (double number)
	{
		if ( -1.0 < number )
		{
			if ( number < 1.0 )
				return (double)::acos(number);
			else
				return 0.0;
		}
		else
		{
			return PI_DOUBLE;
		}
	}

	SK_FORCE_INLINE float Math::aSin (float number)
	{
		if ( -1.0f < number )
		{
			if ( number < 1.0f )
				return (float)::asin(number);
			else
				return -HALF_PI;
		}
		else
		{
			return HALF_PI;
		}
	}

	SK_FORCE_INLINE float Math::aTan (float number)
	{
		return (float)::atan(number);
	}

	SK_FORCE_INLINE float Math::aTan2 (float fY, float fX)
	{
		return (float)::atan2(fY,fX);
	}

	SK_FORCE_INLINE float Math::normalizeInMinusPiPi(float angle)
	{
		return SK::Math::ceil((angle - SK::Math::PI) / (2.0f * SK::Math::PI)) * -2.0f * SK::Math::PI + angle;
	}

	SK_FORCE_INLINE void  Math::setSeed(uint32_t seed)
	{
		srand(seed);
	}	

	SK_FORCE_INLINE int32_t Math::getRAND_MAX()
	{
		return RAND_MAX;
	}

	SK_FORCE_INLINE int32_t Math::random()
	{
		return rand();
	}

	SK_FORCE_INLINE float Math::unitRandom ()
	{
//		static const float REAL_RAND_MAX = (float) RAND_MAX; - causes optimisation issues leading to undefined symbol.
		return float( (float) Math::random() / (float) RAND_MAX );	
	}

	SK_FORCE_INLINE float Math::symmetricRandom ()
	{
		return 2.f * unitRandom() - 1.0f;
	}	

	SK_FORCE_INLINE float Math::normalRandom(float mean /*= 0.0f*/, float stdDev /*= 1.0f*/)
	{
		// This implementation is the Box-Muller method (see http://mathworld.wolfram.com/Box-MullerTransformation.html).
		// NOTE: this method generates two samples drawn from a reduced normal distribution. In order to take advantage
		//       of these two samples returned be computation, we maintain a static boolean (called wasY1Used) that
		//       keeps track of the calls.
		float x1, x2, w, y1;
		static float y2;
		static bool wasY1Used = false;

		if (wasY1Used)
		{
			wasY1Used = false;

			y1 = y2;

		}
		else
		{
			wasY1Used = true;

			do
			{
				x1 = 2.0f * unitRandom() - 1.0f;
				x2 = 2.0f * unitRandom() - 1.0f;

				w = x1 * x1 + x2 * x2;
			} while ( w >= 1.0f );

			w = sqrt( (-2.0f * log(w) ) / w );
			y1 = x1 * w;
			y2 = x2 * w;
		}

		return mean + y1 * stdDev ;
	}

}//end of namespace SK

