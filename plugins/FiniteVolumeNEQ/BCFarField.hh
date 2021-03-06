#ifndef COOLFluiD_Numerics_FiniteVolumeNEQ_BCFarField_hh
#define COOLFluiD_Numerics_FiniteVolumeNEQ_BCFarField_hh

//////////////////////////////////////////////////////////////////////////////

#include "MathTools/FunctionParser.hh"
#include "Framework/DataProcessingData.hh"
#include "Framework/DataSocketSource.hh"
#include "Framework/DataSocketSink.hh"
#include "Framework/VectorialFunction.hh"
#include "Framework/PhysicalModel.hh"

#include "FiniteVolume/FVMCC_BC.hh"
//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Numerics {

   namespace FiniteVolume {

//////////////////////////////////////////////////////////////////////////////

///
/// This class create a socket for a far field boundary condition obtained with ICP
/// @author George Chatzigeordis
/// @author Nadege Villedieu


class BCFarField : public FVMCC_BC {
public: // functions

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Constructor.
   */
  BCFarField(const std::string& name);

  /**
   * Default destructor
   */
  virtual ~BCFarField();

  /**
   * Returns the DataSocket's that this command needs as sinks
   * @return a vector of SafePtr with the DataSockets
   */
  // virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSink> > needsSockets();



  /**
   * Returns the DataSocket's that this command provides as sources
   * @return a vector of SafePtr with the DataSockets
   */
  // virtual std::vector<Common::SafePtr<Framework::BaseDataSocketSource> > providesSockets();

  /**
   * Set up private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void setup();

  /**
   * Unset up private data and data of the aggregated classes
   * in this command
   */
  virtual void unsetup();
   
  /**
   * Apply boundary condition on the given face
   */
  void setGhostState(Framework::GeometricEntity *const face) ;

  
 protected: // functions


private: // data

  /// the socket stores the data of the mean flow
  // Framework::DataSocketSource<RealVector> socket_meanflow;

  /// the socket stores the states of the mean flow from Fluent
  // Framework::DataSocketSource<RealVector> socket_fluent_states;

  /// the socket stores the coordinates of the mean flow from Fluent
  // Framework::DataSocketSource<RealVector> socket_fluent_coords;

  /// string to hold the file name
//***  std::string m_file_name;

  /// number of nodes per element in Fluent
//***  std::valarray<CFuint> nbNodesPerElemFluent;

 /// Name of Input File where the Boundary Conditions declared.
   std::string m_nameInputFile;

std::vector< std::vector<CFreal> > V_Coords;

std::vector< std::vector<CFreal> > V_States;

std::vector<CFuint> V_Pairing;

}; // end of class BCFarField

//////////////////////////////////////////////////////////////////////////////

    } // namespace LinEuler

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_FiniteVolumeNEQ_BCFarField_hh
