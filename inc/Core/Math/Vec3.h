#ifndef VEC_3_H
#define VEC_3_H

#include <cmath>
#include "Utils/Constants.h"
#include <ostream>

namespace Math {
    template <typename T>
    struct tvec3 {
        union {
          T x;
          T s;
          T p;
        };

        union {
          T y;
          T t;
          T q;
        };

        union {
          T z;
          T v;
          T r;
        };

        tvec3(T x, T y, T z) : x(x), y(y), z(z) {}
        tvec3(T x) : x(x), y(x), z(x) {}
        tvec3() : x(0), y(0), z(0) {}

        inline tvec3& operator+=(T t) {
            x += t; y += t; z += t;
            return *this;
        }

        inline tvec3& operator-=(T t) {
            return *this -= t;
        }

        inline tvec3& operator+=(const tvec3& vec) {
            this->x += vec.x; this->y += vec.y; this->z += vec.z;
            return *this;
        }

        inline tvec3& operator-=(const tvec3& vec) {
            return *this -= vec;
        }

        inline tvec3& operator*=(T t) {
            x *= t; y *= t; z *= t;
            return *this;
        }

        inline tvec3& operator/=(T t) {
            return *this *= (1/t);
        }

        inline tvec3& operator-() {
            return *this *= -1;
        }

        inline const T length_squared() const {
            return x*x + y*y + z*z;
        }

        inline const T length() const {
            return std::sqrt(length_squared());
        }
    };

    template <typename T>
    inline tvec3<T> operator+(const tvec3<T>& vec, T t) {
        return tvec3(vec.x + t, vec.y + t, vec.z + t);
    }

    template <typename T>
    inline tvec3<T> operator-(const tvec3<T>& vec, T t) {
        return vec + (-t);
    }

    template <typename T>
    inline tvec3<T> operator+(T t, const tvec3<T>& vec) {
        return vec + t;
    }

    template <typename T>
    inline tvec3<T> operator-(T t, const tvec3<T>& vec) {
        return t + (-1*vec);
    }

    template <typename T>
    inline tvec3<T> operator+(const tvec3<T>& a, const tvec3<T>& b) {
        return tvec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    template <typename T>
    inline tvec3<T> operator-(const tvec3<T>& a, const tvec3<T>& b) {
        return tvec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    template <typename T>
    inline tvec3<T> operator*(const tvec3<T>& vec, T t) {
        return tvec3(vec.x*t, vec.y*t, vec.z*t);
    }

    template <typename T>
    inline tvec3<T> operator*(T t, const tvec3<T>& vec) {
        return vec*t;
    }

    template <typename T>
    inline tvec3<T> operator/(const tvec3<T>& vec, T t) {
        return vec*(1/t);
    }

    template <typename T>
    inline tvec3<T> normalize(const tvec3<T>& vec) {
        return vec / vec.length();
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& out, const tvec3<T>& vec) {
      return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    }

    typedef tvec3<Real> vec3;
    typedef tvec3<int> ivec3;
};

#endif
