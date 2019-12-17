
#include <iostream>
#include "taco.h"
#include "taco/util/timers.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>

#include "taco/tensor.h"
#include "taco/format.h"
#include "taco/error.h"
#include "taco/util/strings.h"
#include "taco/util/files.h"
#include <cstdio>
#include <cstdlib>
#include <vector>


struct coo_t
{
	int32_t	idx0;
	int32_t	idx1;
	int32_t	idx2;
	int32_t	idx3;
	double	val;
};


using namespace taco;
int cmp_0123(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_123(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_23(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_3(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_0132(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_132(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_32(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_2(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_0213(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_213(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_13(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_0231(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_231(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_31(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_1(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_0312(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_312(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_12(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_0321(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_321(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_21(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_1023(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_023(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_1032(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_032(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_1203(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_203(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_03(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_1230(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_230(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_30(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_0(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_1302(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_302(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_02(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_1320(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_320(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_20(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_2013(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_013(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_2031(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_031(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_2103(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_103(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_2130(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_130(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_2301(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_301(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_01(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_2310(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_310(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_10(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_3012(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_012(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_3021(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_021(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_3102(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_102(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_3120(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_120(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_3201(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_201(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_3210(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_210(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3)
int transpose_coo_0123_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0123);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3)
int transpose_coo_0123_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2, 3)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_123);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3)
int transpose_coo_0123_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2, 3)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_23);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3)
int transpose_coo_0123_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2, 3)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3)
int transpose_coo_0123_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 2, 3)
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2)
int transpose_coo_0132_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 3, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0132);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2)
int transpose_coo_0132_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 3, 2)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_132);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2)
int transpose_coo_0132_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 1, 3, 2)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_32);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2)
int transpose_coo_0132_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 2)
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_301 = (int *)malloc(c_size*sizeof(int));
	int *quotient_301 = (int *)malloc(c_size*sizeof(int));
	int current_301 = 0;
	bucket_301[0] = 0;
	quotient_301[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_301++;
			quotient_301[current_301] = i;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_301++;
			quotient_301[current_301] = i;
		}
		bucket_301[i] = current_301;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_301[i];
		B3_count[idx3]--;
	}
	free(bucket_301);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_301[perm[i]]] = C_coords_scratch[i];
		quotient_301[perm[i]] ++;
	}
	free(quotient_301);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0, 1])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2)
int transpose_coo_0132_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 2)
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_301 = (int *)malloc(c_size*sizeof(int));
	int *quotient_301 = (int *)malloc(c_size*sizeof(int));
	int current_301 = 0;
	bucket_301[0] = 0;
	quotient_301[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_301++;
			quotient_301[current_301] = i;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_301++;
			quotient_301[current_301] = i;
		}
		bucket_301[i] = current_301;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_301[i];
		B3_count[idx3]--;
	}
	free(bucket_301);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_301[perm[i]]] = C_coords_scratch[i];
		quotient_301[perm[i]] ++;
	}
	free(quotient_301);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0, 1])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3)
int transpose_coo_0213_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 1, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0213);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3)
int transpose_coo_0213_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 1, 3)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_213);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3)
int transpose_coo_0213_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 3)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_13);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3)
int transpose_coo_0213_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 3)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3)
int transpose_coo_0213_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 3)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1)
int transpose_coo_0231_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 3, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0231);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1)
int transpose_coo_0231_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 2, 3, 1)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_231);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1)
int transpose_coo_0231_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_31);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1)
int transpose_coo_0231_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0]), (2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1)
int transpose_coo_0231_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0]), (2, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2)
int transpose_coo_0312_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 3, 1, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0312);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2)
int transpose_coo_0312_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 3, 1, 2)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_312);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2)
int transpose_coo_0312_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 2)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_12);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2)
int transpose_coo_0312_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 2)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2)
int transpose_coo_0312_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 2)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1)
int transpose_coo_0321_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 3, 2, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_0321);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1)
int transpose_coo_0321_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (0, 3, 2, 1)
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_321);
			qsort_start = i;
		}
	}
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1)
int transpose_coo_0321_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_21);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1)
int transpose_coo_0321_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0]), (3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1)
int transpose_coo_0321_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_20 = (int *)malloc(c_size*sizeof(int));
	int *quotient_20 = (int *)malloc(c_size*sizeof(int));
	int current_20 = 0;
	bucket_20[0] = 0;
	quotient_20[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_20++;
			quotient_20[current_20] = i;
		}
		bucket_20[i] = current_20;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_20[i];
		B2_count[idx2]--;
	}
	free(bucket_20);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[perm[i]]] = C_coords_scratch[i];
		quotient_20[perm[i]] ++;
	}
	free(quotient_20);
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_30 = (int *)malloc(c_size*sizeof(int));
	int *quotient_30 = (int *)malloc(c_size*sizeof(int));
	int current_30 = 0;
	bucket_30[0] = 0;
	quotient_30[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_30++;
			quotient_30[current_30] = i;
		}
		bucket_30[i] = current_30;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_30[i];
		B3_count[idx3]--;
	}
	free(bucket_30);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[perm[i]]] = C_coords_scratch[i];
		quotient_30[perm[i]] ++;
	}
	free(quotient_30);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [0]), (3, [0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3)
int transpose_coo_1023_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 0, 2, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1023);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3)
int transpose_coo_1023_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_023);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3)
int transpose_coo_1023_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_23);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3)
int transpose_coo_1023_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3)
int transpose_coo_1023_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2)
int transpose_coo_1032_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 0, 3, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1032);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2)
int transpose_coo_1032_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_032);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2)
int transpose_coo_1032_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_32);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2)
int transpose_coo_1032_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Fix and sort on [1, 0]
	// Create buckets and quotient
	int *bucket_310 = (int *)malloc(c_size*sizeof(int));
	int *quotient_310 = (int *)malloc(c_size*sizeof(int));
	int current_310 = 0;
	bucket_310[0] = 0;
	quotient_310[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_310++;
			quotient_310[current_310] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_310++;
			quotient_310[current_310] = i;
		}
		bucket_310[i] = current_310;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_310[i];
		B3_count[idx3]--;
	}
	free(bucket_310);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_310[perm[i]]] = C_coords_scratch[i];
		quotient_310[perm[i]] ++;
	}
	free(quotient_310);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [1, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2)
int transpose_coo_1032_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Fix and sort on [1, 0]
	// Create buckets and quotient
	int *bucket_310 = (int *)malloc(c_size*sizeof(int));
	int *quotient_310 = (int *)malloc(c_size*sizeof(int));
	int current_310 = 0;
	bucket_310[0] = 0;
	quotient_310[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_310++;
			quotient_310[current_310] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_310++;
			quotient_310[current_310] = i;
		}
		bucket_310[i] = current_310;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_310[i];
		B3_count[idx3]--;
	}
	free(bucket_310);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_310[perm[i]]] = C_coords_scratch[i];
		quotient_310[perm[i]] ++;
	}
	free(quotient_310);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [1, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3)
int transpose_coo_1203_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 2, 0, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1203);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3)
int transpose_coo_1203_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_203);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3)
int transpose_coo_1203_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_03);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3)
int transpose_coo_1203_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3)
int transpose_coo_1203_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0)
int transpose_coo_1230_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 2, 3, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1230);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0)
int transpose_coo_1230_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_230);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0)
int transpose_coo_1230_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_30);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0)
int transpose_coo_1230_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0)
int transpose_coo_1230_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2)
int transpose_coo_1302_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 3, 0, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1302);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2)
int transpose_coo_1302_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_302);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2)
int transpose_coo_1302_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_02);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2)
int transpose_coo_1302_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2)
int transpose_coo_1302_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0)
int transpose_coo_1320_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (1, 3, 2, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_1320);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0)
int transpose_coo_1320_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_320);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0)
int transpose_coo_1320_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_20);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0)
int transpose_coo_1320_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0)
int transpose_coo_1320_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3)
int transpose_coo_2013_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 0, 1, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2013);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3)
int transpose_coo_2013_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_013);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3)
int transpose_coo_2013_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_13);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3)
int transpose_coo_2013_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3)
int transpose_coo_2013_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1)
int transpose_coo_2031_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 0, 3, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2031);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1)
int transpose_coo_2031_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_031);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1)
int transpose_coo_2031_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_31);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1)
int transpose_coo_2031_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Fix and sort on [2, 0]
	// Create buckets and quotient
	int *bucket_320 = (int *)malloc(c_size*sizeof(int));
	int *quotient_320 = (int *)malloc(c_size*sizeof(int));
	int current_320 = 0;
	bucket_320[0] = 0;
	quotient_320[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_320++;
			quotient_320[current_320] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_320++;
			quotient_320[current_320] = i;
		}
		bucket_320[i] = current_320;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_320[i];
		B3_count[idx3]--;
	}
	free(bucket_320);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_320[perm[i]]] = C_coords_scratch[i];
		quotient_320[perm[i]] ++;
	}
	free(quotient_320);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [2, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1)
int transpose_coo_2031_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Fix and sort on [2, 0]
	// Create buckets and quotient
	int *bucket_320 = (int *)malloc(c_size*sizeof(int));
	int *quotient_320 = (int *)malloc(c_size*sizeof(int));
	int current_320 = 0;
	bucket_320[0] = 0;
	quotient_320[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_320++;
			quotient_320[current_320] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_320++;
			quotient_320[current_320] = i;
		}
		bucket_320[i] = current_320;
	}

	// Histogram sort on mode 3 into the permutation array
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_320[i];
		B3_count[idx3]--;
	}
	free(bucket_320);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_320[perm[i]]] = C_coords_scratch[i];
		quotient_320[perm[i]] ++;
	}
	free(quotient_320);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [2, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3)
int transpose_coo_2103_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 1, 0, 3)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2103);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3)
int transpose_coo_2103_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_103);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3)
int transpose_coo_2103_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_03);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3)
int transpose_coo_2103_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_3);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3)
int transpose_coo_2103_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0)
int transpose_coo_2130_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 1, 3, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2130);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0)
int transpose_coo_2130_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_130);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0)
int transpose_coo_2130_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_30);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0)
int transpose_coo_2130_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0)
int transpose_coo_2130_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1)
int transpose_coo_2301_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 3, 0, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2301);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1)
int transpose_coo_2301_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_301);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1)
int transpose_coo_2301_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_01);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1)
int transpose_coo_2301_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1)
int transpose_coo_2301_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0)
int transpose_coo_2310_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (2, 3, 1, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_2310);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0)
int transpose_coo_2310_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_310);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0)
int transpose_coo_2310_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_10);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0)
int transpose_coo_2310_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0)
int transpose_coo_2310_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2)
int transpose_coo_3012_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 0, 1, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3012);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2)
int transpose_coo_3012_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_012);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2)
int transpose_coo_3012_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_12);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2)
int transpose_coo_3012_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2)
int transpose_coo_3012_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1)
int transpose_coo_3021_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 0, 2, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3021);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1)
int transpose_coo_3021_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_021);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1)
int transpose_coo_3021_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_21);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1)
int transpose_coo_3021_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Fix and sort on [3, 0]
	// Create buckets and quotient
	int *bucket_230 = (int *)malloc(c_size*sizeof(int));
	int *quotient_230 = (int *)malloc(c_size*sizeof(int));
	int current_230 = 0;
	bucket_230[0] = 0;
	quotient_230[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_230++;
			quotient_230[current_230] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_230++;
			quotient_230[current_230] = i;
		}
		bucket_230[i] = current_230;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_230[i];
		B2_count[idx2]--;
	}
	free(bucket_230);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_230[perm[i]]] = C_coords_scratch[i];
		quotient_230[perm[i]] ++;
	}
	free(quotient_230);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [3, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1)
int transpose_coo_3021_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Fix and sort on [3, 0]
	// Create buckets and quotient
	int *bucket_230 = (int *)malloc(c_size*sizeof(int));
	int *quotient_230 = (int *)malloc(c_size*sizeof(int));
	int current_230 = 0;
	bucket_230[0] = 0;
	quotient_230[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_230++;
			quotient_230[current_230] = i;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_230++;
			quotient_230[current_230] = i;
		}
		bucket_230[i] = current_230;
	}

	// Histogram sort on mode 2 into the permutation array
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_230[i];
		B2_count[idx2]--;
	}
	free(bucket_230);

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_230[perm[i]]] = C_coords_scratch[i];
		quotient_230[perm[i]] ++;
	}
	free(quotient_230);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, [3, 0])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2)
int transpose_coo_3102_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 1, 0, 2)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3102);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2)
int transpose_coo_3102_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_102);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2)
int transpose_coo_3102_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_02);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2)
int transpose_coo_3102_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_2);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2)
int transpose_coo_3102_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0)
int transpose_coo_3120_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 1, 2, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3120);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0)
int transpose_coo_3120_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_120);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0)
int transpose_coo_3120_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_20);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0)
int transpose_coo_3120_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0)
int transpose_coo_3120_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1)
int transpose_coo_3201_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 2, 0, 1)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3201);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1)
int transpose_coo_3201_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_201);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1)
int transpose_coo_3201_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_01);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1)
int transpose_coo_3201_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_1);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1)
int transpose_coo_3201_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0)
int transpose_coo_3210_k0(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();

	// Sort the coordinates to be in (3, 2, 1, 0)
	// Use qsort to sort the subtrees
	qsort(C_coords, c_size, sizeof(struct coo_t), cmp_3210);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0)
int transpose_coo_3210_k1(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_210);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0)
int transpose_coo_3210_k2(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_10);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0)
int transpose_coo_3210_k3(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Use qsort to sort the subtrees
	int qsort_start = 0;
	for(int i = 1; i < c_size; i ++)
	{
		int qsort_same = 1;
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			qsort_same = 0;
		}
		else if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			qsort_same = 0;
		}
		if (!qsort_same || i == c_size - 1) { // Sort if at the end of a segment
			qsort(&C_coords[qsort_start], (i - qsort_start), sizeof(struct coo_t), cmp_0);
			qsort_start = i;
		}
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0)
int transpose_coo_3210_k4(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 < B1_size; idx1 ++)
	{
		B1_count[idx1] += B1_count[idx1 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx1 = C_coords[i].idx1;
		int idx = B1_count[idx1] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B1_count[idx1]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B1_count);

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 < B2_size; idx2 ++)
	{
		B2_count[idx2] += B2_count[idx2 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx2 = C_coords[i].idx2;
		int idx = B2_count[idx2] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B2_count[idx2]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B2_count);

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 < B3_size; idx3 ++)
	{
		B3_count[idx3] += B3_count[idx3 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx3 = C_coords[i].idx3;
		int idx = B3_count[idx3] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B3_count[idx3]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B3_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}

int main(int argc, char* argv[]) {
  char *p;
  int TOTAL;
  int SPLIT;
  long conv = strtol(argv[1], &p, 10);

  TOTAL = conv;

  conv = strtol(argv[2], &p, 10);
  SPLIT = conv;
   std::string filename = argv[3];

  // Read tensor data  
  int order = 4;
  int * dimensions = (int*)malloc(sizeof(int)*order);
  memset(dimensions, 0, sizeof(int)*order);
  
  int32_t init_alloc_size = 1048576;
  int32_t A_capacity = init_alloc_size;
  struct coo_t *A = (struct coo_t *)malloc(sizeof(struct coo_t)* A_capacity);

  std::fstream stream;
  util::openStream(stream, filename, fstream::in);

  std::string line;
  if (!std::getline(stream, line)) {
    return -1;
  }


  int size = 0;

  do {
      if(size >= A_capacity){
          int32_t A_capacity_new = 2 * (A_capacity);
          A = (struct coo_t*)realloc(A, sizeof(struct coo_t) * A_capacity_new);
          A_capacity = A_capacity_new;
        }

    char* linePtr = (char*)line.data();

    // Generated by coo/gen_taco_to_list.py

	long idx0 = strtol(linePtr, &linePtr, 10);
	A[size].idx0 = (int32_t)idx0 - 1;
	dimensions[0] = std::max(dimensions[0], (int)idx0 - 1);
	long idx1 = strtol(linePtr, &linePtr, 10);
	A[size].idx1 = (int32_t)idx1 - 1;
	dimensions[1] = std::max(dimensions[1], (int)idx1 - 1);
	long idx2 = strtol(linePtr, &linePtr, 10);
	A[size].idx2 = (int32_t)idx2 - 1;
	dimensions[2] = std::max(dimensions[2], (int)idx2 - 1);
	long idx3 = strtol(linePtr, &linePtr, 10);
	A[size].idx3 = (int32_t)idx3 - 1;
	dimensions[3] = std::max(dimensions[3], (int)idx3 - 1);

    double val = strtod(linePtr, &linePtr);
    A[size].val = val;
    size ++;

  } while (std::getline(stream, line));

  stream.close();

		if(0 % TOTAL == SPLIT){
		cout << "0123, 0, 0" ;
		// (0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0123_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(1 % TOTAL == SPLIT){
		cout << "0123, 1, 0" ;
		// (0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0123_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(2 % TOTAL == SPLIT){
		cout << "0123, 2, 0" ;
		// (0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0123_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(3 % TOTAL == SPLIT){
		cout << "0123, 3, 0" ;
		// (0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0123_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(4 % TOTAL == SPLIT){
		cout << "0123, 4, 0" ;
		// (0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0123_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(5 % TOTAL == SPLIT){
		cout << "0132, 0, 0" ;
		// (0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0132_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(6 % TOTAL == SPLIT){
		cout << "0132, 1, 0" ;
		// (0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0132_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(7 % TOTAL == SPLIT){
		cout << "0132, 2, 0" ;
		// (0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0132_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(8 % TOTAL == SPLIT){
		cout << "0132, 3, 1" ;
		// (0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0132_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(9 % TOTAL == SPLIT){
		cout << "0132, 4, 1" ;
		// (0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0132_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(10 % TOTAL == SPLIT){
		cout << "0213, 0, 0" ;
		// (0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0213_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(11 % TOTAL == SPLIT){
		cout << "0213, 1, 0" ;
		// (0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0213_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(12 % TOTAL == SPLIT){
		cout << "0213, 2, 1" ;
		// (0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0213_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(13 % TOTAL == SPLIT){
		cout << "0213, 3, 1" ;
		// (0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0213_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(14 % TOTAL == SPLIT){
		cout << "0213, 4, 1" ;
		// (0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0213_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(15 % TOTAL == SPLIT){
		cout << "0231, 0, 0" ;
		// (0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0231_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(16 % TOTAL == SPLIT){
		cout << "0231, 1, 0" ;
		// (0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0231_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(17 % TOTAL == SPLIT){
		cout << "0231, 2, 1" ;
		// (0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0231_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(18 % TOTAL == SPLIT){
		cout << "0231, 3, 2" ;
		// (0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0231_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(19 % TOTAL == SPLIT){
		cout << "0231, 4, 2" ;
		// (0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0231_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(20 % TOTAL == SPLIT){
		cout << "0312, 0, 0" ;
		// (0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0312_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(21 % TOTAL == SPLIT){
		cout << "0312, 1, 0" ;
		// (0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0312_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(22 % TOTAL == SPLIT){
		cout << "0312, 2, 1" ;
		// (0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0312_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(23 % TOTAL == SPLIT){
		cout << "0312, 3, 1" ;
		// (0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0312_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(24 % TOTAL == SPLIT){
		cout << "0312, 4, 1" ;
		// (0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0312_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(25 % TOTAL == SPLIT){
		cout << "0321, 0, 0" ;
		// (0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0321_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(26 % TOTAL == SPLIT){
		cout << "0321, 1, 0" ;
		// (0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0321_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(27 % TOTAL == SPLIT){
		cout << "0321, 2, 1" ;
		// (0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0321_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(28 % TOTAL == SPLIT){
		cout << "0321, 3, 2" ;
		// (0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0321_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(29 % TOTAL == SPLIT){
		cout << "0321, 4, 2" ;
		// (0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_0321_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(30 % TOTAL == SPLIT){
		cout << "1023, 0, 0" ;
		// (1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1023_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(31 % TOTAL == SPLIT){
		cout << "1023, 1, 1" ;
		// (1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1023_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(32 % TOTAL == SPLIT){
		cout << "1023, 2, 1" ;
		// (1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1023_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(33 % TOTAL == SPLIT){
		cout << "1023, 3, 1" ;
		// (1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1023_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(34 % TOTAL == SPLIT){
		cout << "1023, 4, 1" ;
		// (1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1023_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(35 % TOTAL == SPLIT){
		cout << "1032, 0, 0" ;
		// (1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1032_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(36 % TOTAL == SPLIT){
		cout << "1032, 1, 1" ;
		// (1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1032_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(37 % TOTAL == SPLIT){
		cout << "1032, 2, 1" ;
		// (1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1032_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(38 % TOTAL == SPLIT){
		cout << "1032, 3, 2" ;
		// (1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1032_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(39 % TOTAL == SPLIT){
		cout << "1032, 4, 2" ;
		// (1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1032_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(40 % TOTAL == SPLIT){
		cout << "1203, 0, 0" ;
		// (1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1203_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(41 % TOTAL == SPLIT){
		cout << "1203, 1, 1" ;
		// (1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1203_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(42 % TOTAL == SPLIT){
		cout << "1203, 2, 2" ;
		// (1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1203_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(43 % TOTAL == SPLIT){
		cout << "1203, 3, 2" ;
		// (1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1203_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(44 % TOTAL == SPLIT){
		cout << "1203, 4, 2" ;
		// (1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1203_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(45 % TOTAL == SPLIT){
		cout << "1230, 0, 0" ;
		// (1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1230_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(46 % TOTAL == SPLIT){
		cout << "1230, 1, 1" ;
		// (1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1230_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(47 % TOTAL == SPLIT){
		cout << "1230, 2, 2" ;
		// (1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1230_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(48 % TOTAL == SPLIT){
		cout << "1230, 3, 3" ;
		// (1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1230_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(49 % TOTAL == SPLIT){
		cout << "1230, 4, 3" ;
		// (1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1230_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(50 % TOTAL == SPLIT){
		cout << "1302, 0, 0" ;
		// (1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1302_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(51 % TOTAL == SPLIT){
		cout << "1302, 1, 1" ;
		// (1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1302_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(52 % TOTAL == SPLIT){
		cout << "1302, 2, 2" ;
		// (1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1302_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(53 % TOTAL == SPLIT){
		cout << "1302, 3, 2" ;
		// (1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1302_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(54 % TOTAL == SPLIT){
		cout << "1302, 4, 2" ;
		// (1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1302_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(55 % TOTAL == SPLIT){
		cout << "1320, 0, 0" ;
		// (1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1320_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(56 % TOTAL == SPLIT){
		cout << "1320, 1, 1" ;
		// (1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1320_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(57 % TOTAL == SPLIT){
		cout << "1320, 2, 2" ;
		// (1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1320_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(58 % TOTAL == SPLIT){
		cout << "1320, 3, 3" ;
		// (1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1320_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(59 % TOTAL == SPLIT){
		cout << "1320, 4, 3" ;
		// (1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_1320_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(60 % TOTAL == SPLIT){
		cout << "2013, 0, 0" ;
		// (2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2013_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(61 % TOTAL == SPLIT){
		cout << "2013, 1, 1" ;
		// (2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2013_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(62 % TOTAL == SPLIT){
		cout << "2013, 2, 1" ;
		// (2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2013_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(63 % TOTAL == SPLIT){
		cout << "2013, 3, 1" ;
		// (2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2013_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(64 % TOTAL == SPLIT){
		cout << "2013, 4, 1" ;
		// (2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2013_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(65 % TOTAL == SPLIT){
		cout << "2031, 0, 0" ;
		// (2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2031_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(66 % TOTAL == SPLIT){
		cout << "2031, 1, 1" ;
		// (2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2031_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(67 % TOTAL == SPLIT){
		cout << "2031, 2, 1" ;
		// (2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2031_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(68 % TOTAL == SPLIT){
		cout << "2031, 3, 2" ;
		// (2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2031_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(69 % TOTAL == SPLIT){
		cout << "2031, 4, 2" ;
		// (2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2031_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(70 % TOTAL == SPLIT){
		cout << "2103, 0, 0" ;
		// (2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2103_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(71 % TOTAL == SPLIT){
		cout << "2103, 1, 1" ;
		// (2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2103_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(72 % TOTAL == SPLIT){
		cout << "2103, 2, 2" ;
		// (2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2103_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(73 % TOTAL == SPLIT){
		cout << "2103, 3, 2" ;
		// (2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2103_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(74 % TOTAL == SPLIT){
		cout << "2103, 4, 2" ;
		// (2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2103_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(75 % TOTAL == SPLIT){
		cout << "2130, 0, 0" ;
		// (2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2130_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(76 % TOTAL == SPLIT){
		cout << "2130, 1, 1" ;
		// (2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2130_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(77 % TOTAL == SPLIT){
		cout << "2130, 2, 2" ;
		// (2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2130_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(78 % TOTAL == SPLIT){
		cout << "2130, 3, 3" ;
		// (2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2130_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(79 % TOTAL == SPLIT){
		cout << "2130, 4, 3" ;
		// (2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2130_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(80 % TOTAL == SPLIT){
		cout << "2301, 0, 0" ;
		// (2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2301_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(81 % TOTAL == SPLIT){
		cout << "2301, 1, 1" ;
		// (2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2301_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(82 % TOTAL == SPLIT){
		cout << "2301, 2, 2" ;
		// (2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2301_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(83 % TOTAL == SPLIT){
		cout << "2301, 3, 2" ;
		// (2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2301_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(84 % TOTAL == SPLIT){
		cout << "2301, 4, 2" ;
		// (2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2301_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(85 % TOTAL == SPLIT){
		cout << "2310, 0, 0" ;
		// (2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2310_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(86 % TOTAL == SPLIT){
		cout << "2310, 1, 1" ;
		// (2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2310_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(87 % TOTAL == SPLIT){
		cout << "2310, 2, 2" ;
		// (2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2310_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(88 % TOTAL == SPLIT){
		cout << "2310, 3, 3" ;
		// (2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2310_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(89 % TOTAL == SPLIT){
		cout << "2310, 4, 3" ;
		// (2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_2310_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(90 % TOTAL == SPLIT){
		cout << "3012, 0, 0" ;
		// (3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3012_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(91 % TOTAL == SPLIT){
		cout << "3012, 1, 1" ;
		// (3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3012_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(92 % TOTAL == SPLIT){
		cout << "3012, 2, 1" ;
		// (3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3012_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(93 % TOTAL == SPLIT){
		cout << "3012, 3, 1" ;
		// (3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3012_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(94 % TOTAL == SPLIT){
		cout << "3012, 4, 1" ;
		// (3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3012_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(95 % TOTAL == SPLIT){
		cout << "3021, 0, 0" ;
		// (3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3021_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(96 % TOTAL == SPLIT){
		cout << "3021, 1, 1" ;
		// (3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3021_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(97 % TOTAL == SPLIT){
		cout << "3021, 2, 1" ;
		// (3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3021_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(98 % TOTAL == SPLIT){
		cout << "3021, 3, 2" ;
		// (3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3021_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(99 % TOTAL == SPLIT){
		cout << "3021, 4, 2" ;
		// (3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3021_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(100 % TOTAL == SPLIT){
		cout << "3102, 0, 0" ;
		// (3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3102_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(101 % TOTAL == SPLIT){
		cout << "3102, 1, 1" ;
		// (3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3102_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(102 % TOTAL == SPLIT){
		cout << "3102, 2, 2" ;
		// (3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3102_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(103 % TOTAL == SPLIT){
		cout << "3102, 3, 2" ;
		// (3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3102_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(104 % TOTAL == SPLIT){
		cout << "3102, 4, 2" ;
		// (3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3102_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(105 % TOTAL == SPLIT){
		cout << "3120, 0, 0" ;
		// (3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3120_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(106 % TOTAL == SPLIT){
		cout << "3120, 1, 1" ;
		// (3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3120_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(107 % TOTAL == SPLIT){
		cout << "3120, 2, 2" ;
		// (3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3120_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(108 % TOTAL == SPLIT){
		cout << "3120, 3, 3" ;
		// (3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3120_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(109 % TOTAL == SPLIT){
		cout << "3120, 4, 3" ;
		// (3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3120_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(110 % TOTAL == SPLIT){
		cout << "3201, 0, 0" ;
		// (3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3201_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(111 % TOTAL == SPLIT){
		cout << "3201, 1, 1" ;
		// (3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3201_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(112 % TOTAL == SPLIT){
		cout << "3201, 2, 2" ;
		// (3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3201_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(113 % TOTAL == SPLIT){
		cout << "3201, 3, 2" ;
		// (3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3201_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(114 % TOTAL == SPLIT){
		cout << "3201, 4, 2" ;
		// (3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3201_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(115 % TOTAL == SPLIT){
		cout << "3210, 0, 0" ;
		// (3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3210_k0(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(116 % TOTAL == SPLIT){
		cout << "3210, 1, 1" ;
		// (3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3210_k1(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(117 % TOTAL == SPLIT){
		cout << "3210, 2, 2" ;
		// (3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3210_k2(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(118 % TOTAL == SPLIT){
		cout << "3210, 3, 3" ;
		// (3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3210_k3(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(119 % TOTAL == SPLIT){
		cout << "3210, 4, 3" ;
		// (3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_0123);
			transpose_coo_3210_k4(A, size, order, dimensions);
		}
		cout << endl;

		}
	free(A);
	free(dimensions);
}
