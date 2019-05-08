#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H
#include "MMath.h"
/// This class creates a 4x4 matrix stack. 
namespace  MATH {

class MatrixStack {		
	protected:
		int	stackDepth;  
		int	stackPointer;
		Matrix4	*stack;

	public:
		/// The depth of the stack is default 32 or set it to whatever is required
		MatrixStack(int stackDepth_ = 32);
		~MatrixStack();

		/// C11: prevent these from being created by default 
		MatrixStack(const MatrixStack&) = delete;
		MatrixStack(MatrixStack&&) = delete;
		MatrixStack& operator=(const MatrixStack&) = delete;
		MatrixStack& operator=(MatrixStack&&) = delete;


		/// These functions operate just like their OpenGL counterparts 

		/// Loads the identity matrix on to the top of the stack
		void loadIdentity();

		/// Loads an arbitrary matrix on to the top of the stack
		void loadMatrix(const Matrix4 m);

		/// Multiplies the supplied matrix by the matrix on the top of the stack
		void multMatrix(const Matrix4 m);

		void pushMatrix();				/// Warning: can throw a std::string exception on overflow 
		void popMatrix();				/// Warning: can throw a std::string exception on underflow

		void scale(const float x, const float y, const float z);	
		void translate(const float x, const float y, const float z);
		void rotate(const float angle, const float x, const float y, const float z);

		/// These are copies of the OpenGL glu library 
		void orthographic(const float xMin, const float xMax,
						  const float yMin, const float yMax,
						  const float zMin, const float zMax);
	
		void perspective( const float fovy, const float aspect, const float zNear, const float zFar);
		void lookAt( const Vec3& eye, const Vec3& at, const Vec3& up );

		/// This is my invention 
		void unOrtho(const Matrix4 & ortho);

		//// An inline operator overload to mult a vector by the top of the matrix stack
		inline Vec4 operator * ( const Vec4& v ) const { return stack[stackPointer] * v;}
		
		/// Returns a pointer to the top of the matrix stack as a floating point array
		const float* getMatrixfv() const ;
		void print() const;
	};	
}
#endif