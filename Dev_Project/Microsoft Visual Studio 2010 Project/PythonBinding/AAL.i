%module AAL
%include <python/stl.i>
%include "std_vector.i"

/*Get rid of this. Something like %include <typemaps.i> should help with this maybe*/
%apply bool* INPUT { bool* composit };
%apply int { AAL::uint, uint };

%typemap(out) AAL::DecVector {
	AAL::DecVector vec=$1;
	$result = PyList_New(vec.size());
	for(int i = 0; i < vec.size(); i++) {
		PyList_SetItem($result, i, Py_BuildValue("(ss)", vec[i].getNumber().ToString().c_str(), vec[i].getDegree().ToString().c_str()));
	}
}
/*Get rid of this. Try handle exceptions, where it is needed, or use something like %include <python/exception.i> */
%exception {
   try {
      $action
   } catch (AAL::Exception* e) {
	  PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(e->cp866()));
      return NULL;
   } catch(...) { 
	  PyErr_SetString(PyExc_RuntimeError, "Unknown Exception");
      return NULL; 
	}
}

%{
#include "./AAF/AAL/PrimeTester.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Ellipticcurves.h"
#include "./AAF/AAL/TableManager.h"
#include "./AAF/AAL/EllipticcurvesGF2.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include "./AAF/AAL/NumberVector.h"
#include "./AAF/AAL/PolynomGF7.h"

#include <vector>
#include <string> 
using namespace AAL;
%}


%include "./AAF/AAL/Integer.h"
%include "./AAF/AAL/Algorithms.h"
%include "./AAF/AAL/DecompositionManager.h"
%include "./AAF/AAL/PrimeTester.h"
%include "./AAF/AAL/Matrix.h"
%include "./AAF/AAL/Polynom.h"
%include "./AAF/AAL/PolynomGF3.h"
%include "./AAF/AAL/Ellipticcurves.h"
%include "./AAF/AAL/IntegerBinom.h"
%include "./AAF/AAL/IntegerBinomEllipticcurves.h"
%include "./AAF/AAL/Converter.h"


%include "./AAF/AAL/TableManager.h"
%include "./AAF/AAL/EllipticcurvesGF2.h"
%include "./AAF/AAL/FactorizationAlgorithms.h"
%include "./AAF/AAL/NumberVector.h"
%include "./AAF/AAL/PolynomGF2_m_4.h"
%include "./AAF/AAL/PolynomGF2_mY_7.h"
%include "./AAF/AAL/PolynomGF7.h"

namespace std {
    %template(IntVector) vector<int>;
	%template(DecompositionMemberVector) vector<AAL::DecompositionMember>;
	%template(IntegerBinomVector) vector<AAL::IntegerBinom>;
	%template(IntegerBinomEllipticPointVector) vector<AAL::IntegerBinomEllipticPoint>;
	%template(IntegerPVector) vector<AAL::Integer*>;
	%template(IntegerVector) vector<AAL::Integer>;
}


%extend AAL::Integer {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Integer(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::NumberVector {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.NumberVector(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::Polynom {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Polynom(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::PolynomGF3 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Polynom(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::PolynomGF7 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Polynom(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::Matrix {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Matrix(), %u x %u", $self->getRowCount(),$self->getColCount());
       return tmp;
   }
};

%extend AAL::IntegerBinomModulePolynom {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinomModulePolynom(%s,%s,%s)", $self->getA0().ToString().c_str(),$self->getA1().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};
%extend AAL::IntegerBinom {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinom(%s,%s,%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};

%extend AAL::IntegerBinomEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinomEllipticPoint(%s,%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str());
       return tmp;
   }
};
%extend AAL::IntegerBinomEllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinomEllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};

%extend AAL::EllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.EllipticCurve(%s,%s,%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.EllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.EllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::SuperSingularEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.SuperSingularEllipticCurve(%s,%s,%s,%s)", $self->getModule().ToString().c_str(),$self->getA3().ToString().c_str(),$self->getA4().ToString().c_str(),$self->getA6().ToString().c_str());
       return tmp;
   }
};
%extend AAL::NonSuperSingularEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.NonSuperSingularEllipticCurve(%s,%s,%s)", $self->getModule().ToString().c_str(),$self->getA2().ToString().c_str(),$self->getA6().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPointGF2 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.EllipticPointGF2(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::FactorizationAlgorithms {
   char *__repr__() {
       return "AAL.FactorizationAlgorithms";
   }
};
%extend AAL::PolynomGF2_m_4 {
   char *__repr__() {
       return "AAL.PolynomGF2_m_4";
   }
};
%extend AAL::PolynomGF2_mY_7 {
   char *__repr__() {
       return "AAL.PolynomGF2_mY_7";
   }
};
%extend AAL::PolynomGF7_mY_3 {
   char *__repr__() {
       return "AAL.PolynomGF7_mY_3";
   }
};
%extend AAL::TableManager {
   char *__repr__() {
       return "AAL.TableManager";
   }
};
%extend AAL::PrimeTester {
   char *__repr__() {
       return "AAL.PrimeTester";
   }
};