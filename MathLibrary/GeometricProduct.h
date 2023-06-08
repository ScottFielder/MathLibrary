#ifndef GEOMETRICPRODUCT_H
#define GEOMETRICPRODUCT_H
#include "DualQuat.h"
#include "Flector.h"
namespace MATH {

	/// I wrote this out on paper. My wrist is still hurting.
	/// You don't need the brackets, it just helps my eyes
	inline const DualQuat operator * (DualQuat a, DualQuat b) {
		MATH::DualQuat result;
		result.w = (a.w * b.w) - (a.e23 * b.e23) - (a.e31 * b.e31) - (a.e12 * b.e12);
		result.e23 = (a.w * b.e23) + (a.e23 * b.w) -     (a.e31 * b.e12) + (a.e12 * b.e31);
		result.e31 = (a.w * b.e31) + (a.e23 * b.e12) +   (a.e31 * b.w) -   (a.e12 * b.e23);
		result.e12 = (a.w * b.e12) - (a.e23 * b.e31) +   (a.e31 * b.e23) + (a.e12 * b.w);
		result.e01 = (a.w * b.e01) - (a.e23 * b.e0123) - (a.e31 * b.e03) + (a.e12 * b.e02)
			+ (a.e01 * b.w) - (a.e02 * b.e12) + (a.e03 * b.e31) - (a.e0123 * b.e23);
		result.e02 = (a.w * b.e02) + (a.e23 * b.e03) - (a.e31 * b.e0123) - (a.e12 * b.e01)
			+ (a.e01 * b.e12) - (a.e03 * b.e23) + (a.e02 * b.w) - (a.e0123 * b.e31);
		result.e03 = (a.w * b.e03) - (a.e23 * b.e02) + (a.e31 * b.e01) - (a.e12 * b.e0123)
			- (a.e01 * b.e31) + (a.e02 * b.e23) + (a.e03 * b.w) - (a.e0123 * b.e12);
		result.e0123 = (a.w * b.e0123) + (a.e23 * b.e01) + (a.e31 * b.e02) + (a.e12 * b.e03)
			+ (a.e01 * b.e23) + (a.e02 * b.e31) + (a.e03 * b.e12) + (a.e0123 * b.w);
		return result;
	}

	// It's amazing that a plane and a point pops out when you multiply a dual quat with a Vec4 
	// That's why we need the Flectors
	inline const Flector operator * (const DualQuat& dq, const Vec4& p){
		Flector result;
		result.plane.e0 =  dq.e12 * p.e021 + dq.e31 * p.e013 + dq.e23 * p.e032 + dq.e0123 * p.e123;
		result.plane.e1 = -dq.e23 * p.e123;
		result.plane.e2 = -dq.e31 * p.e123;
		result.plane.e3 = -dq.e12 * p.e123;

		result.point.e032 =  dq.e12 * p.e013 - dq.e31 * p.e021 - dq.e01 * p.e123 + dq.w * p.e032;
		result.point.e013 = -dq.e12 * p.e032 + dq.e23 * p.e021 - dq.e02 * p.e123 + dq.w * p.e013;
		result.point.e021 =  dq.e31 * p.e032 - dq.e23 * p.e013 - dq.e03 * p.e123 + dq.w * p.e021;
		result.point.e123 = dq.w * p.e123;
		return result;
	}

	inline const Flector operator * (const Vec4& p, const DualQuat& q) {
		/// A few signs flip when you multiply the other way round
		Flector result;
		result.plane.e0 = q.e12 * p.e021 + q.e31 * p.e013 + q.e23 * p.e032 + q.e0123 * p.e123;
		result.plane.e1 = -q.e23 * p.e123;
		result.plane.e2 = -q.e31 * p.e123;
		result.plane.e3 = -q.e12 * p.e123;

		result.point.e032 = -q.e12 * p.e013 + q.e31 * p.e021 + q.e01 * p.e123 + q.w * p.e032;
		result.point.e013 = q.e12 * p.e032 - q.e23 * p.e021 + q.e02 * p.e123 + q.w * p.e013;
		result.point.e021 = -q.e31 * p.e032 + q.e23 * p.e013 + q.e03 * p.e123 + q.w * p.e021;
		result.point.e123 = q.w * p.e123;
		return result;
	}

	inline const Flector operator * (const Plane& p, const DualQuat& q) {
		Flector result;
		result.plane.e0 = p.e0 * q.w - p.e2 * q.e02 - p.e1 * q.e01 - p.e3 * q.e03;
		result.plane.e1 = p.e1 * q.w - p.e2 * q.e12 + p.e3 * q.e31;
		result.plane.e2 = p.e1 * q.e12 + p.e2 * q.w - p.e3 * q.e23;
		result.plane.e3 = p.e2 * q.e23 + p.e3 * q.w - p.e1 * q.e31;

		result.point.e032 = -p.e0 * q.e23 + p.e1 * q.e0123 + p.e2 * q.e03 - p.e3 * q.e02;
		result.point.e013 = -p.e0 * q.e31 - p.e1 * q.e03 + p.e2 * q.e0123 + p.e3 * q.e01;
		result.point.e021 = -p.e0 * q.e12 + p.e1 * q.e02 - p.e2 * q.e01 + p.e3 * q.e0123;
		result.point.e123 = p.e1 * q.e23 + p.e2 * q.e31 + p.e3 * q.e12;
		return result;
	}

	inline const Flector operator * (const Flector& f, const DualQuat& dq) {
		Flector result = f.point * dq;;
		result += f.plane * dq;
		return result;
	}

	inline const DualQuat operator * (const Plane& plane, const Vec4& point){
		DualQuat result;
		result.w = 0.0f;
		result.e23 = plane.e1 * point.e123;
		result.e31 = plane.e2 * point.e123;
		result.e12 = plane.e3 * point.e123;
		result.e01 = plane.e3 * point.e013 - plane.e2 * point.e021;
		result.e02 = plane.e1 * point.e021 - plane.e3 * point.e032;
		result.e03 = plane.e2 * point.e032 - plane.e1 * point.e013;
		result.e0123 = plane.e0 * point.e123 + plane.e1 * point.e032
			+ plane.e2 * point.e013 + plane.e3 * point.e021;
		return result;
	}

	inline const DualQuat operator * (const Plane& p1, const Plane& p2)
	{
		// Plane 1 * Plane 2 = a dual quaternion
		// This one wasn't too bad to figure out on paper, as a plane only has e0, e1, e2, and e3 inside
		// After multiplying and keeping track of the e combos you end up with a dual quaternion
		DualQuat result;
		result.w = p1.e1 * p2.e1 + p1.e2 * p2.e2 + p1.e3 * p2.e3;
		result.e23 = p1.e2 * p2.e3 - p1.e3 * p2.e2;
		result.e31 = p1.e3 * p2.e1 - p1.e1 * p2.e3;
		result.e12 = p1.e1 * p2.e2 - p1.e2 * p2.e1;
		result.e01 = p1.e0 * p2.e1 - p1.e1 * p2.e0;
		result.e02 = p1.e0 * p2.e2 - p1.e2 * p2.e0;
		result.e03 = p1.e0 * p2.e3 - p1.e3 * p2.e0;
		result.e0123 = 0.0f;
		return result;
	}

	inline const DualQuat operator * (const Vec4& p1, const Vec4& p2)
	{
		// Point 1 * Point 2 = a dual quaternion
		// This one wasn't too bad to figure out on paper either, just end up with the infinite line 
		// and a term for w
		DualQuat result;
		result.w = -p1.e123 * p2.e123;
		result.e23 = 0.0f;
		result.e31 = 0.0f;
		result.e12 = 0.0f;
		result.e01 = p1.e032 * p2.e123 - p1.e123 * p2.e032;
		result.e02 = p1.e013 * p2.e123 - p1.e123 * p2.e013;
		result.e03 = p1.e021 * p2.e123 - p1.e123 * p2.e021;
		result.e0123 = 0.0f;
		return result;
	}
}
#endif