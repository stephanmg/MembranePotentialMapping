/****************************************************************************/
/*                                                                          */
/* File:      globals.h                                            	*/
/*                                                                          */
/* Purpose:   global variables    */ 
/*                                                                          */
/* Author:	  Markus M. Knodel                                              */
/*                Goethe Center for Scientific Computing             */
/*                University of Frankfurt                   */
/*                Kettenhofweg 139                           */
/*                60325 Frankfurt              */
/*                Germany              */
/*                email: markus.knodel@gcsc.uni-frankfurt.de    */
/*																			*/
/* History:   2009 begin            									    */
/*                                                                          */
/* Remarks:                                                                 */
/*                                                                          */
/****************************************************************************/


#ifndef __globals_h__
#define __globals_h__

/* system includes */
#include <stddef.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <vector>
#include <string>
#include "solve.h"
#include <fstream>

using namespace std;

namespace ug {
namespace membrane_potential_mapping {
namespace bg {

class BG
{
public:

   static int ap_interval_duration_in_ms; // which stimulation transformation should be choosen
   void install_can_gates(double cond = 1000);
   void install_cal_gates(double cond = 0.3*0.6);
   void install_cat_gates(double cond = 0.3);
   bool installed_can_gates();
   bool installed_cal_gates();
   bool installed_cat_gates();
   
 solve_gating solgat;

 double Neumann_flux;

 string output_file_current;
 
 double  conductivity; // assumed as 1000 mA / mV !
 
 static double Voltage( double time_glob ); // returns the voltage ( time in milliseconds here: if trivial case, i. e. typical AP given)
  
 static double ttrafo_into_ap( double time ); // 100 Hz trafo; time in ms here
   
   double timestepping_of_gates_and_calc_current( double time, double delta_t );
   double calc_current_at_start( double time );
   double get_Neumann_Flux();
   // returns flux in Mol/s
   double get_Neumann_Flux_as_Concentration(const double dt=1.0, const double valency=2.0) const;
   inline double dCa(double delta_t=1e-4) const {
   		return delta_t * 1e3 * solgat.dCa(); // solgat.dCa() === 0
   	}
   BG();
private:
   bool inst_can_gates;
   bool inst_cal_gates;
   bool inst_cat_gates;
};
}	 
}
}
#endif

