#ifndef CMDB_MAPEVALS_H
#define CMDB_MAPEVALS_H

// include headers that implement a archive in simple text format
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/vector.hpp>
#include "chomp/Rect.h"
#include "chomp/Toplex.h"

class MapEvals {
 private:
  friend class boost::serialization::access;
  chomp::Rect parameter_;
  typedef chomp::Toplex::value_type GridElement;
  std::vector < GridElement > arguments_;
  std::vector < std::vector < GridElement > > values_;
 public:
  
  void insert ( const GridElement & ge ) {
    arguments_ . push_back ( ge );
    values_ . push_back ( std::vector < GridElement > () );
  }
  chomp::Rect & parameter ( void ) {
    return parameter_;
  }
  
  GridElement arg ( size_t i ) const {
    return arguments_ [ i ];
  }
  
  std::vector<GridElement> & val ( size_t i ) {
    return values_ [ i ];
  }
  size_t size ( void ) const {
    return arguments_ . size ();
  }
  
template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & parameter_;
    ar & arguments_;
    ar & values_;
  }

 void load ( const char * filename ) {
   std::ifstream ifs(filename);
   boost::archive::text_iarchive ia(ifs);
   ia >> *this;
   // 
 }
 void save ( const char * filename ) {
   std::ofstream ofs(filename);
   boost::archive::text_oarchive oa(ofs);
   oa << *this;
   // oa closes ofs
 }

};
#endif