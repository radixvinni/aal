%module AAL
%include <python/stl.i>
%include "std_vector.i"

/*Get rid of this. Something like %include <typemaps.i> should help with this maybe*/
%apply bool* INPUT { bool* composit };
%apply int { AAL::uint, uint };

/*Get rid of this. Try handle exceptions, where it is needed, or use something like %include <python/exception.i> */
%exception {
   try {
      $action
   } catch (AAL::Exception* e) {
      PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(e->cp1251()));
      return NULL;
   } catch(...) { 
      PyErr_SetString(PyExc_RuntimeError, "Unknown Exception");
      return NULL; 
    }
}

%feature("autodoc", "1");

%{
#include "./AAF/AAL/PrimeTester.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Ellipticcurves.h"
#include "./AAF/AAL/TableManager.h"
#include "./AAF/AAL/EllipticcurvesGF2.h"
#include "./AAF/AAL/EllipticcurvesGF3.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include "./AAF/AAL/NumberVector.h"
#include "./AAF/AAL/PolynomGF7.h"

#include <vector>
#include <string>

using namespace AAL;
%}

%include "./AAF/AAL/BasicType.h"
%template(ucharBasicType) AAL::BasicType<AAL::uchar>;
%template(uintBasicType) AAL::BasicType<AAL::uint>;

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
%include "./AAF/AAL/EllipticcurvesGF3.h"
%include "./AAF/AAL/FactorizationAlgorithms.h"
%include "./AAF/AAL/NumberVector.h"
%include "./AAF/AAL/PolynomGF2_m_4.h"
%include "./AAF/AAL/PolynomGF3_m_6.h"
%include "./AAF/AAL/PolynomGF2_mY_7.h"
%include "./AAF/AAL/PolynomGF3_mY_9.h"
%include "./AAF/AAL/PolynomGF7.h"

%include "stl.i"
namespace std {
    %template(_string_list) std::vector<std::string>;
    %template(_int_list) std::vector<int>;
    %template(_double_list) std::vector<double>;
    
    %template(IntVector) vector<int>;
    %template(DecompositionMemberVector) vector<AAL::DecompositionMember>;
    %template(IntegerBinomVector) vector<AAL::IntegerBinom>;
    %template(IntegerBinomEllipticPointVector) vector<AAL::IntegerBinomEllipticPoint>;
    %template(IntegerPVector) vector<AAL::Integer*>;
    %template(IntegerVector) vector<AAL::Integer>;
}

%extend std::vector<AAL::DecompositionMember> {
  char *__repr__() {
      static char tmp[1024];
      PyObject* result = PyList_New($self->size());
      for(int i = 0; i < $self->size(); i++) {
          PyList_SetItem(result, i, Py_BuildValue("(ss)", $self->at(i).getNumber().ToString().c_str(), $self->at(i).getDegree().ToString().c_str()));
      }
      PyObject* objectsRepresentation = PyObject_Repr(result);
    const char* s = PyString_AsString(objectsRepresentation);
    sprintf(tmp,"AAL.DecompositionMemberVector(%d): %s", $self->size(), s);
    return tmp;
    }
  PyObject *toList() {
      PyObject* result = PyList_New($self->size());
      for(int i = 0; i < $self->size(); i++) {
          PyList_SetItem(result, i, Py_BuildValue("(ss)", $self->at(i).getNumber().ToString().c_str(), $self->at(i).getDegree().ToString().c_str()));
      }
      return result;
  }
}

%extend AAL::Integer {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.Integer(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%pythoncode %{

Integer.ModAdd_ = Integer.ModAdd
Integer.ModAddInFp_ = Integer.ModAddInFp
Integer.ModSub_ = Integer.ModSub
Integer.SubInFp_ = Integer.SubInFp
Integer.ModMul_ = Integer.ModMul
Integer.MulInFp_ = Integer.MulInFp
Integer.ModDiv_ = Integer.ModDiv
Integer.DivInFp_ = Integer.DivInFp
Integer.ModPow_ = Integer.ModPow
Integer.PowInFp_ = Integer.PowInFp
Integer.ModSqrt_ = Integer.ModSqrt
Integer.Inverse_ = Integer.Inverse
Integer.InverseInFp_ = Integer.InverseInFp

temp = Integer()

Integer.ModAdd = lambda s,a,b,m: s.ModAdd_(a,b,m).Add(s,m) if temp.ModAdd_(a,b,m).isNegative() else s.ModAdd_(a,b,m)
Integer.ModAddInFp = lambda s,a,b,m: s.ModAddInFp_(a,b,m).Add(s,m) if temp.ModAddInFp_(a,b,m).isNegative() else s.ModAddInFp_(a,b,m)
Integer.ModSub = lambda s,a,b,m: s.ModSub_(a,b,m).Add(s,m) if temp.ModSub_(a,b,m).isNegative() else s.ModSub_(a,b,m)
Integer.SubInFp = lambda s,a,b,m: s.SubInFp_(a,b,m).Add(s,m) if temp.SubInFp_(a,b,m).isNegative() else s.SubInFp_(a,b,m)
Integer.ModMul = lambda s,a,b,m: s.ModMul_(a,b,m).Add(s,m) if temp.ModMul_(a,b,m).isNegative() else s.ModMul_(a,b,m)
Integer.MulInFp = lambda s,a,b,m: s.MulInFp_(a,b,m).Add(s,m) if temp.MulInFp_(a,b,m).isNegative() else s.MulInFp_(a,b,m)
Integer.ModDiv = lambda s,a,b,m: s.ModDiv_(a,b,m).Add(s,m) if temp.ModDiv_(a,b,m).isNegative() else s.ModDiv_(a,b,m)
Integer.DivInFp = lambda s,a,b,m: s.DivInFp_(a,b,m).Add(s,m) if temp.DivInFp_(a,b,m).isNegative() else s.DivInFp_(a,b,m)
Integer.ModPow = lambda s,a,b,m: s.ModPow_(a,b,m).Add(s,m) if temp.ModPow_(a,b,m).isNegative() else s.ModPow_(a,b,m)
Integer.PowInFp = lambda s,a,b,m: s.PowInFp_(a,b,m).Add(s,m) if temp.PowInFp_(a,b,m).isNegative() else s.PowInFp_(a,b,m)

Integer.ModSqrt = lambda s,a,m: s.ModSqrt_(a,m).Add(s,m) if temp.ModSqrt_(a,m).isNegative() else s.ModSqrt_(a,m)
Integer.Inverse = lambda s,a,m: s.Inverse_(a,m).Add(s,m) if temp.Inverse_(a,m).isNegative() else s.Inverse_(a,m)
Integer.InverseInFp = lambda s,a,m: s.InverseInFp_(a,m).Add(s,m) if temp.InverseInFp_(a,m).isNegative() else s.InverseInFp_(a,m)

%}

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
       sprintf(tmp,"AAL.PolynomGF3(%s)", $self->ToString().c_str());
       return tmp;
   }
};
%extend AAL::PolynomGF7 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.PolynomGF7(%s)", $self->ToString().c_str());
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
       sprintf(tmp,"AAL.IntegerBinomModulePolynom(%s,%s,module=%s)", $self->getA0().ToString().c_str(),$self->getA1().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};
%extend AAL::IntegerBinom {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinom(%s,%s,module=%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};

%extend AAL::IntegerBinomEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.IntegerBinomEllipticPoint(a=%s,b=%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str());
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
       sprintf(tmp,"AAL.EllipticCurve(a=%s,b=%s,module=%s)", $self->getA().ToString().c_str(),$self->getB().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticCurveGF3 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.EllipticCurveGF3(a2=%s,a4=%s,a6=%s,module=%s)", $self->getA2().ToString().c_str(),$self->getA4().ToString().c_str(),$self->getA6().ToString().c_str(),$self->getModule().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       if ($self->isInfinite())
       sprintf(tmp,"AAL.EllipticPoint(точка на бесконечности)");
       else
       sprintf(tmp,"AAL.EllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPointGF2 {
   char *__repr__() {
       static char tmp[1024];
       if ($self->isInfinite())
       sprintf(tmp,"AAL.EllipticPointGF2(точка на бесконечности)");
       else
       sprintf(tmp,"AAL.EllipticPointGF2(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::EllipticPointGF3 {
   char *__repr__() {
       static char tmp[1024];
       if ($self->isInfinite())
       sprintf(tmp,"AAL.EllipticPointGF3(точка на бесконечности)");
       else
       sprintf(tmp,"AAL.EllipticPointGF3(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::SuperSingularEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.SuperSingularEllipticCurve(module=%s,a3=%s,a4=%s,a6=%s)", $self->getModule().ToString().c_str(),$self->getA3().ToString().c_str(),$self->getA4().ToString().c_str(),$self->getA6().ToString().c_str());
       return tmp;
   }
};
%extend AAL::NonSuperSingularEllipticCurve {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.NonSuperSingularEllipticCurve(module=%s,a2=%s,a6=%s)", $self->getModule().ToString().c_str(),$self->getA2().ToString().c_str(),$self->getA6().ToString().c_str());
       return tmp;
   }
};
%pythoncode %{
SuperSingularEllipticCurve.getOrder = lambda curve: curve.getOrd(curve.getModule().ToString().rfind('1'))
%}
%extend AAL::SuperSingularEllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       if ($self->isInfinite())
       sprintf(tmp,"AAL.SuperSingularEllipticPoint(точка на бесконечности)");
       else
       sprintf(tmp,"AAL.SuperSingularEllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
       return tmp;
   }
};
%extend AAL::NonSuperSingularEllipticPoint {
   char *__repr__() {
       static char tmp[1024];
       if ($self->isInfinite())
       sprintf(tmp,"AAL.NonSuperSingularEllipticPoint(точка на бесконечности)");
       else
       sprintf(tmp,"AAL.NonSuperSingularEllipticPoint(x=%s,y=%s)", $self->getX().ToString().c_str(),$self->getY().ToString().c_str());
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
       static char tmp[1024];
       sprintf(tmp,"AAL.PolynomGF2_m_4(module=%s,a0=%s,a1=%s,a2=%s,a3=%s)", $self->getModule().ToString().c_str(),$self->getA0().ToString().c_str(),$self->getA1().ToString().c_str(),$self->getA2().ToString().c_str(),$self->getA3().ToString().c_str());
       return tmp;
   }
};
%extend AAL::PolynomGF3_m_6 {
   char *__repr__() {
       static char tmp[1024];
       sprintf(tmp,"AAL.PolynomGF3_m_6(module=%s,a0=%s,a1=%s,a2=%s,a3=%s,a4=%s,a5=%s)", $self->getModule().ToString().c_str(),$self->getA0().ToString().c_str(),$self->getA1().ToString().c_str(),$self->getA2().ToString().c_str(),$self->getA3().ToString().c_str(),$self->getA4().ToString().c_str(),$self->getA5().ToString().c_str());
       return tmp;
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
