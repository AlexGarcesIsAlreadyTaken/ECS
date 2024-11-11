#ifndef VEC_4_H
#define VEC_4_H

#include <cmath>
#include "Utils/Constants.h"
#include <ostream>

namespace Math {
    template <typename T>
    struct tvec4 {
        T x, y, z, w;

        tvec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        tvec4(T x) : x(x), y(x), z(x), w(x) {}
        tvec4() : x(0), y(0), z(0), w(0) {}

        inline tvec4& operator+=(T t) {
            x += t; y += t; z += t; w += t;
            return *this;
        }

        inline tvec4& operator-=(T t) {
            return *this -= t;
        }

        inline tvec4& operator+=(const tvec4& vec) {
            this->x += vec.x; this->y += vec.y; this->z += vec.z; this->w += vec.w;
            return *this;
        }

        inline tvec4& operator-=(const tvec4& vec) {
            return *this -= vec;
        }

        inline tvec4& operator*=(T t) {
            x *= t; y *= t; z *= t; w *= t;
            return *this;
        }

        inline tvec4& operator/=(T t) {
            return *this *= (1/t);
        }

        inline tvec4& operator-() {
            return *this *= -1;
        }

        inline const T length_squared() const {
            return x*x + y*y + z*z + w*w;
        }

        inline const T length() const {
            return std::sqrt(length_squared());
        }
    };

    template <typename T>
    inline tvec4<T> operator+(const tvec4<T>& vec, T t) {
        return tvec4(vec.x + t, vec.y + t, vec.z + t, vec.w + t);
    }

    template <typename T>
    inline tvec4<T> operator-(const tvec4<T>& vec, T t) {
        return vec + (-t);
    }

    template <typename T>
    inline tvec4<T> operator+(T t, const tvec4<T>& vec) {
        return vec + t;
    }

    template <typename T>
    inline tvec4<T> operator-(T t, const tvec4<T>& vec) {
        return t + (-1*vec);
    }

    template <typename T>
    inline tvec4<T> operator+(const tvec4<T>& a, const tvec4<T>& b) {
        return tvec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + a.z);
    }

    template <typename T>
    inline tvec4<T> operator-(const tvec4<T>& a, const tvec4<T>& b) {
        return tvec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    template <typename T>
    inline tvec4<T> operator*(const tvec4<T>& vec, T t) {
        return tvec4(vec.x*t, vec.y*t, vec.z*t, vec.w*t);
    }

    template <typename T>
    inline tvec4<T> operator*(T t, const tvec4<T>& vec) {
        return vec*t;
    }

    template <typename T>
    inline tvec4<T> operator/(const tvec4<T>& vec, T t) {
        return vec*(1/t);
    }

    template <typename T>
    inline tvec4<T> normalize(const tvec4<T>& vec) {
        return vec / vec.length();
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& out, const tvec4<T>& vec) {
      return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    }

    typedef tvec4<Real> vec4;
    typedef tvec4<int32_t> ivec4;
};

#endif
