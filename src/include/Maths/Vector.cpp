#include <cmath>
#include <cfloat>

#include "Vector.hpp"

#define CMP(x, y)                      \
(   fabsf ((x) - (y)) <= FLT_EPSILON *  \
    fmaxf(1.0f,                          \
    fmaxf(fabsf(x), fabsf(y)))            \
)

//Adding vectors
vec2 operator+(const vec2& l, const vec2& r)
{
    return{l.x + r.x, l.y + l.y};
}

vec3 operator+(const vec3& l, const vec3& r)
{
    return{l.x + r.x, l.y + r.y, l.z + r.z};
}

//Subtracting vectors
vec2 operator-(const vec2& l, const vec2& r)
{
    return{l.x - r.x, l.y - r.y};
}

vec3 operator-(const vec3 l, const vec3& r)
{
    return{l.x - r.x, l.y - r.y, l.z - r.z};
}

//Multipling vectors
vec2 operator*(const vec2& l, const vec2& r)
{
    return{l.x * r.x, l.y * r.y};
}

vec3 operator*(const vec3& l, vec3& r)
{
    return{l.x * r.x, l.y * r.y, l.z * r.z};
}

//Multipling with scalars
vec2 operator*(const vec2& l, float r)
{
    return{l.x * r, l.y * r};
}

vec3 operator*(const vec3& l, float r)
{
    return{l.x * r, l.y * r, l.z * r};
}

//Boolean operations and compare 
bool operator==(const vec2& l, const vec2& r)
{
    return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator==(const vec3& l, const vec3& r)
{
    return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}

bool operator!=(const vec2& l, const vec2& r)
{
    return !(l == r);
}

bool operator!=(const vec3& l, const vec3& r)
{
    return !(l == r);
}

//The dot product functions
float Dot(const vec2& l, const vec2& r)
{
    return l.x * r.x + l.y * r.y;
}

float Dot(const vec3& l, const vec3& r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

//The magnitude functions
float Magnitude(const vec2& v)
{
    return sqrtf(Dot(v, v));
}

float Magnitude(const vec3& v)
{
    return sqrtf(Dot(v, v));
}

float MagnitudeSqr(const vec2& v)
{
    return Dot(v, v);
}

float MagnitudeSqr(const vec3& v)
{
    return Dot(v, v);
}

//The functions for normalising vectors

void Normalize(vec2& v)
{
    v = v * (1.0f / Magnitude(v));
}

void Normalize(vec3& v)
{
    v = v * (1.0f / Magnitude(v));
}

vec2 Normalized(const vec2& v)
{
    return v * (1.0f / Magnitude(v));
}

vec3 Normalized(const vec3& v)
{
    return v * (1.0f / Magnitude(v));
}