#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

#include <adolc/adolc.h>

#include "const.h"

BOOST_AUTO_TEST_SUITE( trace_vector )


/***********************************/
/* Tests for traceless scalar mode */
/* Author: Philipp Schuette        */
/***********************************/


/* Naming convention for test cases:  Operatorname_Operator_FOV_Forward for
 * foward derivative evulation in vector mode.
 *
 * For documentation of concrete test implementation, check traceless scalar
 * mode test implementation.  The testing order is consistent with that file
 * as well.
 */

BOOST_AUTO_TEST_CASE(ExpOperator_FOV_Forward)
{
  double a = 2., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = exp(ad);

  ad >>= aout;
  trace_off();

  a = std::exp(a);
  double aDerivative = a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 2.0;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 2., tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(MultOperator_FOV_Forward)
{
  double a = 2., b = 3.5, out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = ad * bd;

  ad >>= out;
  trace_off();

  double aDerivative = b;
  double bDerivative = a;
  a = a * b;

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 2.;
  x[1] = 3.5;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AddOperator_FOV_Forward)
{
  double a = 2.5, b = 3., out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = ad + bd;

  ad >>= out;
  trace_off();

  double aDerivative = 1.;
  double bDerivative = 1.;
  a = a + b;

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 2.5;
  x[1] = 3.;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SubOperator_FOV_Forward)
{
  double a = 1.5, b = 3.2, out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = ad - bd;

  ad >>= out;
  trace_off();

  double aDerivative = 1.;
  double bDerivative = -1.;
  a = a - b;

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 1.5;
  x[1] = 3.2;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(DivOperator_FOV_Forward)
{
  double a = 0.5, b = 4.5, out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = ad / bd;

  ad >>= out;
  trace_off();

  double aDerivative = 1. / b;
  double bDerivative = -a / (b*b);
  a = a / b;

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 0.5;
  x[1] = 4.5;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(TanOperator_FOV_Forward)
{
  double a = 0.7, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = tan(ad);

  ad >>= aout;
  trace_off();

  a = tan(a);
  double aDerivative = 1. + a*a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 0.7;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + std::pow(2, i);
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative * (1. + std::pow(2, 0)), tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + std::pow(2, 1)), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SinOperator_FOV_Forward)
{
  double a = 1.2, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = sin(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = std::cos(a);
  a = sin(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.2;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i * (-2.0);
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative , tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (-1.), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(CosOperator_FOV_Forward)
{
  double a = 1.2, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = cos(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = -std::sin(a);
  a = cos(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.2;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i * 2.;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 3., tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SqrtOperator_FOV_Forward)
{
  double a = 2.2, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = sqrt(ad);

  ad >>= aout;
  trace_off();

  a = std::sqrt(a);
  double aDerivative = 1. / (2.*a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 2.2;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. * std::pow(2, i);
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 2., tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(LogOperator_FOV_Forward)
{
  double a = 4.9, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = log(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / a;
  a = std::log(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 4.9;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i * 5.5;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 6.5, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SinhOperator_FOV_Forward)
{
  double a = 4., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = sinh(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = std::cosh(a);
  a = std::sinh(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 4.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - std::sqrt(2.*i);
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - std::sqrt(2.)), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(CoshOperator_FOV_Forward)
{
  double a = 4., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = cosh(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = std::sinh(a);
  a = std::cosh(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 4.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i * 3.2;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 4.2, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(TanhOperator_FOV_Forward)
{
  double a = 4., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = tanh(ad);

  ad >>= aout;
  trace_off();

  a = std::tanh(a);
  double aDerivative = 1. - a*a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 4.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - 1.3*i;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 1.3), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AsinOperator_FOV_Forward)
{
  double a = 0.9, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = asin(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (std::sqrt(1. - a*a));
  a = std::asin(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 0.9;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*(i + 1.7)*4.3;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 2.7*4.3), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AcosOperator_FOV_Forward)
{
  double a = 0.8, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = acos(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = -1. / (std::sqrt(1. - a*a));
  a = std::acos(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 0.8;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*(i + 0.7)*3.4;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 1.7*3.4), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AtanOperator_FOV_Forward)
{
  double a = 9.8, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = atan(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (1. + a*a);
  a = std::atan(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 9.8;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*(i - 0.3)*4.3;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 0.7*4.3), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(Log10Operator_FOV_Forward)
{
  double a = 12.3, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = log10(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (a * std::log(10));
  a = std::log10(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 12.3;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*9.9;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 9.9), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

#if defined(ATRIG_ERF)
BOOST_AUTO_TEST_CASE(AsinhOperator_FOV_Forward)
{
  double a = 0.6, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = asinh(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (std::sqrt(a*a + 1.));
  a = std::asinh(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 0.6;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*6.2;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 6.2), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AcoshOperator_FOV_Forward)
{
  double a = 1.7, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = acosh(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (std::sqrt(a*a - 1.));
  a = std::acosh(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.7;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*3.1;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 3.1), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(AtanhOperator_FOV_Forward)
{
  double a = 0.6, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = atanh(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1. / (1. - a*a);
  a = std::atanh(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 0.6;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*2.2;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 2.2), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}
#endif

BOOST_AUTO_TEST_CASE(InclOperator_FOV_Forward)
{
  double a = 5., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = ++ad;

  ad >>= aout;
  trace_off();

  double aDerivative = 1.;
  a = ++a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 5.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*4.2;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 4.2), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(DeclOperator_FOV_Forward)
{
  double a = 5., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = --ad;

  ad >>= aout;
  trace_off();

  double aDerivative = 1.;
  a = --a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 5.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*4.2;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 4.2), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SignPlusOperator_FOV_Forward)
{
  double a = 1.5, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = +ad;

  ad >>= aout;
  trace_off();

  double aDerivative = 1.;
  a = +a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.5;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*0.8;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 0.8), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(SignMinusOperator_FOV_Forward)
{
  double a = 1.5, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = -ad;

  ad >>= aout;
  trace_off();

  double aDerivative = -1.;
  a = -a;

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.5;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*0.8;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 0.8), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(Atan2Operator_FOV_Forward)
{
  double a = 12.3, b = 2.1, out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = atan2(ad, bd);

  ad >>= out;
  trace_off();

  double aDerivative = b / (a*a + b*b);
  double bDerivative = -a / (a*a + b*b);
  a = std::atan2(a, b);

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 12.3;
  x[1] = 2.1;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(PowOperator_FOV_Forward_1)
{
  double a = 2.3, e = 3.5, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = pow(ad, e);

  ad >>= aout;
  trace_off();

  double aDerivative = e * std::pow(a, e - 1.);
  a = std::pow(a, e);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 2.3;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*0.5;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. + 0.5), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(PowOperator_FOV_Forward_2)
{
  double a = 2.3, b = 3.5, out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = pow(ad, bd);

  ad >>= out;
  trace_off();

  double aDerivative = b * std::pow(a, b - 1.);
  double bDerivative = std::log(a) * std::pow(a, b);
  a = std::pow(a, b);

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 2.3;
  x[1] = 3.5;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(PowOperator_FOV_Forward_3)
{
  double a = 2.3, e = 3.5, eout;
  adouble ed;

  trace_on(1);
  ed <<= e;

  ed = pow(a, ed);

  ed >>= eout;
  trace_off();

  double eDerivative = std::log(a) * std::pow(a, e);
  a = std::pow(a, e);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 3.5;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i*0.5;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == eDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == eDerivative * (1. + 0.5), tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

/* Frexp operator is not differentiable and does not have to be tested. */

BOOST_AUTO_TEST_CASE(LdexpOperator_FOV_Forward_1)
{
  double a = 4., b = 3., out;
  adouble ad, bd;

  trace_on(1);
  ad <<= a;
  bd <<= b;

  ad = ad * pow(2., bd);

  ad >>= out;
  trace_off();

  double aDerivative = std::pow(2., b);
  double bDerivative = a * std::log(2.) * std::pow(2., b);
  a = a * std::pow(2., b);

  double *x = myalloc1(2);
  double **xd = myalloc2(2, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  /* Test partial derivative wrt a and b. */
  x[0] = 4.;
  x[1] = 3.;
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (i == j)
        xd[i][j] = 1.;
      else
        xd[i][j] = 0.;
    }
  }

  fov_forward(1, 1, 2, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == bDerivative, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(LdexpOperator_FOV_Forward_2)
{
  double a = 4., e = 3., aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = ldexp(ad, e);

  ad >>= aout;
  trace_off();

  double aDerivative = std::pow(2., e);
  a = std::ldexp(a, e);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 4.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * 2., tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(LdexpOperator_FOV_Forward_3)
{
  double a = 4., e = 3., eout;
  adouble ed;

  trace_on(1);
  ed <<= e;

  ed = a * pow(2., ed);

  ed >>= eout;
  trace_off();

  double eDerivative = a * std::log(2.) * std::pow(2., e);
  e = std::ldexp(a, e);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 3.;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. + i;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == e, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == eDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == eDerivative * 2., tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}

BOOST_AUTO_TEST_CASE(FabsOperator_FOV_Forward)
{
  double a = 1.4, aout;
  adouble ad;

  trace_on(1);
  ad <<= a;

  ad = fabs(ad);

  ad >>= aout;
  trace_off();

  double aDerivative = 1.;
  a = std::fabs(a);

  double *x = myalloc1(1);
  double **xd = myalloc2(1, 2);
  double *y = myalloc1(1);
  double **yd = myalloc2(1, 2);

  x[0] = 1.4;
  
  for (int i = 0; i < 2; i++) {
    xd[0][i] = 1. - i*1.5;
  }

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 1.5), tt::tolerance(tol));

  x[0] = -5.;

  a = std::fabs(-5.);
  aDerivative = -1.;

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == a, tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == aDerivative, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == aDerivative * (1. - 1.5), tt::tolerance(tol));

  x[0] = 0.;
  
  xd[0][0] = 2.5;
  xd[0][1] = -3.5;

  fov_forward(1, 1, 1, 2, x, xd, y, yd);

  BOOST_TEST(*y == 0., tt::tolerance(tol));
  BOOST_TEST(yd[0][0] == 2.5, tt::tolerance(tol));
  BOOST_TEST(yd[0][1] == 3.5, tt::tolerance(tol));

  myfree1(x);
  myfree2(xd);
  myfree1(y);
  myfree2(yd);
}




BOOST_AUTO_TEST_SUITE_END()

