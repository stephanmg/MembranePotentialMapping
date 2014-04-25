/*!
 * \file transform.cpp
 * \brief implementation of preprocessing: uses high-level embedding of the Python language
 *
 * \see http://docs.python.org/extending/embedding.html
 *
 * TODO: integrate for usage within VRL
 *
 * \date created on Aug 3, 2012
 * \author Stephan Grein
 */


#include "/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/Python.h"
#include <exception>
#include <sstream>
#include <string>
#include <fstream>

#include <common/log.h>
#include <common/error.h>

#include "transform.h"

using namespace ug::membrane_potential_mapping;

void Transform::modify_hoc_setup(number dt, long steps, number vinit) {
	try {
		m_dt = dt;
		m_steps = steps;
		m_vinit = vinit;
	} catch (const std::exception& exception) {
		UG_THROW("Fatal error in Transform::modify_hoc_setup occured. Stopping execution with:" << exception.what() << std::endl);
    }
}

void Transform::extract_timesteps_and_obj(bool gen_objfile, const std::string& neugen_executable, const std::string& neutria_executable) {
	try {
		/*! initializes the Python interpreter */
		Py_Initialize();

		if (PyRun_SimpleString("from neuron import h") == -1) throw;
		if (PyRun_SimpleString("from neuron import hoc") == -1) throw;

		/*! command string buffer */
		std::stringstream command;

		/*! 1st NEURON cmd */
		command << "h.load_file("
				<< m_hocfile
				<< ")";
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! 2nd NEURON cmd */
		if (PyRun_SimpleString("h.load_file(mview.hoc)") == -1) throw;

		/*! 3rd NEURON cmd */
		if (PyRun_SimpleString("h.define_shape()") == -1) throw;

		/*! 4th NEURON cmd */
		if (PyRun_SimpleString("modelView = h.ModelView(0)") == -1) throw;

		/*! 5th NEURON cmd */
		if (PyRun_SimpleString("modelxml = h.ModelViewXML(modelView)") == -1) throw;

		/*! 6th NEURON cmd */
		command << "modelxml.xportLevel1(" << m_xmlfile << ")";
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! 1st hoc cmd */
		command << "hoc.execute('"
				<< "dt="
				<< m_dt
				<< ')\'\\n';
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! 2nd hoc cmd */
		command << "hoc.execute('"
				<< "tstop"
				<< m_steps*m_dt
				<< ')\'\\n';
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! 3rd hoc cmd */
		command << "hoc.execute('"
				<< "finitialize("
				<< m_vinit
				<< ')'
				<< ')\'\\n';
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! 4th hoc cmd */
		command << "hoc.execute('"
				<< "while(t < tstop) { " << "\\n"
				<< "sprint(fname, " << m_timestepdirectory << "/" << "%f.csv)" << ", t/1000) \\n"
				<< "outfile = wopen(fname, \'w\') \\n"
				<< "forall for i=0,n3d()-1 fprint(\"%f %f %f %f\n\", x3d(i), y3d(i), z3d(i), v(i)) \\n"
				<< "wopen() \\n"
				<< "fadvance() \\n"
				<< "} \\n"
				<< '\')\\n';
		if (PyRun_SimpleString(command.str().c_str()) == -1) throw;
		command.clear();

		/*! shut down the Python interpreter */
		Py_Finalize();

   std::string directory = m_xmlfile;
   directory.erase(directory.find_last_of(".", std::string::npos));

   std::string xmlfile = m_xmlfile;
   xmlfile.erase(directory.find_first_of(".", std::string::npos));

		if (gen_objfile) {

			command << "cd " << directory << std::endl;
			if (system(command.str().c_str()) == -1) throw;
			command.clear();

			command << "java -jar " << neugen_executable << " " << xmlfile << std::endl;
			if (system(command.str().c_str()) == -1) throw;
			command.clear();

			std::ofstream neutria("neutria.lua");
			neutria << "neutria.set_hoc_params_low()" << std::endl
					<< "neutria.open_simple_hoc('test.shoc')" << std::endl
					<< "neutria.create_grid_hoc_spline()" << std::endl
					<< "neutria.save_grid_to_file('" << m_objfile << "')" << std::endl;
			if (system(command.str().c_str()) == -1) throw;
			command.clear();

			command << neutria_executable << " neutria.lua" << std::endl;
			if (system(command.str().c_str()) == -1) throw;
			command.clear();
		}
	} catch (const std::exception& exception) {
		UG_THROW("Fatal error in Transform::extract_timesteps_and_obj occured. Stopping execution with:" << exception.what() << std::endl);
	}
}
