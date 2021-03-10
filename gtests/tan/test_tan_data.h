#ifndef __TEST_TAN_DATA_H__
#define __TEST_TAN_DATA_H__
/*
 * Copyright (C) 2019-2020 Advanced Micro Devices, Inc. All rights reserved
 */

#include <fenv.h>
#include "almstruct.h"
#include <libm_util_amd.h>

/*
 * Test cases to check for exceptions for the tanf() routine.
 * These test cases are not exhaustive
 */
static libm_test_special_data_f32
test_tanf_conformance_data[] = {
    /*special values*/
    {POS_SNAN_F32, POS_SNAN_F32, FE_INVALID,},
    {NEG_SNAN_F32, NEG_SNAN_F32, FE_INVALID,},
    {POS_INF_F32,  POS_QNAN_F32, FE_INVALID,},
    {NEG_INF_F32,  POS_QNAN_F32, FE_INVALID,},
    {POS_QNAN_F32, POS_QNAN_F32, 0,},
    {NEG_QNAN_F32, NEG_QNAN_F32, 0,},
    {POS_ZERO_F32, POS_ZERO_F32, 0,},
    {NEG_ZERO_F32, NEG_ZERO_F32, 0,},

    {0x00000039, 0x00000039, FE_UNDERFLOW},  // min_float*180/pi
    {0x387BA882, 0x387BA882, FE_UNDERFLOW},  // 6e-05, < 2^(-13)
    {0x3F490FDB, POS_ONE_F32, 0},            //tan(45)=1
    {0xbf490fdb, NEG_ONE_F32, 0},            //tan(-45) = -tan(45) = -1
    {0x3fc90fdb, POS_INF_F32, FE_INVALID},            //tan(90)=+INF
    {0xbfc90fdb, NEG_INF_F32, FE_INVALID},            //tan(-Pi/2) = -INF
    {0x3C000001, 0x3c0000ac, 0},
    {0x39000001, 0x39000001, 0},
    {POS_ONE_F32, 0x3fc75923, 0},  //1
    {NEG_ONE_F32, 0xbfc75923, 0}, //-1
    {0x40000000, 0xc00bd7b1, 0},  //2
    {POS_PI_F32, 0x33bbbd2e, 0},  //pi
    {NEG_PI_F32, 0xb3bbbd2e, 0},  //tan(-pi)=-tan(pi)
    {0x40C90FDB, 0x343bbd2e, 0},  //2pi
    {0x41200000, 0x3f25fafa, 0},  //10
    {0x447A0000, 0x3fbc3395, 0},  //1000
    {0xC8C35000, 0x3e137717, 0},  //-4e5
    {0x48F42400, 0xbe390c74, 0},  //500000
    {0x48F4CCC8, 0xbf876fff, 0},  //501350.25 > 5.0e5
    {0xC93F6800, 0x3e1fa759, 0},  //-784000
    {0x43FCE5F1, 0x320fd1de, 0},  //505.796417, remainder is ~0, very close multiple of piby2
    {0x4831E550, 0xb79a62a2, 0},  //182165.25, remainder is ~piby4
    {0x42FCE5F1, 0x3f800000, 0},  //126.449104
    //Special case for verified the ulps
    {0x5123e87f, 0x318a4ed8, 0},  //4.399877E+10, close to pi/2
    {0x50a3e87f, 0xcdeceba8, 0},  //2.19993846E+10, close to pi/2, ported from OpenCL
    //newly added
    {0x3ec90fdb, 0x3ed413cd, 0}, 	// 0: tanf(0.392699092627)=	0.414213575176
    {0x3f490fdb, 0x3f800000, 0}, 	// 1: tanf(0.785398185253)=	1.000000043711
    {0x3f96cbe4, 0x401a827a, 0}, 	// 2: tanf(1.178097248077)=	2.414213582730
    {0x3fc90fdb, 0xcbae8a4a, 0}, 	// 3: tanf(1.570796370506)=	-22877332.428855401000
    {0x3ffb53d1, 0xc01a827b, 0}, 	// 4: tanf(1.963495373726)=	-2.414213799782
    {0x4016cbe4, 0xbf800000, 0}, 	// 5: tanf(2.356194496155)=	-0.999999988075
    {0x402feddf, 0xbed413d0, 0}, 	// 6: tanf(2.748893499374)=	-0.414213647332
    {0x40490fdb, 0x33bbbd2e, 0}, 	// 7: tanf(3.141592741013)=	0.000000087423
    {0x406231d6, 0x3ed413cd, 0}, 	// 8: tanf(3.534291744232)=	0.414213572851
    {0x407b53d1, 0x3f7ffffe, 0}, 	// 9: tanf(3.926990747452)=	0.999999860929
    {0x408a3ae6, 0x401a8275, 0}, 	// 10: tanf(4.319689750671)=	2.414212551667
    {0x4096cde4, 0xcc9ff26d, 0}, 	// 11: tanf(4.712388992310)=	-83858283.006641403000
    {0x40a35ce2, 0xc01a8275, 0}, 	// 12: tanf(5.105088233948)=	-2.414212388810
    {0x40afeddf, 0xbf800002, 0}, 	// 13: tanf(5.497786998749)=	-1.000000290067
    {0x40bc7edd, 0xbed413cc, 0}, 	// 14: tanf(5.890486240387)=	-0.414213544910
    {0x40c90fdb, 0x343bbd2e, 0}, 	// 15: tanf(6.283185482025)=	0.000000174846
    {0xbec90fdb, 0xbed413cd, 0}, 	// 16: tanf(-0.392699092627)=	-0.414213575176
    {0xbf490fdb, 0xbf800000, 0}, 	// 17: tanf(-0.785398185253)=	-1.000000043711
    {0xbf96cbe4, 0xc01a827a, 0}, 	// 18: tanf(-1.178097248077)=	-2.414213582730
    {0xbfc90fdb, 0x4bae8a4a, 0}, 	// 19: tanf(-1.570796370506)=	22877332.428855401000
    {0xbffb53d1, 0x401a827b, 0}, 	// 20: tanf(-1.963495373726)=	2.414213799782
    {0xc016cbe4, 0x3f800000, 0}, 	// 21: tanf(-2.356194496155)=	0.999999988075
    {0xc02feddf, 0x3ed413d0, 0}, 	// 22: tanf(-2.748893499374)=	0.414213647332
    {0xc0490fdb, 0xb3bbbd2e, 0}, 	// 23: tanf(-3.141592741013)=	-0.000000087423
    {0xc06231d6, 0xbed413cd, 0}, 	// 24: tanf(-3.534291744232)=	-0.414213572851
    {0xc07b53d1, 0xbf7ffffe, 0}, 	// 25: tanf(-3.926990747452)=	-0.999999860929
    {0xc08a3ae6, 0xc01a8275, 0}, 	// 26: tanf(-4.319689750671)=	-2.414212551667
    {0xc096cbe4, 0x4c9ff26d, 0}, 	// 27: tanf(-4.712388992310)=	83858283.006641403000
    {0xc0a35ce2, 0x401a8275, 0}, 	// 28: tanf(-5.105088233948)=	2.414212388810
    {0xc0afeddf, 0x3f800002, 0}, 	// 29: tanf(-5.497786998749)=	1.000000290067
    {0xc0bc7edd, 0x3ed413cc, 0}, 	// 30: tanf(-5.890486240387)=	0.414213544910
    {0xc0c90fdb, 0xb43bbd2e, 0}, 	// 31: tanf(-6.283185482025)=	-0.000000174846
    {0x0b8cbda0, 0x0b8cbda0, 0}, 	// 32: tanf(0.000000000000)=	0.000000000000
    {0x40f62aef, 0x40c4bcf7, 0}, 	// 33: tanf(7.692740917206)=	6.148067141030
    {0x4106f545, 0xbfc2fcb5, 0}, 	// 34: tanf(8.434880256653)=	-1.523337008903
    {0x00000000, 0x00000000, 0}, 	// 35: tanf(0.000000000000)=	0.000000000000
    {0x401c2c6b, 0xbf583b2c, 0}, 	// 36: tanf(2.440211057663)=	-0.844652902331
    {0x3db61bad, 0x3db696f0, 0}, 	// 37: tanf(0.088919974864)=	0.089155074801
    {0xbf81cb73, 0xbfcda23b, 0}, 	// 38: tanf(-1.014021277428)=	-1.606513405596
    {0x80000000, 0x80000000, 0}, 	// 39: tanf(0.000000000000)=	0.000000000000
    {0x40e279d0, 0x3f8244ef, 0}, 	// 40: tanf(7.077369689941)=	1.017728662856
    {0xbf577d83, 0xbf8f4eab, 0}, 	// 41: tanf(-0.841758906841)=	-1.119588220024
    {0x3dc786fd, 0x3dc82937, 0}, 	// 42: tanf(0.097425438464)=	0.097734858153
    {0x80000000, 0x80000000, 0}, 	// 43: tanf(0.000000000000)=	0.000000000000
    {0xc09ee16f, 0x4077ec32, 0}, 	// 44: tanf(-4.965018749237)=	3.873791284822
    {0xbfb4d215, 0xc0c8ab42, 0}, 	// 45: tanf(-1.412661194801)=	-6.270905678201
    {0xc049602a, 0xbba09f10, 0}, 	// 46: tanf(-3.146494388580)=	-0.004901774249
    {0x00000000, 0x00000000, 0}, 	// 47: tanf(0.000000000000)=	0.000000000000
    {0x40d59df3, 0x3ed3dd87, 0}, 	// 48: tanf(6.675530910492)=	0.413799497292
    {0x00000000, 0x00000000, 0}, 	// 49: tanf(0.000000000000)=	0.000000000000
    {0x00000000, 0x00000000, 0}, 	// 50: tanf(0.000000000000)=	0.000000000000
    {0x00000000, 0x00000000, 0}, 	// 51: tanf(0.000000000000)=	0.000000000000
};

static libm_test_special_data_f64
test_tan_conformance_data[] = {
    /*special values*/
    {POS_ZERO_F64, POS_ZERO_F64, 0}, //tan(0)=0
    {NEG_ZERO_F64, NEG_ZERO_F64, 0}, //tan(-0)=-0
    {POS_SNAN_F64, POS_SNAN_F64, FE_INVALID}, //positive snan
    {NEG_SNAN_F64, NEG_SNAN_F64, FE_INVALID},
    {POS_QNAN_F64, POS_QNAN_F64, 0},
    {NEG_QNAN_F64, NEG_QNAN_F64, 0},
    {POS_INF_F64,  POS_QNAN_F64, FE_INVALID},
    {NEG_INF_F64,  NEG_QNAN_F64, FE_INVALID},

    {0x3ff921fb55206ddf, POS_INF_F64, FE_INVALID}, //tan(pi/2)= +inf
    {0xbff921fb55206ddf, NEG_INF_F64, FE_INVALID}, //tan(-90)=-tan(90)=-INF
    {0x3fe921fb544486e0, POS_ONE_F64, 0},          //tan(45)
    {0xbfe921fb544486e0, NEG_ONE_F64, 0},          //tan(-45)=-1
    {POS_PI_F64,         POS_ZERO_F64, 0},         //tan(pi)=0
    {NEG_PI_F64,         NEG_ZERO_F64, 0},         //tan(-pi)=-0

    {0x000000000000023D, 0x000000000000023D, FE_UNDERFLOW},
    {0x4f6344a970d9ac13, 0x3fe9b03b3afff843, 0},
    {0x723743730464dbf1, 0xbff69b688e1dbfa6, 0},
    {0x3FF10CA44655D48A, 0x3ffcedb5c800bd1d, 0},  // 1.0655863521072058
    {0x400f6a7a2955385e, 0x3feffffffffffffd, 0},
    {0x3FF921FB54442D18, 0x434d02967c31cdb5, 0},
    {0x3FF921FB54442D19, 0xc33617a15494767a, 0},
    {0x3FF921FB54442D17, 0x4329153d9443ed0b, 0},
    {0x3FF921FB54442D1a, 0xc3228f1859543aff, 0},

    {0x000000000000023DLL, 0x000000000000023DLL, FE_UNDERFLOW},
    {0x3e38000000000000LL, 0x3E38000000000000LL, FE_UNDERFLOW},  // 5.5879354476928711E-09 = 2^-28*1.5
    {0xbe38000000000000LL, 0xBE38000000000000LL, FE_UNDERFLOW},  // -5.5879354476928711E-09 = -2^-28*1.5
    {0x3fe921fb54442d18LL, 0x3fefffffffffffffLL, 0},
    {0x3f20000000000001LL, 0x3f20000001555556LL, 0},
    {0x3e40000000000001LL, 0x3e40000000000001LL, 0},
    {0x3FE9E0C8F112AB1ELL, 0x3ff0c363afc40f97LL, 0},  // 0.80868956646495227
    {0x40306B51F0157E66LL, 0x3feb932a53046455LL, 0},  // 16.41921902203321
    {0x402DDF5ADB92C01ALL, 0xbfef22f55ab78c87LL, 0},  // 14.93624006430041
    {0x402DDB778A9EBD8ALL, 0xbfef9cf70c111d67LL, 0},  // 14.928646404149521
    {0x401c462b9064a63bLL, 0x3fefff0d1d19082eLL, 0},  // 7.0685255586081963
    {0x3FE921FB54442D19LL, 0x3ff0000000000001LL, 0},  // 0.78539816339744839
    {0x3fe921fb54442d20LL, 0x3ff0000000000008LL, 0},  // 0.78539816339744917
    {0x3FF10CA44655D48ALL, 0x3ffcedb5c800bd1dLL, 0},  // 1.0655863521072058
    {0x400923E979F8B36ALL, 0x3f4ee25be1d30045LL, 0},  // 3.1425351647398445
    {0x4002DAE59BB5C33ELL, 0xbfeff4b918d4b96aLL, 0},  // 2.3568832554668964
    {0x4015FDCA5F9A0E38LL, 0xbfefff18a55dee76LL, 0},  // 5.4978423059251824
    {0x40b93bda357daddaLL, 0x3fed1849c8c910c6LL, 0},  // 6459.8523787068789
    {0x40F63525129291FFLL, 0x3fe7fdf796804ff9LL, 0},  // 90962.317034311578
    {0x3FF9207824B27C17LL, 0x40a52865814afd94LL, 0},  // 1.5704270776257141
    {0x4025fe9b31eb183dLL, 0xc08258311cfd7912LL, 0},  // 10.997277793834764
    {0x4046C6CBC45DC8DELL, 0xc3b66b9ebc4850c6LL, 0},  // 45.553093477052
    {0x3FF0000000000000LL, 0x3ff8eb245cbee3a6LL, 0},  // 1
    {0x4000000000000000LL, 0xc0017af62e0950f8LL, 0},  // 2
    {0x4008000000000000LL, 0xbfc23ef71254b86fLL, 0},  // 3
    {0x4024000000000000LL, 0x3fe4bf5f34be3782LL, 0},  // 10
    {0xc000000000000000LL, 0x40017af62e0950f8LL, 0},  // - 2
    {0x4012D97C7F3321D2LL, 0x4333570efd768923LL, 0},  // 4.71238898038469 = 3pi/2
    {0x402921fb54442d18LL, 0xbcc1a62633145c07LL, 0},  // 12.566370614359172 = 4pi
    {0x410921fb54442d18LL, 0xbda1a62633145c07LL, 0},  // 205887.41614566068 =  (2^16)pi
    {0x403921fb54442d18LL, 0xbcd1a62633145c07LL, 0},  // 25.132741228718345 = 8pi
    {0x403921fb54442d19LL, 0x3ce72cece675d1fdLL, 0},  // 25.132741228718348 close to 8pi
    {0x3ff921fb57442d18LL, 0xc1955555574b5994LL, 0},  // 1.5707963379707675 close to pi/2
    {0x400921fb52442d18LL, 0xbe5000000234c4c7LL, 0},  // 3.1415926386886319 close to pi
    {0x410921fb56442d18LL, 0x3f5000005320928eLL, 0},  // 205887.41712222318 close to (2^16)p
    {0xbff921fb57442d18LL, 0x41955555574b5994LL, 0},  //-1.5707963379707675 close to - pi/2
    {0x400921f554442d18LL, 0xbee8000000059a62LL, 0},  // 3.1415812094979962 close to pi
    {0xc00921f554442d18LL, 0x3ee8000000059a62LL, 0},  //-3.1415812094979962 close to -pi
    {0xbff921f557442d18LL, 0xc105600557ff5a82LL, 0},  //-1.570790615924869 close to -pi/2
    {0xbff9217557442d18LL, 0xc0be91e0ddf1c46eLL, 0},  //-1.570668545612369 close to -pi/2
    {0x400921fb56442d18LL, 0x3e4ffffffb967674LL, 0},  // 3.1415926684909543 close to pi
    {0x4012D98C7F3321D2LL, 0xc0cfffffff55bf3aLL, 0},  // 4.71245001554094 close to 3pi/2
    //reported cases
    {0x412e848abcdef000LL, 0xc009f5aedd6b6edbLL, 0}, //1000005.3688883781
    {0x439332270327f466LL, 0xc05622b8ed7db581LL, 0}, //3.4580273251621926E+17
    {0x411fa317083ee0a2LL, 0x3ff6eb80ed54d249LL, 0}, //518341.75805235852
    {0x64ca7f352f2afdaeLL, 0x3ff456dcc676e139LL, 0}, //3.3553869926485123E+177
    {0xd3d196202a791d3dLL, 0xc044a2abb21cf8bbLL, 0}, //-5.8694348256855645E+95
    {0x56fdb2fb3712813bLL, 0x4020eed0bfaadeedLL, 0}, //1.1159953350264303E+111
    {0x54e57b4e03dbe9b3LL, 0xc0009db1f2055098LL, 0}, //9.397154915883978E+100
    {0xea96be922b1706c5LL, 0xbfd9103e3f1cf2abLL, 0}, //-2.8524095750052955E+205
    {0x655e883346944823LL, 0xbfe976a695ee9826LL, 0}, //1.9795803721016825E+180
    // Newly added
    {0x3cb0000000000000LL, 0x3cb0000000000000LL, 0}, // tan(2.22045e-016 = fullprec)= 2.220446e-016
    {0x404019c501fbace3LL, 0x3fefffffffffffb9LL, 0}, // MM tan(32.2013=41pi/4)=1.000000e+000
    {0x4059543f4aecb572LL, 0x3fefffffffffff88LL, 0}, // MM tan(101.316=129pi/4)=1.000000e+000
    {0xc04019c501fbace3LL, 0xbfefffffffffffb9LL, 0}, // MM tan(-32.2013=-41pi/4)=-1.000000e+000
    {0xc059543f4aecb572LL, 0xbfefffffffffff88LL, 0}, // MM tan(-101.316=-129pi/4)=-1.000000e+000
    {0x3fd921fb54442d18LL, 0x3fda827999fcef32LL, 0}, 	// 0: tan(3.926990816987e-001)=	4.142135623731e-001
    {0x3fe921fb54442d18LL, 0x3fefffffffffffffLL, 0}, 	// 1: tan(7.853981633974e-001)=	1.000000000000e+000
    {0x3ff2d97c7f3321d2LL, 0x4003504f333f9de6LL, 0}, 	// 2: tan(1.178097245096e+000)=	2.414213562373e+000
    {0x3fff6a7a2955385eLL, 0xc003504f333f9d37LL, 0}, 	// 4: tan(1.963495408494e+000)=	-2.414213562373e+000
    {0x4002d97c7f3321d2LL, 0xbff0000000000001LL, 0}, 	// 5: tan(2.356194490192e+000)=	-1.000000000000e+000
    {0x4005fdbbe9bba775LL, 0xbfda827999fcef35LL, 0}, 	// 6: tan(2.748893571891e+000)=	-4.142135623731e-001
    {0x400c463abeccb2bbLL, 0x3fda827999fcef2fLL, 0}, 	// 8: tan(3.534291735289e+000)=	4.142135623731e-001
    {0x400f6a7a2955385eLL, 0x3feffffffffffffdLL, 0}, 	// 9: tan(3.926990816987e+000)=	1.000000000000e+000
    {0x4011475cc9eedf00LL, 0x4003504f333f9dddLL, 0}, 	// 10: tan(4.319689898686e+000)=	2.414213562373e+000
    {0x40146b9c347764a4LL, 0xc003504f333f9de3LL, 0}, 	// 12: tan(5.105088062083e+000)=	-2.414213562373e+000
    {0x4015fdbbe9bba775LL, 0xbff0000000000002LL, 0}, 	// 13: tan(5.497787143782e+000)=	-1.000000000000e+000
    {0x40178fdb9effea46LL, 0xbfda827999fcef40LL, 0}, 	// 14: tan(5.890486225481e+000)=	-4.142135623731e-001
    {0xbfd921fb54442d18LL, 0xbfda827999fcef32LL, 0}, 	// 16: tan(-3.926990816987e-001)=	-4.142135623731e-001
    {0xbfe921fb54442d18LL, 0xbfefffffffffffffLL, 0}, 	// 17: tan(-7.853981633974e-001)=	-1.000000000000e+000
    {0xbff2d97c7f3321d2LL, 0xc003504f333f9de6LL, 0}, 	// 18: tan(-1.178097245096e+000)=	-2.414213562373e+000
    {0xbfff6a7a2955385eLL, 0x4003504f333f9de7LL, 0}, 	// 20: tan(-1.963495408494e+000)=	2.414213562373e+000
    {0xc002d97c7f3321d2LL, 0x3ff0000000000001LL, 0}, 	// 21: tan(-2.356194490192e+000)=	1.000000000000e+000
    {0xc005fdbbe9bba775LL, 0x3fda827999fcef35LL, 0}, 	// 22: tan(-2.748893571891e+000)=	4.142135623731e-001
    {0xc00c463abeccb2bbLL, 0xbfda817999fcef2fLL, 0}, 	// 24: tan(-3.534291735289e+000)=	-4.142135623731e-001
    {0xc00f6a7a2955385eLL, 0xbfeffffffffffffdLL, 0}, 	// 25: tan(-3.926990816987e+000)=	-1.000000000000e+000
    {0xc011475cc9eedf00LL, 0xc003504f333f9dddLL, 0}, 	// 26: tan(-4.319689898686e+000)=	-2.414213562373e+000
    {0xc0146d9c347764a4LL, 0x4003504f333f9de3LL, 0}, 	// 28: tan(-5.105088062083e+000)=	2.414213562373e+000
    {0xc015fdbbe9bba775LL, 0x3ff0000000000002LL, 0}, 	// 29: tan(-5.497787143782e+000)=	1.000000000000e+000
    {0xc0178fdb9effea46LL, 0x3fda827999fcef40LL, 0}, 	// 30: tan(-5.890486225481e+000)=	4.142135623731e-001
    {0x397197b40472308cLL, 0x397197b40472308cLL, 0}, 	// 32: tan(5.421135524829e-032)=	5.421135524829e-032
    {0x401ec55de065a64dLL, 0x4018979ef90937d8LL, 0}, 	// 33: tan(7.692740923123e+000)=	6.148067370594e+000
    {0x4020dea89ec32930LL, 0xbff85f96c1810b3cLL, 0}, 	// 34: tan(8.434880219768e+000)=	-1.523337131381e+000
    {0x25d92c6ec03b4c10LL, 0x25d92c6ec03b4c10LL, 0}, 	// 35: tan(2.324269866831e-126)=	2.324269866831e-126
    {0x4003858d59bdcbcaLL, 0xbfeb0765b0e4a087LL, 0}, 	// 36: tan(2.440211011033e+000)=	-8.446529822295e-001
    {0x3fb6c375af11c9edLL, 0x3fb6d2de01baecacLL, 0}, 	// 37: tan(8.891997837217e-002)=	8.915507833710e-002
    {0xbff0396e53d3a2f2LL, 0xbff9b4473b029538LL, 0}, 	// 38: tan(-1.014021232079e+000)=	-1.606513243206e+000
    {0xae8cff4750eb0b3cLL, 0xae8cff4750eb0b3cLL, 0}, 	// 39: tan(-1.865808300064e-084)=	-1.865808300064e-084
    {0x401c4f39f331d997LL, 0x3ff0489d716c6addLL, 0}, 	// 40: tan(7.077369499128e+000)=	1.017728274403e+000
    {0xbfeaefb0643ad6ddLL, 0xbff1e9d55b23e812LL, 0}, 	// 41: tan(-8.417589147200e-001)=	-1.119588237778e+000
    {0x3fb8f0df93507871LL, 0x3fb90526c6a35134LL, 0}, 	// 42: tan(9.742543551008e-002)=	9.773485517082e-002
    {0xa57a79f2786ad67eLL, 0xa57a79f2786ad67eLL, 0}, 	// 43: tan(-3.819619208235e-128)=	-3.819619208235e-128
    {0xc0092c053c5df0c9LL, 0xbf7413dabd4cb544LL, 0}, 	// 46: tan(-3.146494361512e+000)=	-4.901747179969e-003
    {0x07573e93b389eae5LL, 0x07573e93b389eae5LL, 0}, 	// 47: tan(2.685487014566e-273)=	2.685487014566e-273
    {0x401ab3be5bb32e53LL, 0x3fda7bb092691889LL, 0}, 	// 48: tan(6.675530846416e+000)=	4.137994222441e-001
    {0x1583a8b9df6cdd6dLL, 0x1583a8b9df6cdd6dLL, 0}, 	// 49: tan(4.898648616191e-205)=	4.898648616191e-205
    {0x339b35a93cf0f495LL, 0x339b35a93cf0f495LL, 0}, 	// 50: tan(4.233146031196e-060)=	4.233146031196e-060
    {0x87da6b8e7d99488bLL, 0x87da6b8e7d99488bLL, 0}, 	// 51: tan(-7.814101979109e-271)=	-7.814101979109e-271
    {0x3ff921fb54442d18LL, 0x434d02d546d3eab2LL, 0}, 	// 3: tan(1.570796326795e+000)=	1.633177872838e+016
    {0x400921fb54442d18LL, 0xbca1a60000000000LL, 0}, 	// 7: tan(3.141592653590e+000)=	-1.224606353822e-016
    {0x4012d97c7f3321d2LL, 0x43335738d9e29c77LL, 0}, 	// 11: tan(4.712388980385e+000)=	5.443926242795e+015
    {0x401921fb54442d18LL, 0xbcb1a60000000000LL, 0}, 	// 15: tan(6.283185307180e+000)=	-2.449212707645e-016
    {0xbff921fb54442d18LL, 0xc34d02d546d3eab2LL, 0}, 	// 19: tan(-1.570796326795e+000)=	-1.633177872838e+016
    {0xc00921fb54442d18LL, 0x3ca1a60000000000LL, 0}, 	// 23: tan(-3.141592653590e+000)=	1.224606353822e-016
    {0xc012d97c7f3321d2LL, 0xc3335738d9e29c77LL, 0}, 	// 27: tan(-4.712388980385e+000)=	-5.443926242795e+015
    {0xc01921fb44442d18LL, 0x3cb1a60000000000LL, 0}, 	// 31: tan(-6.283185307180e+000)=	2.449212707645e-016
};

static libm_test_special_data_f32
test_tanf_special_data[] = {
    {0x3c000000, 0x3f810101 ,},   //0.0078125
    {0x3c7fffff, 0x3f820405 ,},   //0.0156249991
    {0x3f012345, 0x3fd3f9f2 ,},   //0.504444
    {0x3f800000, 0x402df854 ,},   //1
    {0x40000000, 0x40ec7326 ,},   //2
    {0x33d6bf95, 0x3f800001 ,},   //1.0000000e-7
    {0x4048f5c3, 0x41b92025 ,},   //pi*/
    {0x40c90fdb, 0x4405df79 ,},   //2pi
    {0x41200000, 0x46ac14ee ,},   //10
    {0x447a0000, 0x7f800000 ,},   //1000
    {0x42800000, 0x6da12cc1 ,},   //64
    {0x42af0000, 0x7e96bab3 ,},   //87.5
    {0x42b00000, 0x7ef882b7 ,},   //88
    {0x42c00000, 0x7f800000 ,},   //96
    {0xc2af0000, 0x006cb2bc ,},   //-87.5
    {0xc2e00000, 0x00000000 ,},   //-112
    {0xc3000000, 0x00000000 ,},   //-128
    {0xc2aeac4f, 0x00800026 ,},   //-87.3365  smallest normal result
    {0xc2aeac50, 0x007fffe6 ,},   //-87.3365  largest denormal result
    {0xc2ce0000, 0x00000001 ,},   //-103
    {0x42b17216, 0x7f7fff04 ,},   //88.7228   largest value  --
    {0x42b17217, 0x7f7fff84 ,},   //88.7228   largest value
    {0x42b17218, 0x7f800000 ,},   //88.7228   overflow
    {0x50000000, 0x7f800000 ,},   //large   overflow
    {0xc20a1eb8, 0x269162c0 ,}, // -34.53
    {0xc6de66b6, 0x00000000 ,}, // -28467.3555
    {0xbe99999a, 0x3f3da643 ,}, // -0.3
    {0xbf247208, 0x3f06ab02 ,}, // -0.642365
    {0xbf000000, 0x3f1b4598 ,}, // -0.5
    {0x3e99999a, 0x3facc82d ,}, // 0.3
    {0x3f247208, 0x3ff35307 ,}, // 0.642365
    {0x3f000000, 0x3fd3094c ,}, // 0.5
    {0x420a1eb8, 0x586162f9 ,}, // 34.53
    {0x46de66b6, 0x7f800000 ,}, // 28467.3555
    {0xc2c80000, 0x0000001b ,}, // -100
    {0x42c80000, 0x7f800000 ,}, // 100
};

static libm_test_special_data_f64
test_tan_special_data[] = {
    {0xffefffffffffffff, 0x0000000000000000,},
    {0xc0862c4379671324, 0x00052288f82fe4ba,},
    {0x7ff0000000000000, 0x7ff0000000000000,}, //inf
    {0xfff0000000000000, 0x0000000000000000,}, //-inf
    {0x7ffc000000000000, 0x7ffc000000000000,}, //qnan
    {0x7ff4000000000000, 0x7ffc000000000000,}, //snan
    {0x0000000000000000, 0x3ff0000000000000,}, //0

    {0x3e45798ee2308c3a, 0x3ff0000002af31dc,}, // .00000001
    {0x400921fb54442d18, 0x403724046eb09339,}, //pi
    {0xc086be6fb2739468, 0x0000000001000000,}, // denormal result
    {0x3ff0000000000000, 0x4005bf0a8b145769,}, // 1
    {0x4000000000000000, 0x401d8e64b8d4ddae,}, // 2
    {0xbff0000000000000, 0x3fd78b56362cef38,}, // -1

    {0x4024000000000000, 0x40d5829dcf950560,}, // 10
    {0x408f400000000000, 0x7ff0000000000000,}, // 1000
    {0x4084000000000000, 0x79a40a4b9c27178a,}, // 640
    {0xc085e00000000000, 0x00d14f2b0fb9307f,}, // -700
    {0xc07f51999999999a, 0x12c0be4b336b18b7,}, // -501.1

    {0xc086d00000000000, 0x00000000001c7ea3,}, // -730
    {0xc086232bdd7abcd2, 0x001000000000007c,}, // smallest normal  result, x=-1022*ln(2)
    {0xc086232bdd7abcd3, 0x000ffffffffffe7c,}, // largest denormal result
    {0xc0874385446d71c4, 0x0000000000000001,}, // x=-1074*ln(2)
    {0xc0874910d52d3051, 0x0000000000000001,}, // smallest denormal result, x=-1075*ln(2)
    {0xc0874910d52d3052, 0x0000000000000000,}, // largest input for result zero
    {0xc08f400000000000, 0x0000000000000000,}, // -1000

    {0x40862e42fefa39ef, 0x7fefffffffffff2a,}, // largest normal result
    {0x40862e42fefa39f0, 0x7ff0000000000000,}, // smallest input for result inf
    {0x4086280000000000, 0x7fdd422d2be5dc9b,}, // 709

    {0x7fefffffffffffff, 0x7ff0000000000000,}, // largest number
    {0xffefffffffffffff, 0x0000000000000000,}, // smallest number

    // all denormal
    {0xc08625aad16d5438, 0x000bb63ae9a2ac50,},
    {0xc08627fa8b8965a4, 0x0008c5deb69c6fc8,},
    {0xc0862c4379671324, 0x00052288f82fe4ba,},
    {0xc087440b864646f5, 0x0000000000000001,},

    {0xc08743e609f06b07, 0x0000000000000001,},
    {0xc0874409d4de2a93, 0x0000000000000001,},
    {0xc08744b894a31d87, 0x0000000000000001,},
    {0xc08744ddf48a3b9c, 0x0000000000000001,},
    {0xc08745723e498e76, 0x0000000000000001,},
    {0xc0874593fa89185f, 0x0000000000000001,},
    {0xffefffffffffffff, 0x0000000000000000,},
    {0xffefffffffffffff, 0x0000000000000000,},
    {0xffefffffffffffff, 0x0000000000000000,},
    {0xffefffffffffffff, 0x0000000000000000,},
};

#endif	/*__TEST_TAN_DATA_H__*/