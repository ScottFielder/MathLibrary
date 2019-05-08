#ifndef STACKMNGR_H
#define STACKMNGR_H

#include "Matrix.h"
#include "MatrixStack.h"


/// This class is used to manage the various matrix stacks in OpenGL programming version 330 and on.
/// This is created as singleton since more than one Stack Manager would be confusing if not stupid - SSF

namespace MATH {

	class StackMngr {
	public:
		/// An enum for the three needed matricies.  Both projection and ModelView are treated as matrix stacks,
		/// the normal matrix is derived before being returned. 
		enum StdMatricies {
			PROJECTION, MODELVIEW, NORMAL
		};

	private:
		static StackMngr* instance; 
		MatrixStack* projection;
		MatrixStack* modelView; 
		MatrixStack* currentMatrixStack; /// Point to the top of whichever stack is currently active
		float normal[9];   /// The normal matrix doesn't need a stack


		StackMngr(); /// Default starting condition of the Manager is PROJECTION matrix
		~StackMngr();

	public:
		/// Don't allow these to be created by default
		StackMngr(const StackMngr&) = delete;
		StackMngr(StackMngr&&) = delete;
		StackMngr& operator=(const StackMngr&) = delete;
		StackMngr& operator=(StackMngr&&) = delete;
		
	public:
		/// This makes it a singleton
		static StackMngr* getInstance();

		/// Don't forget to kill the instance - 
		/// probably should use a smart pointer to insure this, hmm
		static void deleteInstance();


		/// works just like the OpenGL version - selects which matrix stack is active
		void matrixMode(StdMatricies whichMatrix);

		void loadIdentity();
		void loadMatrix(const Matrix4& m);   
		void multMatrix(const Matrix4& m);
		
		void pushMatrix();			/// Warning: can throw a std::string exception on overflow 
		void popMatrix();			/// Warning: can throw a std::string exception on underflow 


		void scale(const float x, const float y, const float z);	
		void translate(const float x, const float y, const float z);
		void rotate(const float radians, const float x, const float y, const float z);


		void perspective( const float fovy, const float aspect,const float zNear, const float zFar);
		void lookAt( const Vec3& eye, const Vec3& at, const Vec3& up );

		/// An inline operator overload to mult a vector by the top of the matrix stack
		inline Vec4 operator * ( const Vec4& v ) const { return *currentMatrixStack * v;}
		const float* getMatrixfv(StdMatricies whichMatrix);

		/// Just return the currently active matrix as a float array
		const float* getMatrixfv() ;

		void print() ;
	};

}
#endif