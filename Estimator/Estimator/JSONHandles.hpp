/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/
#ifndef JSON_HEADERS_HPP
#define JSON_HEADERS_HPP

#include <boost/lexical_cast.hpp>
#include <json/json.h>
#include <complex>
#include <string>
#include <vector>
#include <fstream>

class IJsonSerializable
{
  public:
    virtual ~IJsonSerializable() {}
    virtual void Serialize(Json::Value& root) =0;
    virtual void Deserialize(Json::Value& root) =0;
};

class Serialize_Coordinate: public IJsonSerializable
{
  public:
    typedef double elem_data_type;
    typedef std::complex<elem_data_type> array_elem_type;
    
    Serialize_Coordinate() {}
    virtual ~Serialize_Coordinate(){}
    
    virtual void Serialize(Json::Value& root);
    virtual void Deserialize(Json::Value& root);
    
    void Serialize_guesses(Json::Value& root, std::vector<array_elem_type>::size_type i);
    void Deserialize_guesses(Json::Value& root);

    std::vector<array_elem_type>& getCoordinates(){ return guesses; }
    std::string& getName() { return person; }
  private:
    std::string person;
    std::vector<array_elem_type> guesses;
};

void Serialize_Coordinate::Serialize(Json::Value& root)
{
  root["person"] = person;
  std::vector<array_elem_type>::size_type size = guesses.size();
  Json::Value cord;
  for(std::vector<array_elem_type>::size_type i=0; i<size; ++i){
    Serialize_guesses(cord,i);
    root["guesses"].append(cord);
  }
}

void Serialize_Coordinate::Deserialize(Json::Value& root)
{
  person = root.get("person","").asString();
  if(root.get("guesses","").isArray()){
    Json::Value g = root["guesses"];
    int size = root.get("guesses","").size();
    for(int i=0; i<size; i++)
      Deserialize_guesses(g[i]);
  }
}

//here comes a pair of cordinates
void Serialize_Coordinate::Deserialize_guesses(Json::Value& root)
{
  std::string y_cor = root.get("y",0.0).asString();
  std::string x_cor = root.get("x",0.0).asString();
  elem_data_type x,y;
  try{
    x = boost::lexical_cast<elem_data_type>(x_cor);
    y = boost::lexical_cast<elem_data_type>(y_cor);
  } catch(boost::bad_lexical_cast &){
    std::cerr<<"Error:: Invalid element type\n";
  }
  guesses.push_back(array_elem_type(x,y));
}

//here comes a pair of cordinates
void Serialize_Coordinate::Serialize_guesses(Json::Value& root, std::vector<array_elem_type>::size_type i)
{
  try {
    root["y"] =  boost::lexical_cast<std::string>(guesses[i].imag());
    root["x"] =  boost::lexical_cast<std::string>(guesses[i].real());
  } catch(boost::bad_lexical_cast &){
    std::cerr<<"Error:: Invalid element type\n";
  }
}

class CJsonSerializer
{
  public:
    static bool Serialize(IJsonSerializable* pObj, std::string& output);
    static bool Deserialize(IJsonSerializable* pObj, std::string& input);
    static bool Serialize(IJsonSerializable* pObj, std::ofstream& foutput);
    static bool Deserialize(IJsonSerializable* pObj, std::ifstream& finput);

  private:
    CJsonSerializer() {}
};

bool CJsonSerializer::Serialize(IJsonSerializable* pObj, std::string& output)
{
  if(pObj == NULL)
    return false;
      
  Json::Value serializeRoot;
  pObj->Serialize(serializeRoot);
            
  Json::StyledWriter writer;
  output = writer.write(serializeRoot);
return true;
}
 
bool CJsonSerializer::Deserialize(IJsonSerializable* pObj, std::string& input)
{
  if(pObj == NULL)
    return false;
      
  Json::Value deserializeRoot;
  Json::Reader reader;

  if(!reader.parse(input, deserializeRoot))
    return false;
  pObj->Deserialize(deserializeRoot);

return true;
}

bool CJsonSerializer::Serialize(IJsonSerializable* pObj, std::ofstream& foutput)
{
  std::string str;
  Serialize(pObj,str);
  foutput<<str;
return true;
}

bool CJsonSerializer::Deserialize(IJsonSerializable* pObj, std::ifstream& finput)
{
  std::string str((std::istreambuf_iterator<char>(finput)),
                       std::istreambuf_iterator<char>());
  Deserialize(pObj,str);
return true;
}

#endif //JSON_HEADERS_HPP
