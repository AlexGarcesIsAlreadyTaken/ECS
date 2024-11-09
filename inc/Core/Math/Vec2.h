#ifndef VEC_H
#define VEC_H

#include "Utils/Constants.h"

namespace Math {
    template <typename T>
    struct tvec2 {
        union {
          T x;
          T u;
          T s;
          T p;
        };

        union {
          T y;
          T v;
          T t;
          T r;
        };

        tvec2(T x, T y) : x(x), y(y) {}
        tvec2(T x) : x(x), y(x) {}
        tvec2() : x(0), y(0) {}

        inline tvec2& operator+=(T t) {
            x += t; y += t;
            return *this;
        }

        inline tvec2& operator-=(T t) {
            return *this -= t;
        }

        inline tvec2& operator+=(const tvec2& vec) {
            this->x += vec.x; this->y += vec.y;
            return *this;
        }

        inline tvec2& operator-=(const tvec2& vec) {
            return *this -= vec;
        }

        inline tvec2& operator*=(T t) {
            x *= t; y *= t;
            return *this;
        }

        inline tvec2& operator/=(T t) {
            return *this *= (1/t);
        }

        inline tvec2& operator-() {
            return *this *= -1;
        }

        inline const T length_squared() const {
            return x*x + y*y;
        }

        inline const T length() const {
            return std::sqrt(length_squared());
        }
    };

    template <typename T>
    inline tvec2<T> operator+(const tvec2<T>& vec, T t) {
        return tvec2(vec.x + t, vec.y + t);
    }

    template <typename T>
    inline tvec2<T> operator-(const tvec2<T>& vec, T t) {
        return vec + (-t);
    }

    template <typename T>
    inline tvec2<T> operator+(T t, const tvec2<T>& vec) {
        return vec + t;
    }

    template <typename T>
    inline tvec2<T> operator-(T t, const tvec2<T>& vec) {
        return t + (-1*vec);
    }

    template <typename T>
    inline tvec2<T> operator+(const tvec2<T>& a, const tvec2<T>& b) {
        return tvec2(a.x + b.x, a.y + b.y);
    }

    template <typename T>
    inline tvec2<T> operator-(const tvec2<T>& a, const tvec2<T>& b) {
        return tvec2(a.x - b.x, a.y - b.y);
    }

    template <typename T>
    inline tvec2<T> operator*(const tvec2<T>& vec, T t) {
        return tvec2(vec.x*t, vec.y*t);
    }

    template <typename T>
    inline tvec2<T> operator*(T t, const tvec2<T>& vec) {
        return vec*t;
    }

    template <typename T>
    inline tvec2<T> operator/(const tvec2<T>& vec, T t) {
        return vec*(1/t);
    }

    typedef tvec2<Real> vec2;
    typedef tvec2<int> ivec2;
    
};

#endif
