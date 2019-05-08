/// This is the test bed for my math library - SSF
/// This is currently version 1.16 - SSF Dec 2017

#include "MMath.h"
#include "QMath.h"
#include "EMath.h"
#include "Fourier.h"
#include "Randomizer.h"
#include <glm/vec3.hpp> /// glm::vec3
#include <glm/vec4.hpp> /// glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> /// glm::mat4
#include <glm/gtc/matrix_transform.hpp> /// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> /// glm::value_ptr
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

using namespace MATH;
using namespace glm;

void FFT_test();
void LookAt_Test();
void UnOrtho_Test();
void Rotation_Test();
void Vec3Mat4Test();
void multiplyMatrixTest();
void viewportNDCTest();

/// Utility call for glm to my world
void glmPrintM4(glm::mat4  mat);



int main(int argc, char*argv[]) {


	Euler euler1, euler2, euler3; /// Just some temps
	Euler orientation(0.0f, 90.0f, 0.0f);
	printf("Orientation: "); orientation.print();
	
	Matrix3 rotationM = EMath::EulerToMatirix3(orientation);
	printf("Rotation Matrix:\n "); rotationM.print();

	///EMath::Matrix3ToEuler(rotationM, euler1, euler2);

	euler3 = EMath::Matrix3ToEuler(rotationM);
	///printf("Euler1:"); euler1.print();
	///printf("Euler2:"); euler2.print();
	printf("Euler3:"); euler3.print();


	

	printf("\nHere are the resulting matricies\n");
	Matrix3 m1 = EMath::EulerToMatirix3(euler3);
	m1.print();
	printf("\n");

	//Matrix3 m2 = EMath::EulerToMatirix3(euler2);
	//m2.print();


	getchar();
}


void viewportNDCTest() {
	Matrix4 m = MMath::viewportNDC(1024, 1024);
	Vec3 pos0(0, 0, 0);
	Vec3 result0 = m * pos0;
	result0.print();

	Vec3 pos1(-1, 1, 0);
	Vec3 result1 = m * pos1;
	result1.print();
}

void multiplyMatrixTest() {
	Matrix4 tmSSF = MMath::translate(10.0f, 10.0f, 10.0f);
	Matrix4 rmSSF = MMath::rotate(90.0, 0, 1.0f, 0);
	Matrix4 resultSSF = tmSSF * rmSSF;
	resultSSF.print();

	glm::mat4 mt = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
	glm::mat4 mr = glm::rotate(mat4(), 90.0f*DEGREES_TO_RADIANS, vec3(0, 1.0f, 0));
	glm::mat4 result = mt * mr;
	
	glmPrintM4(result);
	getchar();
}
void Vec3Mat4Test() {
	Matrix4 translate = MMath::rotate(90.0, 0.0, 1.0,0.0);
	Vec3 pos(5.0, 0.0, 0.0);
	Vec4 xxx = pos;
	xxx.print();
	Vec3 result = translate * pos;
	result.print();
}
void Rotation_Test(){
	mat4 rot2 = rotate(mat4(), 3.141592654f/2.0f, vec3(1.0f,0.0f,0.0f));
	float  m[16] = {0.0};

	const float *pSource = (const float*)glm::value_ptr(rot2);
	for (int i = 0; i < 16; ++i)
		m[i] = pSource[i];
	printf("%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n\n",
				m[0], m[4], m[8],  m[12],
				m[1], m[5], m[9],  m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]);

}
void UnOrtho_Test(){
		int w = 800, h = 600;
		Matrix4 ndc = MMath::viewportNDC(w,h);
	
		float xMax = 10.0, xMin = -10.0, yMax = 10.0, yMin = -10.0, zMax = 1.0, zMin = -10.0;
		Matrix4 ortho = MMath::orthographic(xMin, xMax, 
											yMin, yMax, 
											zMin, zMax);

		Matrix4 projection = ortho * ndc;
		projection.print();
	
		Matrix4 m;
		/// This is the ortho * ndc matrix broken down into its parts 
		Matrix4 m1 = MMath::scale(2.0f / (xMax - xMin), 2.0f / (yMax - yMin),-2.0f / (zMax - zMin));
		Matrix4 m2 = MMath::translate( -(xMax + xMin) / (xMax - xMin), -(yMax + yMin) / (yMax - yMin), -(zMax + zMin) / (zMax - zMin)); 
		Matrix4 m3 = MMath::scale(1.0f, -1.0f, 1.0f);
		Matrix4 m4 = MMath::scale(float(w)/2.0f, float(h)/2.0f, 1 - 0);
		Matrix4 m5 = MMath::translate(float(w)/2.0f,float(h)/2.0f, 0);

		/// Here they are in their inverse 
		Matrix4 m6 = MMath::inverse(m1);
		Matrix4 m7 = MMath::translate( (xMax + xMin) / (xMax - xMin), (yMax + yMin) / (yMax - yMin), (zMax + zMin) / (zMax - zMin)); 
		Matrix4 m8 = MMath::scale(1.0f, -1.0f, 1.0f);
		Matrix4 m9 = MMath::inverse(MMath::scale(float(w)/2.0f, float(h)/2.0f, 1 - 0));
		Matrix4 m10 = MMath::translate(-float(w)/2.0f,-float(h)/2.0f, 0);

		m = m1*m2*m3*m4*m5;  /// creates the ortho * ndc
		m *= m10 *m9 *m8 *m7 *m6; /// Now back out 
		m.print(); /// Should be an identity matrix
		/// It is!!!
		
		Matrix4 invOrtho = MMath::unOrtho(projection );
		invOrtho.print();
		Vec3 v1(400.0,300.0,0.0);
		Vec3 v2(10.0,0.0,10.0);
		Vec3 result1 = invOrtho  * v1;
		result1.print();
		
	}


void LookAt_Test(){

	glm::mat4 mt = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f),
								glm::vec3(0.0f, 0.0f, 0.0f), 
								glm::vec3(1.0f, 0.0f, 0.0f));
	
	Vec3 v = Vec3(0, 0, 0);
	Matrix4 lookat = MMath::lookAt(Vec3(0.0,0.0,-10.0), Vec3(0,0,0), Vec3(1,0,0));
	
	lookat.print();
	glmPrintM4(mt);
	Vec3 v1 = lookat * v;
	v1.print();
	
	


}


void FFT_test(){
#define SAMPLE_SIZE 512
	FILE *fp;

	float data[2 * SAMPLE_SIZE];
	float orig_data[2 * SAMPLE_SIZE];
	float transformed[2 * SAMPLE_SIZE];

	/// Change this as you will, keep it under the Nyquist frequency (1/2*step)
	float freq = 2.0f;
	float theta = 0.0f;
	float step = 2.0f * M_PI / SAMPLE_SIZE;

	Randomizer r; /// I'll use this to create some noise

	//////////////////////////////////////////////////////////////////
	/// Create a data sample SAMPLE_SIZE long times 2 (real and imaginary components)
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		data[i] = cos(theta * freq) + 0.7f*cos(theta * freq * 3) + (float) r.box_muller(0.0, 0.5); /// real
		data[i + 1] = 0.0f;									  ///img
		theta += step;
	}
	//////////////////////////////////////////////////////////////////



	/// Just make a copy of the original data
	memcpy(orig_data, data, 2 * SAMPLE_SIZE * sizeof(float));


	/// Now do the FFT on the noisy data
	Fourier::fft(data, 2 * SAMPLE_SIZE, Fourier::DIRECTION::FORWARD);

	/// Keep a copy of the tranformed data
	memcpy(transformed, data, 2 * SAMPLE_SIZE * sizeof(float));

	//////////////////////////////////////////////////////////////////
	/// A cheezy version of a filter
	//for (int i = 0; i < 2 * SAMPLE_SIZE; i++){
	//if (abs(data[i] < 100.0f)) data[i] = 0.0f;
	//}

	//////////////////////////////////////////////////////////////////
	/// Now do the reverse transform then renormalize
	Fourier::fft(data, 2 * SAMPLE_SIZE, Fourier::DIRECTION::REVERSE);

	/// Re-normalize the data
	for (int i = 0; i < 2 * SAMPLE_SIZE; i++){
		data[i] *= 1.0f / float(SAMPLE_SIZE);
	}

	//////////////////////////////////////////////////////////////////
	/// Write it all out in files
	//////////////////////////////////////////////////////////////////
	if (fopen_s(&fp, "0.orig_data.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f\n", orig_data[i], orig_data[i + 1]);
	}
	fclose(fp);



	if (fopen_s(&fp, "1.transformed.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f\n", transformed[i], transformed[i + 1]);
	}
	fclose(fp);


	if (fopen_s(&fp, "2.orig&reverse.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f, %f, %f\n", orig_data[i], orig_data[i + 1], data[i], data[i + 1]);
	}
	fclose(fp);


}

/// This is a print statement for a glm::mat4 - they don't have one 
void glmPrintM4(glm::mat4  mat) {
	int i, j;
	for (j = 0; j<4; j++) {
		for (i = 0; i<4; i++) {
			printf("%1.8f ", mat[i][j]);
		}
		printf("\n");
	}
}