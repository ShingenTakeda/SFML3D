#ifndef H_MATH_VECTOR
#define H_MATH_VECTOR

typedef struct vec2
{
    union
    {
        struct
        {
            float x;
            float y;
        };

        float asArray[2];
    };

    float& operator[](int i)
    {
        return asArray[i];
    };
} vec2;

typedef struct vec3
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };

        float asArray[3];
    };

    float& operator[](int i)
    {
        return asArray[i];
    }
} vec3;

vec2 operator+(const vec2& l, const vec2& r);
vec3 operator+(const vec3& l, const vec3& r);

vec2 operator-(const vec2& l, const vec2& r);
vec3 operator-(const vec3& l, const vec3& r);

vec2 operator*(const vec2& l, float r);
vec3 operator*(const vec3& l, float r);

bool operator==(const vec2& l, const vec2& r);
bool operator==(const vec3& l, const vec2& r);
bool operator!=(const vec2& l, const vec2& r);
bool operator!=(const vec3& l, const vec3& r);

//Declarations for the dot product
float Dot(const vec2& l, const vec2& r);
float Dot(const vec3& l, const vec3& r);

//Declarations for magnitude
float Magnitude(const vec2& v);
float Magnitude(const vec3& v);

float MagnitudeSqr(const vec2& v);
float MagnitudeSqr(const vec3& v);

//Declarations for the normalasng vectors
void Normalize(vec2& v);
void Normalize(vec3& v);

vec2 Normalized(const vec2& v);
vec3 Normalized(const vec3& v);

#endif