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
// $Log: vector.h,v $
// Revision 1.1  2002/02/13 11:57:19  dan
// Initial Revision
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _HYDROGEN_VECTOR_H
#define _HYDROGEN_VECTOR_H

#include "hydrogen/common.h"
#include "hydrogen/vector_gore.h"

#include <iostream.h>

BEGIN_NAMESPACE(H2)

//////////////////////////////////////////////////////////////////////////////
// VectorXY - Vector in R2 space
struct DescXY
{
    float X, Y;
};

class VectXY : public Vector::Base<2, DescXY>
{

public:
    typedef Vector::Base<2, DescXY> BaseType;

    inline VectXY()
    {}

    inline VectXY(const float x, const float y)
    {
        X = x, Y = y;
    }
    
    template<class ARGTYPE>
    inline VectXY(const ARGTYPE& A)
    {
        BaseType::operator=(A);
    }

    template<class ARGTYPE> 
    inline VectXY& operator =(const ARGTYPE& A)
    {
        BaseType::operator=(A);
        return *this;
    }
};

//////////////////////////////////////////////////////////////////////////////
// VectorXYZ - Vector in R3 space
struct DescXYZ
{
    float X, Y, Z;
};

class VectXYZ : public Vector::Base<3, DescXYZ>
{

public:
    typedef Vector::Base<3, DescXYZ> BaseType;

    inline VectXYZ()
    {}

    inline VectXYZ(const float x, const float y, const float z)
    {
        X = x, Y = y, Z = z;
    }
    
    template<class ARGTYPE>
    inline VectXYZ(const ARGTYPE& A)
    {
        BaseType::operator=(A);
    }

    template<class ARGTYPE> 
    inline VectXYZ& operator =(const ARGTYPE& A)
    {
        BaseType::operator=(A);
        return *this;
    }

//     inline float& operator[](const int i)
//     {
//         return BaseType::operator[](i);
//     }

    inline VectXYZ
    Cross(const VectXYZ& RHS) const
    {
        return VectXYZ(Y*RHS.Z - Z*RHS.Y,
                       Z*RHS.X - X*RHS.Z,
                       X*RHS.Y - Y*RHS.X);
    }
};

//////////////////////////////////////////////////////////////////////////////
// VectorXYZW - Vector in R4 space
struct DescXYZW
{
    float X, Y, Z, W;
};

class VectXYZW : public Vector::Base<4, DescXYZW>
{

public:
    typedef Vector::Base<4, DescXYZW> BaseType;

    inline VectXYZW()
    {}

    inline VectXYZW(const float x, const float y, const float z, const float w)
    {
        X = x, Y = y, Z = z, W = w;
    }
    
    template<class ARGTYPE>
    inline VectXYZW(const ARGTYPE& A)
    {
        BaseType::operator=(A);
    }

    template<class ARGTYPE> 
    inline VectXYZW& operator =(const ARGTYPE& A)
    {
        BaseType::operator=(A);
        return *this;
    }
};

END_NAMESPACE

inline 
ostream&
operator<<(ostream& os, const Hydrogen::VectXY& v)
{
    os << "<" << v.X << ", " << v.Y << ">";
    return os;
}

inline 
ostream&
operator<<(ostream& os, const Hydrogen::VectXYZ& v)
{
    os << "<" << v.X << ", " << v.Y << ", " << v.Z << ">";
    return os;
}

inline 
ostream&
operator<<(ostream& os, const Hydrogen::VectXYZW& v)
{
    os << "<" << v.X << ", " << v.Y << ", " << v.Z << ", " << v.W << ">";
    return os;
}

#endif // _HYDROGEN_VECTOR_H
