/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/


#include "INCHeaders.hpp"

int main(int argc, char** argv)
{
  QApplication a(argc,argv);
  QwtPlot plot;

  std::string filename = "guesses.txt";
  Serialize_Coordinate guess_cord;
  point_type pt;
  container cords;
  try {
   pt = estimate(filename,guess_cord);
   cords = guess_cord.getCoordinates();
  }catch(std::exception& e){
    std::cerr<<"Error:"<<e.what();
    return -1;
  }

  QwtPlotCurve loc("Location");
  QwtPlotCurve est("Estimate");
  std::vector<double> xs;
  std::vector<double> ys;

  container::const_iterator it = cords.begin();
  for ( ; it!= cords.end(); ++it)
  {
    xs.push_back(it->real());
    ys.push_back(it->imag());
  }

  const int xdelta=10, ydelta=10;
  const int scaling = 5;
  std::pair<double,double> x_range =  std_container_utils::find_max(xs);
  std::pair<double,double> y_range =  std_container_utils::find_max(ys);


  plot.setCanvasBackground(Qt::white);
  plot.setGeometry(0,0,640,480);
  plot.setAxisScale(QwtPlot::xBottom,
                    x_range.first -xdelta,
                    x_range.second +xdelta,
                    (x_range.second-x_range.first)/scaling);
  plot.setAxisScale(QwtPlot::yLeft,
                    y_range.first -ydelta,
                    y_range.second +ydelta,
                    (y_range.second-y_range.first)/scaling);



  QPen pen_1 = QPen(Qt::red, 2.0);
  QPen pen_2 = QPen(Qt::black, 6.0);

  /// @todo insert legend
  loc.setStyle(QwtPlotCurve::CurveStyle::Dots);
  loc.setPen(pen_1);
  loc.setData(&xs[0],&ys[0],xs.size());
  loc.attach(&plot);

  double x_es = pt.real();
  double y_es = pt.imag();

  est.setStyle(QwtPlotCurve::CurveStyle::Dots);
  est.setPen(pen_2);
  est.setData(&x_es,&y_es,1);
  est.attach(&plot);

  plot.replot();
  plot.show();

return a.exec();
}


point_type estimate(std::string& filename, Serialize_Coordinate& guess_cord)
{
  /// uncomment the lines to see the output on command line
  //std::cout.setf(std::ios::fixed);
  //std::cout.precision(9);
  std::ifstream input(filename);
  CJsonSerializer::Deserialize(&guess_cord, input);
  Estimate_centroid<std::complex<double> > es;
  container& cords = guess_cord.getCoordinates();
  es.setPoints(cords);
  point_type cord = es.Estimate();
  //std::cout<<"Best estimated location is:"<<cord;
  return cord;
}
