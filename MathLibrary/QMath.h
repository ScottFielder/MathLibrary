#ifndef QMATH_H
#define QMATH_H
#include <math.h>
#include "Quaternion.h"
#include "Matrix.h"
namespace MATH{


	class QMath {
	public:
		inline static float mag(const Quaternion &q){
				return(sqrt((q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z) ));
		}

		
	};
}
#endif