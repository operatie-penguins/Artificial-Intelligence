#pragma once

// Вспомогательные процедуры и классы.

#include <cassert>
#include <vector>
#include <set>
#include <cmath>
#include <d3dx9math.h>
#include <dxerr.h>
#include <sstream>
#include <cfloat>

// Обработка ошибок.
class AppError
{
protected:
	std::stringstream ErrString;
public:

	AppError& operator<<( const std::string& Str )
	{
		ErrString << Str;
		return *this;
	}
	AppError& operator<<( float FVal )
	{
		ErrString << FVal;
		return *this;
	}
	AppError& operator<<( int IVal )
	{
		ErrString << IVal;
		return *this;
	}
	~AppError();
};

class AppDXError : public AppError
{
public:
	AppDXError( HRESULT HR )
	{
		ErrString << DXGetErrorString( HR );
	}
};

#define Error(Msg)(AppError() << " in " << __FUNCTION__ << " " << Msg)
#define DXError(HResult,Msg)(AppDXError(HResult) << " in " << __FUNCTION__ << " " << Msg)

template<class T>
class vec_iter : public std::vector<T>::iterator
{
	std::vector<T>& Vector;
public:
	vec_iter( std::vector<T>& Vec ) : Vector(Vec)
	{
		*(std::vector<T>::iterator*)this = Vec.begin();
	}
	operator bool()
	{
		return( *this != Vector.end() );
	}
};

template<class T>
class vec_const_iter : public std::vector<T>::const_iterator
{
	const std::vector<T>& Vector;
public:
	vec_const_iter( const std::vector<T>& Vec ) : Vector(Vec)
	{
		*(std::vector<T>::const_iterator*)this = Vec.begin();
	}
	operator bool()
	{
		return( *this != Vector.end() );
	}
};
// Здесь описывать все общие константы.
namespace Constants
{
	const float Pi = 3.1415926535f;
	const float HalfPi = 0.5f*Pi;
	const float Pi2 = 2.0f*Pi;
	const float FNearZero = 0.00001f;
	const float CmpEps = 0.001f;
};
template<typename T>
inline T Min( const T& A, const T& B )
{
	return (A < B) ? A : B;
}
template<typename T>
inline T Max( const T& A, const T& B )
{
	return (A > B) ? A : B;
}
template<typename T>
inline T Sign( const T& V )
{
	return (T)(V > 0 ? 1 : -1);
}
inline float DegToRad( float Deg )
{
	return Deg*3.14159265f/180;
}
inline void ClampAngle( float& Ang )
{
	if( Ang > Constants::Pi2 )
		Ang -= Constants::Pi2;
	if( Ang < -Constants::Pi2 )
		Ang += Constants::Pi2;
}
inline float RandomFloat()
{
	return (float)(rand() - RAND_MAX/2) / (0.5f*RAND_MAX);
}

template< typename Fn >
inline float IntegrateQuadrature( float A, float B, Fn F )
{
	return 0.5f*(B-A)*( F(0.5f*(A+B) - 0.2886751f*(B-A)) + F(0.5f*(A+B) + 0.2886751f*(B-A)) );
}

class Vector2
{
public:
	Vector2()
	{}
	Vector2( float fx, float fy ) : x(fx), y(fy)
	{}

	float x, y;
};

class Vector3
{
public:
	Vector3()
	{}
	Vector3( float X, float Y, float Z ) : x(X), y(Y), z(Z)
	{}
	Vector3( float *XYZ ) : x(XYZ[0]), y(XYZ[1]), z(XYZ[2])
	{}
	Vector3( const D3DXVECTOR3& V ) : x(V.x), y(V.y), z(V.z)
	{}
	Vector3 operator-() const
	{
		return Vector3( -x, -y, -z );
	}
	Vector3& operator+=( const Vector3& Rhs )
	{
		x += Rhs.x;
		y += Rhs.y;
		z += Rhs.z;
		return *this;
	}
	Vector3& operator-=( const Vector3& Rhs )
	{
		x -= Rhs.x;
		y -= Rhs.y;
		z -= Rhs.z;
		return *this;
	}
	Vector3 operator+( const Vector3& Rhs ) const
	{
		return( Vector3( *this ) += Rhs );
	}
	Vector3 operator-( const Vector3& Rhs ) const
	{
		return( Vector3( *this ) -= Rhs );
	}
	friend Vector3 operator*( float F, const Vector3& Rhs )
	{
		return Vector3( F*Rhs.x, F*Rhs.y, F*Rhs.z );
	}
	friend Vector3 operator/( float F, const Vector3& Rhs )
	{
		return Vector3( F / Rhs.x, F / Rhs.y, F / Rhs.z );
	}
	Vector3 operator*( const Vector3& Rhs )
	{
		return Vector3( x*Rhs.x, y*Rhs.y, z*Rhs.z );
	}
	Vector3& operator*=( float F )
	{
		x *= F;
		y *= F;
		z *= F;
		return *this;
	}
	float operator[]( int i ) const
	{
		assert( (unsigned)i < 3 );
		return *((float*)this + i);
	}
	float& operator[]( int i )
	{
		assert( (unsigned)i < 3 );
		return *((float*)this + i);
	}
	operator D3DXVECTOR3&()
	{
		return *(D3DXVECTOR3*)this;
	}
	operator D3DXVECTOR3*()
	{
		return (D3DXVECTOR3*)this;
	}
	float Length() const
	{
		return sqrt( x*x + y*y + z*z );
	}
	float Normalize()
	{
		float L = x*x + y*y + z*z;
		if( L > Constants::FNearZero )
		{
			L = sqrt( L );
			x /= L;
			y /= L;
			z /= L;
			return L; 
		}
		return 0;
	}
	Vector3 Cross( const Vector3& Rhs ) const
	{
		return Vector3( y*Rhs.z-Rhs.y*z, -x*Rhs.z+Rhs.x*z, x*Rhs.y-Rhs.x*y );
	}
	float Dot( const Vector3& Rhs ) const
	{
		return x*Rhs.x + y*Rhs.y + z*Rhs.z;
	}
	Vector3 Pack( int i1, int i2, int i3 ) const
	{
		return Vector3( (*this)[i1], (*this)[i2], (*this)[i3] );
	}
	bool Less( const Vector3& Rhs ) const
	{
		return( x < (Rhs.x + Constants::CmpEps) && y < (Rhs.y + Constants::CmpEps) && z < (Rhs.z + Constants::CmpEps) );
	}
	bool Greater( const Vector3& Rhs ) const
	{
		return( x > (Rhs.x - Constants::CmpEps) && y > (Rhs.y - Constants::CmpEps) && z > (Rhs.z - Constants::CmpEps) );
	}
	void Min( const Vector3& Lhs, const Vector3& Rhs )
	{
		x = ::Min( Lhs.x, Rhs.x );
		y = ::Min( Lhs.y, Rhs.y );
		z = ::Min( Lhs.z, Rhs.z );
	}
	void Max( const Vector3& Lhs, const Vector3& Rhs )
	{
		x = ::Max( Lhs.x, Rhs.x );
		y = ::Max( Lhs.y, Rhs.y );
		z = ::Max( Lhs.z, Rhs.z );
	}

	float x, y, z;
};

inline Vector3 Transform( const D3DXMATRIX& M, const Vector3& V )
{
	return Vector3(
		M._11*V.x + M._21*V.y + M._31*V.z + M._41,
		M._12*V.x + M._22*V.y + M._32*V.z + M._42,
		M._13*V.x + M._23*V.y + M._33*V.z + M._43
	);
}

inline Vector3 TransformVector( const D3DXMATRIX& M, const Vector3& V )
{
	return Vector3(
		M._11*V.x + M._21*V.y + M._31*V.z,
		M._12*V.x + M._22*V.y + M._32*V.z,
		M._13*V.x + M._23*V.y + M._33*V.z
	);
}

class BBox
{
public:
	Vector3 Min;
	Vector3 Max;

	BBox() : Min(FLT_MAX,FLT_MAX,FLT_MAX), Max(-FLT_MAX,-FLT_MAX,-FLT_MAX)
	{}
	BBox( const Vector3& vMin, const Vector3& vMax )
		: Min(vMin), Max(vMax)
	{}
	// Доступ к значениям.
	const Vector3&	GetExtent( unsigned i ) const
	{
		assert( i < 2 );
		return (&Min)[i];
	}
	BBox& operator+=( const BBox& Rhs )
	{
		Min.x = ::Min( Min.x, Rhs.Min.x );
		Min.y = ::Min( Min.y, Rhs.Min.y );
		Min.z = ::Min( Min.z, Rhs.Min.z );

		Max.x = ::Max( Max.x, Rhs.Max.x );
		Max.y = ::Max( Max.y, Rhs.Max.y );
		Max.z = ::Max( Max.z, Rhs.Max.z );
		return *this;
	}
	void AddPoint( const Vector3& V )
	{
		Min.x = ::Min( V.x, Min.x );
		Min.y = ::Min( V.y, Min.y );
		Min.z = ::Min( V.z, Min.z );
		
		Max.x = ::Max( V.x, Max.x );
		Max.y = ::Max( V.y, Max.y );
		Max.z = ::Max( V.z, Max.z );
	}
	BBox operator+=( const Vector3& V )
	{
		Min += V;
		Max += V;
		return *this;
	}
	BBox operator+( const BBox& Rhs ) const
	{
		BBox Temp( *this );
		return( Temp += Rhs );
	}
	BBox operator+( const Vector3& V ) const
	{
		BBox Temp( *this );
		Temp += V;
		return Temp;
	}
	BBox Transform( const D3DXMATRIX& M ) const
	{
		BBox Temp;
		for( int i=0; i<2; i++ )
			for( int j=0; j<2; j++ )
				for( int k=0; k<2; k++ )
					Temp.AddPoint( ::Transform( M, Vector3( GetExtent( i ).x, GetExtent( j ).y, GetExtent( k ).z )) );
		return Temp;
	}
	// RayOrg - начало луча,
	// RayDir - направление луча,
	// Near - координата точки касания на луче (если касание есть).
	bool TestRayIntersection( const Vector3& RayOrg, const Vector3& RayDir,
							float& Near ) const
	{
		Vector3 invR = 1.0f / RayDir;
		Vector3 tbot = invR * (Min - RayOrg);
		Vector3 ttop = invR * (Max - RayOrg);
		// re-order intersections to find smallest and largest on each axis
		Vector3 tmin, tmax;
		tmin.Min( ttop, tbot );
		tmax.Max( ttop, tbot );
		// find the largest tmin and the smallest tmax
		float t0[2];
		t0[0] = ::Max( tmin.x, tmin.y );
		t0[1] = ::Max( tmin.x, tmin.z );
		Near = ::Max (t0[0], t0[1]);
		t0[0] = ::Min( tmax.x, tmax.y );
		t0[1] = ::Min( tmax.x, tmax.z );
		float Far = ::Min( t0[0], t0[1] );
		// check for hit
		if ( Near > Far )
		{
			Near = 0;
			return false;
		}
		else
			return true;
	}

	// Проверка принадлежности точки.
	bool CheckPoint( const Vector3& P ) const
	{
		return( P.Greater(Min) && P.Less( Max ) );
	}

	// Проверка на столкновение с другим боксом.
	bool CheckBBox( const BBox& Other ) const
	{
		for( int i=0; i < 2; i++ )
			for( int j=0; j < 2; j++ )
				for( int k=0; k < 2; k++ )
				{
					if( Other.CheckPoint( Vector3( GetExtent(i).x, GetExtent(j).y, GetExtent(k).z ) ) )
						return true;
					if( CheckPoint( Vector3( Other.GetExtent(i).x, Other.GetExtent(j).y, Other.GetExtent(k).z ) ) )
						return true;
				}
				
		return false;
	}
};

class OBBox
{
public:
	BBox			Box; // В локальной системе координат объекта.
	D3DXMATRIXA16	LocalMat; // Матрица перехода в локальную систему координат.

	OBBox()
	{}

	OBBox( const BBox& LocalBox, const D3DXMATRIX& WorldToLocal )
		: Box( LocalBox ), LocalMat( WorldToLocal )
	{
	}

	bool CheckPoint( const Vector3& P ) const
	{
		Vector3 TP = Transform( LocalMat, P );
		return Box.CheckPoint( TP );
	}

	// Считается, что обе координатные системы в одном масштабе.
	bool TestRayIntersection( const Vector3& RayOrg, const Vector3& RayDir,	float& Near ) const
	{
		Vector3 TrRayOrg = Transform( LocalMat, RayOrg );
		Vector3 TrRayDir = TransformVector( LocalMat, RayDir );
		TrRayDir.Normalize();
		return Box.TestRayIntersection( TrRayOrg, TrRayDir, Near );
	}

	// Проверка столкновения с другим OBBoxом.
	bool CheckOBBox( const OBBox& Other ) const
	{
		D3DXMATRIXA16	This2Other;
		D3DXMatrixInverse( &This2Other, NULL, &LocalMat );
		D3DXMatrixMultiply( &This2Other, &This2Other, &Other.LocalMat );

		BBox ThisAA;
		for( int i=0; i < 2; i++ )
			for( int j=0; j < 2; j++ )
				for( int k=0; k < 2; k++ )
					ThisAA.AddPoint( Transform( This2Other, Vector3( Box.GetExtent(i).x, Box.GetExtent(j).y, Box.GetExtent(k).z) ) );

		return ThisAA.CheckBBox( Other.Box );
	}

	// Проверка пересечения с ААBB в мировой СК.
	bool CheckBBox( const BBox& OtherBox ) const
	{
		BBox BoxInLocal;
		for( int i=0; i < 2; i++ )
			for( int j=0; j < 2; j++ )
				for( int k=0; k < 2; k++ )
					BoxInLocal.AddPoint( Transform( LocalMat, Vector3( OtherBox.GetExtent(i).x, OtherBox.GetExtent(j).y, OtherBox.GetExtent(k).z ) ) );

		return Box.CheckBBox( BoxInLocal );
	}
};

// Выделяет части строки, разделенные нетерминалом(мб несколькими)
class Tokenizator
{
	const std::string& Tkns;
	int		Pos;
	char	NTerm;
public:
	Tokenizator( const std::string& Str ) : Tkns(Str), Pos(0), NTerm(' ')
	{}
	void Begin( char NonTerm )
	{
		NTerm = NonTerm;
		Pos = 0;
	}
	std::string NextToken()
	{
		int L = Tkns.find_first_not_of( NTerm, Pos );
		int R = Tkns.find_first_of( NTerm, L );
		Pos = R;
		return (L != std::string::npos) ? Tkns.substr( L, R-L ) : "";
	}
};