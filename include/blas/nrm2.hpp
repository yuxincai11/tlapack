// Copyright (c) 2017-2021, University of Tennessee. All rights reserved.
// Copyright (c) 2021, University of Colorado Denver. All rights reserved.
//
// This file is part of T-LAPACK.
// T-LAPACK is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#ifndef BLAS_NRM2_HH
#define BLAS_NRM2_HH

#include "blas/utils.hpp"

namespace blas {

/**
 * @return 2-norm of vector,
 *     $|| x ||_2 = (\sum_{i=0}^{n-1} |x_i|^2)^{1/2}$.
 *
 * Generic implementation for arbitrary data types.
 * TODO: generic implementation does not currently scale to avoid over- or underflow.
 *
 * @param[in] n
 *     Number of elements in x. n >= 0.
 *
 * @param[in] x
 *     The n-element vector x, in an array of length (n-1)*incx + 1.
 *
 * @param[in] incx
 *     Stride between elements of x. incx > 0.
 *
 * @ingroup nrm2
 */
template< typename T >
real_type<T>
nrm2(
    blas::size_t n,
    T const * x, blas::int_t incx )
{
    typedef real_type<T> real_t;

    // check arguments
    blas_error_if( incx <= 0 );

    // todo: scale to avoid overflow & underflow
    real_t result = 0;
    if (incx == 1) {
        // unit stride
        for (size_t i = 0; i < n; ++i) {
            result += real(x[i]) * real(x[i]) + imag(x[i]) * imag(x[i]);
        }
    }
    else {
        // non-unit stride
        size_t ix = 0;
        for (size_t i = 0; i < n; ++i) {
            result += real(x[ix]) * real(x[ix]) + imag(x[ix]) * imag(x[ix]);
            ix += incx;
        }
    }
    return sqrt( result );
}

}  // namespace blas

#endif        //  #ifndef BLAS_NRM2_HH
