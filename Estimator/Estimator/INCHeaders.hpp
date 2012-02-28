/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/

#ifndef INCHEADERS_HPP
#define INCHEADERS_HPP

#include "JSONHandles.hpp"
#include "Location.hpp"

#include "ComplexUtils.hpp"
#include "VectorUtils.hpp"

#include <cmath>
#include <qapplication.h>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>

#include <exception>
#include <complex>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

typedef std::vector<std::complex<double> > container;
typedef std::complex<double> point_type;

point_type estimate(std::string& filename, Serialize_Coordinate& guess_cord);

#endif // INCHEADERS_HPP
