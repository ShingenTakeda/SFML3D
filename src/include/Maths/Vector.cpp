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

vec3 operator-(const vec3& l, const vec3& r)
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

//Functions for cross product operations
vec3 Cross(const vec3& l, const vec3& r)
{
    vec3 result;

    result.x = l.y * r.z - l.z * r.y;
    result.y = l.z * r.x - l.x * r.z;
    result.z = l.x * r.y - l.y * r.x;

    return result;
}

//Functions for projections and perpendicular stuff
vec2 Project(const vec2& length, const vec2& direction)
{
    float dot = Dot(length, direction);
    float magSq = MagnitudeSqr(direction);
    return direction * (dot / magSq);
}
vec3 Project(const vec3& length, const vec3& direction)
{
    float dot = Dot(length, direction);
    float magSq = MagnitudeSqr(direction);
    return direction * (dot / magSq);
}

vec2 Perpendicular(const vec2& len, const vec2& dir)
{
    return len - Project(len, dir);
}

vec3 Perpendicular(const vec3& len, const vec3& dir)
{
    return len - Project(len, dir);
}

//Functions for reflections
vec2 Reflections(const vec2& sourceVector, const vec2& normal)
{
    float d = Dot(sourceVector, normal);
    return  sourceVector - normal * (d * 2.0f);
}

vec3 Reflections(const vec3& sourceVector, const vec3& normal)
{
    float d = Dot(sourceVector, normal);
    return  sourceVector - normal * (d * 2.0f);
}