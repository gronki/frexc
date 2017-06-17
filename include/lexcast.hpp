#include <sstream>

/*
 * OPERATOR RZUTOWANA LEKSYKALNEGO
 * Wziêty z ksi¹¿ki: 
 *  N.Josuttis - Programowanie obiektowe C++
 *  Helion, 2003 ISBN 83-7361-195-9
 */

template <typename Target, typename Source>
Target lexical_cast (const Source& in) {
	std::stringstream interpreter;
	Target out;
	
	if (!(interpreter << in) || !(interpreter >> out) ||
		!(interpreter >> std::ws).eof()) {
			throw "lexical casting error";
	}
	
	return out;
}
