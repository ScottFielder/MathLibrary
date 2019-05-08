#ifndef VECTOR_H
#define VECTOR_H
#include <string> /// Used for passing exceptions 
		///
		/// Vec3 definitions followed by Vec4 
		/// a Plane plus a Sphere is added at the end just for fun.
		/// There are notes at the bottom of this file you might want to read
		///

namespace  MATH {

/// This is used in normalizing vectors. Dividing by zero is a well known
/// problem but dividing by nearly zero is also a problem. 1.0x10-7 is very
/// small in "float" percision. 
	#ifndef VERY_SMALL
	#define VERY_SMALL 1.0e-7f
	#endif

	#ifndef M_PI
	#define M_PI 3.14159265358979323846f
	#endif

	#ifndef DEGREES_TO_RADIANS
	#define DEGREES_TO_RADIANS (M_PI / 180.0f)
	#endif	


	struct Vec3 {
		float  x,y,z;	///  Structures are default public!
		
		/// Just a little utility to populate a vector
		inline void Load( float _x, float _y, float _z ) {
			x = _x; y = _y; z = _z; 
		}

		/// Here's a set of constructors
		inline Vec3( float s = float(0.0) ){
			Load(s,s,s);
		}

		inline Vec3( float _x, float _y, float _z ){
			Load(_x,_y,_z);
		}
		
		/// A copy constructor
		inline Vec3( const Vec3& v ) { 
			/// In this context "const" means I promise not to modify anything v points to 
			Load(v.x,v.y,v.z); 
		}

		///////////////////////////////////////////////////////////
		/// Operator overloads (see note 1 at the end of this file)
		///////////////////////////////////////////////////////////

		/// An assignment operator   
		inline Vec3& operator = (const Vec3& v){
			Load(v.x,v.y,v.z); 
			return *this;
		}

		
		/// Now we can use the Vec3 like an array but we'll need two overloads
		inline const float operator [] ( int index) const {  /// This one is for reading the Vec3 as if where an array
			return *(&x + index); 
		}

		inline float& operator [] ( int index ) {	/// This one is for writing to the Vec3 as if where an array.  
			return *(&x + index);					/// See note 2 at the end of this file about lvalues and rvalues
		}
	

		/// Add two Vec3s
		inline const Vec3 operator + ( const Vec3& v ) const { 
			return Vec3( x + v.x, y + v.y, z + v.z ); 
		}

		/// Add a Vec3 to itself
		inline Vec3& operator += ( const Vec3& v ){ 
			x += v.x;  
			y += v.y;  
			z += v.z;  
			return *this; 
		}

		/// Take the negative of a Vec3
		inline const Vec3 operator - () const  { 
			return Vec3( -x, -y, -z ); 
		}   

		/// Subtract two Vec3s
		inline const Vec3 operator - ( const Vec3& v ) const { 
			return Vec3(x - v.x, y - v.y, z - v.z ); 
		}

		/// Subtract a Vec 3 from itself
		inline Vec3& operator -= ( const Vec3& v ){ 
			x -= v.x;  
			y -= v.y;  
			z -= v.z;  
			return *this;
		}

		/// Multiply a Vec3 by a scalar
		inline const Vec3  operator * ( const float s ) const { 
			return Vec3(s*x, s*y, s*z ); 
		}

		
		/// Multiply a scaler by a Vec3  - Ha! It's the scalar first then the Vec3
		/// Overloaded and a friend, ouch! It's the only way to make it work with a scalar first.
		/// Friends are tricky, look them up. 
		inline friend Vec3 operator * ( const float s, const Vec3& v ) { 
			return v * s; 
		}

		/// Multiply a Vec3 by a scalar and assign it to itself
		inline Vec3& operator *= ( const float s ) { 
			x *= s; 
			y *= s;  
			z *= s;  
			return *this; 
		}
		

		/// Divide by a scalar - Watch for divide by zero issues
		inline const Vec3 operator / ( const float s ) const {
	#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( fabs(s) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
	#endif
		float r = 1.0f / s;
		return *this * r;
		}


		inline Vec3& operator /= ( const float s ) {
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( std::fabs(s) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif // DEBUG
		float r = 1.0f / s;
		*this *= r;
		return *this;
		}

		inline void print() { 
			printf("%f %f %f\n", x,y,z);		  
		}

		///
		/// Type conversion operators 
		///
		inline operator const float* () const {
			return static_cast<const float*>(&x);
		}

		inline operator float* () {
			return static_cast<float*>(&x);
		}

	};


		/// Vec4 definitions
		/// I am intentionally creating a Vec4 from a Vec3 so I can pass a Vec4 into a Subroutine that wants a Vec3
		/// in many cases this will be mathamatically OK, just be careful Vec4's are not quaterinians
		
	struct Vec4: public Vec3 {
		///float  x;	///
		///float  y;	///  
		///float  z;	/// From Vec3
		float  w;

		/// Here's a set of constructors
		inline Vec4( float s = float(0.0) ){ x=s; y=s; z=s; w=s;}
		inline Vec4( float _x, float _y, float _z, float _w){ x=_x; y=_y; z=_z; w=_w;} 
		inline Vec4( const Vec4& v ) { 
			x = v.x;  
			y = v.y;  
			z = v.z; 
			w = v.w;
		}

		inline Vec4( const Vec3& v ) { 
			x = v.x;  
			y = v.y;  
			z = v.z; 
			w = 1.0f;
		}
		
		/// An assignment operator
		inline Vec4& operator = (const Vec4& v){
			x = v.x;  
			y = v.y;  
			z = v.z; 
			w = v.w;
			return *this;
		}

		/// See Vec3 definition 
		inline float& operator [] ( int index ) { 
			return *(&x + index); 
		}
		inline const float operator [] ( int i ) const { 
			return *(&x + i); 
		}

		/// See Vec3 definition 
		inline Vec4 operator + ( const Vec4& v ) const { 
			return Vec4( x + v.x, y + v.y, z + v.z, w + v.w ); 
		}

		/// See Vec3 definition 
		inline Vec4& operator += ( const Vec4& v ){ 
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this; 
		}

		//// See Vec3 definition 
		inline Vec4 operator - () const  { 
			return Vec4( -x, -y, -z, -w );
		}   

		/// See Vec3 definition 
		inline Vec4 operator - ( const Vec4& v ) const { 
			return Vec4( x - v.x, y - v.y, z - v.z, v.w - w);
		}

		/// See Vec3 definition 
		inline Vec4& operator -= ( const Vec4& v ){ 
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		/// See Vec3 definition 
		inline Vec4 operator * ( const float s ) const { 
			return Vec4( s*x, s*y, s*z, s*w);
		}

		/// See Vec3 definition 
		inline Vec4& operator *= ( const float s ) { 
			x *= s;
			y *= s;
			z *= s;
			w*= s;
			return *this;
		}

		/// See Vec3 definition 
		 friend Vec4 operator * ( const float s, const Vec4& v ) { 
			 return v * s; 
		 }


		inline Vec4 operator / ( const float s ) const {
#ifdef DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( std::fabs(s) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif
		float r = 1.0f / s;
		return *this * r;
		}

		inline Vec4& operator /= ( const float s ) {
	#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( std::fabs(s) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
	#endif // DEBUG

		float r = 1.0f / s;
		*this *= r;
		return *this;
		}

		inline void print() { 
			printf("%f %f %f %f\n", x,y,z,w);		  
		}

		///
		/// Type conversion operators 
		///
		inline operator const float* () const { 
			return static_cast<const float*>( &x );
		}

		inline operator float* () { 
			return static_cast<float*>( &x );
		}

	};

	
	/// Just some extra stuff for fun
			
	///		A Sphere could be thought of as a just a center point (x,y,z) 
	///		comes from Vec3 then just add a radius
	struct Sphere : public Vec3 {
		float r;
		Sphere( float s = 0.0f ){ x = s; y = s; z = s; r = s;}

		Sphere( float _x, float _y, float _z, float _r){
			x = _x; y = _y; z = _z; r = _r;
		}

		inline Sphere( const Sphere& v ) { 
			x = v.x;  y = v.y;  z = v.z; r = v.r;
		}

		inline void print() { 
			printf("%f %f %f %f\n", x,y,z,r);		  
		}
	};


	/// A solution to the circular dependency problem.  
	/// This is what is called a "forward declaration."
	/// See note 3 at the bottom of this page.
	class VMath;  
	
	///  float x,y,z; came from vector as the normal to the surface + distance to the surface (d) 
	struct Plane : public Vec3 {
		float d;

		/// Here's a set of constructors
		inline Plane( float _s = 0.0f ){
			x = _s;
			y = _s;
			z = _s;
			d = _s;
		}
		inline Plane( float _x, float _y, float _z, float _d){
			x = _x;
			y = _y;
			z = _z;
			d = _d;
		}
		
		inline Plane( const Plane& v ) { 
			x = v.x;  
			y = v.y;  
			z = v.z; 
			d = v.d;
		}

		/// This creates a normalized equation of a plane.
		/// Important: See note 3.
		inline Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2){
			Vec3 a = v1-v0; 
			Vec3 b = v2-v0;
			Vec3 n = Vec3(a.y * b.z - a.z * b.y, /// This is the cross product
						  a.z * b.x - a.x * b.z,
						  a.x * b.y - a.y * b.x);
			float magnitude = float(sqrt(n.x * n.x + n.y * n.y + n.z * n.z)); /// normalize
		 
			Plane(x / magnitude,y / magnitude, z / magnitude, a.x * b.x + a.y * b.y + a.z * b.z);
		}


		/// Convert this plane into a normalized plane
		inline void normalize(){
			float a = sqrt(x*x + y*y + z*z);
			x /= a;
			y /= a;
			z /= a;
			d /= a; 
		}
		inline void print() { 
			printf("%f %f %f %f\n", x,y,z,d);		  
		}
	};
}

#endif


		/*** Note 1.
		I know, I hate operator overloading as a general rule but a few make sense!! Just be careful and 
		consistent. In the following code, I will overload many operators. I don't believe in 
		overloading when the operator is less than obvious.  
		For example, in this class, the relational operators (== != < > <= >=) might mean "in relation 
		to their magnitude or direction" I'm just not sure. Just write a function to do that and don't make 
		me guess what the operator might mean. Use the idea of "Least Astonishment" don't surprise me,
		or shock me or anything else that will piss me or others off-SSF
		***/

		/*** Note 2.
		In straight C programming, lvalues and rvalues literially means left and right assignments.  For example, 
		int x = 5; x is the lvalue and 5 is the rvalue. Easy. In C++ it get a bit more tricky. The modern idea is
		rvalues are temporary vaules residing in the registers of the CPU. lvalues are actual memory locations.  
		In the code:
			inline float& operator [] ( int index ) {	
				return *(&x + index);					
			}
		To read this precicely, &x is the address of the x variable (the first in the list of x,y,z) add to that 
		address the index as if it were an array. Then *(&x + index) dereferences that address back into the 
		object, the float& reference returns it as an address and thus an lvalue.
		***/

		/*** Note 3.
		The issue here is that I need to use functions in Vector from VMath which require Vector but VMath
		also requires Vector - this is a classic circular dependency problem or sometimes known as mutual recursion.
		To solve this it requires a forward declaration.  A "forward declaration" is the declaration of a class for which 
		the you have not yet given a complete definition of (whateverClass.h). To do this all you need is the statement:  
		"class VMath;"  This warns the compiler that I will be using VMath in Vector; HOWEVER, in this case, it won't work because
		I'm using the vector.h as a totally inlined set of functions - sometimes your just screwed 
		***/