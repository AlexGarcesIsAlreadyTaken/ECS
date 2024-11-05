#ifndef MAT4_H
#define MAT4_H

#include "Core/Math/Constants.h"
#include "Utils/Constants.h"
#include "Core/Math/Vec3.h"

namespace Math {
	struct mat4 {
		Real mat[4][4];

		mat4(Real t) {
			mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = t;
		}

		mat4();

		inline Real* operator[](const uint8_t i) {
			return mat[i];
		}

		inline const Real* operator[](const uint8_t i) const {
			return mat[i];
		}

		inline mat4& operator+=(const mat4& mat) {
			for (uint8_t i = 0; i < 16; ++i) this->mat[i/4][i%4] += mat[i/4][i%4];
			return *this;
		}

		inline mat4& operator-=(const mat4& mat) {
			for (uint8_t i = 0; i < 16; ++i) this->mat[i/4][i%4] -= mat[i/4][i%4];
			return *this;
		}

		inline mat4& operator+=(Real t) {
			for (uint8_t i = 0; i < 16; ++i) this->mat[i/4][i%4] += t;
			return *this;
		}

		inline mat4& operator-=(Real t) {
			return *this += (-t);
		}

		inline mat4& operator*=(Real t) {
			for (uint8_t i = 0; i < 16; ++i) this->mat[i/4][i%4] *= t;
			return *this;
		}

		inline mat4& operator/=(Real t) {
			return *this *= (1/t);
		}

		inline mat4&operator*=(const mat4& mat) {
			mat4 aux = *this;
			for (uint8_t i = 0; i < 4; i++) {
				for (uint8_t j = 0; j < 4; j++) {
					this->mat[i][j] = 0;
					for (uint8_t k = 0; k < 4; k++) {
						this->mat[i][j] += aux[i][k]*mat[k][j];
					}
				}
			}
			return *this;
		}
	};

	mat4 transpose(const mat4& mat) {
		mat4 ret;
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				ret[i][j] = mat[j][i];
			}
		}
		return ret;
	}

	inline mat4 operator+(const mat4& mat, const Real t) {
		mat4 ret;
		for (uint8_t i = 0; i < 16; i++) ret[i/4][i%4] = mat[i/4][i%4] + t;
		return ret;
	}

	inline mat4 operator+(const Real t, const mat4& mat) { return mat + t; }

	inline mat4 operator*(const mat4& mat, const Real t) {
		mat4 ret;
		for (uint8_t i = 0; i < 16; i++) ret[i/4][i%4] = mat[i/4][i%4]*t;
		return ret;
	}

	inline mat4 operator*(const Real t, const mat4& mat) { return mat*t; }

	inline mat4 operator-(const mat4& mat, const Real t) { return mat + (-t); }
	inline mat4 operator-(const Real t, const mat4& mat) { return t + (-1*mat); }

	inline mat4 operator+(const mat4& a, const mat4& b) {
		mat4 mat;
		for (uint8_t i = 0; i < 16; i++) mat[i/4][i%4] = a[i/4][i%4] + b[i/4][i%4];
		return mat;
	}
	
	inline mat4 operator-(const mat4& a, const mat4& b) {
		mat4 mat;
		for (uint8_t i = 0; i < 16; i++) mat[i/4][i%4] = a[i/4][i%4] - b[i/4][i%4];
		return mat;
	}

	inline mat4 operator*(const mat4& a, const mat4& b) {
		mat4 ret;
		for (uint8_t i = 0; i < 4; i++) {
			for (uint8_t j = 0; j < 4; j++) {
					ret[i][j] = 0;
				for (uint8_t k = 0; k < 4; k++) {
					ret[i][j] += a[i][j] + b[i][j];
				}
			}
		}
		return ret;
	}

	inline mat4 translate(const mat4& mat, const vec3& vec) {
		mat4 aux(1);
		aux[0][3] = vec.x; 
		aux[1][3] = vec.y; 
		aux[2][3] = vec.z;
		return aux*mat;
	}

	inline mat4 scale(const mat4& mat, const vec3& vec) {
		mat4 _mat(1);
		_mat[0][0] = vec.x;
		_mat[1][1] = vec.y; 
		_mat[2][2] = vec.z;
		return _mat*mat;
	}

	inline mat4 rotate(const mat4& mat, const vec3& angles) {
		mat4 matZ(1);
		matZ[0][0] = std::cos(angles.z); matZ[0][1] = -std::sin(angles.z);
		matZ[1][0] = std::sin(angles.z); matZ[1][1] = std::cos(angles.z);

		mat4 matY(1);
		matY[0][0] = std::cos(angles.y); matY[0][2] = std::sin(angles.y);
		matY[2][0] = -std::sin(angles.y); matY[2][2] = std::cos(angles.y);

		mat4 matX(1);
		matY[1][1] = std::cos(angles.x); matY[1][2] = -std::sin(angles.x);
		matY[2][1] = std::sin(angles.x); matY[2][2] = std::cos(angles.x);

		return matZ*matY*matX*mat;
	}
};
#endif
