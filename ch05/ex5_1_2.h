#pragma once

// 1)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c5/e1.htm
// false;
// 4;
// a,c,undefined behavior,undefined behavior;
// 0,2,-1
// L=(b,c,d),L=(a,b,d),L=(a,b,c)
// L=(e,a,b,c,d),L=(a,b,f,c,d),L=(a,b,c,g,d),L=(a,b,c,d,h),ub,ub;

// 2)
// initial:
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    a	b	c	d	e	_	_	_	_	_
// insert(0,f)
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    f	a	b	c	d	e	_	_	_	_		
// insert(3,g)
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    f	a	b	g	c	d	e	_	_	_
// insert(7,h)
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    f	a	b	g	c	d	e	h	_	_
// erase(0)
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    a	b	g	c	d	e	h	_	_	_
// erase(4)
// element [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
//		    a	b	g	c	e	h	_	_	_	_
