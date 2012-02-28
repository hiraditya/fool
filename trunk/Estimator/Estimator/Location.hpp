/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include<vector>
#include<complex>
#include<exception>

template<typename elem_type>
class Estimator{
  public:
/*    Estimator(std::vector<elem_type>& pts)
      :points(pts)
    { }*/
    virtual void setPoints(std::vector<elem_type>& pts)
    { points = pts; }
    virtual elem_type Estimate() =0;
    virtual ~Estimator()
    { }
  protected:
    std::vector<elem_type> points;
};

template<typename elem_type>
class Estimate_mode : public Estimator<elem_type> {
  public:
    typedef double difference_type;
    typedef size_t count_type;
    typedef std::map<difference_type, count_type> bar_chart;
    
    elem_type Estimate()
    {
      if(!ChartReady())
        InitializeChart();
      return estimated_point;
    }

    void InitializeChart()
    {
      typedef typename std::vector<elem_type>::iterator v_iter;
      v_iter iter = Estimator<elem_type>::points.begin();
      v_iter end =  Estimator<elem_type>::points.end();
      for( ; iter != end; ++iter)
      {
        //to be implemented
      }
      chart_ready = true;
    }

    bool ChartReady()
    { return chart_ready; }

    void setDelta(difference_type d=1.0)
    { delta = d; }

  private:
    bool chart_ready;
    difference_type delta;
    elem_type estimated_point;
    bar_chart freq_dist;
};

template<typename elem_type>
class Estimate_centroid : public Estimator<elem_type> {
  public:

    elem_type Estimate()
    {
      typename elem_type::value_type total_size = Estimator<elem_type>::points.size();
      if(!total_size)
        throw std::exception();//to avoid divide by zero error
      typedef typename std::vector<elem_type>::iterator v_iter;
      v_iter iter = Estimator<elem_type>::points.begin();
      v_iter end = Estimator<elem_type>::points.end();
      for( ; iter!= end; ++iter)
        estimated_point += *iter;
      estimated_point = estimated_point/total_size;
      return estimated_point;
    }

    elem_type getEstimatedPoint()
    { return estimated_point; }

  private:
    elem_type estimated_point;
};

#endif //LOCATION_HPP
