/*
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __LIBM_TESTS_H__
#define __LIBM_TESTS_H__

#include <stdio.h>
#include <stdint.h>

#include <fenv.h>

/*
 * Use directly the FMA3 version or glibc version,
 * For proper execution following values needs to be generated by
 * build system
 */

#define PROTOTYPE_GLIBC    0xf1
#define PROTOTYPE_AOCL     0xf2
#define PROTOTYPE_TEST_V1  0xf8
#define PROTOTYPE_TEST_V2  0xf9
#define PROTOTYPE_SVML     0xf4

#if (LIBM_PROTOTYPE == PROTOTYPE_AOCL)
#pragma message "compiling for AOCL"
#define LIBM_FUNC(x) FN_PROTOTYPE(x)
#define LIBM_FUNC_VEC(prec, elem, fn) FN_PROTOTYPE(vr##prec##elem##_##fn)

#elif (LIBM_PROTOTYPE == PROTOTYPE_GLIBC)
#pragma message "compiling for GLIBC"
#define LIBM_FUNC(x)    x
#define LIBM_FUNC_VEC(prec, elem, fn) _ZGV##prec##N##elem##v_##fn

#elif (LIBM_PROTOTYPE == PROTOTYPE_SVML)
#pragma message "compiling for Intel SVML"
#define LIBM_FUNC(x) x
#define LIBM_FUNC_VEC(prec, elem, fn) __svml_##fn##elem

#else
#error "unknown LIBM_PROTOTYPE"
#endif

#endif  /* __LIBM_TESTS_H__ */

