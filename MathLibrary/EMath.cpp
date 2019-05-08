#include "EMath.h"
#include "MMath.h"

using namespace MATH;

/// Convert Eular angles to a 3x3 rotation matrix
Matrix3 EMath::EulerToMatirix3(const Euler& e) {
	/// Note: If you want to multiply xaxis, yaxis,zaix in that order. I think
	/// it should be m = z * y * x <- reading right to left. Just my opinion.  
	Matrix3 m = Matrix3(MMath::rotate(e.zAxis, Vec3(0.0f, 0.0f, 1.0f)) *
						MMath::rotate(e.yAxis, Vec3(0.0f, 1.0f, 0.0f)) *
						MMath::rotate(e.xAxis, Vec3(1.0f, 0.0f, 0.0f)));
	return m;
}



#define RAD2DEGREES 180.0f/M_PI
/// Convert a 3x3 rot matrix to Eular angles. I claim there are two solutions
/// So I will load e1 and e2 with the solutions - this is just beta
void EMath::Matrix3ToEuler(const Matrix3 &m, Euler &e1, Euler &e2) {
	//printf("m[2] = %1.20f\n", m[2]);
	if (m[2] < 1.0f && m[2] > -1.0f) {
		e1.yAxis = -asin(m[2]);
		e2.yAxis = M_PI - -asin(m[2]);

		e1.xAxis = atan2(m[5] / cos(e1.yAxis), m[8] / cos(e1.yAxis));
		e2.xAxis = atan2(m[5] / cos(e2.yAxis), m[8] / cos(e2.yAxis));

		e1.zAxis = atan2(m[1] / cos(e1.yAxis), m[0] / cos(e1.yAxis));
		e2.zAxis = atan2(m[1] / cos(e2.yAxis), m[0] / cos(e2.yAxis));

		e1.xAxis *= RAD2DEGREES;
		e1.yAxis *= RAD2DEGREES;
		e1.zAxis *= RAD2DEGREES;

		e2.xAxis *= RAD2DEGREES;
		e2.yAxis *= RAD2DEGREES;
		e2.zAxis *= RAD2DEGREES;
		

			
	} else { /// m[2] would have to be +/- 1.000000000000f exactly
		printf("Special case: Gimbal lock!\n");
	}

}



Euler EMath::Matrix3ToEuler(const Matrix3 &m) {
	Euler e;
	e.xAxis = atan2(m[5], m[8]);

	float cos1 = cos(e.xAxis);
	float cos2 = sqrt((m[0] * m[0]) + (m[1] * m[1]));
	float sin1 = sin(e.xAxis);
	
	e.yAxis = atan2(-m[2], cos2);
	e.zAxis = atan2(sin1*m[6] - cos1*m[3], cos1*m[4] - sin1*m[7]);

	e.xAxis *= RAD2DEGREES;
	e.yAxis *= RAD2DEGREES;
	e.zAxis *= RAD2DEGREES;
	return e;
}
#undef RAD2DEGREES