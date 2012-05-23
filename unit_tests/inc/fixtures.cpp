/*
 * fixtures.cpp
 *
 *  Created on: Apr 27, 2012
 *      Author: stephan grein
 */

#include <boost/test/included/unit_test.hpp>

#include "../../vm2ug.h"
#include "../../mvec.h"
#include "../../common_typedefs.h"

#ifdef MPMDEFAULT
#include "../../bg_default/bg.h"
#else
#include "../../bg_simple/bg.h"
#endif

using namespace boost::unit_test;

template <class T> struct FixtureVUG {
	ug::membrane_potential_mapping::Vm2uG<T>* vm2ug;

	FixtureVUG() : vm2ug(new ug::membrane_potential_mapping::Vm2uG<T>("","")) { BOOST_TEST_MESSAGE("setup fixture >>vm2ug<<"); }
	~FixtureVUG() { BOOST_TEST_MESSAGE("teardown fixture >>vm2ug<<"); }

};

struct FixtureBG {
	ug::membrane_potential_mapping::bg::BG* bg;

	FixtureBG() : bg(new ug::membrane_potential_mapping::bg::BG()) { BOOST_TEST_MESSAGE("setup fixture >>vm2ug<<"); }
	~FixtureBG() { BOOST_TEST_MESSAGE("teardown fixture >>bg<<"); }

};

