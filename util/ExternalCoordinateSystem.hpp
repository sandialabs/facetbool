
#ifndef EXTERNAL_COORDINATE_SYSTEM_HPP
#define EXTERNAL_COORDINATE_SYSTEM_HPP

class ExternalCoordinateSystem
{
  public:

  virtual ~ExternalCoordinateSystem() {}

	//given s,n return x,y,z
	virtual bool GetXYZ( double s, double n,
   		    		 double &x, double &y, double &z ) = 0;
   	
  //given x,y,z , return an s,n
  virtual bool GetSN( double x, double y, double z,
	      			double &s, double &n ) = 0;	  
};

#endif