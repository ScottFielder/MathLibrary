#include "MatrixStack.h"
#include <string>
/// See the header file for more about this class
using namespace MATH;

MatrixStack::MatrixStack(int stackDepth_) {
	stackDepth = stackDepth_;
	stack = new Matrix4[stackDepth];
	stackPointer = 0;
	stack[0].loadIdentity();
}

MatrixStack::~MatrixStack(void) {
	if (stack) delete [] stack;
}

void MatrixStack::pushMatrix() { 
	if(stackPointer < stackDepth) {
		stackPointer++;
		stack[stackPointer] = stack[stackPointer-1];
	}else{
		std::string errorMsg("Stack Overflow");
		throw errorMsg;
	}
}
		
void MatrixStack::popMatrix() {
	if(stackPointer > 0){
		stackPointer--;
	}else{
		std::string errorMsg("Stack Underflow");
		throw errorMsg;
	}
}

void MatrixStack::loadIdentity() { 
	stack[stackPointer].loadIdentity();
}
		
void MatrixStack::loadMatrix(const Matrix4 m) { 
	stack[stackPointer] = m;
}   
            
void MatrixStack::multMatrix(const Matrix4 m) {
	stack[stackPointer] = m * stack[stackPointer];
}
                 					
void MatrixStack::scale(const float x, const float y, const float z) {
	stack[stackPointer] *= MMath::scale(x,y,z);
}
						
void MatrixStack::translate(const float x, const float y, const float z) {
	stack[stackPointer] *= MMath::translate(x,y,z);
}
					
void MatrixStack::rotate(const float angle, const float x, const float y, const float z) {
	stack[stackPointer] *= MMath::rotate(angle,x,y,z);
}

void MatrixStack::orthographic(const float xMin, const float xMax,
								const float yMin, const float yMax,
								const float zMin, const float zMax){
	stack[stackPointer] *= MMath::orthographic(xMin, xMax, yMin, yMax, zMin, zMax);
}

void MatrixStack::unOrtho(const Matrix4 & ortho){
	stack[stackPointer] *= MMath::unOrtho(ortho);
}

void MatrixStack::perspective( const float fovy, const float aspect,const float zNear, const float zFar) {
	stack[stackPointer] *= MMath::perspective(fovy,aspect,zNear,zFar);
}

void MatrixStack::lookAt( const Vec3& eye, const Vec3& at, const Vec3& up ) {
	stack[stackPointer] *= MMath::lookAt(eye.x,eye.y,eye.z, at.x,at.y,at.z ,up.x,up.y,up.z);
}	

void MatrixStack::print() const {
		stack[stackPointer].print();
}

const float* MatrixStack::getMatrixfv() const { return stack[stackPointer]; }