// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4 -*- ///////////////
//
// File:
// Author:
//
// Summary:
//
// © Copyright 2001 Daniel Glastonbury.  All rights reserved.
//
//----------------------------------------------------------------------------
// $Revision: 1.1 $    $Author: dan $    $Date: 2002/02/13 11:57:19 $
//----------------------------------------------------------------------------
// $Log: vector_gore.h,v $
// Revision 1.1  2002/02/13 11:57:19  dan
// Initial Revision
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _HYDROGEN_VECTORGORE_H
#define _HYDROGEN_VECTORGORE_H

#include "hydrogen/common.h"

#include <cmath>

#pragma inline_depth(255)
#pragma inline_recursion(on)
#pragma auto_inline(on)
#define inline __forceinline

BEGIN_NAMESPACE(Vector)

//////////////////////////////////////////////////////////////////////////////
// Vector Arguments
template<class ARG1>
class VectArg
{
public:
	inline VectArg(const ARG1& Arg) :
		m_Arg1(Arg)
	{}

	inline const float Eval(const int i) const
	{
		return m_Arg1.Eval(i);
	}

private:
	const ARG1& m_Arg1;
};

template<>
class VectArg<const float>
{
public:
	inline VectArg(const ARG1& Arg) :
		m_Arg1(Arg)
	{}

	inline const float Eval(const int i) const
	{
		return m_Arg1;
	}

private:
	const ARG1& m_Arg1;
};

//////////////////////////////////////////////////////////////////////////////
// Vector Expressions

template<class ARG1, class ARG2, class EVAL>
class VectExp2
{
public:
	inline VectExp2(const ARG1& Arg1, const ARG2& Arg2) :
		m_Arg1(Arg1), m_Arg2(Arg2)
	{}

	inline const float Eval(const int i) const
	{
		return EVAL::Eval(i, m_Arg1, m_Arg2);
	}

private:
	const VectArg<ARG1> m_Arg1;
	const VectArg<ARG2> m_Arg2;
};

template<class ARG1, class EVAL>
class VectExp1
{
public:
	inline VectExp1(const ARG1& Arg1 ) : 
		m_Arg1(Arg1)
	{}

	inline const float Eval(const int i) const
    {
		return EVAL::Eval(i, m_Arg1.Eval(i)); 
	}

private:
	const VectArg<ARG1> m_Arg1;
};

template<class ARG1, class EVAL>
class VectExp1BC
{
public:
	inline VectExp1BC(const ARG1& Arg1, const float f) : 
		m_Arg1(Arg1), m_Arg2(f)
	{}

	inline const float Eval(const int i) const
    {
		return EVAL::Eval(i, m_Arg1, m_Arg2); 
	}

private:
	const VectArg<ARG1> m_Arg1;
    const float m_Arg2;
};

//////////////////////////////////////////////////////////////////////////////
// Vector Base Class
template<int DIM, class T>
class Base : public T
{
public:
	inline float& operator [](const int i)
	{
		return ((float*)this)[i];
	}

	inline const float Eval(const int i) const
	{
		return ((float*)this)[i];
	}

	//////////////////////////////////////////////////////////////////////////
	// Assignment
	template<class ARG>
	struct Assigment
	{
		template<int I, class R>
		struct Recurse
		{
			enum { COUNTER = I+1 };

			static inline void Assign(Base<DIM, T>& V, const ARG& A) 
            {
				V[I] = A.Eval(I);
				Recurse<COUNTER, int>::Assign(V, A);
			}
		};

		// Termination condition
		template<> 
		struct Recurse<DIM, int>
		{
			static inline void Assign(Base<DIM, T>& V, const ARG& A)
			{}
		};

		static inline void Assign(Base<DIM, T>& V, const ARG& A)
        {
			Recurse<0, int>::Assign(V, A);
		}
	};

	template<class ARGTYPE>
	inline const Base<DIM, T>& 
	operator =(const ARGTYPE& A)
    {
		Assigment<ARGTYPE>::Assign(*this, A);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	// Dot Product
	template<class ARG1, class ARG2>
	struct DotProd
	{
		template<int I, class R>
		struct Recurse
		{
			enum { COUNTER = I+1 };

			static inline float Dot_Prod(const ARG1& A, const ARG2& B)
			{
				return A.Eval(I) * B.Eval(I) +
					Recurse<COUNTER, int>::Dot_Prod(A, B);
			}
		};

		// Termination condition
		template<>
		struct Recurse<DIM, int>
		{
			static inline float Dot_Prod(const ARG1& A, const ARG2& B)
			{
				return 0;
			}
		};

		static inline float Dot_Prod(const ARG1& A, const ARG2& B)
		{
			return Recurse<0, int>::Dot_Prod(A, B);
		}
	};

	template<class ARGTYPE>
	inline float
	Dot(const ARGTYPE& A) const
	{
		return DotProd<Base<DIM, T>, ARGTYPE>::Dot_Prod(*this, A);
	}

    //////////////////////////////////////////////////////////////////////////
    // Length
    inline float
    LengthSqr() const
    {
        return Dot(*this);
    }

    inline float
    Length() const
    {
        return sqrtf(LengthSqr());
    }
};

//////////////////////////////////////////////////////////////////////////////
// Addition
struct Sum
{
	template<class ARG1, class ARG2> 
	inline static const float 
	Eval(const int i, const ARG1& A, const ARG2& B)
    { 
		return A.Eval(i) + B.Eval(i);
	}
};

template<class RARG1, class RARG2> 
inline const VectExp2<const RARG1, const RARG2, Sum> 
operator +(const RARG1& RA, const RARG2& RB)
{
	return VectExp2<const RARG1, const RARG2, Sum>(RA, RB);
}

//////////////////////////////////////////////////////////////////////////////
// Subtraction
struct Sub
{
	template<class ARG1, class ARG2> 
	inline static const float 
	Eval(const int i, const ARG1& A, const ARG2& B)
    { 
		return A.Eval(i) - B.Eval(i);
	}
};

template<class RARG1, class RARG2> 
inline const VectExp2<const RARG1, const RARG2, Sub> 
operator -(const RARG1& RA, const RARG2& RB)
{
	return VectExp2<const RARG1, const RARG2, Sub>(RA, RB);
}

//////////////////////////////////////////////////////////////////////////////
// Scalar Multiplication
struct Mul
{
    template<class ARG1>
    inline static const float
    Eval(const int i, const ARG1& A, const float B)
    {
        return A.Eval(i)*B;
    }
};

template<class RARG1>
inline const VectExp1BC<const RARG1, Mul>
operator *(const RARG1& RA, const float RB)
{
    return VectExp1BC<const RARG1, Mul>(RA, RB);
}

template<class RARG1>
inline const VectExp1BC<const RARG1, Mul>
operator *(const float RA, const RARG1& RB)
{
    return VectExp1BC<const RARG1, Mul>(RB, RA);
}

//////////////////////////////////////////////////////////////////////////////
// Dodgy Vector Multiplication
#if 0
struct MulVec
{
	template<class ARG1, class ARG2> 
	inline static const float 
	Eval(const int i, const ARG1& A, const ARG2& B)
    { 
		return A.Eval(i) * B.Eval(i);
	}
};

template<class RARG1, class RARG2> 
inline const VectExp2<const RARG1, const RARG2, MulVec> 
operator *(const RARG1& RA, const RARG2& RB)
{
	return VectExp2<const RARG1, const RARG2, MulVec>(RA, RB);
}
#endif

//////////////////////////////////////////////////////////////////////////////
// Scalar Division
struct Div
{
    template<class ARG1>
    inline static const float
    Eval(const int i, const ARG1& A, const float B)
    {
        return A.Eval(i)/B;
    }
};

template<class RARG1>
inline const VectExp1BC<const RARG1, Mul>
operator /(const RARG1& RA, const float RB)
{
    return VectExp1BC<const RARG1, Div>(RA, RB);
}

END_NAMESPACE

#endif //_HYDROGEN_VECTORGORE_H
