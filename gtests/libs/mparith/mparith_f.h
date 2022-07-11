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


#ifndef MPARITH_F_H_INCLUDED
#define MPARITH_F_H_INCLUDED 1

#include "precision.h"

extern void mpinit(int *base, int *mantis, int *emin, int *emax, int *round, int *n, int *params, int *ifail);
extern int chksum(int *params);
extern void mpinitcopy(int *params_in, int *mantis, int *emin, int *emax, int *n_out, int *params_out, int *ifail);
extern int get_base(int *params);
extern int get_mantis(int *params);
extern int get_emin(int *params);
extern int get_emax(int *params);
extern int get_sign(int *params);
extern int get_iexo(int *params);
extern int get_wplaces(int *params);
extern int get_fptype(int *params);
extern int get_radix(int *params);
extern int get_radigs(int *params);
extern int get_places(int *params);
extern int get_last(int *params);
extern int get_round(int *params);
extern int get_verbos(int *params);
extern int get_mplen(int *params);
extern void mptod(int *xmp, int *n, int *params, REAL *x, int *ifail);
extern void dtomp(REAL *x, int *xmp, int *n, int *params, int *ifail);
extern void itomp(int *k, int *xmp, int *n, int *params, int *ifail);
extern void mpshow(const char *title, int *xmp, int *n, int *params);
extern int mpisreg(int *xmp, int *n, int *params);
extern int mpisfake(int *xmp, int *n, int *params);
extern int mpiszero(int *xmp, int *n, int *params);
extern int mpisinfinity(int *xmp, int *n, int *params);
extern int mpisnan(int *xmp, int *n, int *params);
extern int mpispos(int *xmp, int *n, int *params);
extern int mpisneg(int *xmp, int *n, int *params);
extern int regcon(void);
extern int zercon(void);
extern int infcon(void);
extern int qnancon(void);
extern int snancon(void);
extern int poscon(void);
extern int negcon(void);
extern void assign(int *x, int *y, int *n, int *params);
extern void mpcopy(int *source, int *dest, int *n, int *params, int *ifail);
extern void mpcopy2(int *source, int *n_source, int *params_source, int *dest, int *n_dest, int *params_dest, int *ifail);
extern int mpeq(int *left, int *right, int *n, int *params);
extern int mplt(int *left, int *right, int *n, int *params);
extern int mpgt(int *left, int *right, int *n, int *params);
extern int mpge(int *left, int *right, int *n, int *params);
extern int mple(int *left, int *right, int *n, int *params);
extern int mpne(int *left, int *right, int *n, int *params);
extern void next(int *x, int *n, int *params, int *up);
extern void fix(int *result, int *n, int *params, int *iround, int *iamrnd, int *sticky);
extern void ieee(int *result, int *n, int *params, int *iround, int *iamrnd, int *sticky);
extern void chop(int *result, int *n, int *params, int *iround);
extern void tomsin(int *result, int *n, int *params, int *iround);
extern void toplin(int *result, int *n, int *params, int *iround);
extern void mproundl(int *x, int *n, int *params, int *iround);
extern void mproundu(int *x, int *n, int *params, int *iround);
extern void mpfloor(int *xmp, int *ymp, int *n, int *params, int *iwork, int *ifail);
extern void mpceil(int *xmp, int *ymp, int *n, int *params, int *iwork, int *ifail);
extern void mptrunc(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mprint(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mpround(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mpfrac(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mpfrexp(int *xmp, int *ymp, int *iymp, int *n, int *params, int *ifail);
extern void mpldexp(int *xmp, int expn, int *ymp, int *n, int *params, int *ifail);
extern void mpmodf(int *xmp, int *ymp, int *iymp, int *n, int *params, int *ifail);
extern int mpmod(int *xmp, int *n, int *params, int *k, int *iwork, int *ifail);
extern int mpmod4(int *xmp, int *n, int *params, int *ifail);
extern int isanint(int *xmp, int *n, int *params, int *ifail);
extern int mpilogb(int *xmp, int *emin_x, int *n, int *params, int *ifail);
extern void mplogb(int *xmp, int *emin_x, int *ymp, int *n, int *params, int *ifail);
extern int mpfinite(int *xmp, int *n, int *params, int *ifail);
extern void plus(int *left, int *right, int *result, int *n, int *params, int *ifail);
extern void minus(int *left, int *right, int *result, int *n, int *params, int *ifail);
extern void times(int *left, int *right, int *result, int *n, int *params, int *ifail);
extern void times2(int *left, int *n_left, int *params_left, int *right, int *n_right, int *params_right, int *result, int *n_result, int *params_result, int *ifail);
extern void divide(int *left, int *right, int *result, int *n, int *params, int *iwork, int *ifail);
extern void divide2(int *left, int *n_left, int *params_left, int *right, int *n_right, int *params_right, int *result, int *n_result, int *params_result, int *iwork, int *ifail);
extern void mpiroot(int *right, int *result, int *n, int *params, int *iwork, int *ifail);
extern void mproot(int *right, int *result, int *n, int *params, int *iwork, int *ifail);
extern void mphypot(int *xmp, int *ymp, int *result, int *n, int *params, int *iwork, int *ifail);
extern void mpfma(int *xmp, int *ymp, int *zmp, int *result, int *n, int *params, int *iwork, int *ifail);
extern void mpipow(int *k, int *x, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mppow(int *xmp, int *ymp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpfmod(int *xmp, int *ymp, int *n, int *params, int *result, int *ifail);
extern void mpfabs(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mpremainder(int *xmp, int *ymp, int *n, int *params, int *result, int *ifail);
extern void mpremquo(int *xmp, int *ymp, int *qmp, int *n, int *params, int *result, int *ifail);
extern void mpfmin(int *xmp, int *ymp, int *n, int *params, int *result, int *ifail);
extern void mpfmax(int *xmp, int *ymp, int *n, int *params, int *result, int *ifail);
extern void mpfdim(int *xmp, int *ymp, int *n, int *params, int *result, int *ifail);
extern void mpfract(int *xmp, int *n, int *params, int *ymp, int *iymp, int *ifail);
extern char itoc(int *i);
extern char *itoc10(int *i, int *width);
extern int mptoi(int *xmp, int *n, int *params, int *ifail);
extern void mp2dec(int *xmp, int *n, int *params, int *digits, int *iwork, int *ifail, char *c, int c_len);
extern void lowadd(int *left, int *right, int *n, int *params, int *result, int *iround, int *iamrnd, int *sticky);
extern void lowsub(int *left, int *right, int *n, int *params, int *result, int *iround, int *iamrnd, int *sticky, int *nought);
extern void lowmul(int *left, int *right, int *n, int *params, int *result, int *iround, int *iamrnd, int *sticky);
extern void lowmul2(int *left, int *n_left, int *params_left, int *right, int *n_right, int *params_right, int *result, int *n_result, int *params_result, int *iround, int *iamrnd, int *sticky);
extern void lowdiv(int *left, int *right, int *n, int *params, int *result, int *iround, int *iamrnd, int *sticky, int *denom, int *divi);
extern void lowdiv2(int *left, int *n_left, int *params_left, int *right, int *n_right, int *params_right, int *result, int *n_result, int *params_result, int *iround, int *iamrnd, int *sticky, int *denom, int *divi);
extern void lowroo(int *x, int *n, int *params, int *result, int *iround, int *iamrnd, int *sticky, int *d, int *u);
extern void mpnegate(int *xmp, int *n, int *params, int *ifail);
extern void mpchgsign(int *xmp, int *ymp, int *n, int *params, int *ifail);
extern void mpcopysign(int *xmp, int *ymp, int *result, int *n, int *params, int *ifail);
extern void mpabs(int *xmp, int *n, int *params, int *ifail);
extern void mpsin_kernel(int *xmp, int *n, int *params, int *result, int *iwork);
extern void mpremainder_piby2(int *xmp, int *n, int *params,
                              int *pi_over_two, int *two_over_pi, int *n_pi,
                              int *params_pi, int *result, int *region,
                              int *iwork, int *ifail);
extern void mpremainder_90d(int *xmp, int *n, int *params,
                            int *pi_over_two, int *n_pi,
                            int *params_pi, int *result, int *region,
                            int *iwork, int *ifail);
extern void mpsincostan(int *xmp, int *n, int *params, int *pi_over_two, int *two_over_pi, int *n_pi, int *params_pi, int *result_sin, int *result_cos, int *result_tan, int *iwork, int *ifail);
extern void mpsincostand(int *xmp, int *n, int *params, int *pi_over_two, int *two_over_pi, int *n_pi, int *params_pi, int *result_sin, int *result_cos, int *result_tan, int *iwork, int *ifail);
extern void mpcos_kernel(int *xmp, int *n, int *params, int *result, int *iwork);
extern void mpatan_kernel(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpatan(int *xmp, int *n, int *params, int *result, int *pi_over_two, int *n_pi, int *params_pi, int *iwork, int *ifail);
extern void mpatan2(int *ymp, int *xmp, int *n, int *params, int *result, int *pi, int *pi_over_two, int *n_pi, int *params_pi, int *iwork, int *ifail);
extern void mpasin_kernel(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpacos_kernel(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpasin(int *xmp, int *n, int *params, int *result, int *pi_over_two, int *n_pi, int *params_pi, int *iwork, int *ifail);
extern void mpacos(int *xmp, int *n, int *params, int *result, int *pi_over_two, int *n_pi, int *params_pi, int *iwork, int *ifail);
extern void mpsinh(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpcosh(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mptanh(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpasinh(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpacosh(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpatanh(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mplog_kernel(int *xmp, int *n, int *params, int *result, int *iwork);
extern void mplog_kernel2(int *xmp, int *n, int *params, int *result, int *iwork);
extern void mplog(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mplog1p(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mplog10(int *xmp, int *logbase, int *log10e, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mplog2(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void epsilon(int *n, int *params, int *eps);
extern void mplarge(int *n, int *params, int *large);
extern void mpsmall(int *n, int *params, int *small);
extern void get_pi(int *n, int *params, int *pi, int *iwork);
extern void get_pi_etc(int *n, int *params, int *pi, int *two_pi, int *pi_over_two, int *two_over_pi, int *iwork, int *ifail);
extern void get_precomputed_pi_etc(int *n, int *params, int *pi, int *two_pi, int *pi_over_two, int *two_over_pi, int *ifail);
extern void get_log_etc(int *n, int *params, int *logbase, int *log10e, int *iwork, int *ifail);
extern void get_precomputed_log_etc(int *n, int *params, int *logbase, int *log10e, int *ifail);
extern void get_e(int *n, int *params, int *e, int *iwork);
extern void exp_kernel(int *x, int *n, int *params, int *result, int *iwork);
extern void mpexp(int *xmp, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpexp2(int *xmp, int *logbase, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpexp10(int *xmp, int *log10e, int *n, int *params, int *result, int *iwork, int *ifail);
extern void mpsinh_kernel(int *x, int *n, int *params, int *result, int *iwork);
extern void mpcosh_kernel(int *x, int *n, int *params, int *result, int *iwork);
extern void mpreldiff(REAL *x, int *base_x, int *mantis_x, int *emin_x, int *emax_x, int *xmp, int *n, int *params, REAL *r, REAL *ulps, int *iwork, int *ifail);
extern int ipower(int *i, int k);
extern int myimax(int i, int j);
extern int myimin(int i, int j);
extern int myiabs(int i);
extern REAL myfabs(REAL f);
extern int p01abf(int *ifail, int *ierr, const char *srname, int *nrec, const char *rec);
extern int x02bhf(void);
extern int x02bjf(void);
extern int x02bkf(void);
extern int x02blf(void);
extern int x02baf(void);
#if 0
void createzero(int *sign, REAL *r);
void createlargest(int *sign, int *mantis, int *emax, REAL *r);
void createinfinity(int *sign, REAL *r);
void createnan(int *sign, int *signalling, REAL *r);
int diszero(REAL *x);
int dispos(REAL *x);
int disneg(REAL *x);
int disinf(REAL *x);
int disnan(REAL *x);
#endif

#endif
