#pragma once

// ex7_1
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e1.htm

// ex7_2
// map(i1, i2, i3, i4, i5) = i1 * u2 * u3 * u4 * u5 + i2 * u3 * u4 * u5 + i3 * u4 * u5 + i4 * u5 + i5

// ex7_3
// map(i1, i2, i3, ..., ik-1, ik) = i1 * u2 * u3 * ... * uk-1 * uk + i2 * u3 * ... * uk-1 * uk + ... + ik-1 * uk + ik

// ex7_4
// 1)
// [0][0][0] [1][0][0] [0][1][0] [1][1][0] [0][2][0] [1][2][0] 
// [0][0][1] [1][0][1] [0][1][1] [1][1][1] [0][2][1] [1][2][1]
// [0][0][2] [1][0][2] [0][1][2] [1][1][2] [0][2][2] [1][2][2]
// [0][0][3] [1][0][3] [0][1][3] [1][1][3] [0][2][3] [1][2][3]
// 2)
// map(i1,i2,i3) = i3*u2*u1 + i2*u1 + i1

// ex7_5
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e5.htm

// ex7_6
// map(i1,i2,i3,...,ik) = ik * uk-1 * uk-1 * ... * u1 + ik-1 * uk-2 * ... * u1 + ... + i2 * u1 + u1

// ex7_7
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e7.htm
// 1)
// [2][4] [2][3] [2][2] [2][1] [2][0]
// [1][4] [1][3] [1][2] [1][1] [1][0]
// [0][4] [0][3] [0][2] [0][1] [0][0]
// 2)
// score(u1,u2) = u1*u2 - (u1*x + u2) - 1

// ex7_8
// 1)
// [2][4] [1][4] [0][4]
// [2][3] [1][3] [0][3]
// [2][2] [1][2] [0][2]
// [2][1] [1][1] [0][1]
// [2][0] [1][0] [0][0]
// 2)
// score(u1,u2) = u1*u2 - (u1 + u2*c) - 1

// ex7_9
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e9.htm

// ex7_10
// 1)
// 4m + 4mn + 4mnp;4mnp;
// 2)
// (4m + 4mn + 4mnp)/(4mnp) = 1/np + 1/p + 1 
// the maximum value of the ratio is 1/4 + 1/2 + 1 = 7/4.
// 3)
// 

// ex7_11
// 1)
// 4m + 4mn + 4mnp + 4mnpq; 4mnpq;
// 2)
// (4m + 4mn + 4mnp + 4mnpq)/(4mnpq) = 1/npq + 1/pq + 1/q + 1
// the maximum value of the ratio is 1/8 + 1/4 + 1/2 + 1 = 17/8 .

// ex7_12
// 1£©
// 4u1 + 4u1u2 + ... + 4u1u2...uk-1uk; 4u1u2...uk-1uk;
// 2£©
// 1/u2u3...uk + 1/u3...uk + ... + 1/uk + 1
// 3£©
//

// ex7_13
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e13.htm

// ex7_14
// 1)
// 0  1  2
// 3  4  5
// 6  7  8
// 9  10 11
// 12 13 14
// 15 16 17
// 2)
//495.0000   	540.0000   	585.0000
//540.0000   	591.0000   	642.0000
//585.0000   	642.0000   	699.0000