
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
	int32_t	idx4;
	double	val;
};


using namespace taco;
int cmp_01234(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_01243(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_01324(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_01342(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_01423(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_01432(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_02134(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_02143(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_02314(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_02341(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_02413(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_02431(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_03124(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_03142(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_03214(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_03241(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_03412(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_03421(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04123(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04132(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04213(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04231(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04312(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_04321(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_10234(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_10243(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_10324(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_10342(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_10423(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_10432(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_12034(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_12043(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_12304(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_12340(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_12403(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_12430(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_13024(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_13042(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_13204(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_13240(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_13402(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_13420(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14023(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14032(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14203(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14230(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14302(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_14320(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_20134(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_20143(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_20314(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_20341(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_20413(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_20431(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_21034(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_21043(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_21304(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_21340(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_21403(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_21430(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_23014(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_23041(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_23104(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_23140(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_23401(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_23410(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24013(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24031(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24103(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24130(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24301(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_24310(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_30124(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_30142(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_30214(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_30241(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_30412(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_30421(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_31024(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_31042(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_31204(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_31240(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_31402(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_31420(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_32014(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_32041(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_32104(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	return 0;
}
int cmp_32140(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
		return 1;
	}
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_32401(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_32410(const void *p, const void *q)
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
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34012(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34021(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34102(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34120(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34201(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_34210(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
int cmp_40123(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_40132(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_40213(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_40231(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_40312(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_40321(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_41023(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_41032(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_41203(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_41230(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_41302(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_41320(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_42013(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_42031(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_42103(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx3 < s->idx3) {
		return -1;
	} else if (r->idx3 > s->idx3) {
		return 1;
	}
	return 0;
}
int cmp_42130(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_42301(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_42310(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_43012(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_43021(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_43102(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx2 < s->idx2) {
		return -1;
	} else if (r->idx2 > s->idx2) {
		return 1;
	}
	return 0;
}
int cmp_43120(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
int cmp_43201(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx1 < s->idx1) {
		return -1;
	} else if (r->idx1 > s->idx1) {
		return 1;
	}
	return 0;
}
int cmp_43210(const void *p, const void *q)
{
	struct coo_t * r = (struct coo_t *)p;
	struct coo_t * s = (struct coo_t *)q;
	if(r->idx4 < s->idx4) {
		return -1;
	} else if (r->idx4 > s->idx4) {
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
	if(r->idx0 < s->idx0) {
		return -1;
	} else if (r->idx0 > s->idx0) {
		return 1;
	}
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 3, 4)
int transpose_coo_01234_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 2, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (3, []), (2, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 4, 3)
int transpose_coo_01243_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 2, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (4, []), (2, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2, 4)
int transpose_coo_01324_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (2, []), (3, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 4, 2)
int transpose_coo_01342_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (4, []), (3, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 4, 2, 3)
int transpose_coo_01423_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 4, 2, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (4, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 4, 3, 2)
int transpose_coo_01432_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 4, 3, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (4, []), (1, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3, 4)
int transpose_coo_02134_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (3, []), (1, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 4, 3)
int transpose_coo_02143_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (4, []), (1, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1, 4)
int transpose_coo_02314_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (1, []), (3, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 4, 1)
int transpose_coo_02341_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (4, []), (3, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 4, 1, 3)
int transpose_coo_02413_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 4, 1, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (4, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 4, 3, 1)
int transpose_coo_02431_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 4, 3, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (4, []), (2, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2, 4)
int transpose_coo_03124_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (2, []), (1, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 4, 2)
int transpose_coo_03142_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (4, []), (1, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1, 4)
int transpose_coo_03214_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(4, []), (1, []), (2, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 4, 1)
int transpose_coo_03241_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (4, []), (2, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 4, 1, 2)
int transpose_coo_03412_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 4, 1, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (4, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 4, 2, 1)
int transpose_coo_03421_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 4, 2, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (4, []), (3, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 1, 2, 3)
int transpose_coo_04123_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 1, 2, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (1, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 1, 3, 2)
int transpose_coo_04132_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 1, 3, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (1, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 2, 1, 3)
int transpose_coo_04213_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 2, 1, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (2, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 2, 3, 1)
int transpose_coo_04231_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 2, 3, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (2, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 3, 1, 2)
int transpose_coo_04312_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 3, 1, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (3, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 3, 2, 1)
int transpose_coo_04321_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 3, 2, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (3, []), (4, []), (0, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3, 4)
int transpose_coo_10234_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (3, []), (2, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 4, 3)
int transpose_coo_10243_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (4, []), (2, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2, 4)
int transpose_coo_10324_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (2, []), (3, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 4, 2)
int transpose_coo_10342_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (4, []), (3, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 4, 2, 3)
int transpose_coo_10423_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 4, 2, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (2, []), (4, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 4, 3, 2)
int transpose_coo_10432_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 4, 3, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (3, []), (4, []), (0, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3, 4)
int transpose_coo_12034_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (3, []), (0, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 4, 3)
int transpose_coo_12043_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (4, []), (0, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0, 4)
int transpose_coo_12304_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (3, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 4, 0)
int transpose_coo_12340_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (3, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 4, 0, 3)
int transpose_coo_12403_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 4, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (0, []), (4, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 4, 3, 0)
int transpose_coo_12430_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 4, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (3, []), (4, []), (2, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2, 4)
int transpose_coo_13024_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (2, []), (0, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 4, 2)
int transpose_coo_13042_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (4, []), (0, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0, 4)
int transpose_coo_13204_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (2, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 4, 0)
int transpose_coo_13240_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (2, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 4, 0, 2)
int transpose_coo_13402_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 4, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (0, []), (4, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 4, 2, 0)
int transpose_coo_13420_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 4, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (2, []), (4, []), (3, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 0, 2, 3)
int transpose_coo_14023_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 0, 2, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (2, []), (0, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 0, 3, 2)
int transpose_coo_14032_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 0, 3, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (3, []), (0, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 2, 0, 3)
int transpose_coo_14203_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 2, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (0, []), (2, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 2, 3, 0)
int transpose_coo_14230_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 2, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (3, []), (2, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 3, 0, 2)
int transpose_coo_14302_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 3, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (0, []), (3, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 3, 2, 0)
int transpose_coo_14320_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 3, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (2, []), (3, []), (4, []), (1, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3, 4)
int transpose_coo_20134_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (3, []), (1, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 4, 3)
int transpose_coo_20143_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (4, []), (1, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1, 4)
int transpose_coo_20314_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (1, []), (3, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 4, 1)
int transpose_coo_20341_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (4, []), (3, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 4, 1, 3)
int transpose_coo_20413_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 4, 1, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (1, []), (4, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 4, 3, 1)
int transpose_coo_20431_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 4, 3, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (3, []), (4, []), (0, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3, 4)
int transpose_coo_21034_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (3, []), (0, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 4, 3)
int transpose_coo_21043_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 4, 3)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(3, []), (4, []), (0, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0, 4)
int transpose_coo_21304_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (3, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 4, 0)
int transpose_coo_21340_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (3, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 4, 0, 3)
int transpose_coo_21403_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 4, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (0, []), (4, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 4, 3, 0)
int transpose_coo_21430_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 4, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (3, []), (4, []), (1, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1, 4)
int transpose_coo_23014_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (1, []), (0, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 4, 1)
int transpose_coo_23041_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (4, []), (0, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0, 4)
int transpose_coo_23104_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (1, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 4, 0)
int transpose_coo_23140_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (1, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 4, 0, 1)
int transpose_coo_23401_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 4, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (0, []), (4, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 4, 1, 0)
int transpose_coo_23410_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 4, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (1, []), (4, []), (3, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 0, 1, 3)
int transpose_coo_24013_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 0, 1, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (1, []), (0, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 0, 3, 1)
int transpose_coo_24031_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 0, 3, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (3, []), (0, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 1, 0, 3)
int transpose_coo_24103_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 1, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(3, []), (0, []), (1, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 1, 3, 0)
int transpose_coo_24130_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 1, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (3, []), (1, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 3, 0, 1)
int transpose_coo_24301_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 3, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (0, []), (3, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 3, 1, 0)
int transpose_coo_24310_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 3, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (1, []), (3, []), (4, []), (2, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2, 4)
int transpose_coo_30124_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (2, []), (1, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 4, 2)
int transpose_coo_30142_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (4, []), (1, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1, 4)
int transpose_coo_30214_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (1, []), (2, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 4, 1)
int transpose_coo_30241_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (4, []), (2, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 4, 1, 2)
int transpose_coo_30412_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 4, 1, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (1, []), (4, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 4, 2, 1)
int transpose_coo_30421_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 4, 2, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (2, []), (4, []), (0, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2, 4)
int transpose_coo_31024_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (2, []), (0, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 4, 2)
int transpose_coo_31042_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 4, 2)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(2, []), (4, []), (0, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0, 4)
int transpose_coo_31204_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (2, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 4, 0)
int transpose_coo_31240_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (2, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 4, 0, 2)
int transpose_coo_31402_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 4, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (0, []), (4, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 4, 2, 0)
int transpose_coo_31420_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 4, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (2, []), (4, []), (1, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1, 4)
int transpose_coo_32014_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (1, []), (0, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 4, 1)
int transpose_coo_32041_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 4, 1)

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(1, []), (4, []), (0, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0, 4)
int transpose_coo_32104_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0, 4)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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
	cout << " ,  [(4, []), (0, []), (1, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 4, 0)
int transpose_coo_32140_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 4, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (4, []), (1, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 4, 0, 1)
int transpose_coo_32401_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 4, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (0, []), (4, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 4, 1, 0)
int transpose_coo_32410_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 4, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (1, []), (4, []), (2, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 0, 1, 2)
int transpose_coo_34012_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 0, 1, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (1, []), (0, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 0, 2, 1)
int transpose_coo_34021_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 0, 2, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (2, []), (0, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 1, 0, 2)
int transpose_coo_34102_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 1, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(2, []), (0, []), (1, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 1, 2, 0)
int transpose_coo_34120_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 1, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (2, []), (1, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 2, 0, 1)
int transpose_coo_34201_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 2, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(1, []), (0, []), (2, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 2, 1, 0)
int transpose_coo_34210_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 2, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);

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
	cout << " ,  [(0, []), (1, []), (2, []), (4, []), (3, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 1, 2, 3)
int transpose_coo_40123_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 1, 2, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (1, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 1, 3, 2)
int transpose_coo_40132_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 1, 3, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (1, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 2, 1, 3)
int transpose_coo_40213_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 2, 1, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (2, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 2, 3, 1)
int transpose_coo_40231_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 2, 3, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (2, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 3, 1, 2)
int transpose_coo_40312_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 3, 1, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (3, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 3, 2, 1)
int transpose_coo_40321_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 3, 2, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (3, []), (0, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 0, 2, 3)
int transpose_coo_41023_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 0, 2, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (2, []), (0, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 0, 3, 2)
int transpose_coo_41032_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 0, 3, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (3, []), (0, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 2, 0, 3)
int transpose_coo_41203_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 2, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (0, []), (2, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 2, 3, 0)
int transpose_coo_41230_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 2, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (3, []), (2, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 3, 0, 2)
int transpose_coo_41302_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 3, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (0, []), (3, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 3, 2, 0)
int transpose_coo_41320_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 3, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (2, []), (3, []), (1, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 0, 1, 3)
int transpose_coo_42013_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 0, 1, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (1, []), (0, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 0, 3, 1)
int transpose_coo_42031_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 0, 3, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (3, []), (0, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 1, 0, 3)
int transpose_coo_42103_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 1, 0, 3)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(3, []), (0, []), (1, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 1, 3, 0)
int transpose_coo_42130_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 1, 3, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (3, []), (1, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 3, 0, 1)
int transpose_coo_42301_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 3, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (0, []), (3, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 3, 1, 0)
int transpose_coo_42310_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 3, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (1, []), (3, []), (2, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 0, 1, 2)
int transpose_coo_43012_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 0, 1, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (1, []), (0, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 0, 2, 1)
int transpose_coo_43021_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 0, 2, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (2, []), (0, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 1, 0, 2)
int transpose_coo_43102_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 1, 0, 2)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(2, []), (0, []), (1, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 1, 2, 0)
int transpose_coo_43120_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 1, 2, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (2, []), (1, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 2, 0, 1)
int transpose_coo_43201_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 2, 0, 1)

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

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(1, []), (0, []), (2, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 2, 1, 0)
int transpose_coo_43210_all(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	taco::util::Timer timer;
	timer.start();
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 2, 1, 0)

	// Histogram sort on mode 0
	int B0_size = dimensions[0];
	int32_t *B0_count = (int32_t *)calloc(B0_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx0 = C_coords[i].idx0;
		B0_count[idx0]++;
	}

	// Prefix sum over B0_count
	for(int idx0 = 1; idx0 < B0_size; idx0 ++)
	{
		B0_count[idx0] += B0_count[idx0 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx0 = C_coords[i].idx0;
		int idx = B0_count[idx0] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B0_count[idx0]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B0_count);

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

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 < B4_size; idx4 ++)
	{
		B4_count[idx4] += B4_count[idx4 - 1];
	}
	for( int i = c_size - 1; i >= 0; i--)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		B4_count[idx4]--;
	}

	memcpy(C_coords, C_coords_scratch, c_size*sizeof(struct coo_t));


	free(B4_count);
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	timer.stop();
	taco::util::TimeResults res = timer.getResult();
	cout << " ,  [(0, []), (1, []), (2, []), (3, []), (4, [])] ";
	cout << " , "<< res ;
	return 0;
}

int main(int argc, char* argv[]) {
  std::string filename = "./lbnl-network.tns";
  char *p;
  int TOTAL;
  int SPLIT;
  long conv = strtol(argv[1], &p, 10);

  TOTAL = conv;

  conv = strtol(argv[2], &p, 10);
  SPLIT = conv;
  // Read tensor data  
  int order = 5;
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
	long idx4 = strtol(linePtr, &linePtr, 10);
	A[size].idx4 = (int32_t)idx4 - 1;
	dimensions[4] = std::max(dimensions[4], (int)idx4 - 1);

    double val = strtod(linePtr, &linePtr);
    A[size].val = val;
    size ++;

  } while (std::getline(stream, line));

  stream.close();

		if(0 % TOTAL == SPLIT){
		cout << "01234, 5, 5" ;
		// (0, 1, 2, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01234_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(1 % TOTAL == SPLIT){
		cout << "01243, 5, 5" ;
		// (0, 1, 2, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01243_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(2 % TOTAL == SPLIT){
		cout << "01324, 5, 5" ;
		// (0, 1, 3, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01324_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(3 % TOTAL == SPLIT){
		cout << "01342, 5, 5" ;
		// (0, 1, 3, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01342_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(4 % TOTAL == SPLIT){
		cout << "01423, 5, 5" ;
		// (0, 1, 4, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01423_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(5 % TOTAL == SPLIT){
		cout << "01432, 5, 5" ;
		// (0, 1, 4, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_01432_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(6 % TOTAL == SPLIT){
		cout << "02134, 5, 5" ;
		// (0, 2, 1, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02134_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(7 % TOTAL == SPLIT){
		cout << "02143, 5, 5" ;
		// (0, 2, 1, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02143_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(8 % TOTAL == SPLIT){
		cout << "02314, 5, 5" ;
		// (0, 2, 3, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02314_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(9 % TOTAL == SPLIT){
		cout << "02341, 5, 5" ;
		// (0, 2, 3, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02341_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(10 % TOTAL == SPLIT){
		cout << "02413, 5, 5" ;
		// (0, 2, 4, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02413_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(11 % TOTAL == SPLIT){
		cout << "02431, 5, 5" ;
		// (0, 2, 4, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_02431_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(12 % TOTAL == SPLIT){
		cout << "03124, 5, 5" ;
		// (0, 3, 1, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03124_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(13 % TOTAL == SPLIT){
		cout << "03142, 5, 5" ;
		// (0, 3, 1, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03142_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(14 % TOTAL == SPLIT){
		cout << "03214, 5, 5" ;
		// (0, 3, 2, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03214_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(15 % TOTAL == SPLIT){
		cout << "03241, 5, 5" ;
		// (0, 3, 2, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03241_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(16 % TOTAL == SPLIT){
		cout << "03412, 5, 5" ;
		// (0, 3, 4, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03412_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(17 % TOTAL == SPLIT){
		cout << "03421, 5, 5" ;
		// (0, 3, 4, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_03421_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(18 % TOTAL == SPLIT){
		cout << "04123, 5, 5" ;
		// (0, 4, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04123_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(19 % TOTAL == SPLIT){
		cout << "04132, 5, 5" ;
		// (0, 4, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04132_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(20 % TOTAL == SPLIT){
		cout << "04213, 5, 5" ;
		// (0, 4, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04213_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(21 % TOTAL == SPLIT){
		cout << "04231, 5, 5" ;
		// (0, 4, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04231_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(22 % TOTAL == SPLIT){
		cout << "04312, 5, 5" ;
		// (0, 4, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04312_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(23 % TOTAL == SPLIT){
		cout << "04321, 5, 5" ;
		// (0, 4, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_04321_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(24 % TOTAL == SPLIT){
		cout << "10234, 5, 5" ;
		// (1, 0, 2, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10234_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(25 % TOTAL == SPLIT){
		cout << "10243, 5, 5" ;
		// (1, 0, 2, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10243_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(26 % TOTAL == SPLIT){
		cout << "10324, 5, 5" ;
		// (1, 0, 3, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10324_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(27 % TOTAL == SPLIT){
		cout << "10342, 5, 5" ;
		// (1, 0, 3, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10342_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(28 % TOTAL == SPLIT){
		cout << "10423, 5, 5" ;
		// (1, 0, 4, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10423_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(29 % TOTAL == SPLIT){
		cout << "10432, 5, 5" ;
		// (1, 0, 4, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_10432_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(30 % TOTAL == SPLIT){
		cout << "12034, 5, 5" ;
		// (1, 2, 0, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12034_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(31 % TOTAL == SPLIT){
		cout << "12043, 5, 5" ;
		// (1, 2, 0, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12043_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(32 % TOTAL == SPLIT){
		cout << "12304, 5, 5" ;
		// (1, 2, 3, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12304_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(33 % TOTAL == SPLIT){
		cout << "12340, 5, 5" ;
		// (1, 2, 3, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12340_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(34 % TOTAL == SPLIT){
		cout << "12403, 5, 5" ;
		// (1, 2, 4, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12403_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(35 % TOTAL == SPLIT){
		cout << "12430, 5, 5" ;
		// (1, 2, 4, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_12430_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(36 % TOTAL == SPLIT){
		cout << "13024, 5, 5" ;
		// (1, 3, 0, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13024_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(37 % TOTAL == SPLIT){
		cout << "13042, 5, 5" ;
		// (1, 3, 0, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13042_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(38 % TOTAL == SPLIT){
		cout << "13204, 5, 5" ;
		// (1, 3, 2, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13204_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(39 % TOTAL == SPLIT){
		cout << "13240, 5, 5" ;
		// (1, 3, 2, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13240_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(40 % TOTAL == SPLIT){
		cout << "13402, 5, 5" ;
		// (1, 3, 4, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13402_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(41 % TOTAL == SPLIT){
		cout << "13420, 5, 5" ;
		// (1, 3, 4, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_13420_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(42 % TOTAL == SPLIT){
		cout << "14023, 5, 5" ;
		// (1, 4, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14023_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(43 % TOTAL == SPLIT){
		cout << "14032, 5, 5" ;
		// (1, 4, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14032_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(44 % TOTAL == SPLIT){
		cout << "14203, 5, 5" ;
		// (1, 4, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14203_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(45 % TOTAL == SPLIT){
		cout << "14230, 5, 5" ;
		// (1, 4, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14230_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(46 % TOTAL == SPLIT){
		cout << "14302, 5, 5" ;
		// (1, 4, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14302_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(47 % TOTAL == SPLIT){
		cout << "14320, 5, 5" ;
		// (1, 4, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_14320_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(48 % TOTAL == SPLIT){
		cout << "20134, 5, 5" ;
		// (2, 0, 1, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20134_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(49 % TOTAL == SPLIT){
		cout << "20143, 5, 5" ;
		// (2, 0, 1, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20143_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(50 % TOTAL == SPLIT){
		cout << "20314, 5, 5" ;
		// (2, 0, 3, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20314_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(51 % TOTAL == SPLIT){
		cout << "20341, 5, 5" ;
		// (2, 0, 3, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20341_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(52 % TOTAL == SPLIT){
		cout << "20413, 5, 5" ;
		// (2, 0, 4, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20413_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(53 % TOTAL == SPLIT){
		cout << "20431, 5, 5" ;
		// (2, 0, 4, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_20431_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(54 % TOTAL == SPLIT){
		cout << "21034, 5, 5" ;
		// (2, 1, 0, 3, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21034_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(55 % TOTAL == SPLIT){
		cout << "21043, 5, 5" ;
		// (2, 1, 0, 4, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21043_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(56 % TOTAL == SPLIT){
		cout << "21304, 5, 5" ;
		// (2, 1, 3, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21304_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(57 % TOTAL == SPLIT){
		cout << "21340, 5, 5" ;
		// (2, 1, 3, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21340_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(58 % TOTAL == SPLIT){
		cout << "21403, 5, 5" ;
		// (2, 1, 4, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21403_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(59 % TOTAL == SPLIT){
		cout << "21430, 5, 5" ;
		// (2, 1, 4, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_21430_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(60 % TOTAL == SPLIT){
		cout << "23014, 5, 5" ;
		// (2, 3, 0, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23014_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(61 % TOTAL == SPLIT){
		cout << "23041, 5, 5" ;
		// (2, 3, 0, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23041_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(62 % TOTAL == SPLIT){
		cout << "23104, 5, 5" ;
		// (2, 3, 1, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23104_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(63 % TOTAL == SPLIT){
		cout << "23140, 5, 5" ;
		// (2, 3, 1, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23140_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(64 % TOTAL == SPLIT){
		cout << "23401, 5, 5" ;
		// (2, 3, 4, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23401_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(65 % TOTAL == SPLIT){
		cout << "23410, 5, 5" ;
		// (2, 3, 4, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_23410_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(66 % TOTAL == SPLIT){
		cout << "24013, 5, 5" ;
		// (2, 4, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24013_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(67 % TOTAL == SPLIT){
		cout << "24031, 5, 5" ;
		// (2, 4, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24031_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(68 % TOTAL == SPLIT){
		cout << "24103, 5, 5" ;
		// (2, 4, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24103_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(69 % TOTAL == SPLIT){
		cout << "24130, 5, 5" ;
		// (2, 4, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24130_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(70 % TOTAL == SPLIT){
		cout << "24301, 5, 5" ;
		// (2, 4, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24301_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(71 % TOTAL == SPLIT){
		cout << "24310, 5, 5" ;
		// (2, 4, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_24310_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(72 % TOTAL == SPLIT){
		cout << "30124, 5, 5" ;
		// (3, 0, 1, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30124_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(73 % TOTAL == SPLIT){
		cout << "30142, 5, 5" ;
		// (3, 0, 1, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30142_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(74 % TOTAL == SPLIT){
		cout << "30214, 5, 5" ;
		// (3, 0, 2, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30214_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(75 % TOTAL == SPLIT){
		cout << "30241, 5, 5" ;
		// (3, 0, 2, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30241_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(76 % TOTAL == SPLIT){
		cout << "30412, 5, 5" ;
		// (3, 0, 4, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30412_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(77 % TOTAL == SPLIT){
		cout << "30421, 5, 5" ;
		// (3, 0, 4, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_30421_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(78 % TOTAL == SPLIT){
		cout << "31024, 5, 5" ;
		// (3, 1, 0, 2, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31024_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(79 % TOTAL == SPLIT){
		cout << "31042, 5, 5" ;
		// (3, 1, 0, 4, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31042_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(80 % TOTAL == SPLIT){
		cout << "31204, 5, 5" ;
		// (3, 1, 2, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31204_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(81 % TOTAL == SPLIT){
		cout << "31240, 5, 5" ;
		// (3, 1, 2, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31240_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(82 % TOTAL == SPLIT){
		cout << "31402, 5, 5" ;
		// (3, 1, 4, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31402_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(83 % TOTAL == SPLIT){
		cout << "31420, 5, 5" ;
		// (3, 1, 4, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_31420_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(84 % TOTAL == SPLIT){
		cout << "32014, 5, 5" ;
		// (3, 2, 0, 1, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32014_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(85 % TOTAL == SPLIT){
		cout << "32041, 5, 5" ;
		// (3, 2, 0, 4, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32041_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(86 % TOTAL == SPLIT){
		cout << "32104, 5, 5" ;
		// (3, 2, 1, 0, 4)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32104_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(87 % TOTAL == SPLIT){
		cout << "32140, 5, 5" ;
		// (3, 2, 1, 4, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32140_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(88 % TOTAL == SPLIT){
		cout << "32401, 5, 5" ;
		// (3, 2, 4, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32401_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(89 % TOTAL == SPLIT){
		cout << "32410, 5, 5" ;
		// (3, 2, 4, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_32410_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(90 % TOTAL == SPLIT){
		cout << "34012, 5, 5" ;
		// (3, 4, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34012_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(91 % TOTAL == SPLIT){
		cout << "34021, 5, 5" ;
		// (3, 4, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34021_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(92 % TOTAL == SPLIT){
		cout << "34102, 5, 5" ;
		// (3, 4, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34102_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(93 % TOTAL == SPLIT){
		cout << "34120, 5, 5" ;
		// (3, 4, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34120_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(94 % TOTAL == SPLIT){
		cout << "34201, 5, 5" ;
		// (3, 4, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34201_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(95 % TOTAL == SPLIT){
		cout << "34210, 5, 5" ;
		// (3, 4, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_34210_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(96 % TOTAL == SPLIT){
		cout << "40123, 5, 5" ;
		// (4, 0, 1, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40123_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(97 % TOTAL == SPLIT){
		cout << "40132, 5, 5" ;
		// (4, 0, 1, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40132_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(98 % TOTAL == SPLIT){
		cout << "40213, 5, 5" ;
		// (4, 0, 2, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40213_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(99 % TOTAL == SPLIT){
		cout << "40231, 5, 5" ;
		// (4, 0, 2, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40231_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(100 % TOTAL == SPLIT){
		cout << "40312, 5, 5" ;
		// (4, 0, 3, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40312_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(101 % TOTAL == SPLIT){
		cout << "40321, 5, 5" ;
		// (4, 0, 3, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_40321_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(102 % TOTAL == SPLIT){
		cout << "41023, 5, 5" ;
		// (4, 1, 0, 2, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41023_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(103 % TOTAL == SPLIT){
		cout << "41032, 5, 5" ;
		// (4, 1, 0, 3, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41032_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(104 % TOTAL == SPLIT){
		cout << "41203, 5, 5" ;
		// (4, 1, 2, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41203_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(105 % TOTAL == SPLIT){
		cout << "41230, 5, 5" ;
		// (4, 1, 2, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41230_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(106 % TOTAL == SPLIT){
		cout << "41302, 5, 5" ;
		// (4, 1, 3, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41302_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(107 % TOTAL == SPLIT){
		cout << "41320, 5, 5" ;
		// (4, 1, 3, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_41320_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(108 % TOTAL == SPLIT){
		cout << "42013, 5, 5" ;
		// (4, 2, 0, 1, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42013_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(109 % TOTAL == SPLIT){
		cout << "42031, 5, 5" ;
		// (4, 2, 0, 3, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42031_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(110 % TOTAL == SPLIT){
		cout << "42103, 5, 5" ;
		// (4, 2, 1, 0, 3)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42103_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(111 % TOTAL == SPLIT){
		cout << "42130, 5, 5" ;
		// (4, 2, 1, 3, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42130_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(112 % TOTAL == SPLIT){
		cout << "42301, 5, 5" ;
		// (4, 2, 3, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42301_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(113 % TOTAL == SPLIT){
		cout << "42310, 5, 5" ;
		// (4, 2, 3, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_42310_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(114 % TOTAL == SPLIT){
		cout << "43012, 5, 5" ;
		// (4, 3, 0, 1, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43012_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(115 % TOTAL == SPLIT){
		cout << "43021, 5, 5" ;
		// (4, 3, 0, 2, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43021_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(116 % TOTAL == SPLIT){
		cout << "43102, 5, 5" ;
		// (4, 3, 1, 0, 2)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43102_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(117 % TOTAL == SPLIT){
		cout << "43120, 5, 5" ;
		// (4, 3, 1, 2, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43120_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(118 % TOTAL == SPLIT){
		cout << "43201, 5, 5" ;
		// (4, 3, 2, 0, 1)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43201_all(A, size, order, dimensions);
		}
		cout << endl;

		}
		if(119 % TOTAL == SPLIT){
		cout << "43210, 5, 5" ;
		// (4, 3, 2, 1, 0)
		for(int i = 0; i < 100; i ++){
			qsort(A, size, sizeof(struct coo_t), cmp_01234);
			transpose_coo_43210_all(A, size, order, dimensions);
		}
		cout << endl;

		}
	free(A);
	free(dimensions);
}
