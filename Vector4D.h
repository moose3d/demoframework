// from here: http://www.terathon.com/code/vector4d.html
#ifndef __Vector4D_h__
#define __Vector4D_h__
#include "Vector3D.h"

struct Vector4D
{

    
        float   x;
        float   y;
        float   z;
        float   w;
        
        Vector4D() {}
        
        Vector4D(const Vector3D& v, float u)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = u;
        }

        Vector4D(float r, float s, float t, float u)
        {
            x = r;
            y = s;
            z = t;
            w = u;
        }
        
        Vector4D(const Vector3D& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = 0.0F;
        }
        
        Vector4D(const Point3D& p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
            w = 1.0F;
        }
        
        Vector4D(const Vector2D& v)
        {
            x = v.x;
            y = v.y;
            z = 0.0F;
            w = 0.0F;
        }
        
        Vector4D(const Point2D& p)
        {
            x = p.x;
            y = p.y;
            z = 0.0F;
            w = 1.0F;
        }
        
        Vector4D& Set(const Vector3D &v, float u)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = u;
            return (*this);
        }
        
        Vector4D& Set(float r, float s, float t, float u)
        {
            x = r;
            y = s;
            z = t;
            w = u;
            return (*this);
        }
        
        float& operator [](long k)
        {
            return ((&x)[k]);
        }
        
        const float& operator [](long k) const
        {
            return ((&x)[k]);
        }
        
        Vector3D& GetVector3D(void)
        {
            return (*reinterpret_cast<Vector3D *>(this));
        }
        
        const Vector3D& GetVector3D(void) const
        {
            return (*reinterpret_cast<const Vector3D *>(this));
        }
        
        Point3D& GetPoint3D(void)
        {
            return (*reinterpret_cast<Point3D *>(this));
        }
        
        const Point3D& GetPoint3D(void) const
        {
            return (*reinterpret_cast<const Point3D *>(this));
        }
        
        Vector4D& operator =(const Vector3D& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = 0.0F;
            return (*this);
        }
        
        Vector4D& operator =(const Point3D& p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
            w = 1.0F;
            return (*this);
        }
        
        Vector4D& operator =(const Vector2D& v)
        {
            x = v.x;
            y = v.y;
            z = 0.0F;
            w = 0.0F;
            return (*this);
        }
        
        Vector4D& operator =(const Point2D& p)
        {
            x = p.x;
            y = p.y;
            z = 0.0F;
            w = 1.0F;
            return (*this);
        }
        
        Vector4D& operator +=(const Vector4D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return (*this);
        }
        
        Vector4D& operator +=(const Vector3D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return (*this);
        }
        
        Vector4D& operator +=(const Vector2D& v)
        {
            x += v.x;
            y += v.y;
            return (*this);
        }
        
        Vector4D& operator -=(const Vector4D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return (*this);
        }
        
        Vector4D& operator -=(const Vector3D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return (*this);
        }
        
        Vector4D& operator -=(const Vector2D& v)
        {
            x -= v.x;
            y -= v.y;
            return (*this);
        }
        
        Vector4D& operator *=(float t)
        {
            x *= t;
            y *= t;
            z *= t;
            w *= t;
            return (*this);
        }
        
        Vector4D& operator /=(float t)
        {
            float f = 1.0F / t;
            x *= f;
            y *= f;
            z *= f;
            w *= f;
            return (*this);
        }
        
        Vector4D& operator &=(const Vector4D& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return (*this);
        }
        
        Vector4D operator -(void) const
        {
            return (Vector4D(-x, -y, -z, -w));
        }
        
        Vector4D operator +(const Vector4D& v) const
        {
            return (Vector4D(x + v.x, y + v.y, z + v.z, w + v.w));
        }
        
        Vector4D operator +(const Vector3D& v) const
        {
            return (Vector4D(x + v.x, y + v.y, z + v.z, w));
        }
        
        Vector4D operator +(const Vector2D& v) const
        {
            return (Vector4D(x + v.x, y + v.y, z, w));
        }
        
        Vector4D operator -(const Vector4D& v) const
        {
            return (Vector4D(x - v.x, y - v.y, z - v.z, w - v.w));
        }
        
        Vector4D operator -(const Vector3D& v) const
        {
            return (Vector4D(x - v.x, y - v.y, z - v.z, w));
        }
        
        Vector4D operator -(const Vector2D& v) const
        {
            return (Vector4D(x - v.x, y - v.y, z, w));
        }
        
        Vector4D operator *(float t) const
        {
            return (Vector4D(x * t, y * t, z * t, w * t));
        }
        
        Vector4D operator /(float t) const
        {
            float f = 1.0F / t;
            return (Vector4D(x * f, y * f, z * f, w * f));
        }
        
        float operator *(const Vector4D& v) const
        {
            return (x * v.x + y * v.y + z * v.z + w * v.w);
        }
        
        float operator *(const Vector3D& v) const
        {
            return (x * v.x + y * v.y + z * v.z);
        }
        
        float operator *(const Point3D& p) const
        {
            return (x * p.x + y * p.y + z * p.z + w);
        }
        
        float operator *(const Vector2D& v) const
        {
            return (x * v.x + y * v.y);
        }
        
        float operator *(const Point2D& p) const
        {
            return (x * p.x + y * p.y + w);
        }
        
        Vector3D operator %(const Vector3D& v) const
        {
            return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z,
                    x * v.y - y * v.x));
        }
        
        Vector4D operator &(const Vector4D& v) const
        {
            return (Vector4D(x * v.x, y * v.y, z * v.z, w * v.w));
        }
        
        bool operator ==(const Vector4D& v) const
        {
            return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w));
        }
        
        bool operator !=(const Vector4D& v) const
        {
            return ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w));
        }
        
        Vector4D& Normalize(void)
        {
            return (*this /= sqrtf(x * x + y * y + z * z + w * w));
        }
        
        Vector4D& RotateAboutX(float angle);
        Vector4D& RotateAboutY(float angle);
        Vector4D& RotateAboutZ(float angle);
        Vector4D& RotateAboutAxis(float angle, const Vector3D& axis);

        void ToArray( float * pArray ) { pArray[0] = x; pArray[1] = y; pArray[2] = z; pArray[3] = w; }
};


inline Vector4D operator +(const Vector3D& v1, const Vector4D& v2)
{
    return (Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v2.w));
}

inline Vector4D operator +(const Vector2D& v1, const Vector4D& v2)
{
    return (Vector4D(v1.x + v2.x, v1.y + v2.y,  v2.z, v2.w));
}

inline Vector4D operator -(const Vector3D& v1, const Vector4D& v2)
{
    return (Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, -v2.w));
}

inline Vector4D operator -(const Vector2D& v1, const Vector4D& v2)
{
    return (Vector4D(v1.x - v2.x, v1.y - v2.y, -v2.z, -v2.w));
}

inline Vector4D operator *(float t, const Vector4D& v)
{
    return (Vector4D(t * v.x, t * v.y, t * v.z, t * v.w));
}

inline float operator *(const Vector3D& v1, const Vector4D& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float operator *(const Point3D& v1, const Vector4D& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v2.w);
}

inline float operator *(const Vector2D& v1, const Vector4D& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

inline float operator *(const Point2D& v1, const Vector4D& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v2.w);
}

inline float Dot(const Vector4D& v1, const Vector4D& v2)
{
    return (v1 * v2);
}

inline float Magnitude(const Vector4D& v)
{
    return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

inline float InverseMag(const Vector4D& v)
{
    return (1.0F / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

inline float SquaredMag(const Vector4D& v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline Vector4D& Vector4D::RotateAboutX(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float ny = c * y - s * z;
    float nz = c * z + s * y;
    
    y = ny;
    z = nz;
    
    return (*this);
}

inline Vector4D& Vector4D::RotateAboutY(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x + s * z;
    float nz = c * z - s * x;
    
    x = nx;
    z = nz;
    
    return (*this);
}

inline Vector4D& Vector4D::RotateAboutZ(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x - s * y;
    float ny = c * y + s * x;
    
    x = nx;
    y = ny;
    
    return (*this);
}

inline Vector4D& Vector4D::RotateAboutAxis(float angle, const Vector3D& axis)
{
    float s = sinf(angle);
    float c = cosf(angle);
    float k = 1.0F - c;
    
    float nx = x * (c + k * axis.x * axis.x) + y * (k * axis.x * axis.y - s * axis.z)
            + z * (k * axis.x * axis.z + s * axis.y);
    float ny = x * (k * axis.x * axis.y + s * axis.z) + y * (c + k * axis.y * axis.y)
            + z * (k * axis.y * axis.z - s * axis.x);
    float nz = x * (k * axis.x * axis.z - s * axis.y) + y * (k * axis.y * axis.z + s * axis.x)
            + z * (c + k * axis.z * axis.z);
    
    x = nx;
    y = ny;
    z = nz;
    
    return (*this);
}

#endif
