#include "Framework/CFL.hh"
#include "Framework/MethodCommandProvider.hh"
#include "Framework/LSSIdxMapping.hh"
#include "Framework/LSSMatrix.hh"
#include "Framework/MeshData.hh"

#include "SpectralFD/SpectralFD.hh"
#include "SpectralFD/SpectralFDElementData.hh"
#include "SpectralFD/StdTimeRHSJacob.hh"

//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace COOLFluiD::Framework;
using namespace COOLFluiD::Common;

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace SpectralFD {

//////////////////////////////////////////////////////////////////////////////

MethodCommandProvider<StdTimeRHSJacob, SpectralFDMethodData, SpectralFDModule> StdTimeRHSJacob("StdTimeRHSJacob");

//////////////////////////////////////////////////////////////////////////////

StdTimeRHSJacob::StdTimeRHSJacob(const std::string& name) :
  SpectralFDMethodCom(name),
  m_cellBuilder(CFNULL),
  m_lss(CFNULL),
  socket_updateCoeff("updateCoeff"),
  m_solPntsLocalCoords(CFNULL),
  m_nbrEqs()
{
}

//////////////////////////////////////////////////////////////////////////////

StdTimeRHSJacob::~StdTimeRHSJacob()
{
}

//////////////////////////////////////////////////////////////////////////////

void StdTimeRHSJacob::setup()
{
  SpectralFDMethodCom::setup();

  // get number of equations in the physical model
  m_nbrEqs = PhysicalModelStack::getActive()->getNbEq();

  // get cell builder
  m_cellBuilder = getMethodData().getStdTrsGeoBuilder();

  // linear system solver
  m_lss = getMethodData().getLinearSystemSolver()[0];
}

//////////////////////////////////////////////////////////////////////////////

void StdTimeRHSJacob::execute()
{
  CFAUTOTRACE;

  SafePtr<LSSMatrix> jacobMatrix = m_lss->getMatrix();

  DataHandle< CFreal> updateCoeff = socket_updateCoeff.getDataHandle();

  const CFreal cfl = getMethodData().getCFL()->getCFLValue();

  const LSSIdxMapping& idxMapping =
      getMethodData().getLinearSystemSolver()[0]->getLocalToGlobalMapping();

  // get the elementTypeData
  SafePtr< vector<ElementTypeData> > elemType = MeshDataStack::getActive()->getElementTypeData();

  // get InnerCells TopologicalRegionSet
  SafePtr<TopologicalRegionSet> cells = MeshDataStack::getActive()->getTrs("InnerCells");

  // get the geodata of the geometric entity builder and set the TRS
  StdTrsGeoBuilder::GeoData& geoData = m_cellBuilder->getDataGE();
  geoData.trs = cells;

  // loop over element types
  const CFuint nbrElemTypes = elemType->size();
  for (CFuint iElemType = 0; iElemType < nbrElemTypes; ++iElemType)
  {
    // get start and end indexes for this type of element
    const CFuint startIdx = (*elemType)[iElemType].getStartIdx();
    const CFuint endIdx   = (*elemType)[iElemType].getEndIdx();

    // get the local spectral FD data
    vector< SpectralFDElementData* >& sdLocalData = getMethodData().getSDLocalData();

    // get solution point local coordinates
    m_solPntsLocalCoords = sdLocalData[iElemType]->getSolPntsLocalCoords();

    // add the diagonal entries in the jacobian (updateCoeff/CFL)
    for (CFuint elemIdx = startIdx; elemIdx < endIdx; ++elemIdx)
    {
      // build the GeometricEntity
      geoData.idx = elemIdx;
      GeometricEntity* cell = m_cellBuilder->buildGE();

      // get the states in this cell
      vector< State* >* cellStates = cell->getStates();

      if ((*cellStates)[0]->isParUpdatable())
      {
        // get the cell volume
        const CFreal invCellVolume = 1.0/cell->computeVolume();

        // get jacobian determinants at solution points
        const std::valarray<CFreal> jacobDet =
            cell->computeGeometricShapeFunctionJacobianDeterminant(*m_solPntsLocalCoords);

        // add diagonal values
        const CFuint firstStateID = (*cellStates)[0]->getLocalID();
        const CFreal updateCoeffDivCFL = invCellVolume*updateCoeff[firstStateID]/cfl;// should be the same for all states
        const CFuint nbrSolPnts = cellStates->size();
        for (CFuint iSol = 0; iSol < nbrSolPnts; ++iSol)
        {
          const CFuint stateID = (*cellStates)[iSol]->getLocalID();
          CFuint globalID = idxMapping.getColID(stateID)*m_nbrEqs;
          for (CFuint iEq = 0; iEq < m_nbrEqs; ++iEq, ++globalID)
          {
            if (getMethodData().doComputeJacobian())
            {
              jacobMatrix->addValue(globalID, globalID, updateCoeffDivCFL*jacobDet[iSol]);
            }
          }
        }
      }

      //release the GeometricEntity
      m_cellBuilder->releaseGE();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////

vector<SafePtr<BaseDataSocketSink> >
StdTimeRHSJacob::needsSockets()
{
  vector<SafePtr<BaseDataSocketSink> > result;

  result.push_back(&socket_updateCoeff);

  return result;
}

//////////////////////////////////////////////////////////////////////////////

  } // namespace SpectralFD

} // namespace COOLFluiD
