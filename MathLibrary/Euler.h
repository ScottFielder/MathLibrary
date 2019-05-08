#ifndef EULAR_H
#define EULAR_h
#include <stdio.h>

namespace MATH {

	class  Euler {
	public:
		float xAxis;
		float yAxis;
		float zAxis;

		/// Just a little utility to populate a vector
		inline void set(float _xAxis, float _yAxis, float _zAxis) {
			xAxis = _xAxis; yAxis = _yAxis; zAxis = _zAxis;
		}

		/// Here's a set of constructors
		inline Euler(float s = float(0.0)) {
			set(s, s, s);
		}

		inline Euler(float _xAxis, float _yAxis, float _zAxis) {
			set(_xAxis, _yAxis, _zAxis);
		}

		/// A copy constructor
		inline Euler(const Euler& e) {
			/// In this context "const" means I promise not to modify anything v points to 
			set(e.xAxis, e.yAxis, e.zAxis);
		}

		///////////////////////////////////////////////////////////
		/// Operator overloads 
		///////////////////////////////////////////////////////////

		/// An assignment operator   
		inline Euler& operator = (const Euler& e) {
			set(e.xAxis, e.yAxis, e.zAxis);
			return *this;
		}


		/// Now we can use the Vec3 like an array but we'll need two overloads
		inline const float operator [] (int index) const {  /// This one is for reading the Euler as if where an array
			return *(&xAxis + index);
		}

		inline float& operator [] (int index) {	/// This one is for writing to the Euler as if where an array.  
			return *(&xAxis + index);					
		}

		inline void print() {
			printf("%f %f %f\n", xAxis, yAxis, zAxis);
		}
	};
}
#endif
