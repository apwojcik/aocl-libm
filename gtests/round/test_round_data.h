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

#include <fenv.h>
#include "almstruct.h"
#include <libm_util_amd.h>
/*
 * Test cases to check for exceptions for the roundf() routine.
 * These test cases are not exhaustive
 * These values as as per GLIBC output
 */
static libm_test_special_data_f32
test_roundf_conformance_data[] = {
    {POS_SNAN_F32, POS_QNAN_F32, FE_INVALID},
    {NEG_SNAN_F32, NEG_QNAN_F32, FE_INVALID},
    {POS_QNAN_F32, POS_QNAN_F32, 0},
    {NEG_QNAN_F32, NEG_QNAN_F32, 0},
    {POS_INF_F32,  POS_INF_F32,  0},
    {NEG_INF_F32,  NEG_INF_F32,  0},
    {POS_ONE_F32,  POS_ONE_F32,  0},
    {NEG_ONE_F32,  NEG_ONE_F32,  0},
    {POS_ZERO_F32, POS_ZERO_F32, 0},
    {NEG_ZERO_F32, NEG_ZERO_F32, 0},
    {POS_PI_F32,     0x40400000, 0},
    {NEG_PI_F32,     0xc0400000, 0},

    /*Range of all values from 2^-3 to 2^36*/
    {0x3e000000,0x00000000,0}, // 0.125000 = 2^-3
    {0x3ec00000,0x00000000,0}, // 0.375000= 2^-3
    {0x3f200000,0x3f800000,0}, // 0.625000= 2^-3
    {0x3e800000,0x00000000,0}, // 0.250000 = 2^-2
    {0x3f000000,0x3f800000,0}, // 0.500000= 2^-2
    {0x3f400000,0x3f800000,0}, // 0.750000= 2^-2
    {0x3f000000,0x3f800000,0}, // 0.500000 = 2^-1
    {0x3f400000,0x3f800000,0}, // 0.750000= 2^-1
    {0x3f800000,0x3f800000,0}, // 1.000000= 2^-1
    {0x3f800000,0x3f800000,0}, // 1.000000 = 2^0
    {0x3fa00000,0x3f800000,0}, // 1.250000= 2^0
    {0x3fc00000,0x40000000,0}, // 1.500000= 2^0
    {0x40000000,0x40000000,0}, // 2.000000 = 2^1
    {0x40100000,0x40000000,0}, // 2.250000= 2^1
    {0x40200000,0x40400000,0}, // 2.500000= 2^1
    {0x40800000,0x40800000,0}, // 4.000000 = 2^2
    {0x40880000,0x40800000,0}, // 4.250000= 2^2
    {0x40900000,0x40a00000,0}, // 4.500000= 2^2
    {0x41000000,0x41000000,0}, // 8.000000 = 2^3
    {0x41040000,0x41000000,0}, // 8.250000= 2^3
    {0x41080000,0x41100000,0}, // 8.500000= 2^3
    {0x41800000,0x41800000,0}, // 16.000000 = 2^4
    {0x41820000,0x41800000,0}, // 16.250000= 2^4
    {0x41840000,0x41880000,0}, // 16.500000= 2^4
    {0x42000000,0x42000000,0}, // 32.000000 = 2^5
    {0x42010000,0x42000000,0}, // 32.250000= 2^5
    {0x42020000,0x42040000,0}, // 32.500000= 2^5
    {0x42800000,0x42800000,0}, // 64.000000 = 2^6
    {0x42808000,0x42800000,0}, // 64.250000= 2^6
    {0x42810000,0x42820000,0}, // 64.500000= 2^6
    {0x43000000,0x43000000,0}, // 128.000000 = 2^7
    {0x43004000,0x43000000,0}, // 128.250000= 2^7
    {0x43008000,0x43010000,0}, // 128.500000= 2^7
    {0x43800000,0x43800000,0}, // 256.000000 = 2^8
    {0x43802000,0x43800000,0}, // 256.250000= 2^8
    {0x43804000,0x43808000,0}, // 256.500000= 2^8
    {0x44000000,0x44000000,0}, // 512.000000 = 2^9
    {0x44001000,0x44000000,0}, // 512.250000= 2^9
    {0x44002000,0x44004000,0}, // 512.500000= 2^9
    {0x44800000,0x44800000,0}, // 1024.000000 = 2^10
    {0x44800800,0x44800000,0}, // 1024.250000= 2^10
    {0x44801000,0x44802000,0}, // 1024.500000= 2^10
    {0x45000000,0x45000000,0}, // 2048.000000 = 2^11
    {0x45000400,0x45000000,0}, // 2048.250000= 2^11
    {0x45000800,0x45001000,0}, // 2048.500000= 2^11
    {0x45800000,0x45800000,0}, // 4096.000000 = 2^12
    {0x45800200,0x45800000,0}, // 4096.250000= 2^12
    {0x45800400,0x45800800,0}, // 4096.500000= 2^12
    {0x46000000,0x46000000,0}, // 8192.000000 = 2^13
    {0x46000100,0x46000000,0}, // 8192.250000= 2^13
    {0x46000200,0x46000400,0}, // 8192.500000= 2^13
    {0x46800000,0x46800000,0}, // 16384.000000 = 2^14
    {0x46800080,0x46800000,0}, // 16384.250000= 2^14
    {0x46800100,0x46800200,0}, // 16384.500000= 2^14
    {0x47000000,0x47000000,0}, // 32768.000000 = 2^15
    {0x47000040,0x47000000,0}, // 32768.250000= 2^15
    {0x47000080,0x47000100,0}, // 32768.500000= 2^15
    {0x47800000,0x47800000,0}, // 65536.000000 = 2^16
    {0x47800020,0x47800000,0}, // 65536.250000= 2^16
    {0x47800040,0x47800080,0}, // 65536.500000= 2^16
    {0x48000000,0x48000000,0}, // 131072.000000 = 2^17
    {0x48000010,0x48000000,0}, // 131072.250000= 2^17
    {0x48000020,0x48000040,0}, // 131072.500000= 2^17
    {0x48800000,0x48800000,0}, // 262144.000000 = 2^18
    {0x48800008,0x48800000,0}, // 262144.250000= 2^18
    {0x48800010,0x48800020,0}, // 262144.500000= 2^18
    {0x49000000,0x49000000,0}, // 524288.000000 = 2^19
    {0x49000004,0x49000000,0}, // 524288.250000= 2^19
    {0x49000008,0x49000010,0}, // 524288.500000= 2^19
    {0x49800000,0x49800000,0}, // 1048576.000000 = 2^20
    {0x49800002,0x49800000,0}, // 1048576.250000= 2^20
    {0x49800004,0x49800008,0}, // 1048576.500000= 2^20
    {0x4a000000,0x4a000000,0}, // 2097152.000000 = 2^21
    {0x4a000001,0x4a000000,0}, // 2097152.250000= 2^21
    {0x4a000002,0x4a000004,0}, // 2097152.500000= 2^21
    {0x4a800000,0x4a800000,0}, // 4194304.000000 = 2^22
    {0x4b000000,0x4b000000,0}, // 8388608.000000 = 2^23
    {0x4b800000,0x4b800000,0}, // 16777216.000000 = 2^24
    {0x4c000000,0x4c000000,0}, // 33554432.000000 = 2^25
    {0x4c800000,0x4c800000,0}, // 67108864.000000 = 2^26
    {0x4d000000,0x4d000000,0}, // 134217728.000000 = 2^27
    {0x4d800000,0x4d800000,0}, // 268435456.000000 = 2^28
    {0x4e000000,0x4e000000,0}, // 536870912.000000 = 2^29
    {0x4e800000,0x4e800000,0}, // 1073741824.000000 = 2^30
    {0x4f000000,0x4f000000,0}, // 2147483648.000000 = 2^31
    {0x4f800000,0x4f800000,0}, // 4294967296.000000= 2^32
    {0x50000000,0x50000000,0}, // 8589934592.000000 = 2^33
    {0x50800000,0x50800000,0}, // 17179869184.000000 = 2^34
    {0x51000000,0x51000000,0}, // 34359738368.000000 = 2^a,0X43b40000,0},
    {0X1,0X0,0},
    {0X5fde6,0X0,0},
    {0X7fffff,0X0,0},
    {0X80000001,0X80000000,0},
    {0X805def12,0X80000000,0},
    {0X807fffff,0X80000000,0},
    {0X800000,0X0,0},
    {0X43b3c4ea,0X43b40000,0},
    {0X7f7fffff,0X7f7fffff,0},
    {0X80800000,0X80000000,0},
    {0Xc5812e71,0Xc5813000,0},
    {0Xff7fffff,0Xff7fffff,0},
    {0X7f800000,0X7f800000,0},
    {0Xff800000,0Xff800000,0},
    {0X7fc00000,0X7fc00000,0},
    {0X7fe1a570,0X7fe1a570,0},
    {0X3fc90fdb,0X40000000,0},
    {0X40490fdb,0X40400000,0},
    {0X40c90fdb,0X40c00000,0},
    {0X402df853,0X40400000,0},
    {0X402df854,0X40400000,0},
    {0X402df855,0X40400000,0},
    {0X0,0X0,0},
    {0X37c0f01f,0X0,0},
    {0X3efffeb0,0X0,0},
    {0X3f0000c9,0X3f800000,0},
    {0X3f0000c9,0X3f800000,0},
    {0X80000000,0X80000000,0},
    {0Xb7c0f01f,0X80000000,0},
    {0Xbefffeb0,0X80000000,0},
    {0Xbf0000c9,0Xbf800000,0},
    {0X3f800000,0X3f800000,0},
    {0X3f700001,0X3f800000,0},
    {0X3f87fffe,0X3f800000,0},
    {0X3fbfffac,0X3f800000,0},
    {0X3fc00064,0X40000000,0},
    {0Xbf800000,0Xbf800000,0},
    {0Xbf700001,0Xbf800000,0},
    {0Xbf87fffe,0Xbf800000,0},
    {0Xbfbfffac,0Xbf800000,0},
    {0Xbfc00064,0Xc0000000,0},
    {0X40000000,0X40000000,0},
    {0Xc0000000,0Xc0000000,0},
    {0X41200000,0X41200000,0},
    {0Xc1200000,0Xc1200000,0},
    {0X447a0000,0X447a0000,0},
    {0Xc47a0000,0Xc47a0000,0},
    {0X4286cccc,0X42860000,0},
    {0Xc286cccc,0Xc2860000,0},
    {0X44f7f333,0X44f80000,0},
    {0Xc4f7f333,0Xc4f80000,0},
    {0X42af0000,0X42b00000,0},
    {0Xc2af0000,0Xc2b00000,0},
    {0X48015e40,0X48015e40,0},
    {0Xc8015e40,0Xc8015e40,0},
    {0X4b000000,0X4b000000,0},
    {0X4b000001,0X4b000001,0},
    {0X4affffff,0X4b000000,0},
    {0Xcb000000,0Xcb000000,0},
    {0Xcb000001,0Xcb000001,0},
    {0Xcaffffff,0Xcb000000,0},
};

static libm_test_special_data_f64
test_round_conformance_data[] = {
    // special accuracy tests
    {0x3e30000000000000LL, 0x3ff0000000000000LL, 0},  //min, small enough that round(x) = 1 //
    {0x3E2FFFFFFFFFFFFFLL, 0x3ff0000000000000LL, 0}, //min - 1 bit
    {0x3e30000000000001LL, 0x3ff0000000000000LL, 0}, //min + 1 bit
    {0xFE37E43C8800759CLL, 0x7ff0000000000000LL, 0}, //lambda + x = 1, x = -1.0000000000000000e+300
    {0xFE37E43C8800758CLL, 0x7ff0000000000000LL, 0}, //lambda + x < 1
    {0xFE37E43C880075ACLL, 0x7ff0000000000000LL, 0}, //lambda + x > 1
    {0x408633ce8fb9f87eLL, 0x7ff0000000000000LL, 0}, //max arg, x = 89.41598629223294,max roundf arg
    {0x408633ce8fb9f87dLL, 0x7feffffffffffd3bLL, 0}, //max arg - 1 bit
    {0x408633ce8fb9f87fLL, 0x7ff0000000000000LL, 0}, //max arg + 1 bit
    {0x408633ce8fb9f8ffLL, 0x7ff0000000000000LL, 0}, // > max
    {0x408633ce8fb9f800LL, 0x7feffffffffe093bLL, 0}, // < max
    {0x4034000000000000LL, 0x41aceb088b68e804LL, 0}, //small_threshold = 20
    {0x4035000000000000LL, 0x41c3a6e1fd9eecfdLL, 0}, //small_threshold+1 = 21
    {0x4033000000000000LL, 0x419546d8f9ed26e2LL, 0}, //small_threshold - 1 = 19

    //round special exception checks
    {POS_ZERO_F64, 0x3FF0000000000000LL,0 },  //0
    {NEG_ZERO_F64, 0x3FF0000000000000LL,0 },  //0
    {POS_INF_F64, POS_INF_F64,   0 },
    {NEG_INF_F64, POS_INF_F64,   0 },
    {POS_SNAN_F64, POS_SNAN_F64, 0 },  //
    {NEG_SNAN_F64, NEG_SNAN_F64, 0 },  //
    {POS_QNAN_F64, POS_QNAN_F64, 0 },  //
    {NEG_QNAN_F64, NEG_QNAN_F64, 0 },  //
    {0x4086340000000000LL, POS_INF_F64, 0},  // 710.5
    {0x0000000000000001LL, 0x3ff0000000000000LL, 0}, // denormal min
    {0x0005fde623545abcLL, 0x3ff0000000000000LL, 0}, // denormal intermediate
    {0x000FFFFFFFFFFFFFLL, 0x3ff0000000000000LL, 0}, // denormal max
    {0x8000000000000001LL, 0x3ff0000000000000LL, 0}, // -denormal min
    {0x8002344ade5def12LL, 0x3ff0000000000000LL, 0}, // -denormal intermediate
    {0x800FFFFFFFFFFFFFLL, 0x3ff0000000000000LL, 0}, // -denormal max
    {0x0010000000000000LL, 0x3ff0000000000000LL, 0}, // normal min
    {0x43b3c4eafedcab02LL, 0x7ff0000000000000LL, 0}, // normal intermediate
    {0x7FEFFFFFFFFFFFFFLL, 0x7ff0000000000000LL, 0}, // normal max
    {0x8010000000000000LL, 0x3ff0000000000000LL, 0}, // -normal min
    {0xc5812e71245acfdbLL, 0x7ff0000000000000LL, 0}, // -normal intermediate
    {0xFFEFFFFFFFFFFFFFLL, 0x7ff0000000000000LL, 0}, // -normal max
    {0x7FF0000000000000LL, 0x7ff0000000000000LL, 0}, // inf
    {0xFFF0000000000000LL, 0x7ff0000000000000LL, 0}, // -inf
    {0x7FF8000000000000LL, 0x7ff8000000000000LL, 0}, // qnan min
    {0x7FFe1a5701234dc3LL, 0x7ffe1a5701234dc3LL, 0}, // qnan intermediate
    {0x7FFFFFFFFFFFFFFFLL, 0x7fffffffffffffffLL, 0}, // qnan max
    {0xFFF8000000000000LL, 0xfff8000000000000LL, 0}, // indeterninate
    {0xFFF8000000000001LL, 0xfff8000000000001LL, 0}, // -qnan min
    {0xFFF9123425dcba31LL, 0xfff9123425dcba31LL, 0}, // -qnan intermediate
    {0xFFFFFFFFFFFFFFFFLL, 0xffffffffffffffffLL, 0}, // -qnan max
    {0x7FF0000000000001LL, 0x7ff8000000000001LL, 0}, // snan min
    {0x7FF5344752a0bd90LL, 0x7ffd344752a0bd90LL, 0}, // snan intermediate
    {0x7FF7FFFFFFFFFFFFLL, 0x7fffffffffffffffLL, 0}, // snan max
    {0xFFF0000000000001LL, 0xfff8000000000001LL, 0}, // -snan min
    {0xfFF432438995fffaLL, 0xfffc32438995fffaLL, 0}, // -snan intermediate
    {0xFFF7FFFFFFFFFFFFLL, 0xffffffffffffffffLL, 0}, // -snan max
    {0x3FF921FB54442D18LL, 0x400412cc2a8d4e9eLL, 0}, // pi/2
    {0x400921FB54442D18LL, 0x40272f147fee4000LL, 0}, // pi
    {0x401921FB54442D18LL, 0x4070bbf2bc2b69c6LL, 0}, // 2pi
    {0x3FFB7E151628AED3LL, 0x4007046b4f3f7e0cLL, 0}, // e --
    {0x4005BF0A8B145769LL, 0x401e70c4a4f41684LL, 0}, // e
    {0x400DBF0A8B145769LL, 0x40349be1e586228dLL, 0}, // e ++
    {0x0000000000000000LL, 0x3ff0000000000000LL, 0}, // 0
    {0x3C4536B8B14B676CLL, 0x3ff0000000000000LL, 0}, // 0.0000000000000000023
    {0x3FDFFFFBCE4217D3LL, 0x3ff20ac0fa498d2cLL, 0}, // 0.4999989999999999999
    {0x3FE000000000006CLL, 0x3ff20ac1862ae8edLL, 0}, // 0.500000000000012
    {0x8000000000000000LL, 0x3ff0000000000000LL, 0}, // -0
    {0xBBDB2752CE74FF42LL, 0x3ff0000000000000LL, 0}, // -0.000000000000000000023
    {0xBFDFFFFBCE4217D3LL, 0x3ff20ac0fa498d2cLL, 0}, // -0.4999989999999999999
    {0xBFE000000000006CLL, 0x3ff20ac1862ae8edLL, 0}, // -0.500000000000012
    {0x3FF0000000000000LL, 0x3ff8b07551d9f550LL, 0}, // 1
    {0x3FEFFFFFC49BD0DCLL, 0x3ff8b0752ef3f8a2LL, 0}, // 0.9999998893750006
    {0x3FF0000000000119LL, 0x3ff8b07551d9f69bLL, 0}, // 1.0000000000000624998
    {0x3FF7FFFEF39085F4LL, 0x4002d1bb0418ae52LL, 0}, // 1.499998999999999967
    {0x3FF8000000000001LL, 0x4002d1bc21e22023LL, 0}, // 1.50000000000000012
    {0xBFF0000000000000LL, 0x3ff8b07551d9f550LL, 0}, // -1
    {0xBFEFFFFFC49BD0DCLL, 0x3ff8b0752ef3f8a2LL, 0}, // -0.9999998893750006
    {0xBFF0000000000119LL, 0x3ff8b07551d9f69bLL, 0}, // -1.0000000000000624998
    {0xBFF7FFFEF39085F4LL, 0x4002d1bb0418ae52LL, 0}, // -1.499998999999999967
    {0xBFF8000000000001LL, 0x4002d1bc21e22023LL, 0}, // -1.50000000000000012

    {0x4000000000000000LL, 0x400e18fa0df2d9bcLL, 0}, // 2
    {0xC000000000000000LL, 0x400e18fa0df2d9bcLL, 0}, // -2
    {0x4024000000000000LL, 0x40c5829dd053712dLL, 0}, // 10
    {0xC024000000000000LL, 0x40c5829dd053712dLL, 0}, // -10
    {0x408F400000000000LL, 0x7ff0000000000000LL, 0}, // 1000
    {0xC08F400000000000LL, 0x7ff0000000000000LL, 0}, // -1000
    {0x4050D9999999999ALL, 0x45f2dd7567cd83eeLL, 0}, // 67.4
    {0xC050D9999999999ALL, 0x45f2dd7567cd83eeLL, 0}, // -67.4
    {0x409EFE6666666666LL, 0x7ff0000000000000LL, 0}, // 1983.6
    {0xC09EFE6666666666LL, 0x7ff0000000000000LL, 0}, // -1983.6
    {0x4055E00000000000LL, 0x47c2d7566d26536bLL, 0}, // 87.5
    {0xC055E00000000000LL, 0x47c2d7566d26536bLL, 0}, // -87.5
    {0x41002BC800000000LL, 0x7ff0000000000000LL, 0}, // 132473
    {0xC1002BC800000000LL, 0x7ff0000000000000LL, 0}, // -132473
    {0x4330000000000000LL, 0x7ff0000000000000LL, 0}, // 2^52
    {0x4330000000000001LL, 0x7ff0000000000000LL, 0}, // 2^52 + 1
    {0x432FFFFFFFFFFFFFLL, 0x7ff0000000000000LL, 0}, // 2^52 -1 + 0.5
    {0xC330000000000000LL, 0x7ff0000000000000LL, 0}, // -2^52
    {0xC330000000000001LL, 0x7ff0000000000000LL, 0}, // -(2^52 + 1)
    {0xC32FFFFFFFFFFFFFLL, 0x7ff0000000000000LL, 0}, // -(2^52 -1 + 0.5)
    //added from ancient libm repo
    {0x3ff921fb54442d18, 0X3ff921fb54442d18}, // 1.5708
    {0x400921fb54442d18, 0X400921fb54442d18}, // 3.14159
    {0x401921fb54442d18, 0X401921fb54442d18}, // 6.28319
    {0x3ffb7e151628aed3, 0X3ffb7e151628aed3}, // 1.71828
    {0x4005bf0a8b145769, 0X4005bf0a8b145769}, // 2.71828
    {0x400dbf0a8b145769, 0X400dbf0a8b145769}, // 3.71828
    {0x0, 0X0}, // 0
    {0x3c4536b8b14b676c, 0X3c4536b8b14b676c}, // 2.3e-18
    {0x3fdffffbce4217d3, 0X3fdffffbce4217d3}, // 0.499999
    {0x3fe000000000006c, 0X3fe000000000006c}, // 0.5
    {0x8000000000000000, 0X0}, // -0
    {0xbbdb2752ce74ff42, 0X3bdb2752ce74ff42}, // -2.3e-20
    {0xbfdffffbce4217d3, 0X3fdffffbce4217d3}, // -0.499999
    {0xbfe000000000006c, 0X3fe000000000006c}, // -0.5
    {0x3ff0000000000000, 0X3ff0000000000000}, // 1
    {0x3fefffffc49bd0dc, 0X3fefffffc49bd0dc}, // 1
    {0x3ff0000000000119, 0X3ff0000000000119}, // 1
    {0x3ff7fffef39085f4, 0X3ff7fffef39085f4}, // 1.5
    {0x3ff8000000000001, 0X3ff8000000000001}, // 1.5
    {0xbff0000000000000, 0X3ff0000000000000}, // -1
    {0xbfefffffc49bd0dc, 0X3fefffffc49bd0dc}, // -1
    {0xbff0000000000119, 0X3ff0000000000119}, // -1
    {0xbff7fffef39085f4, 0X3ff7fffef39085f4}, // -1.5
    {0xbff8000000000001, 0X3ff8000000000001}, // -1.5
    {0x4000000000000000, 0X4000000000000000}, // 2
    {0xc000000000000000, 0X4000000000000000}, // -2
    {0x4024000000000000, 0X4024000000000000}, // 10
    {0xc024000000000000, 0X4024000000000000}, // -10
    {0x408f400000000000, 0X408f400000000000}, // 1000
    {0xc08f400000000000, 0X408f400000000000}, // -1000
    {0x4050d9999999999a, 0X4050d9999999999a}, // 67.4
    {0xc050d9999999999a, 0X4050d9999999999a}, // -67.4
    {0x409efe6666666666, 0X409efe6666666666}, // 1983.6
    {0xc09efe6666666666, 0X409efe6666666666}, // -1983.6
    {0x4055e00000000000, 0X4055e00000000000}, // 87.5
    {0xc055e00000000000, 0X4055e00000000000}, // -87.5
    {0x41002bc800000000, 0X41002bc800000000}, // 132473
    {0xc1002bc800000000, 0X41002bc800000000}, // -132473
    {0x4330000000000000, 0X4330000000000000}, // 4.5036e+15
    {0x4330000000000001, 0X4330000000000001}, // 4.5036e+15
    {0x432fffffffffffff, 0X432fffffffffffff}, // 4.5036e+15
    {0xc330000000000000, 0X4330000000000000}, // -4.5036e+15
    {0xc330000000000001, 0X4330000000000001}, // -4.5036e+15
    {0xc32fffffffffffff, 0X432fffffffffffff}, // -4.5036e+15
    {0x43480677adfcfa00, 0X43480677adfcfa00}, // 1.3525e+16
    {0x435801239871fa00, 0X435801239871fa00}, // 2.70266e+16
    {0x4368111144444444, 0X4368111144444444}, // 5.41933e+16
    {0x4388ffffffffffff, 0X4388ffffffffffff}, // 2.2518e+17
    {0x4398ffffffffffff, 0X4398ffffffffffff}, // 4.5036e+17
    {0x43a8ffffffffffff, 0X43a8ffffffffffff}, // 9.0072e+17
    {0x43b8aaaa68ffffff, 0X43b8aaaa68ffffff}, // 1.77742e+18
    {0x43c8aaaa69ffffff, 0X43c8aaaa69ffffff}, // 3.55484e+18
    {0x43d8009678abcd00, 0X43d8009678abcd00}, // 6.91819e+18
    {0x7fefffffffffffff, 0X7fefffffffffffff}, // 1.79769e+308
    {0x43e8098734209870, 0X43e8098734209870}, // 1.38565e+19
    {0x43f800876abcda00, 0X43f800876abcda00}, // 2.76725e+19
    {0x44080091781cdba0, 0X44080091781cdba0}, // 5.53454e+19
    {0x4408012786abcde0, 0X4408012786abcde0}, // 5.53506e+19
    {0x43b3c4eafedcab02, 0X43b3c4eafedcab02} // 1.42452e+18
};
