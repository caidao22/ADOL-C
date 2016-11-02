/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     adolc-python.i
 Revision: $Id$
 Contents: Provides all C/C++ interfaces of ADOL-C.
 
 Copyright (c) Kshitij Kulshreshtha

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes 
 recipient's acceptance of the terms of the accompanying license file.  
 
----------------------------------------------------------------------------*/

%module adolc
%{
#define SWIG_FILE_WITH_INIT
#include <adolc/adolc.h>
#include "matrixmemory.hpp"
#include <adolc/adolc_fatalerror.h>

static PyObject* PyExc_AdolcException; 
%}

%include "numpy.i"

%init %{
import_array();
PyExc_AdolcException = PyErr_NewExceptionWithDoc("adolc.AdolcException", 
"This exception is thrown if an error condition happens during the call"
" to an ADOL-C library function, which in a pure C/C++ environment would be"
" detected by the return value of that library function. This is generally"
" a warning to retrace the original function at the current point", 
                                NULL, NULL);
PyModule_AddObject(m,"AdolcException",PyExc_AdolcException);
%}

%feature("novaluewrapper") badouble;
%feature("novaluewrapper") adub;
%feature("novaluewrapper") pdouble;
%feature("novaluewrapper") adubref;
%feature("novaluewrapper") adouble;
%feature("novaluewrapper") advector;

%include "../include/adolc/adolc_fatalerror.h"

%extend FatalError {
    virtual const char* __str__() const throw() {
        return (*($self)).what();
    }
}

%ignore operator<<;
%ignore operator>>;
%ignore operator<=;
%ignore operator<;
%ignore operator>=;
%ignore operator>;
%ignore operator==;
%ignore operator!=;
%ignore pow;
%ignore *::operator++;
%ignore *::operator--;
%ignore *::operator=;
%ignore zos_forward_nk;
%ignore zos_forward_partx;
%ignore fos_forward_nk;
%ignore fos_forward_partx;
%ignore hos_forward_nk;
%ignore hos_forward_partx;
%ignore fov_forward_partx;
%ignore fov_offset_forward;
%ignore hov_forward_partx;
%ignore function_;
%ignore gradient_;
%ignore jacobian_;
%ignore large_jacobian_;
%ignore vec_jac_;
%ignore jac_vec_;
%ignore hessian_;
%ignore hess_vec_;
%ignore hessian2_;
%ignore hess_mat_;
%ignore lagra_hess_vec_;
%ignore forodec_;
%ignore accodec_;
%ignore hos_forward_;
%ignore fov_forward_;
%ignore hov_forward_;
%ignore hov_wk_forward_;
%ignore fos_reverse_;
%ignore hos_reverse_;
%ignore hos_ti_reverse_;
%ignore hos_ov_reverse_;
%ignore fov_reverse_;
%ignore hov_reverse_;
%ignore hov_ti_reverse_;
%ignore directional_active_gradient_;
%ignore abs_normal_;
%ignore spread1;
%ignore pack1;
%ignore spread2;
%ignore pack2;
%ignore spread3;
%ignore pack3;
%ignore *::operator[](const badouble&);
%ignore *::operator[](size_t);
%ignore *::operator[](const badouble&) const;
%ignore *::operator[](size_t) const;
%ignore *::operator double;
%ignore *::operator double const&;
%ignore *::operator double&&;
%ignore *::operator adub;
%ignore *::operator const std::vector<adouble>&;
%ignore *::operator std::vector<adouble>&;
%ignore *::operator adouble*;

%typemap(in) locint {
    $1 = PyLong_AsUnsignedLong($input);
 }

%typemap(out) locint {
    $result = PyLong_FromUnsignedLong($1);
 }

%pythoncode %{
AdolcException = _adolc.AdolcException
%}

%inline %{
#define CHECKEXCEPT(rc, func) \
    if ((rc) < 0) {                                                     \
        PyErr_Format(PyExc_AdolcException,                              \
                     "An error has been detected in an ADOL-C library"  \
                     "function (%s). It returned the code %d."          \
                     " Look at previous messages"                       \
                     " printed.",                                       \
                     func, (rc));                                       \
    }
%}

%exception {
    try {
        $action
        if (PyErr_Occurred()) SWIG_fail;
    } catch (FatalError &_e) {
    SWIG_Python_Raise(SWIG_NewPointerObj(
            (new FatalError(static_cast<const FatalError& >(_e))),  
            SWIGTYPE_p_FatalError,SWIG_POINTER_OWN),
        "FatalError", SWIGTYPE_p_FatalError); 
    SWIG_fail;
    }
}

%include "adolc-numpy-for.i"
%include "adolc-numpy-rev.i"
%include "adolc-numpy-drv.i"
%include "adolc_all.hpp"

%extend advector {
    adub* __getitem__(const badouble& index) const {
        return (adub*) (*($self))[index];
    }
    adubref* __getitem__(const badouble& index) {
        return (adubref*) (*($self))[index];
    }
    adouble& __getitem__(size_t index) {
        return (*($self))[index];
    }
    const adouble& __getitem__(size_t index) const {
        return (*($self))[index];
    }
    size_t __len__() const {
        return (*($self)).size();
    }
 }

%ignore frexp;
%ignore operator+;
%ignore operator-;
%ignore operator*;
%ignore operator/;

%include "adubswigfuncs.h"

%extend badouble {
    int __ne__ (const badouble& a) const {
        return (*($self)) != a;
    }
    int __eq__ (const badouble& a) const {
        return (*($self)) == a;
    }
    int __le__ (const badouble& a) const {
        return (*($self)) <= a;
    }
    int __ge__ (const badouble& a) const {
        return (*($self)) >= a;
    }
    int __lt__ (const badouble& a) const {
        return (*($self)) < a;
    }
    int __gt__ (const badouble& a) const {
        return (*($self)) > a;
    }
    int __ne__ (double a) const {
        return (*($self)) != a;
    }
    int __eq__ (double a) const {
        return (*($self)) == a;
    }
    int __le__ (double a) const {
        return (*($self)) <= a;
    }
    int __ge__ (double a) const {
        return (*($self)) >= a;
    }
    int __lt__ (double a) const {
        return (*($self)) < a;
    }
    int __gt__ (double a) const {
        return (*($self)) > a;
    }
    adouble __pow__ (const badouble& a) {
        return pow((*($self)),a);
    }
    adub* __pow__(double c) {
        return (adub*) pow((*($self)),c);
    }
    adouble __rpow__(double c) {
        return pow(c,(*($self)));
    }
    adub* __pow__ (const pdouble& a) {
        return (adub*) pow((*($self)),a);
    }
    adub* __neg__() {
        return (adub*)( - (*($self)));
    }
    adub* __add__ (const badouble& a) {
        return (adub*) ((*($self)) + a);
    }
    adub* __add__ (double a) {
        return (adub*) ((*($self)) + a);
    }
    adub* __radd__ (double a) {
        return (adub*) (a + (*($self)));
    }
    adub* __add__ (const pdouble& a) {
        return (adub*) ((*($self)) + a);
    }
    adub* __sub__ (const badouble& a) {
        return (adub*) ((*($self)) - a);
    }
    adub* __sub__ (double a) {
        return (adub*) ((*($self)) - a);
    }
    adub* __rsub__ (double a) {
        return (adub*) (a - (*($self)));
    }
    adub* __sub__ (const pdouble& a) {
        return (adub*) ((*($self)) - a);
    }
    adub* __mul__ (const badouble& a) {
        return (adub*) ((*($self)) * a);
    }
    adub* __mul__ (double a) {
        return (adub*) ((*($self)) * a);
    }
    adub* __rmul__ (double a) {
        return (adub*) (a * (*($self)));
    }
    adub* __mul__ (const pdouble& a) {
        return (adub*) ((*($self)) * a);
    }
    adub* __div__ (const badouble& a) {
        return (adub*) ((*($self)) / a);
    }
    adub* __div__ (double a) {
        return (adub*) ((*($self)) / a);
    }
    adub* __rdiv__ (double a) {
        return (adub*) (a / (*($self)));
    }
    adub* __div__ (const pdouble& a) {
        return (adub*) ((*($self)) / a);
    }    
    adub* sin() {
        return (adub*) sin(*($self));
    }
    adub* cos() {
        return (adub*) cos(*($self));
    }
    adub* tan() {
        return (adub*) tan(*($self));
    }
    adub* exp() {
        return (adub*) exp(*($self));
    }
    adub* log() {
        return (adub*) log(*($self));
    }
    adub* asin() {
        return (adub*) asin(*($self));
    }
    adub* acos() {
        return (adub*) acos(*($self));
    }
    adub* atan() {
        return (adub*) atan(*($self));
    }
    adub* log10() {
        return (adub*) log10(*($self));
    }
    adub* sinh() {
        return (adub*) sinh(*($self));
    }
    adub* cosh() {
        return (adub*) cosh(*($self));
    }
    adub* tanh() {
        return (adub*) tanh(*($self));
    }
#if defined(ATRIG_ERF)
    adub* asinh() {
        return (adub*) asinh(*($self));
    }
    adub* acosh() {
        return (adub*) acosh(*($self));
    }
    adub* atanh() {
        return (adub*) atanh(*($self));
    }
    adub* erf() {
        return (adub*) erf(*($self));
    }
#endif
    adub* fabs() {
        return (adub*) fabs(*($self));
    }
    adub* abs() {
        return (adub*) fabs(*($self));
    }
    adub* ceil() {
        return (adub*) ceil(*($self));
    }
    adub* floor() {
        return (adub*) floor(*($self));
    }

}

%extend pdouble {
    adub* __neg__() {
        return (adub*)( - (*($self)));
    }
    adub* __add__ (const badouble& a) {
        return (adub*) ((*($self)) + a);
    }
    adub* __add__ (double a) {
        return (adub*) ((*($self)) + a);
    }
    adub* __radd__ (double a) {
        return (adub*) (a + (*($self)));
    }
    adub* __sub__ (const badouble& a) {
        return (adub*) ((*($self)) - a);
    }
    adub* __sub__ (double a) {
        return (adub*) ((*($self)) - a);
    }
    adub* __rsub__ (double a) {
        return (adub*) (a - (*($self)));
    }
    adub* __mul__ (const badouble& a) {
        return (adub*) ((*($self)) * a);
    }
    adub* __mul__ (double a) {
        return (adub*) ((*($self)) * a);
    }
    adub* __rmul__ (double a) {
        return (adub*) (a * (*($self)));
    }
    adub* __div__ (const badouble& a) {
        return (adub*) ((*($self)) / a);
    }
    adub* __div__ (double a) {
        return (adub*) ((*($self)) / a);
    }
    adub* __rdiv__ (double a) {
        return (adub*) (a / (*($self)));
    }
    adub* sin() {
        return (adub*) sin(*($self));
    }
    adub* cos() {
        return (adub*) cos(*($self));
    }
    adub* tan() {
        return (adub*) tan(*($self));
    }
    adub* exp() {
        return (adub*) exp(*($self));
    }
    adub* log() {
        return (adub*) log(*($self));
    }
    adub* asin() {
        return (adub*) asin(*($self));
    }
    adub* acos() {
        return (adub*) acos(*($self));
    }
    adub* atan() {
        return (adub*) atan(*($self));
    }
    adub* log10() {
        return (adub*) log10(*($self));
    }
    adub* sinh() {
        return (adub*) sinh(*($self));
    }
    adub* cosh() {
        return (adub*) cosh(*($self));
    }
    adub* tanh() {
        return (adub*) tanh(*($self));
    }
#if defined(ATRIG_ERF)
    adub* asinh() {
        return (adub*) asinh(*($self));
    }
    adub* acosh() {
        return (adub*) acosh(*($self));
    }
    adub* atanh() {
        return (adub*) atanh(*($self));
    }
    adub* erf() {
        return (adub*) erf(*($self));
    }
#endif
    adub* fabs() {
        return (adub*) fabs(*($self));
    }
    adub* abs() {
        return (adub*) fabs(*($self));
    }
    adub* ceil() {
        return (adub*) ceil(*($self));
    }
    adub* floor() {
        return (adub*) floor(*($self));
    }

}

%pythoncode %{
def fmin(a,b):
    import numpy as np
    if np.isscalar(a) and np.isscalar(b):
        if a > b:
            return b
        else:
            return a
    elif isinstance(a,badouble) or isinstance(b,badouble):
        return _adolc.fmin(a,b)
    else:
	raise(NotImplementedError('Arguments must be scalars or ADOL-C types'))

def fmax(a,b):
    import numpy as np
    if np.isscalar(a) and np.isscalar(b):
        if a < b:
            return b
        else:
            return a
    elif isinstance(a,badouble) or isinstance(b,badouble):
        return _adolc.fmax(a,b)
    else:
	raise(NotImplementedError('Arguments must be scalars or ADOL-C types'))

def fabs(a):
    import numpy as np
    import math as m
    if np.isscalar(a):
        return m.fabs(a)
    elif isinstance(a,badouble):
        return _adolc.fabs(a)
    else:
	raise(NotImplementedError('Arguments must be scalars or ADOL-C types'))
%}

%exception;