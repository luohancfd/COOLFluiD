// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "AdvectionDiffusion3DVarSet.hh"
#include "LinearAdvTerm.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Physics {
namespace LinearAdv {

//////////////////////////////////////////////////////////////////////////////

void AdvectionDiffusion3DVarSet::setup()
{
  AdvectionDiffusionVarSet::setup();
}

//////////////////////////////////////////////////////////////////////////////

RealVector& AdvectionDiffusion3DVarSet::getFlux(const RealVector& state,
                                          const vector<RealVector*>& gradients,
                                          const RealVector& normal,
                                          const CFreal& radius)
{
  const RealVector& gradu = *gradients[0];
  RealVector& adData = getModel().getPhysicalData();
 adData[ADTerm::NU] = getModel().getDiffusionCoeff();

  _flux[0] = adData[ADTerm::NU]*(normal[XX]*gradu[XX] + normal[YY]*gradu[YY] + normal[ZZ]*gradu[ZZ]);

 return _flux;
}

//////////////////////////////////////////////////////////////////////////////

RealMatrix& AdvectionDiffusion3DVarSet::getFlux(const RealVector& state,
                                          const vector<RealVector*>& gradients,
                                          const CFreal& radius)
{
 setGradientState(state);
  const RealVector& gradu = *gradients[0];
  RealVector& adData = getModel().getPhysicalData();
  adData[ADTerm::NU] = getModel().getDiffusionCoeff();

  _fluxVec(0,XX) = adData[ADTerm::NU]*gradu[XX];
  _fluxVec(0,YY) = adData[ADTerm::NU]*gradu[YY];
  _fluxVec(0,ZZ) = adData[ADTerm::NU]*gradu[ZZ];

  return _fluxVec;
}

//////////////////////////////////////////////////////////////////////////////

} // namespace LinearAdv
  }
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////
