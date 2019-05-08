#ifndef QUATERTNION_H
#define QUATERTNION_H
#include "VMath.h"
#include "Matrix.h"

namespace  MATH {

	struct Quaternion : public Vec3 { 
		float w;

		/// Just a little utility to populate a quaternion
		inline void load( float _w, float _x, float _y, float _z ) {
			w = _w; x = _x; y = _y; z = _z; 
		}

		/// This is the unit quaterion by definition 
		inline Quaternion(){
			load(1.0f,0.0f,0.0f,0.0f);
		}


		inline Quaternion(float _w, float _x,  float _y, float _z){
			load(_w,_x,_y,_z);
		}

		/// This is the constructor for a rotation  quartinion 
		/// The w component is degrees and n is the axis of rotations 
		inline Quaternion( float angle, const Vec3& n){
			angle *= DEGREES_TO_RADIANS; ///
			load(cos(angle/2.0f), sin(angle/2.0f)*n.x, sin(angle/2.0f)*n.y, sin(angle/2.0f)*n.z );
		}

		
		/// A copy constructor
		inline Quaternion( const Quaternion& q ) { 
			load(q.w, q.x, q.y, q.z); 
		}

		/// An assignment operator   
		inline Quaternion& operator = (const Quaternion& q){
			load(q.w, q.x, q.y, q.z); 
			return *this;
		}

		/// Take the negative of a Quaternion
		inline const Quaternion operator - () const  { 
			return Quaternion(-w, -x, -y, -z ); 
		}  

		/// Multiply a two quaternions - using the right-hand rule  
		inline const Quaternion operator * (const Quaternion& q) const {
			Vec3 ijk(w*q + q.w * (*this) + VMath::cross(*this, q));
			return Quaternion(w * q.w - VMath::dot(*this, q), ijk.x, ijk.y, ijk.z);
		}

		/// Multiply a quaternion by a Vec3 - using the right-hand rule 
		inline const Quaternion operator * (const Vec4& v) const {
			Vec3 ijk(w*v + v.w * (*this) + VMath::cross(*this, v));
			return Quaternion(w * v.w - VMath::dot(*this, v), ijk.x, ijk.y, ijk.z);
		}
		

		inline const Quaternion conjugate() const {
			return Quaternion( w, -x, -y, -z ); 
		}

		inline Vec3 rotate(const Vec3& v){
			/// This is the standard way q*v*q^-1
			///return Vec3( (*this) * v * (*this).conjugate());

			/// I read an article that shows this way to be faster and it works! 
			Vec3 v2 = VMath::cross(*this, v);
			return v + v2 * (2.0f * w) + VMath::cross(*this, v2) * 2.0f;
		}


		inline  Matrix4 toMatrix(){
			/// This is the fastest way I know...
			 return Matrix4((1.0f - 2.0f*y*y - 2.0f*z*z), (2.0f*x*y + 2.0f * z*w),      (2.0f*x*z - 2.0f*y*w),        0.0f,
					(2.0f*x*y - 2.0f*z*w),        (1.0f - 2.0f*x*x - 2.0f*z*z), (2*y*z + 2*x*w),              0.0f,
					(2.0f*x*z + 2.0f*y*w),        (2.0f*y*z - 2*x*w),           (1.0f - 2.0f*x*x - 2.0f*y*y), 0.0f,
					0.0f,                         0.0f,                         0.0f,                        1.0f);

			/// ... but this is the coolest . My way is just a bit faster on single processor machines,
			/// this method is faster on parallel multicore machines.
			/***
			 Matrix m1( w,  z,  -y,  x,
				   -z,   w,   x,  y,
				    y,  -x,   w,  z,
				   -x,  -y,  -z,  w);

			Matrix m2(  w,   z,  -y,  -x,
				   -z,   w,   x,  -y, 
				    y,  -x,   w,  -z,
				   -x,   y,   z,   w);
			return m1 * m2;
			***/
		}


		/// To work this out you can multipy the three angles as quaternions together. 
		/// q = q(yaw) * q(pitch) * q(roll) the result is as follows
		inline const Quaternion fromEuler(float _yaw, float _pitch, float _roll){
			float cosYaw = cos(0.5f *_yaw * DEGREES_TO_RADIANS);
			float cosPitch = cos(0.5f * _pitch * DEGREES_TO_RADIANS);
			float cosRoll = cos(0.5f  *_roll * DEGREES_TO_RADIANS);
			float sinYaw = sin(0.5f *_yaw * DEGREES_TO_RADIANS);
			float sinPitch = sin(0.5f * _pitch * DEGREES_TO_RADIANS);
			float sinRoll = sin(0.5f  *_roll * DEGREES_TO_RADIANS);
			return Quaternion(	
				(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll),
				(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
				(cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
				(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll));
		}

		
		inline void print() { 
			printf("%f %f %f %f\n", w,x,y,z);		  
		}

	};
}
#endif
