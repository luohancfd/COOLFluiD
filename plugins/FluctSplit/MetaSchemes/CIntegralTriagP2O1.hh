#ifndef COOLFluiD_FluctSplit_CIntegralTriagP2O1_hh
#define COOLFluiD_FluctSplit_CIntegralTriagP2O1_hh

#include "FluctSplit/MetaSchemes/ContourIntegral.hh"
#include "FluctSplit/MetaSchemes/TriagP2.hh"

///////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  namespace FluctSplit {

///////////////////////////////////////////////////////////////////////////////

/// Specialization for CFPolyOrder::ORDER1 contour integration of a P2 triangle
template <> struct CIntegral < TriagP2, CFPolyOrder::ORDER1 >
{
  typedef TriagP2 Elem;
  typedef CIntegral < TriagP2, CFPolyOrder::ORDER1 > Integrator;

  enum { NBSF       = Elem::NBNODES };
  enum { NBQDPT     = 9 };
  enum { NBSUBQDPT  = 3 };
  enum { NBSUBELEM  = Elem::NBSUBELEM  };
  enum { NBSUBNODES = Elem::NBSUBNODES };

  /// Class for each quadrature point in the element
  /// This template must be specialized.
  template < unsigned int QDPT >
  struct QdPt
  {
    /// @post Sum of the weights of all quad points in a subelement face is 1.
    static double weight ();
    static double xi     ();
    static double eta    ();
  };

  /// Class for each quadrature point
  /// This template must be specialized.
  template < unsigned int NELEM >
  struct SubElem
  {
    /// Class for returning the normals as seen form the subelement quadrature point
    template < unsigned int QDPT >
    struct QdPt
    {
      /// Returns the normal on the subelem quadrature point,
      /// as seen from the subelement.
      /// @post normals points to the inside of the subelement and is a unit normal with size 1
      /// @return RealVector of size DIM with the normal components
      template < typename FSDATA >
      static const RealVector& normal ( const FSDATA& data );
      /// Returns the face jacobian at the quadrature point
      /// @post On a straight face it is the ratio between the face area
      ///       and the reference face area
      /// @return RealVector of size DIM with the normal components
      template < typename FSDATA >
      static double face_jacob ( const FSDATA& data );
    };
  };
};

///////////////////////////////////////////////////////////////////////////////

// definition of element quadrature point 0
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<0>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<0>::xi      () { return 0.25; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<0>::eta     () { return 0.00; }

// definition of element quadrature point 1
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<1>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<1>::xi      () { return 0.75; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<1>::eta     () { return 0.00; }

// definition of element quadrature point 2
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<2>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<2>::xi      () { return 0.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<2>::eta     () { return 0.25; }

// definition of element quadrature point 3
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<3>::weight  () { return std::sqrt(2.0); }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<3>::xi      () { return 0.25; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<3>::eta     () { return 0.25; }

// definition of element quadrature point 4
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<4>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<4>::xi      () { return 0.50; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<4>::eta     () { return 0.25; }

// definition of element quadrature point 5
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<5>::weight  () { return std::sqrt(2.0); }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<5>::xi      () { return 0.75; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<5>::eta     () { return 0.25; }

// definition of element quadrature point 6
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<6>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<6>::xi      () { return 0.25; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<6>::eta     () { return 0.50; }

// definition of element quadrature point 7
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<7>::weight  () { return 1.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<7>::xi      () { return 0.00; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<7>::eta     () { return 0.75; }

// definition of element quadrature point 8
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<8>::weight  () { return std::sqrt(2.0); }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<8>::xi      () { return 0.25; }
template <> double CIntegral<TriagP2,CFPolyOrder::ORDER1>::QdPt<8>::eta     () { return 0.75; }

///////////////////////////////////////////////////////////////////////////////

/// Definition of subelem 0 quadrature point 0
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<0>::QdPt<0>
{
  enum { ID = 0 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[0].nodal_normals[2]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[0].nodal_areas[2]; }
};

/// Definition of subelem 0 quadrature point 1
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<0>::QdPt<1>
{
  enum { ID = 3 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[0].nodal_normals[0]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return (1./std::sqrt(2.0)) * data.sub_elem[0].nodal_areas[0]; }
};

/// Definition of subelem 0 quadrature point 2
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<0>::QdPt<2>
{
  enum { ID = 2 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[0].nodal_normals[1]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[0].nodal_areas[1]; }
};

///////////////////////////////////////////////////////////////////////////////

/// Definition of subelem 1 quadrature point 0
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<1>::QdPt<0>
{
  enum { ID = 1 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[1].nodal_normals[2]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[1].nodal_areas[2]; }
};

/// Definition of subelem 1 quadrature point 1
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<1>::QdPt<1>
{
  enum { ID = 5 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[1].nodal_normals[0]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return (1./std::sqrt(2.0)) * data.sub_elem[1].nodal_areas[0]; }
};

/// Definition of subelem 1 quadrature point 2
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<1>::QdPt<2>
{
  enum { ID = 4 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[2].nodal_normals[1]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[2].nodal_areas[1]; }
};

///////////////////////////////////////////////////////////////////////////////

/// Definition of subelem 2 quadrature point 0
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<2>::QdPt<0>
{
  enum { ID = 6 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[2].nodal_normals[2]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[2].nodal_areas[2]; }
};

/// Definition of subelem 2 quadrature point 1
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<2>::QdPt<1>
{
  enum { ID = 8 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[2].nodal_normals[0]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return (1./std::sqrt(2.0)) * data.sub_elem[2].nodal_areas[0]; }
};

/// Definition of subelem 2 quadrature point 2
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<2>::QdPt<2>
{
  enum { ID = 7 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[2].nodal_normals[1]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[2].nodal_areas[1]; }
};

///////////////////////////////////////////////////////////////////////////////

/// Definition of subelem 3 quadrature point 0
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<3>::QdPt<0>
{
  enum { ID = 3 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[3].nodal_normals[2]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return (1./std::sqrt(2.0)) * data.sub_elem[3].nodal_areas[2]; }
};

/// Definition of subelem 3 quadrature point 1
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<3>::QdPt<1>
{
  enum { ID = 4 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[3].nodal_normals[0]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[3].nodal_areas[0]; }
};

/// Definition of subelem 3 quadrature point 2
template <> template <>
struct CIntegral<TriagP2,CFPolyOrder::ORDER1>::SubElem<3>::QdPt<2>
{
  enum { ID = 6 };
  template < typename FSDATA >
  static const RealVector& normal ( const FSDATA& data ) { return data.sub_elem[3].nodal_normals[1]; }
  template < typename FSDATA >
  static double face_jacob ( const FSDATA& data )  { return data.sub_elem[3].nodal_areas[1]; }
};

///////////////////////////////////////////////////////////////////////////////

  } // FluctSplit
} // COOLFluiD

#endif // COOLFluiD_FluctSplit_CIntegralTriagP2O1_hh
