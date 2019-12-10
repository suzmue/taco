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

// Schedule length: 0
// Schedule: []
int transpose_coo_01234(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(4, [0, 1, 2])]
int transpose_coo_01243(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(3, [0, 1])]
int transpose_coo_01324(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, [0, 1]), (3, [0, 1])]
int transpose_coo_01342(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(4, [0, 1])]
int transpose_coo_01423(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, [0, 1]), (4, [0, 1])]
int transpose_coo_01432(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(2, [0])]
int transpose_coo_02134(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, [0]), (4, [0, 2, 1])]
int transpose_coo_02143(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, [0]), (2, [0])]
int transpose_coo_02314(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, [0]), (3, [0]), (2, [0])]
int transpose_coo_02341(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, [0]), (2, [0])]
int transpose_coo_02413(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, [0]), (4, [0]), (2, [0])]
int transpose_coo_02431(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(3, [0])]
int transpose_coo_03124(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, [0]), (4, [0, 3, 1])]
int transpose_coo_03142(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, [0]), (3, [0])]
int transpose_coo_03214(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, [0]), (2, [0]), (3, [0])]
int transpose_coo_03241(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, [0]), (3, [0])]
int transpose_coo_03412(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, [0]), (4, [0]), (3, [0])]
int transpose_coo_03421(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(4, [0])]
int transpose_coo_04123(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, [0]), (3, [0, 4, 1])]
int transpose_coo_04132(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, [0]), (4, [0])]
int transpose_coo_04213(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, [0]), (2, [0]), (4, [0])]
int transpose_coo_04231(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, [0]), (4, [0])]
int transpose_coo_04312(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, [0]), (3, [0]), (4, [0])]
int transpose_coo_04321(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(1, [])]
int transpose_coo_10234(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (4, [1, 0, 2])]
int transpose_coo_10243(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (3, [1, 0])]
int transpose_coo_10324(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (4, [1, 0]), (3, [1, 0])]
int transpose_coo_10342(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (4, [1, 0])]
int transpose_coo_10423(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (3, [1, 0]), (4, [1, 0])]
int transpose_coo_10432(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (1, [])]
int transpose_coo_12034(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (1, []), (4, [1, 2, 0])]
int transpose_coo_12043(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (2, []), (1, [])]
int transpose_coo_12304(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (3, []), (2, []), (1, [])]
int transpose_coo_12340(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (2, []), (1, [])]
int transpose_coo_12403(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (4, []), (2, []), (1, [])]
int transpose_coo_12430(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (1, [])]
int transpose_coo_13024(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (1, []), (4, [1, 3, 0])]
int transpose_coo_13042(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (3, []), (1, [])]
int transpose_coo_13204(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (2, []), (3, []), (1, [])]
int transpose_coo_13240(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (3, []), (1, [])]
int transpose_coo_13402(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (4, []), (3, []), (1, [])]
int transpose_coo_13420(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (1, [])]
int transpose_coo_14023(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (1, []), (3, [1, 4, 0])]
int transpose_coo_14032(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (4, []), (1, [])]
int transpose_coo_14203(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (2, []), (4, []), (1, [])]
int transpose_coo_14230(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (4, []), (1, [])]
int transpose_coo_14302(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (3, []), (4, []), (1, [])]
int transpose_coo_14320(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(2, [])]
int transpose_coo_20134(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (4, [2, 0, 1])]
int transpose_coo_20143(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (3, [2, 0])]
int transpose_coo_20314(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (4, [2, 0]), (3, [2, 0])]
int transpose_coo_20341(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (4, [2, 0])]
int transpose_coo_20413(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (3, [2, 0]), (4, [2, 0])]
int transpose_coo_20431(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (2, [])]
int transpose_coo_21034(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (2, []), (4, [2, 1, 0])]
int transpose_coo_21043(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (1, []), (2, [])]
int transpose_coo_21304(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (3, []), (1, []), (2, [])]
int transpose_coo_21340(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (1, []), (2, [])]
int transpose_coo_21403(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (4, []), (1, []), (2, [])]
int transpose_coo_21430(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (2, [])]
int transpose_coo_23014(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (2, []), (4, [2, 3, 0])]
int transpose_coo_23041(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (3, []), (2, [])]
int transpose_coo_23104(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (1, []), (3, []), (2, [])]
int transpose_coo_23140(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (3, []), (2, [])]
int transpose_coo_23401(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (4, []), (3, []), (2, [])]
int transpose_coo_23410(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (2, [])]
int transpose_coo_24013(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (2, []), (3, [2, 4, 0])]
int transpose_coo_24031(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (4, []), (2, [])]
int transpose_coo_24103(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (1, []), (4, []), (2, [])]
int transpose_coo_24130(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (4, []), (2, [])]
int transpose_coo_24301(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (3, []), (4, []), (2, [])]
int transpose_coo_24310(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(3, [])]
int transpose_coo_30124(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (4, [3, 0, 1])]
int transpose_coo_30142(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (2, [3, 0])]
int transpose_coo_30214(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (4, [3, 0]), (2, [3, 0])]
int transpose_coo_30241(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (4, [3, 0])]
int transpose_coo_30412(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (2, [3, 0]), (4, [3, 0])]
int transpose_coo_30421(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (3, [])]
int transpose_coo_31024(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (3, []), (4, [3, 1, 0])]
int transpose_coo_31042(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (1, []), (3, [])]
int transpose_coo_31204(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (2, []), (1, []), (3, [])]
int transpose_coo_31240(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (1, []), (3, [])]
int transpose_coo_31402(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (4, []), (1, []), (3, [])]
int transpose_coo_31420(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (3, [])]
int transpose_coo_32014(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (3, []), (4, [3, 2, 0])]
int transpose_coo_32041(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (2, []), (3, [])]
int transpose_coo_32104(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(4, []), (1, []), (2, []), (3, [])]
int transpose_coo_32140(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (2, []), (3, [])]
int transpose_coo_32401(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (4, []), (2, []), (3, [])]
int transpose_coo_32410(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (3, [])]
int transpose_coo_34012(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (3, []), (2, [3, 4, 0])]
int transpose_coo_34021(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (4, []), (3, [])]
int transpose_coo_34102(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (1, []), (4, []), (3, [])]
int transpose_coo_34120(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (4, []), (3, [])]
int transpose_coo_34201(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (2, []), (4, []), (3, [])]
int transpose_coo_34210(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 1
// Schedule: [(4, [])]
int transpose_coo_40123(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (3, [4, 0, 1])]
int transpose_coo_40132(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (2, [4, 0])]
int transpose_coo_40213(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (3, [4, 0]), (2, [4, 0])]
int transpose_coo_40231(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(4, []), (3, [4, 0])]
int transpose_coo_40312(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(4, []), (2, [4, 0]), (3, [4, 0])]
int transpose_coo_40321(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(1, []), (4, [])]
int transpose_coo_41023(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (4, []), (3, [4, 1, 0])]
int transpose_coo_41032(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (1, []), (4, [])]
int transpose_coo_41203(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (2, []), (1, []), (4, [])]
int transpose_coo_41230(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (1, []), (4, [])]
int transpose_coo_41302(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (3, []), (1, []), (4, [])]
int transpose_coo_41320(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(2, []), (4, [])]
int transpose_coo_42013(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (4, []), (3, [4, 2, 0])]
int transpose_coo_42031(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (2, []), (4, [])]
int transpose_coo_42103(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(3, []), (1, []), (2, []), (4, [])]
int transpose_coo_42130(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (2, []), (4, [])]
int transpose_coo_42301(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (3, []), (2, []), (4, [])]
int transpose_coo_42310(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 2
// Schedule: [(3, []), (4, [])]
int transpose_coo_43012(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(3, []), (4, []), (2, [4, 3, 0])]
int transpose_coo_43021(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(1, []), (3, []), (4, [])]
int transpose_coo_43102(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(2, []), (1, []), (3, []), (4, [])]
int transpose_coo_43120(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 3
// Schedule: [(2, []), (3, []), (4, [])]
int transpose_coo_43201(struct coo_t *C_coords, int c_size, int order, int *dimensions);
// Schedule length: 4
// Schedule: [(1, []), (2, []), (3, []), (4, [])]
int transpose_coo_43210(struct coo_t *C_coords, int c_size, int order, int *dimensions);
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


int main(int argc, char* argv[]) {
  std::string filename = "/Users/suzymueller/quesadilla/benchmarks/lbnl-network.tns";
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
    
    cout << "size = " << size << endl;
    cout<< "[" << dimensions[0] << ", "<< dimensions[1] << ", "<< dimensions[2] << "]" << endl;

  // Create tensors

    qsort(A, size, sizeof(struct coo_t), cmp_01234);
	// Qsort 01234
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01234;
	t_q_01234.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	t_q_01234.stop();
	taco::util::TimeResults r_q_01234 = t_q_01234.getResult();
	cout << "qsort_01234:" << endl;
	cout << r_q_01234 << endl;
	t_q_01234.clear_cache();
	// Qsort 01243
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01243;
	t_q_01243.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01243);
	t_q_01243.stop();
	taco::util::TimeResults r_q_01243 = t_q_01243.getResult();
	cout << "qsort_01243:" << endl;
	cout << r_q_01243 << endl;
	t_q_01243.clear_cache();
	// Qsort 01324
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01324;
	t_q_01324.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01324);
	t_q_01324.stop();
	taco::util::TimeResults r_q_01324 = t_q_01324.getResult();
	cout << "qsort_01324:" << endl;
	cout << r_q_01324 << endl;
	t_q_01324.clear_cache();
	// Qsort 01342
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01342;
	t_q_01342.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01342);
	t_q_01342.stop();
	taco::util::TimeResults r_q_01342 = t_q_01342.getResult();
	cout << "qsort_01342:" << endl;
	cout << r_q_01342 << endl;
	t_q_01342.clear_cache();
	// Qsort 01423
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01423;
	t_q_01423.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01423);
	t_q_01423.stop();
	taco::util::TimeResults r_q_01423 = t_q_01423.getResult();
	cout << "qsort_01423:" << endl;
	cout << r_q_01423 << endl;
	t_q_01423.clear_cache();
	// Qsort 01432
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_01432;
	t_q_01432.start();
	qsort(A, size, sizeof(struct coo_t), cmp_01432);
	t_q_01432.stop();
	taco::util::TimeResults r_q_01432 = t_q_01432.getResult();
	cout << "qsort_01432:" << endl;
	cout << r_q_01432 << endl;
	t_q_01432.clear_cache();
	// Qsort 02134
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02134;
	t_q_02134.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02134);
	t_q_02134.stop();
	taco::util::TimeResults r_q_02134 = t_q_02134.getResult();
	cout << "qsort_02134:" << endl;
	cout << r_q_02134 << endl;
	t_q_02134.clear_cache();
	// Qsort 02143
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02143;
	t_q_02143.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02143);
	t_q_02143.stop();
	taco::util::TimeResults r_q_02143 = t_q_02143.getResult();
	cout << "qsort_02143:" << endl;
	cout << r_q_02143 << endl;
	t_q_02143.clear_cache();
	// Qsort 02314
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02314;
	t_q_02314.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02314);
	t_q_02314.stop();
	taco::util::TimeResults r_q_02314 = t_q_02314.getResult();
	cout << "qsort_02314:" << endl;
	cout << r_q_02314 << endl;
	t_q_02314.clear_cache();
	// Qsort 02341
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02341;
	t_q_02341.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02341);
	t_q_02341.stop();
	taco::util::TimeResults r_q_02341 = t_q_02341.getResult();
	cout << "qsort_02341:" << endl;
	cout << r_q_02341 << endl;
	t_q_02341.clear_cache();
	// Qsort 02413
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02413;
	t_q_02413.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02413);
	t_q_02413.stop();
	taco::util::TimeResults r_q_02413 = t_q_02413.getResult();
	cout << "qsort_02413:" << endl;
	cout << r_q_02413 << endl;
	t_q_02413.clear_cache();
	// Qsort 02431
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_02431;
	t_q_02431.start();
	qsort(A, size, sizeof(struct coo_t), cmp_02431);
	t_q_02431.stop();
	taco::util::TimeResults r_q_02431 = t_q_02431.getResult();
	cout << "qsort_02431:" << endl;
	cout << r_q_02431 << endl;
	t_q_02431.clear_cache();
	// Qsort 03124
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03124;
	t_q_03124.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03124);
	t_q_03124.stop();
	taco::util::TimeResults r_q_03124 = t_q_03124.getResult();
	cout << "qsort_03124:" << endl;
	cout << r_q_03124 << endl;
	t_q_03124.clear_cache();
	// Qsort 03142
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03142;
	t_q_03142.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03142);
	t_q_03142.stop();
	taco::util::TimeResults r_q_03142 = t_q_03142.getResult();
	cout << "qsort_03142:" << endl;
	cout << r_q_03142 << endl;
	t_q_03142.clear_cache();
	// Qsort 03214
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03214;
	t_q_03214.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03214);
	t_q_03214.stop();
	taco::util::TimeResults r_q_03214 = t_q_03214.getResult();
	cout << "qsort_03214:" << endl;
	cout << r_q_03214 << endl;
	t_q_03214.clear_cache();
	// Qsort 03241
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03241;
	t_q_03241.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03241);
	t_q_03241.stop();
	taco::util::TimeResults r_q_03241 = t_q_03241.getResult();
	cout << "qsort_03241:" << endl;
	cout << r_q_03241 << endl;
	t_q_03241.clear_cache();
	// Qsort 03412
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03412;
	t_q_03412.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03412);
	t_q_03412.stop();
	taco::util::TimeResults r_q_03412 = t_q_03412.getResult();
	cout << "qsort_03412:" << endl;
	cout << r_q_03412 << endl;
	t_q_03412.clear_cache();
	// Qsort 03421
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_03421;
	t_q_03421.start();
	qsort(A, size, sizeof(struct coo_t), cmp_03421);
	t_q_03421.stop();
	taco::util::TimeResults r_q_03421 = t_q_03421.getResult();
	cout << "qsort_03421:" << endl;
	cout << r_q_03421 << endl;
	t_q_03421.clear_cache();
	// Qsort 04123
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04123;
	t_q_04123.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04123);
	t_q_04123.stop();
	taco::util::TimeResults r_q_04123 = t_q_04123.getResult();
	cout << "qsort_04123:" << endl;
	cout << r_q_04123 << endl;
	t_q_04123.clear_cache();
	// Qsort 04132
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04132;
	t_q_04132.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04132);
	t_q_04132.stop();
	taco::util::TimeResults r_q_04132 = t_q_04132.getResult();
	cout << "qsort_04132:" << endl;
	cout << r_q_04132 << endl;
	t_q_04132.clear_cache();
	// Qsort 04213
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04213;
	t_q_04213.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04213);
	t_q_04213.stop();
	taco::util::TimeResults r_q_04213 = t_q_04213.getResult();
	cout << "qsort_04213:" << endl;
	cout << r_q_04213 << endl;
	t_q_04213.clear_cache();
	// Qsort 04231
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04231;
	t_q_04231.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04231);
	t_q_04231.stop();
	taco::util::TimeResults r_q_04231 = t_q_04231.getResult();
	cout << "qsort_04231:" << endl;
	cout << r_q_04231 << endl;
	t_q_04231.clear_cache();
	// Qsort 04312
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04312;
	t_q_04312.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04312);
	t_q_04312.stop();
	taco::util::TimeResults r_q_04312 = t_q_04312.getResult();
	cout << "qsort_04312:" << endl;
	cout << r_q_04312 << endl;
	t_q_04312.clear_cache();
	// Qsort 04321
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_04321;
	t_q_04321.start();
	qsort(A, size, sizeof(struct coo_t), cmp_04321);
	t_q_04321.stop();
	taco::util::TimeResults r_q_04321 = t_q_04321.getResult();
	cout << "qsort_04321:" << endl;
	cout << r_q_04321 << endl;
	t_q_04321.clear_cache();
	// Qsort 10234
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10234;
	t_q_10234.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10234);
	t_q_10234.stop();
	taco::util::TimeResults r_q_10234 = t_q_10234.getResult();
	cout << "qsort_10234:" << endl;
	cout << r_q_10234 << endl;
	t_q_10234.clear_cache();
	// Qsort 10243
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10243;
	t_q_10243.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10243);
	t_q_10243.stop();
	taco::util::TimeResults r_q_10243 = t_q_10243.getResult();
	cout << "qsort_10243:" << endl;
	cout << r_q_10243 << endl;
	t_q_10243.clear_cache();
	// Qsort 10324
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10324;
	t_q_10324.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10324);
	t_q_10324.stop();
	taco::util::TimeResults r_q_10324 = t_q_10324.getResult();
	cout << "qsort_10324:" << endl;
	cout << r_q_10324 << endl;
	t_q_10324.clear_cache();
	// Qsort 10342
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10342;
	t_q_10342.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10342);
	t_q_10342.stop();
	taco::util::TimeResults r_q_10342 = t_q_10342.getResult();
	cout << "qsort_10342:" << endl;
	cout << r_q_10342 << endl;
	t_q_10342.clear_cache();
	// Qsort 10423
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10423;
	t_q_10423.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10423);
	t_q_10423.stop();
	taco::util::TimeResults r_q_10423 = t_q_10423.getResult();
	cout << "qsort_10423:" << endl;
	cout << r_q_10423 << endl;
	t_q_10423.clear_cache();
	// Qsort 10432
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_10432;
	t_q_10432.start();
	qsort(A, size, sizeof(struct coo_t), cmp_10432);
	t_q_10432.stop();
	taco::util::TimeResults r_q_10432 = t_q_10432.getResult();
	cout << "qsort_10432:" << endl;
	cout << r_q_10432 << endl;
	t_q_10432.clear_cache();
	// Qsort 12034
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12034;
	t_q_12034.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12034);
	t_q_12034.stop();
	taco::util::TimeResults r_q_12034 = t_q_12034.getResult();
	cout << "qsort_12034:" << endl;
	cout << r_q_12034 << endl;
	t_q_12034.clear_cache();
	// Qsort 12043
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12043;
	t_q_12043.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12043);
	t_q_12043.stop();
	taco::util::TimeResults r_q_12043 = t_q_12043.getResult();
	cout << "qsort_12043:" << endl;
	cout << r_q_12043 << endl;
	t_q_12043.clear_cache();
	// Qsort 12304
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12304;
	t_q_12304.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12304);
	t_q_12304.stop();
	taco::util::TimeResults r_q_12304 = t_q_12304.getResult();
	cout << "qsort_12304:" << endl;
	cout << r_q_12304 << endl;
	t_q_12304.clear_cache();
	// Qsort 12340
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12340;
	t_q_12340.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12340);
	t_q_12340.stop();
	taco::util::TimeResults r_q_12340 = t_q_12340.getResult();
	cout << "qsort_12340:" << endl;
	cout << r_q_12340 << endl;
	t_q_12340.clear_cache();
	// Qsort 12403
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12403;
	t_q_12403.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12403);
	t_q_12403.stop();
	taco::util::TimeResults r_q_12403 = t_q_12403.getResult();
	cout << "qsort_12403:" << endl;
	cout << r_q_12403 << endl;
	t_q_12403.clear_cache();
	// Qsort 12430
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_12430;
	t_q_12430.start();
	qsort(A, size, sizeof(struct coo_t), cmp_12430);
	t_q_12430.stop();
	taco::util::TimeResults r_q_12430 = t_q_12430.getResult();
	cout << "qsort_12430:" << endl;
	cout << r_q_12430 << endl;
	t_q_12430.clear_cache();
	// Qsort 13024
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13024;
	t_q_13024.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13024);
	t_q_13024.stop();
	taco::util::TimeResults r_q_13024 = t_q_13024.getResult();
	cout << "qsort_13024:" << endl;
	cout << r_q_13024 << endl;
	t_q_13024.clear_cache();
	// Qsort 13042
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13042;
	t_q_13042.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13042);
	t_q_13042.stop();
	taco::util::TimeResults r_q_13042 = t_q_13042.getResult();
	cout << "qsort_13042:" << endl;
	cout << r_q_13042 << endl;
	t_q_13042.clear_cache();
	// Qsort 13204
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13204;
	t_q_13204.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13204);
	t_q_13204.stop();
	taco::util::TimeResults r_q_13204 = t_q_13204.getResult();
	cout << "qsort_13204:" << endl;
	cout << r_q_13204 << endl;
	t_q_13204.clear_cache();
	// Qsort 13240
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13240;
	t_q_13240.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13240);
	t_q_13240.stop();
	taco::util::TimeResults r_q_13240 = t_q_13240.getResult();
	cout << "qsort_13240:" << endl;
	cout << r_q_13240 << endl;
	t_q_13240.clear_cache();
	// Qsort 13402
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13402;
	t_q_13402.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13402);
	t_q_13402.stop();
	taco::util::TimeResults r_q_13402 = t_q_13402.getResult();
	cout << "qsort_13402:" << endl;
	cout << r_q_13402 << endl;
	t_q_13402.clear_cache();
	// Qsort 13420
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_13420;
	t_q_13420.start();
	qsort(A, size, sizeof(struct coo_t), cmp_13420);
	t_q_13420.stop();
	taco::util::TimeResults r_q_13420 = t_q_13420.getResult();
	cout << "qsort_13420:" << endl;
	cout << r_q_13420 << endl;
	t_q_13420.clear_cache();
	// Qsort 14023
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14023;
	t_q_14023.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14023);
	t_q_14023.stop();
	taco::util::TimeResults r_q_14023 = t_q_14023.getResult();
	cout << "qsort_14023:" << endl;
	cout << r_q_14023 << endl;
	t_q_14023.clear_cache();
	// Qsort 14032
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14032;
	t_q_14032.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14032);
	t_q_14032.stop();
	taco::util::TimeResults r_q_14032 = t_q_14032.getResult();
	cout << "qsort_14032:" << endl;
	cout << r_q_14032 << endl;
	t_q_14032.clear_cache();
	// Qsort 14203
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14203;
	t_q_14203.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14203);
	t_q_14203.stop();
	taco::util::TimeResults r_q_14203 = t_q_14203.getResult();
	cout << "qsort_14203:" << endl;
	cout << r_q_14203 << endl;
	t_q_14203.clear_cache();
	// Qsort 14230
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14230;
	t_q_14230.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14230);
	t_q_14230.stop();
	taco::util::TimeResults r_q_14230 = t_q_14230.getResult();
	cout << "qsort_14230:" << endl;
	cout << r_q_14230 << endl;
	t_q_14230.clear_cache();
	// Qsort 14302
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14302;
	t_q_14302.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14302);
	t_q_14302.stop();
	taco::util::TimeResults r_q_14302 = t_q_14302.getResult();
	cout << "qsort_14302:" << endl;
	cout << r_q_14302 << endl;
	t_q_14302.clear_cache();
	// Qsort 14320
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_14320;
	t_q_14320.start();
	qsort(A, size, sizeof(struct coo_t), cmp_14320);
	t_q_14320.stop();
	taco::util::TimeResults r_q_14320 = t_q_14320.getResult();
	cout << "qsort_14320:" << endl;
	cout << r_q_14320 << endl;
	t_q_14320.clear_cache();
	// Qsort 20134
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20134;
	t_q_20134.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20134);
	t_q_20134.stop();
	taco::util::TimeResults r_q_20134 = t_q_20134.getResult();
	cout << "qsort_20134:" << endl;
	cout << r_q_20134 << endl;
	t_q_20134.clear_cache();
	// Qsort 20143
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20143;
	t_q_20143.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20143);
	t_q_20143.stop();
	taco::util::TimeResults r_q_20143 = t_q_20143.getResult();
	cout << "qsort_20143:" << endl;
	cout << r_q_20143 << endl;
	t_q_20143.clear_cache();
	// Qsort 20314
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20314;
	t_q_20314.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20314);
	t_q_20314.stop();
	taco::util::TimeResults r_q_20314 = t_q_20314.getResult();
	cout << "qsort_20314:" << endl;
	cout << r_q_20314 << endl;
	t_q_20314.clear_cache();
	// Qsort 20341
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20341;
	t_q_20341.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20341);
	t_q_20341.stop();
	taco::util::TimeResults r_q_20341 = t_q_20341.getResult();
	cout << "qsort_20341:" << endl;
	cout << r_q_20341 << endl;
	t_q_20341.clear_cache();
	// Qsort 20413
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20413;
	t_q_20413.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20413);
	t_q_20413.stop();
	taco::util::TimeResults r_q_20413 = t_q_20413.getResult();
	cout << "qsort_20413:" << endl;
	cout << r_q_20413 << endl;
	t_q_20413.clear_cache();
	// Qsort 20431
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_20431;
	t_q_20431.start();
	qsort(A, size, sizeof(struct coo_t), cmp_20431);
	t_q_20431.stop();
	taco::util::TimeResults r_q_20431 = t_q_20431.getResult();
	cout << "qsort_20431:" << endl;
	cout << r_q_20431 << endl;
	t_q_20431.clear_cache();
	// Qsort 21034
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21034;
	t_q_21034.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21034);
	t_q_21034.stop();
	taco::util::TimeResults r_q_21034 = t_q_21034.getResult();
	cout << "qsort_21034:" << endl;
	cout << r_q_21034 << endl;
	t_q_21034.clear_cache();
	// Qsort 21043
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21043;
	t_q_21043.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21043);
	t_q_21043.stop();
	taco::util::TimeResults r_q_21043 = t_q_21043.getResult();
	cout << "qsort_21043:" << endl;
	cout << r_q_21043 << endl;
	t_q_21043.clear_cache();
	// Qsort 21304
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21304;
	t_q_21304.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21304);
	t_q_21304.stop();
	taco::util::TimeResults r_q_21304 = t_q_21304.getResult();
	cout << "qsort_21304:" << endl;
	cout << r_q_21304 << endl;
	t_q_21304.clear_cache();
	// Qsort 21340
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21340;
	t_q_21340.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21340);
	t_q_21340.stop();
	taco::util::TimeResults r_q_21340 = t_q_21340.getResult();
	cout << "qsort_21340:" << endl;
	cout << r_q_21340 << endl;
	t_q_21340.clear_cache();
	// Qsort 21403
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21403;
	t_q_21403.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21403);
	t_q_21403.stop();
	taco::util::TimeResults r_q_21403 = t_q_21403.getResult();
	cout << "qsort_21403:" << endl;
	cout << r_q_21403 << endl;
	t_q_21403.clear_cache();
	// Qsort 21430
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_21430;
	t_q_21430.start();
	qsort(A, size, sizeof(struct coo_t), cmp_21430);
	t_q_21430.stop();
	taco::util::TimeResults r_q_21430 = t_q_21430.getResult();
	cout << "qsort_21430:" << endl;
	cout << r_q_21430 << endl;
	t_q_21430.clear_cache();
	// Qsort 23014
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23014;
	t_q_23014.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23014);
	t_q_23014.stop();
	taco::util::TimeResults r_q_23014 = t_q_23014.getResult();
	cout << "qsort_23014:" << endl;
	cout << r_q_23014 << endl;
	t_q_23014.clear_cache();
	// Qsort 23041
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23041;
	t_q_23041.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23041);
	t_q_23041.stop();
	taco::util::TimeResults r_q_23041 = t_q_23041.getResult();
	cout << "qsort_23041:" << endl;
	cout << r_q_23041 << endl;
	t_q_23041.clear_cache();
	// Qsort 23104
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23104;
	t_q_23104.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23104);
	t_q_23104.stop();
	taco::util::TimeResults r_q_23104 = t_q_23104.getResult();
	cout << "qsort_23104:" << endl;
	cout << r_q_23104 << endl;
	t_q_23104.clear_cache();
	// Qsort 23140
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23140;
	t_q_23140.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23140);
	t_q_23140.stop();
	taco::util::TimeResults r_q_23140 = t_q_23140.getResult();
	cout << "qsort_23140:" << endl;
	cout << r_q_23140 << endl;
	t_q_23140.clear_cache();
	// Qsort 23401
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23401;
	t_q_23401.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23401);
	t_q_23401.stop();
	taco::util::TimeResults r_q_23401 = t_q_23401.getResult();
	cout << "qsort_23401:" << endl;
	cout << r_q_23401 << endl;
	t_q_23401.clear_cache();
	// Qsort 23410
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_23410;
	t_q_23410.start();
	qsort(A, size, sizeof(struct coo_t), cmp_23410);
	t_q_23410.stop();
	taco::util::TimeResults r_q_23410 = t_q_23410.getResult();
	cout << "qsort_23410:" << endl;
	cout << r_q_23410 << endl;
	t_q_23410.clear_cache();
	// Qsort 24013
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24013;
	t_q_24013.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24013);
	t_q_24013.stop();
	taco::util::TimeResults r_q_24013 = t_q_24013.getResult();
	cout << "qsort_24013:" << endl;
	cout << r_q_24013 << endl;
	t_q_24013.clear_cache();
	// Qsort 24031
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24031;
	t_q_24031.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24031);
	t_q_24031.stop();
	taco::util::TimeResults r_q_24031 = t_q_24031.getResult();
	cout << "qsort_24031:" << endl;
	cout << r_q_24031 << endl;
	t_q_24031.clear_cache();
	// Qsort 24103
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24103;
	t_q_24103.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24103);
	t_q_24103.stop();
	taco::util::TimeResults r_q_24103 = t_q_24103.getResult();
	cout << "qsort_24103:" << endl;
	cout << r_q_24103 << endl;
	t_q_24103.clear_cache();
	// Qsort 24130
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24130;
	t_q_24130.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24130);
	t_q_24130.stop();
	taco::util::TimeResults r_q_24130 = t_q_24130.getResult();
	cout << "qsort_24130:" << endl;
	cout << r_q_24130 << endl;
	t_q_24130.clear_cache();
	// Qsort 24301
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24301;
	t_q_24301.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24301);
	t_q_24301.stop();
	taco::util::TimeResults r_q_24301 = t_q_24301.getResult();
	cout << "qsort_24301:" << endl;
	cout << r_q_24301 << endl;
	t_q_24301.clear_cache();
	// Qsort 24310
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_24310;
	t_q_24310.start();
	qsort(A, size, sizeof(struct coo_t), cmp_24310);
	t_q_24310.stop();
	taco::util::TimeResults r_q_24310 = t_q_24310.getResult();
	cout << "qsort_24310:" << endl;
	cout << r_q_24310 << endl;
	t_q_24310.clear_cache();
	// Qsort 30124
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30124;
	t_q_30124.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30124);
	t_q_30124.stop();
	taco::util::TimeResults r_q_30124 = t_q_30124.getResult();
	cout << "qsort_30124:" << endl;
	cout << r_q_30124 << endl;
	t_q_30124.clear_cache();
	// Qsort 30142
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30142;
	t_q_30142.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30142);
	t_q_30142.stop();
	taco::util::TimeResults r_q_30142 = t_q_30142.getResult();
	cout << "qsort_30142:" << endl;
	cout << r_q_30142 << endl;
	t_q_30142.clear_cache();
	// Qsort 30214
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30214;
	t_q_30214.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30214);
	t_q_30214.stop();
	taco::util::TimeResults r_q_30214 = t_q_30214.getResult();
	cout << "qsort_30214:" << endl;
	cout << r_q_30214 << endl;
	t_q_30214.clear_cache();
	// Qsort 30241
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30241;
	t_q_30241.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30241);
	t_q_30241.stop();
	taco::util::TimeResults r_q_30241 = t_q_30241.getResult();
	cout << "qsort_30241:" << endl;
	cout << r_q_30241 << endl;
	t_q_30241.clear_cache();
	// Qsort 30412
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30412;
	t_q_30412.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30412);
	t_q_30412.stop();
	taco::util::TimeResults r_q_30412 = t_q_30412.getResult();
	cout << "qsort_30412:" << endl;
	cout << r_q_30412 << endl;
	t_q_30412.clear_cache();
	// Qsort 30421
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_30421;
	t_q_30421.start();
	qsort(A, size, sizeof(struct coo_t), cmp_30421);
	t_q_30421.stop();
	taco::util::TimeResults r_q_30421 = t_q_30421.getResult();
	cout << "qsort_30421:" << endl;
	cout << r_q_30421 << endl;
	t_q_30421.clear_cache();
	// Qsort 31024
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31024;
	t_q_31024.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31024);
	t_q_31024.stop();
	taco::util::TimeResults r_q_31024 = t_q_31024.getResult();
	cout << "qsort_31024:" << endl;
	cout << r_q_31024 << endl;
	t_q_31024.clear_cache();
	// Qsort 31042
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31042;
	t_q_31042.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31042);
	t_q_31042.stop();
	taco::util::TimeResults r_q_31042 = t_q_31042.getResult();
	cout << "qsort_31042:" << endl;
	cout << r_q_31042 << endl;
	t_q_31042.clear_cache();
	// Qsort 31204
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31204;
	t_q_31204.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31204);
	t_q_31204.stop();
	taco::util::TimeResults r_q_31204 = t_q_31204.getResult();
	cout << "qsort_31204:" << endl;
	cout << r_q_31204 << endl;
	t_q_31204.clear_cache();
	// Qsort 31240
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31240;
	t_q_31240.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31240);
	t_q_31240.stop();
	taco::util::TimeResults r_q_31240 = t_q_31240.getResult();
	cout << "qsort_31240:" << endl;
	cout << r_q_31240 << endl;
	t_q_31240.clear_cache();
	// Qsort 31402
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31402;
	t_q_31402.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31402);
	t_q_31402.stop();
	taco::util::TimeResults r_q_31402 = t_q_31402.getResult();
	cout << "qsort_31402:" << endl;
	cout << r_q_31402 << endl;
	t_q_31402.clear_cache();
	// Qsort 31420
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_31420;
	t_q_31420.start();
	qsort(A, size, sizeof(struct coo_t), cmp_31420);
	t_q_31420.stop();
	taco::util::TimeResults r_q_31420 = t_q_31420.getResult();
	cout << "qsort_31420:" << endl;
	cout << r_q_31420 << endl;
	t_q_31420.clear_cache();
	// Qsort 32014
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32014;
	t_q_32014.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32014);
	t_q_32014.stop();
	taco::util::TimeResults r_q_32014 = t_q_32014.getResult();
	cout << "qsort_32014:" << endl;
	cout << r_q_32014 << endl;
	t_q_32014.clear_cache();
	// Qsort 32041
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32041;
	t_q_32041.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32041);
	t_q_32041.stop();
	taco::util::TimeResults r_q_32041 = t_q_32041.getResult();
	cout << "qsort_32041:" << endl;
	cout << r_q_32041 << endl;
	t_q_32041.clear_cache();
	// Qsort 32104
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32104;
	t_q_32104.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32104);
	t_q_32104.stop();
	taco::util::TimeResults r_q_32104 = t_q_32104.getResult();
	cout << "qsort_32104:" << endl;
	cout << r_q_32104 << endl;
	t_q_32104.clear_cache();
	// Qsort 32140
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32140;
	t_q_32140.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32140);
	t_q_32140.stop();
	taco::util::TimeResults r_q_32140 = t_q_32140.getResult();
	cout << "qsort_32140:" << endl;
	cout << r_q_32140 << endl;
	t_q_32140.clear_cache();
	// Qsort 32401
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32401;
	t_q_32401.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32401);
	t_q_32401.stop();
	taco::util::TimeResults r_q_32401 = t_q_32401.getResult();
	cout << "qsort_32401:" << endl;
	cout << r_q_32401 << endl;
	t_q_32401.clear_cache();
	// Qsort 32410
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_32410;
	t_q_32410.start();
	qsort(A, size, sizeof(struct coo_t), cmp_32410);
	t_q_32410.stop();
	taco::util::TimeResults r_q_32410 = t_q_32410.getResult();
	cout << "qsort_32410:" << endl;
	cout << r_q_32410 << endl;
	t_q_32410.clear_cache();
	// Qsort 34012
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34012;
	t_q_34012.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34012);
	t_q_34012.stop();
	taco::util::TimeResults r_q_34012 = t_q_34012.getResult();
	cout << "qsort_34012:" << endl;
	cout << r_q_34012 << endl;
	t_q_34012.clear_cache();
	// Qsort 34021
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34021;
	t_q_34021.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34021);
	t_q_34021.stop();
	taco::util::TimeResults r_q_34021 = t_q_34021.getResult();
	cout << "qsort_34021:" << endl;
	cout << r_q_34021 << endl;
	t_q_34021.clear_cache();
	// Qsort 34102
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34102;
	t_q_34102.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34102);
	t_q_34102.stop();
	taco::util::TimeResults r_q_34102 = t_q_34102.getResult();
	cout << "qsort_34102:" << endl;
	cout << r_q_34102 << endl;
	t_q_34102.clear_cache();
	// Qsort 34120
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34120;
	t_q_34120.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34120);
	t_q_34120.stop();
	taco::util::TimeResults r_q_34120 = t_q_34120.getResult();
	cout << "qsort_34120:" << endl;
	cout << r_q_34120 << endl;
	t_q_34120.clear_cache();
	// Qsort 34201
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34201;
	t_q_34201.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34201);
	t_q_34201.stop();
	taco::util::TimeResults r_q_34201 = t_q_34201.getResult();
	cout << "qsort_34201:" << endl;
	cout << r_q_34201 << endl;
	t_q_34201.clear_cache();
	// Qsort 34210
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_34210;
	t_q_34210.start();
	qsort(A, size, sizeof(struct coo_t), cmp_34210);
	t_q_34210.stop();
	taco::util::TimeResults r_q_34210 = t_q_34210.getResult();
	cout << "qsort_34210:" << endl;
	cout << r_q_34210 << endl;
	t_q_34210.clear_cache();
	// Qsort 40123
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40123;
	t_q_40123.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40123);
	t_q_40123.stop();
	taco::util::TimeResults r_q_40123 = t_q_40123.getResult();
	cout << "qsort_40123:" << endl;
	cout << r_q_40123 << endl;
	t_q_40123.clear_cache();
	// Qsort 40132
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40132;
	t_q_40132.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40132);
	t_q_40132.stop();
	taco::util::TimeResults r_q_40132 = t_q_40132.getResult();
	cout << "qsort_40132:" << endl;
	cout << r_q_40132 << endl;
	t_q_40132.clear_cache();
	// Qsort 40213
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40213;
	t_q_40213.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40213);
	t_q_40213.stop();
	taco::util::TimeResults r_q_40213 = t_q_40213.getResult();
	cout << "qsort_40213:" << endl;
	cout << r_q_40213 << endl;
	t_q_40213.clear_cache();
	// Qsort 40231
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40231;
	t_q_40231.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40231);
	t_q_40231.stop();
	taco::util::TimeResults r_q_40231 = t_q_40231.getResult();
	cout << "qsort_40231:" << endl;
	cout << r_q_40231 << endl;
	t_q_40231.clear_cache();
	// Qsort 40312
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40312;
	t_q_40312.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40312);
	t_q_40312.stop();
	taco::util::TimeResults r_q_40312 = t_q_40312.getResult();
	cout << "qsort_40312:" << endl;
	cout << r_q_40312 << endl;
	t_q_40312.clear_cache();
	// Qsort 40321
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_40321;
	t_q_40321.start();
	qsort(A, size, sizeof(struct coo_t), cmp_40321);
	t_q_40321.stop();
	taco::util::TimeResults r_q_40321 = t_q_40321.getResult();
	cout << "qsort_40321:" << endl;
	cout << r_q_40321 << endl;
	t_q_40321.clear_cache();
	// Qsort 41023
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41023;
	t_q_41023.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41023);
	t_q_41023.stop();
	taco::util::TimeResults r_q_41023 = t_q_41023.getResult();
	cout << "qsort_41023:" << endl;
	cout << r_q_41023 << endl;
	t_q_41023.clear_cache();
	// Qsort 41032
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41032;
	t_q_41032.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41032);
	t_q_41032.stop();
	taco::util::TimeResults r_q_41032 = t_q_41032.getResult();
	cout << "qsort_41032:" << endl;
	cout << r_q_41032 << endl;
	t_q_41032.clear_cache();
	// Qsort 41203
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41203;
	t_q_41203.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41203);
	t_q_41203.stop();
	taco::util::TimeResults r_q_41203 = t_q_41203.getResult();
	cout << "qsort_41203:" << endl;
	cout << r_q_41203 << endl;
	t_q_41203.clear_cache();
	// Qsort 41230
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41230;
	t_q_41230.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41230);
	t_q_41230.stop();
	taco::util::TimeResults r_q_41230 = t_q_41230.getResult();
	cout << "qsort_41230:" << endl;
	cout << r_q_41230 << endl;
	t_q_41230.clear_cache();
	// Qsort 41302
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41302;
	t_q_41302.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41302);
	t_q_41302.stop();
	taco::util::TimeResults r_q_41302 = t_q_41302.getResult();
	cout << "qsort_41302:" << endl;
	cout << r_q_41302 << endl;
	t_q_41302.clear_cache();
	// Qsort 41320
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_41320;
	t_q_41320.start();
	qsort(A, size, sizeof(struct coo_t), cmp_41320);
	t_q_41320.stop();
	taco::util::TimeResults r_q_41320 = t_q_41320.getResult();
	cout << "qsort_41320:" << endl;
	cout << r_q_41320 << endl;
	t_q_41320.clear_cache();
	// Qsort 42013
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42013;
	t_q_42013.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42013);
	t_q_42013.stop();
	taco::util::TimeResults r_q_42013 = t_q_42013.getResult();
	cout << "qsort_42013:" << endl;
	cout << r_q_42013 << endl;
	t_q_42013.clear_cache();
	// Qsort 42031
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42031;
	t_q_42031.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42031);
	t_q_42031.stop();
	taco::util::TimeResults r_q_42031 = t_q_42031.getResult();
	cout << "qsort_42031:" << endl;
	cout << r_q_42031 << endl;
	t_q_42031.clear_cache();
	// Qsort 42103
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42103;
	t_q_42103.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42103);
	t_q_42103.stop();
	taco::util::TimeResults r_q_42103 = t_q_42103.getResult();
	cout << "qsort_42103:" << endl;
	cout << r_q_42103 << endl;
	t_q_42103.clear_cache();
	// Qsort 42130
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42130;
	t_q_42130.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42130);
	t_q_42130.stop();
	taco::util::TimeResults r_q_42130 = t_q_42130.getResult();
	cout << "qsort_42130:" << endl;
	cout << r_q_42130 << endl;
	t_q_42130.clear_cache();
	// Qsort 42301
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42301;
	t_q_42301.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42301);
	t_q_42301.stop();
	taco::util::TimeResults r_q_42301 = t_q_42301.getResult();
	cout << "qsort_42301:" << endl;
	cout << r_q_42301 << endl;
	t_q_42301.clear_cache();
	// Qsort 42310
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_42310;
	t_q_42310.start();
	qsort(A, size, sizeof(struct coo_t), cmp_42310);
	t_q_42310.stop();
	taco::util::TimeResults r_q_42310 = t_q_42310.getResult();
	cout << "qsort_42310:" << endl;
	cout << r_q_42310 << endl;
	t_q_42310.clear_cache();
	// Qsort 43012
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43012;
	t_q_43012.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43012);
	t_q_43012.stop();
	taco::util::TimeResults r_q_43012 = t_q_43012.getResult();
	cout << "qsort_43012:" << endl;
	cout << r_q_43012 << endl;
	t_q_43012.clear_cache();
	// Qsort 43021
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43021;
	t_q_43021.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43021);
	t_q_43021.stop();
	taco::util::TimeResults r_q_43021 = t_q_43021.getResult();
	cout << "qsort_43021:" << endl;
	cout << r_q_43021 << endl;
	t_q_43021.clear_cache();
	// Qsort 43102
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43102;
	t_q_43102.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43102);
	t_q_43102.stop();
	taco::util::TimeResults r_q_43102 = t_q_43102.getResult();
	cout << "qsort_43102:" << endl;
	cout << r_q_43102 << endl;
	t_q_43102.clear_cache();
	// Qsort 43120
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43120;
	t_q_43120.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43120);
	t_q_43120.stop();
	taco::util::TimeResults r_q_43120 = t_q_43120.getResult();
	cout << "qsort_43120:" << endl;
	cout << r_q_43120 << endl;
	t_q_43120.clear_cache();
	// Qsort 43201
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43201;
	t_q_43201.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43201);
	t_q_43201.stop();
	taco::util::TimeResults r_q_43201 = t_q_43201.getResult();
	cout << "qsort_43201:" << endl;
	cout << r_q_43201 << endl;
	t_q_43201.clear_cache();
	// Qsort 43210
	qsort(A, size, sizeof(struct coo_t), cmp_01234);
	taco::util::Timer t_q_43210;
	t_q_43210.start();
	qsort(A, size, sizeof(struct coo_t), cmp_43210);
	t_q_43210.stop();
	taco::util::TimeResults r_q_43210 = t_q_43210.getResult();
	cout << "qsort_43210:" << endl;
	cout << r_q_43210 << endl;
	t_q_43210.clear_cache();


		// (0, 1, 2, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t0;
		t0.start();
		transpose_coo_01234(A, size, order, dimensions);
		t0.stop();
		taco::util::TimeResults r0 = t0.getResult();
		cout << "transpose_coo_01234:" << endl;
		cout << r0 << endl;
		t0.clear_cache();

		// (0, 1, 2, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t1;
		t1.start();
		transpose_coo_01243(A, size, order, dimensions);
		t1.stop();
		taco::util::TimeResults r1 = t1.getResult();
		cout << "transpose_coo_01243:" << endl;
		cout << r1 << endl;
		t1.clear_cache();

		// (0, 1, 3, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t2;
		t2.start();
		transpose_coo_01324(A, size, order, dimensions);
		t2.stop();
		taco::util::TimeResults r2 = t2.getResult();
		cout << "transpose_coo_01324:" << endl;
		cout << r2 << endl;
		t2.clear_cache();

		// (0, 1, 3, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t3;
		t3.start();
		transpose_coo_01342(A, size, order, dimensions);
		t3.stop();
		taco::util::TimeResults r3 = t3.getResult();
		cout << "transpose_coo_01342:" << endl;
		cout << r3 << endl;
		t3.clear_cache();

		// (0, 1, 4, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t4;
		t4.start();
		transpose_coo_01423(A, size, order, dimensions);
		t4.stop();
		taco::util::TimeResults r4 = t4.getResult();
		cout << "transpose_coo_01423:" << endl;
		cout << r4 << endl;
		t4.clear_cache();

		// (0, 1, 4, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t5;
		t5.start();
		transpose_coo_01432(A, size, order, dimensions);
		t5.stop();
		taco::util::TimeResults r5 = t5.getResult();
		cout << "transpose_coo_01432:" << endl;
		cout << r5 << endl;
		t5.clear_cache();

		// (0, 2, 1, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t6;
		t6.start();
		transpose_coo_02134(A, size, order, dimensions);
		t6.stop();
		taco::util::TimeResults r6 = t6.getResult();
		cout << "transpose_coo_02134:" << endl;
		cout << r6 << endl;
		t6.clear_cache();

		// (0, 2, 1, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t7;
		t7.start();
		transpose_coo_02143(A, size, order, dimensions);
		t7.stop();
		taco::util::TimeResults r7 = t7.getResult();
		cout << "transpose_coo_02143:" << endl;
		cout << r7 << endl;
		t7.clear_cache();

		// (0, 2, 3, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t8;
		t8.start();
		transpose_coo_02314(A, size, order, dimensions);
		t8.stop();
		taco::util::TimeResults r8 = t8.getResult();
		cout << "transpose_coo_02314:" << endl;
		cout << r8 << endl;
		t8.clear_cache();

		// (0, 2, 3, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t9;
		t9.start();
		transpose_coo_02341(A, size, order, dimensions);
		t9.stop();
		taco::util::TimeResults r9 = t9.getResult();
		cout << "transpose_coo_02341:" << endl;
		cout << r9 << endl;
		t9.clear_cache();

		// (0, 2, 4, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t10;
		t10.start();
		transpose_coo_02413(A, size, order, dimensions);
		t10.stop();
		taco::util::TimeResults r10 = t10.getResult();
		cout << "transpose_coo_02413:" << endl;
		cout << r10 << endl;
		t10.clear_cache();

		// (0, 2, 4, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t11;
		t11.start();
		transpose_coo_02431(A, size, order, dimensions);
		t11.stop();
		taco::util::TimeResults r11 = t11.getResult();
		cout << "transpose_coo_02431:" << endl;
		cout << r11 << endl;
		t11.clear_cache();

		// (0, 3, 1, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t12;
		t12.start();
		transpose_coo_03124(A, size, order, dimensions);
		t12.stop();
		taco::util::TimeResults r12 = t12.getResult();
		cout << "transpose_coo_03124:" << endl;
		cout << r12 << endl;
		t12.clear_cache();

		// (0, 3, 1, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t13;
		t13.start();
		transpose_coo_03142(A, size, order, dimensions);
		t13.stop();
		taco::util::TimeResults r13 = t13.getResult();
		cout << "transpose_coo_03142:" << endl;
		cout << r13 << endl;
		t13.clear_cache();

		// (0, 3, 2, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t14;
		t14.start();
		transpose_coo_03214(A, size, order, dimensions);
		t14.stop();
		taco::util::TimeResults r14 = t14.getResult();
		cout << "transpose_coo_03214:" << endl;
		cout << r14 << endl;
		t14.clear_cache();

		// (0, 3, 2, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t15;
		t15.start();
		transpose_coo_03241(A, size, order, dimensions);
		t15.stop();
		taco::util::TimeResults r15 = t15.getResult();
		cout << "transpose_coo_03241:" << endl;
		cout << r15 << endl;
		t15.clear_cache();

		// (0, 3, 4, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t16;
		t16.start();
		transpose_coo_03412(A, size, order, dimensions);
		t16.stop();
		taco::util::TimeResults r16 = t16.getResult();
		cout << "transpose_coo_03412:" << endl;
		cout << r16 << endl;
		t16.clear_cache();

		// (0, 3, 4, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t17;
		t17.start();
		transpose_coo_03421(A, size, order, dimensions);
		t17.stop();
		taco::util::TimeResults r17 = t17.getResult();
		cout << "transpose_coo_03421:" << endl;
		cout << r17 << endl;
		t17.clear_cache();

		// (0, 4, 1, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t18;
		t18.start();
		transpose_coo_04123(A, size, order, dimensions);
		t18.stop();
		taco::util::TimeResults r18 = t18.getResult();
		cout << "transpose_coo_04123:" << endl;
		cout << r18 << endl;
		t18.clear_cache();

		// (0, 4, 1, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t19;
		t19.start();
		transpose_coo_04132(A, size, order, dimensions);
		t19.stop();
		taco::util::TimeResults r19 = t19.getResult();
		cout << "transpose_coo_04132:" << endl;
		cout << r19 << endl;
		t19.clear_cache();

		// (0, 4, 2, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t20;
		t20.start();
		transpose_coo_04213(A, size, order, dimensions);
		t20.stop();
		taco::util::TimeResults r20 = t20.getResult();
		cout << "transpose_coo_04213:" << endl;
		cout << r20 << endl;
		t20.clear_cache();

		// (0, 4, 2, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t21;
		t21.start();
		transpose_coo_04231(A, size, order, dimensions);
		t21.stop();
		taco::util::TimeResults r21 = t21.getResult();
		cout << "transpose_coo_04231:" << endl;
		cout << r21 << endl;
		t21.clear_cache();

		// (0, 4, 3, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t22;
		t22.start();
		transpose_coo_04312(A, size, order, dimensions);
		t22.stop();
		taco::util::TimeResults r22 = t22.getResult();
		cout << "transpose_coo_04312:" << endl;
		cout << r22 << endl;
		t22.clear_cache();

		// (0, 4, 3, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t23;
		t23.start();
		transpose_coo_04321(A, size, order, dimensions);
		t23.stop();
		taco::util::TimeResults r23 = t23.getResult();
		cout << "transpose_coo_04321:" << endl;
		cout << r23 << endl;
		t23.clear_cache();

		// (1, 0, 2, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t24;
		t24.start();
		transpose_coo_10234(A, size, order, dimensions);
		t24.stop();
		taco::util::TimeResults r24 = t24.getResult();
		cout << "transpose_coo_10234:" << endl;
		cout << r24 << endl;
		t24.clear_cache();

		// (1, 0, 2, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t25;
		t25.start();
		transpose_coo_10243(A, size, order, dimensions);
		t25.stop();
		taco::util::TimeResults r25 = t25.getResult();
		cout << "transpose_coo_10243:" << endl;
		cout << r25 << endl;
		t25.clear_cache();

		// (1, 0, 3, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t26;
		t26.start();
		transpose_coo_10324(A, size, order, dimensions);
		t26.stop();
		taco::util::TimeResults r26 = t26.getResult();
		cout << "transpose_coo_10324:" << endl;
		cout << r26 << endl;
		t26.clear_cache();

		// (1, 0, 3, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t27;
		t27.start();
		transpose_coo_10342(A, size, order, dimensions);
		t27.stop();
		taco::util::TimeResults r27 = t27.getResult();
		cout << "transpose_coo_10342:" << endl;
		cout << r27 << endl;
		t27.clear_cache();

		// (1, 0, 4, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t28;
		t28.start();
		transpose_coo_10423(A, size, order, dimensions);
		t28.stop();
		taco::util::TimeResults r28 = t28.getResult();
		cout << "transpose_coo_10423:" << endl;
		cout << r28 << endl;
		t28.clear_cache();

		// (1, 0, 4, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t29;
		t29.start();
		transpose_coo_10432(A, size, order, dimensions);
		t29.stop();
		taco::util::TimeResults r29 = t29.getResult();
		cout << "transpose_coo_10432:" << endl;
		cout << r29 << endl;
		t29.clear_cache();

		// (1, 2, 0, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t30;
		t30.start();
		transpose_coo_12034(A, size, order, dimensions);
		t30.stop();
		taco::util::TimeResults r30 = t30.getResult();
		cout << "transpose_coo_12034:" << endl;
		cout << r30 << endl;
		t30.clear_cache();

		// (1, 2, 0, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t31;
		t31.start();
		transpose_coo_12043(A, size, order, dimensions);
		t31.stop();
		taco::util::TimeResults r31 = t31.getResult();
		cout << "transpose_coo_12043:" << endl;
		cout << r31 << endl;
		t31.clear_cache();

		// (1, 2, 3, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t32;
		t32.start();
		transpose_coo_12304(A, size, order, dimensions);
		t32.stop();
		taco::util::TimeResults r32 = t32.getResult();
		cout << "transpose_coo_12304:" << endl;
		cout << r32 << endl;
		t32.clear_cache();

		// (1, 2, 3, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t33;
		t33.start();
		transpose_coo_12340(A, size, order, dimensions);
		t33.stop();
		taco::util::TimeResults r33 = t33.getResult();
		cout << "transpose_coo_12340:" << endl;
		cout << r33 << endl;
		t33.clear_cache();

		// (1, 2, 4, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t34;
		t34.start();
		transpose_coo_12403(A, size, order, dimensions);
		t34.stop();
		taco::util::TimeResults r34 = t34.getResult();
		cout << "transpose_coo_12403:" << endl;
		cout << r34 << endl;
		t34.clear_cache();

		// (1, 2, 4, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t35;
		t35.start();
		transpose_coo_12430(A, size, order, dimensions);
		t35.stop();
		taco::util::TimeResults r35 = t35.getResult();
		cout << "transpose_coo_12430:" << endl;
		cout << r35 << endl;
		t35.clear_cache();

		// (1, 3, 0, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t36;
		t36.start();
		transpose_coo_13024(A, size, order, dimensions);
		t36.stop();
		taco::util::TimeResults r36 = t36.getResult();
		cout << "transpose_coo_13024:" << endl;
		cout << r36 << endl;
		t36.clear_cache();

		// (1, 3, 0, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t37;
		t37.start();
		transpose_coo_13042(A, size, order, dimensions);
		t37.stop();
		taco::util::TimeResults r37 = t37.getResult();
		cout << "transpose_coo_13042:" << endl;
		cout << r37 << endl;
		t37.clear_cache();

		// (1, 3, 2, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t38;
		t38.start();
		transpose_coo_13204(A, size, order, dimensions);
		t38.stop();
		taco::util::TimeResults r38 = t38.getResult();
		cout << "transpose_coo_13204:" << endl;
		cout << r38 << endl;
		t38.clear_cache();

		// (1, 3, 2, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t39;
		t39.start();
		transpose_coo_13240(A, size, order, dimensions);
		t39.stop();
		taco::util::TimeResults r39 = t39.getResult();
		cout << "transpose_coo_13240:" << endl;
		cout << r39 << endl;
		t39.clear_cache();

		// (1, 3, 4, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t40;
		t40.start();
		transpose_coo_13402(A, size, order, dimensions);
		t40.stop();
		taco::util::TimeResults r40 = t40.getResult();
		cout << "transpose_coo_13402:" << endl;
		cout << r40 << endl;
		t40.clear_cache();

		// (1, 3, 4, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t41;
		t41.start();
		transpose_coo_13420(A, size, order, dimensions);
		t41.stop();
		taco::util::TimeResults r41 = t41.getResult();
		cout << "transpose_coo_13420:" << endl;
		cout << r41 << endl;
		t41.clear_cache();

		// (1, 4, 0, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t42;
		t42.start();
		transpose_coo_14023(A, size, order, dimensions);
		t42.stop();
		taco::util::TimeResults r42 = t42.getResult();
		cout << "transpose_coo_14023:" << endl;
		cout << r42 << endl;
		t42.clear_cache();

		// (1, 4, 0, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t43;
		t43.start();
		transpose_coo_14032(A, size, order, dimensions);
		t43.stop();
		taco::util::TimeResults r43 = t43.getResult();
		cout << "transpose_coo_14032:" << endl;
		cout << r43 << endl;
		t43.clear_cache();

		// (1, 4, 2, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t44;
		t44.start();
		transpose_coo_14203(A, size, order, dimensions);
		t44.stop();
		taco::util::TimeResults r44 = t44.getResult();
		cout << "transpose_coo_14203:" << endl;
		cout << r44 << endl;
		t44.clear_cache();

		// (1, 4, 2, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t45;
		t45.start();
		transpose_coo_14230(A, size, order, dimensions);
		t45.stop();
		taco::util::TimeResults r45 = t45.getResult();
		cout << "transpose_coo_14230:" << endl;
		cout << r45 << endl;
		t45.clear_cache();

		// (1, 4, 3, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t46;
		t46.start();
		transpose_coo_14302(A, size, order, dimensions);
		t46.stop();
		taco::util::TimeResults r46 = t46.getResult();
		cout << "transpose_coo_14302:" << endl;
		cout << r46 << endl;
		t46.clear_cache();

		// (1, 4, 3, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t47;
		t47.start();
		transpose_coo_14320(A, size, order, dimensions);
		t47.stop();
		taco::util::TimeResults r47 = t47.getResult();
		cout << "transpose_coo_14320:" << endl;
		cout << r47 << endl;
		t47.clear_cache();

		// (2, 0, 1, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t48;
		t48.start();
		transpose_coo_20134(A, size, order, dimensions);
		t48.stop();
		taco::util::TimeResults r48 = t48.getResult();
		cout << "transpose_coo_20134:" << endl;
		cout << r48 << endl;
		t48.clear_cache();

		// (2, 0, 1, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t49;
		t49.start();
		transpose_coo_20143(A, size, order, dimensions);
		t49.stop();
		taco::util::TimeResults r49 = t49.getResult();
		cout << "transpose_coo_20143:" << endl;
		cout << r49 << endl;
		t49.clear_cache();

		// (2, 0, 3, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t50;
		t50.start();
		transpose_coo_20314(A, size, order, dimensions);
		t50.stop();
		taco::util::TimeResults r50 = t50.getResult();
		cout << "transpose_coo_20314:" << endl;
		cout << r50 << endl;
		t50.clear_cache();

		// (2, 0, 3, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t51;
		t51.start();
		transpose_coo_20341(A, size, order, dimensions);
		t51.stop();
		taco::util::TimeResults r51 = t51.getResult();
		cout << "transpose_coo_20341:" << endl;
		cout << r51 << endl;
		t51.clear_cache();

		// (2, 0, 4, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t52;
		t52.start();
		transpose_coo_20413(A, size, order, dimensions);
		t52.stop();
		taco::util::TimeResults r52 = t52.getResult();
		cout << "transpose_coo_20413:" << endl;
		cout << r52 << endl;
		t52.clear_cache();

		// (2, 0, 4, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t53;
		t53.start();
		transpose_coo_20431(A, size, order, dimensions);
		t53.stop();
		taco::util::TimeResults r53 = t53.getResult();
		cout << "transpose_coo_20431:" << endl;
		cout << r53 << endl;
		t53.clear_cache();

		// (2, 1, 0, 3, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t54;
		t54.start();
		transpose_coo_21034(A, size, order, dimensions);
		t54.stop();
		taco::util::TimeResults r54 = t54.getResult();
		cout << "transpose_coo_21034:" << endl;
		cout << r54 << endl;
		t54.clear_cache();

		// (2, 1, 0, 4, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t55;
		t55.start();
		transpose_coo_21043(A, size, order, dimensions);
		t55.stop();
		taco::util::TimeResults r55 = t55.getResult();
		cout << "transpose_coo_21043:" << endl;
		cout << r55 << endl;
		t55.clear_cache();

		// (2, 1, 3, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t56;
		t56.start();
		transpose_coo_21304(A, size, order, dimensions);
		t56.stop();
		taco::util::TimeResults r56 = t56.getResult();
		cout << "transpose_coo_21304:" << endl;
		cout << r56 << endl;
		t56.clear_cache();

		// (2, 1, 3, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t57;
		t57.start();
		transpose_coo_21340(A, size, order, dimensions);
		t57.stop();
		taco::util::TimeResults r57 = t57.getResult();
		cout << "transpose_coo_21340:" << endl;
		cout << r57 << endl;
		t57.clear_cache();

		// (2, 1, 4, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t58;
		t58.start();
		transpose_coo_21403(A, size, order, dimensions);
		t58.stop();
		taco::util::TimeResults r58 = t58.getResult();
		cout << "transpose_coo_21403:" << endl;
		cout << r58 << endl;
		t58.clear_cache();

		// (2, 1, 4, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t59;
		t59.start();
		transpose_coo_21430(A, size, order, dimensions);
		t59.stop();
		taco::util::TimeResults r59 = t59.getResult();
		cout << "transpose_coo_21430:" << endl;
		cout << r59 << endl;
		t59.clear_cache();

		// (2, 3, 0, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t60;
		t60.start();
		transpose_coo_23014(A, size, order, dimensions);
		t60.stop();
		taco::util::TimeResults r60 = t60.getResult();
		cout << "transpose_coo_23014:" << endl;
		cout << r60 << endl;
		t60.clear_cache();

		// (2, 3, 0, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t61;
		t61.start();
		transpose_coo_23041(A, size, order, dimensions);
		t61.stop();
		taco::util::TimeResults r61 = t61.getResult();
		cout << "transpose_coo_23041:" << endl;
		cout << r61 << endl;
		t61.clear_cache();

		// (2, 3, 1, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t62;
		t62.start();
		transpose_coo_23104(A, size, order, dimensions);
		t62.stop();
		taco::util::TimeResults r62 = t62.getResult();
		cout << "transpose_coo_23104:" << endl;
		cout << r62 << endl;
		t62.clear_cache();

		// (2, 3, 1, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t63;
		t63.start();
		transpose_coo_23140(A, size, order, dimensions);
		t63.stop();
		taco::util::TimeResults r63 = t63.getResult();
		cout << "transpose_coo_23140:" << endl;
		cout << r63 << endl;
		t63.clear_cache();

		// (2, 3, 4, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t64;
		t64.start();
		transpose_coo_23401(A, size, order, dimensions);
		t64.stop();
		taco::util::TimeResults r64 = t64.getResult();
		cout << "transpose_coo_23401:" << endl;
		cout << r64 << endl;
		t64.clear_cache();

		// (2, 3, 4, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t65;
		t65.start();
		transpose_coo_23410(A, size, order, dimensions);
		t65.stop();
		taco::util::TimeResults r65 = t65.getResult();
		cout << "transpose_coo_23410:" << endl;
		cout << r65 << endl;
		t65.clear_cache();

		// (2, 4, 0, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t66;
		t66.start();
		transpose_coo_24013(A, size, order, dimensions);
		t66.stop();
		taco::util::TimeResults r66 = t66.getResult();
		cout << "transpose_coo_24013:" << endl;
		cout << r66 << endl;
		t66.clear_cache();

		// (2, 4, 0, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t67;
		t67.start();
		transpose_coo_24031(A, size, order, dimensions);
		t67.stop();
		taco::util::TimeResults r67 = t67.getResult();
		cout << "transpose_coo_24031:" << endl;
		cout << r67 << endl;
		t67.clear_cache();

		// (2, 4, 1, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t68;
		t68.start();
		transpose_coo_24103(A, size, order, dimensions);
		t68.stop();
		taco::util::TimeResults r68 = t68.getResult();
		cout << "transpose_coo_24103:" << endl;
		cout << r68 << endl;
		t68.clear_cache();

		// (2, 4, 1, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t69;
		t69.start();
		transpose_coo_24130(A, size, order, dimensions);
		t69.stop();
		taco::util::TimeResults r69 = t69.getResult();
		cout << "transpose_coo_24130:" << endl;
		cout << r69 << endl;
		t69.clear_cache();

		// (2, 4, 3, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t70;
		t70.start();
		transpose_coo_24301(A, size, order, dimensions);
		t70.stop();
		taco::util::TimeResults r70 = t70.getResult();
		cout << "transpose_coo_24301:" << endl;
		cout << r70 << endl;
		t70.clear_cache();

		// (2, 4, 3, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t71;
		t71.start();
		transpose_coo_24310(A, size, order, dimensions);
		t71.stop();
		taco::util::TimeResults r71 = t71.getResult();
		cout << "transpose_coo_24310:" << endl;
		cout << r71 << endl;
		t71.clear_cache();

		// (3, 0, 1, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t72;
		t72.start();
		transpose_coo_30124(A, size, order, dimensions);
		t72.stop();
		taco::util::TimeResults r72 = t72.getResult();
		cout << "transpose_coo_30124:" << endl;
		cout << r72 << endl;
		t72.clear_cache();

		// (3, 0, 1, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t73;
		t73.start();
		transpose_coo_30142(A, size, order, dimensions);
		t73.stop();
		taco::util::TimeResults r73 = t73.getResult();
		cout << "transpose_coo_30142:" << endl;
		cout << r73 << endl;
		t73.clear_cache();

		// (3, 0, 2, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t74;
		t74.start();
		transpose_coo_30214(A, size, order, dimensions);
		t74.stop();
		taco::util::TimeResults r74 = t74.getResult();
		cout << "transpose_coo_30214:" << endl;
		cout << r74 << endl;
		t74.clear_cache();

		// (3, 0, 2, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t75;
		t75.start();
		transpose_coo_30241(A, size, order, dimensions);
		t75.stop();
		taco::util::TimeResults r75 = t75.getResult();
		cout << "transpose_coo_30241:" << endl;
		cout << r75 << endl;
		t75.clear_cache();

		// (3, 0, 4, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t76;
		t76.start();
		transpose_coo_30412(A, size, order, dimensions);
		t76.stop();
		taco::util::TimeResults r76 = t76.getResult();
		cout << "transpose_coo_30412:" << endl;
		cout << r76 << endl;
		t76.clear_cache();

		// (3, 0, 4, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t77;
		t77.start();
		transpose_coo_30421(A, size, order, dimensions);
		t77.stop();
		taco::util::TimeResults r77 = t77.getResult();
		cout << "transpose_coo_30421:" << endl;
		cout << r77 << endl;
		t77.clear_cache();

		// (3, 1, 0, 2, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t78;
		t78.start();
		transpose_coo_31024(A, size, order, dimensions);
		t78.stop();
		taco::util::TimeResults r78 = t78.getResult();
		cout << "transpose_coo_31024:" << endl;
		cout << r78 << endl;
		t78.clear_cache();

		// (3, 1, 0, 4, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t79;
		t79.start();
		transpose_coo_31042(A, size, order, dimensions);
		t79.stop();
		taco::util::TimeResults r79 = t79.getResult();
		cout << "transpose_coo_31042:" << endl;
		cout << r79 << endl;
		t79.clear_cache();

		// (3, 1, 2, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t80;
		t80.start();
		transpose_coo_31204(A, size, order, dimensions);
		t80.stop();
		taco::util::TimeResults r80 = t80.getResult();
		cout << "transpose_coo_31204:" << endl;
		cout << r80 << endl;
		t80.clear_cache();

		// (3, 1, 2, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t81;
		t81.start();
		transpose_coo_31240(A, size, order, dimensions);
		t81.stop();
		taco::util::TimeResults r81 = t81.getResult();
		cout << "transpose_coo_31240:" << endl;
		cout << r81 << endl;
		t81.clear_cache();

		// (3, 1, 4, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t82;
		t82.start();
		transpose_coo_31402(A, size, order, dimensions);
		t82.stop();
		taco::util::TimeResults r82 = t82.getResult();
		cout << "transpose_coo_31402:" << endl;
		cout << r82 << endl;
		t82.clear_cache();

		// (3, 1, 4, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t83;
		t83.start();
		transpose_coo_31420(A, size, order, dimensions);
		t83.stop();
		taco::util::TimeResults r83 = t83.getResult();
		cout << "transpose_coo_31420:" << endl;
		cout << r83 << endl;
		t83.clear_cache();

		// (3, 2, 0, 1, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t84;
		t84.start();
		transpose_coo_32014(A, size, order, dimensions);
		t84.stop();
		taco::util::TimeResults r84 = t84.getResult();
		cout << "transpose_coo_32014:" << endl;
		cout << r84 << endl;
		t84.clear_cache();

		// (3, 2, 0, 4, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t85;
		t85.start();
		transpose_coo_32041(A, size, order, dimensions);
		t85.stop();
		taco::util::TimeResults r85 = t85.getResult();
		cout << "transpose_coo_32041:" << endl;
		cout << r85 << endl;
		t85.clear_cache();

		// (3, 2, 1, 0, 4)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t86;
		t86.start();
		transpose_coo_32104(A, size, order, dimensions);
		t86.stop();
		taco::util::TimeResults r86 = t86.getResult();
		cout << "transpose_coo_32104:" << endl;
		cout << r86 << endl;
		t86.clear_cache();

		// (3, 2, 1, 4, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t87;
		t87.start();
		transpose_coo_32140(A, size, order, dimensions);
		t87.stop();
		taco::util::TimeResults r87 = t87.getResult();
		cout << "transpose_coo_32140:" << endl;
		cout << r87 << endl;
		t87.clear_cache();

		// (3, 2, 4, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t88;
		t88.start();
		transpose_coo_32401(A, size, order, dimensions);
		t88.stop();
		taco::util::TimeResults r88 = t88.getResult();
		cout << "transpose_coo_32401:" << endl;
		cout << r88 << endl;
		t88.clear_cache();

		// (3, 2, 4, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t89;
		t89.start();
		transpose_coo_32410(A, size, order, dimensions);
		t89.stop();
		taco::util::TimeResults r89 = t89.getResult();
		cout << "transpose_coo_32410:" << endl;
		cout << r89 << endl;
		t89.clear_cache();

		// (3, 4, 0, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t90;
		t90.start();
		transpose_coo_34012(A, size, order, dimensions);
		t90.stop();
		taco::util::TimeResults r90 = t90.getResult();
		cout << "transpose_coo_34012:" << endl;
		cout << r90 << endl;
		t90.clear_cache();

		// (3, 4, 0, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t91;
		t91.start();
		transpose_coo_34021(A, size, order, dimensions);
		t91.stop();
		taco::util::TimeResults r91 = t91.getResult();
		cout << "transpose_coo_34021:" << endl;
		cout << r91 << endl;
		t91.clear_cache();

		// (3, 4, 1, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t92;
		t92.start();
		transpose_coo_34102(A, size, order, dimensions);
		t92.stop();
		taco::util::TimeResults r92 = t92.getResult();
		cout << "transpose_coo_34102:" << endl;
		cout << r92 << endl;
		t92.clear_cache();

		// (3, 4, 1, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t93;
		t93.start();
		transpose_coo_34120(A, size, order, dimensions);
		t93.stop();
		taco::util::TimeResults r93 = t93.getResult();
		cout << "transpose_coo_34120:" << endl;
		cout << r93 << endl;
		t93.clear_cache();

		// (3, 4, 2, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t94;
		t94.start();
		transpose_coo_34201(A, size, order, dimensions);
		t94.stop();
		taco::util::TimeResults r94 = t94.getResult();
		cout << "transpose_coo_34201:" << endl;
		cout << r94 << endl;
		t94.clear_cache();

		// (3, 4, 2, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t95;
		t95.start();
		transpose_coo_34210(A, size, order, dimensions);
		t95.stop();
		taco::util::TimeResults r95 = t95.getResult();
		cout << "transpose_coo_34210:" << endl;
		cout << r95 << endl;
		t95.clear_cache();

		// (4, 0, 1, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t96;
		t96.start();
		transpose_coo_40123(A, size, order, dimensions);
		t96.stop();
		taco::util::TimeResults r96 = t96.getResult();
		cout << "transpose_coo_40123:" << endl;
		cout << r96 << endl;
		t96.clear_cache();

		// (4, 0, 1, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t97;
		t97.start();
		transpose_coo_40132(A, size, order, dimensions);
		t97.stop();
		taco::util::TimeResults r97 = t97.getResult();
		cout << "transpose_coo_40132:" << endl;
		cout << r97 << endl;
		t97.clear_cache();

		// (4, 0, 2, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t98;
		t98.start();
		transpose_coo_40213(A, size, order, dimensions);
		t98.stop();
		taco::util::TimeResults r98 = t98.getResult();
		cout << "transpose_coo_40213:" << endl;
		cout << r98 << endl;
		t98.clear_cache();

		// (4, 0, 2, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t99;
		t99.start();
		transpose_coo_40231(A, size, order, dimensions);
		t99.stop();
		taco::util::TimeResults r99 = t99.getResult();
		cout << "transpose_coo_40231:" << endl;
		cout << r99 << endl;
		t99.clear_cache();

		// (4, 0, 3, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t100;
		t100.start();
		transpose_coo_40312(A, size, order, dimensions);
		t100.stop();
		taco::util::TimeResults r100 = t100.getResult();
		cout << "transpose_coo_40312:" << endl;
		cout << r100 << endl;
		t100.clear_cache();

		// (4, 0, 3, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t101;
		t101.start();
		transpose_coo_40321(A, size, order, dimensions);
		t101.stop();
		taco::util::TimeResults r101 = t101.getResult();
		cout << "transpose_coo_40321:" << endl;
		cout << r101 << endl;
		t101.clear_cache();

		// (4, 1, 0, 2, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t102;
		t102.start();
		transpose_coo_41023(A, size, order, dimensions);
		t102.stop();
		taco::util::TimeResults r102 = t102.getResult();
		cout << "transpose_coo_41023:" << endl;
		cout << r102 << endl;
		t102.clear_cache();

		// (4, 1, 0, 3, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t103;
		t103.start();
		transpose_coo_41032(A, size, order, dimensions);
		t103.stop();
		taco::util::TimeResults r103 = t103.getResult();
		cout << "transpose_coo_41032:" << endl;
		cout << r103 << endl;
		t103.clear_cache();

		// (4, 1, 2, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t104;
		t104.start();
		transpose_coo_41203(A, size, order, dimensions);
		t104.stop();
		taco::util::TimeResults r104 = t104.getResult();
		cout << "transpose_coo_41203:" << endl;
		cout << r104 << endl;
		t104.clear_cache();

		// (4, 1, 2, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t105;
		t105.start();
		transpose_coo_41230(A, size, order, dimensions);
		t105.stop();
		taco::util::TimeResults r105 = t105.getResult();
		cout << "transpose_coo_41230:" << endl;
		cout << r105 << endl;
		t105.clear_cache();

		// (4, 1, 3, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t106;
		t106.start();
		transpose_coo_41302(A, size, order, dimensions);
		t106.stop();
		taco::util::TimeResults r106 = t106.getResult();
		cout << "transpose_coo_41302:" << endl;
		cout << r106 << endl;
		t106.clear_cache();

		// (4, 1, 3, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t107;
		t107.start();
		transpose_coo_41320(A, size, order, dimensions);
		t107.stop();
		taco::util::TimeResults r107 = t107.getResult();
		cout << "transpose_coo_41320:" << endl;
		cout << r107 << endl;
		t107.clear_cache();

		// (4, 2, 0, 1, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t108;
		t108.start();
		transpose_coo_42013(A, size, order, dimensions);
		t108.stop();
		taco::util::TimeResults r108 = t108.getResult();
		cout << "transpose_coo_42013:" << endl;
		cout << r108 << endl;
		t108.clear_cache();

		// (4, 2, 0, 3, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t109;
		t109.start();
		transpose_coo_42031(A, size, order, dimensions);
		t109.stop();
		taco::util::TimeResults r109 = t109.getResult();
		cout << "transpose_coo_42031:" << endl;
		cout << r109 << endl;
		t109.clear_cache();

		// (4, 2, 1, 0, 3)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t110;
		t110.start();
		transpose_coo_42103(A, size, order, dimensions);
		t110.stop();
		taco::util::TimeResults r110 = t110.getResult();
		cout << "transpose_coo_42103:" << endl;
		cout << r110 << endl;
		t110.clear_cache();

		// (4, 2, 1, 3, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t111;
		t111.start();
		transpose_coo_42130(A, size, order, dimensions);
		t111.stop();
		taco::util::TimeResults r111 = t111.getResult();
		cout << "transpose_coo_42130:" << endl;
		cout << r111 << endl;
		t111.clear_cache();

		// (4, 2, 3, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t112;
		t112.start();
		transpose_coo_42301(A, size, order, dimensions);
		t112.stop();
		taco::util::TimeResults r112 = t112.getResult();
		cout << "transpose_coo_42301:" << endl;
		cout << r112 << endl;
		t112.clear_cache();

		// (4, 2, 3, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t113;
		t113.start();
		transpose_coo_42310(A, size, order, dimensions);
		t113.stop();
		taco::util::TimeResults r113 = t113.getResult();
		cout << "transpose_coo_42310:" << endl;
		cout << r113 << endl;
		t113.clear_cache();

		// (4, 3, 0, 1, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t114;
		t114.start();
		transpose_coo_43012(A, size, order, dimensions);
		t114.stop();
		taco::util::TimeResults r114 = t114.getResult();
		cout << "transpose_coo_43012:" << endl;
		cout << r114 << endl;
		t114.clear_cache();

		// (4, 3, 0, 2, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t115;
		t115.start();
		transpose_coo_43021(A, size, order, dimensions);
		t115.stop();
		taco::util::TimeResults r115 = t115.getResult();
		cout << "transpose_coo_43021:" << endl;
		cout << r115 << endl;
		t115.clear_cache();

		// (4, 3, 1, 0, 2)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t116;
		t116.start();
		transpose_coo_43102(A, size, order, dimensions);
		t116.stop();
		taco::util::TimeResults r116 = t116.getResult();
		cout << "transpose_coo_43102:" << endl;
		cout << r116 << endl;
		t116.clear_cache();

		// (4, 3, 1, 2, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t117;
		t117.start();
		transpose_coo_43120(A, size, order, dimensions);
		t117.stop();
		taco::util::TimeResults r117 = t117.getResult();
		cout << "transpose_coo_43120:" << endl;
		cout << r117 << endl;
		t117.clear_cache();

		// (4, 3, 2, 0, 1)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t118;
		t118.start();
		transpose_coo_43201(A, size, order, dimensions);
		t118.stop();
		taco::util::TimeResults r118 = t118.getResult();
		cout << "transpose_coo_43201:" << endl;
		cout << r118 << endl;
		t118.clear_cache();

		// (4, 3, 2, 1, 0)
		qsort(A, size, sizeof(struct coo_t), cmp_01234);
		taco::util::Timer t119;
		t119.start();
		transpose_coo_43210(A, size, order, dimensions);
		t119.stop();
		taco::util::TimeResults r119 = t119.getResult();
		cout << "transpose_coo_43210:" << endl;
		cout << r119 << endl;
		t119.clear_cache();





}

// transpose permutes the modes of the coordinates to be (0, 1, 2, 3, 4)
int transpose_coo_01234(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 2, 3, 4)
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 2, 4, 3)
int transpose_coo_01243(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 2, 4, 3)
	// Fix and sort on [0, 1, 2]
	// Create buckets and quotient
	int *bucket_4012 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4012 = (int *)malloc(c_size*sizeof(int));
	int current_4012 = 0;
	bucket_4012[0] = 0;
	quotient_4012[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4012++;
			quotient_4012[current_4012] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4012++;
			quotient_4012[current_4012] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4012++;
			quotient_4012[current_4012] = i;
		}
		bucket_4012[i] = current_4012;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4012[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4012[bucket_4012[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4012[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_4012);
	free(quotient_4012);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 2, 4)
int transpose_coo_01324(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 2, 4)
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
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_301[bucket_301[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_301[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_301);
	free(quotient_301);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 3, 4, 2)
int transpose_coo_01342(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 3, 4, 2)
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_401 = (int *)malloc(c_size*sizeof(int));
	int *quotient_401 = (int *)malloc(c_size*sizeof(int));
	int current_401 = 0;
	bucket_401[0] = 0;
	quotient_401[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_401++;
			quotient_401[current_401] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_401++;
			quotient_401[current_401] = i;
		}
		bucket_401[i] = current_401;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_401[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_401[bucket_401[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_401[perm[i]] ++;
	}
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
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_301[bucket_301[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_301[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_401);
	free(quotient_401);
	free(B3_count);
	free(bucket_301);
	free(quotient_301);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 4, 2, 3)
int transpose_coo_01423(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 4, 2, 3)
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_401 = (int *)malloc(c_size*sizeof(int));
	int *quotient_401 = (int *)malloc(c_size*sizeof(int));
	int current_401 = 0;
	bucket_401[0] = 0;
	quotient_401[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_401++;
			quotient_401[current_401] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_401++;
			quotient_401[current_401] = i;
		}
		bucket_401[i] = current_401;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_401[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_401[bucket_401[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_401[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_401);
	free(quotient_401);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 1, 4, 3, 2)
int transpose_coo_01432(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 1, 4, 3, 2)
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
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_301[bucket_301[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_301[perm[i]] ++;
	}
	// Fix and sort on [0, 1]
	// Create buckets and quotient
	int *bucket_401 = (int *)malloc(c_size*sizeof(int));
	int *quotient_401 = (int *)malloc(c_size*sizeof(int));
	int current_401 = 0;
	bucket_401[0] = 0;
	quotient_401[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_401++;
			quotient_401[current_401] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_401++;
			quotient_401[current_401] = i;
		}
		bucket_401[i] = current_401;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_401[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_401[bucket_401[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_401[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_301);
	free(quotient_301);
	free(B4_count);
	free(bucket_401);
	free(quotient_401);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 3, 4)
int transpose_coo_02134(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 3, 4)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 1, 4, 3)
int transpose_coo_02143(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 1, 4, 3)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Fix and sort on [0, 2, 1]
	// Create buckets and quotient
	int *bucket_4021 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4021 = (int *)malloc(c_size*sizeof(int));
	int current_4021 = 0;
	bucket_4021[0] = 0;
	quotient_4021[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4021++;
			quotient_4021[current_4021] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4021++;
			quotient_4021[current_4021] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4021++;
			quotient_4021[current_4021] = i;
		}
		bucket_4021[i] = current_4021;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4021[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4021[bucket_4021[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4021[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B4_count);
	free(bucket_4021);
	free(quotient_4021);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 1, 4)
int transpose_coo_02314(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 1, 4)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 3, 4, 1)
int transpose_coo_02341(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 3, 4, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 4, 1, 3)
int transpose_coo_02413(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 4, 1, 3)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 2, 4, 3, 1)
int transpose_coo_02431(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 2, 4, 3, 1)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 2, 4)
int transpose_coo_03124(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 2, 4)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 1, 4, 2)
int transpose_coo_03142(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 1, 4, 2)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Fix and sort on [0, 3, 1]
	// Create buckets and quotient
	int *bucket_4031 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4031 = (int *)malloc(c_size*sizeof(int));
	int current_4031 = 0;
	bucket_4031[0] = 0;
	quotient_4031[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4031++;
			quotient_4031[current_4031] = i;
		}
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4031++;
			quotient_4031[current_4031] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4031++;
			quotient_4031[current_4031] = i;
		}
		bucket_4031[i] = current_4031;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4031[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4031[bucket_4031[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4031[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B4_count);
	free(bucket_4031);
	free(quotient_4031);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 1, 4)
int transpose_coo_03214(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 1, 4)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 2, 4, 1)
int transpose_coo_03241(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 2, 4, 1)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 4, 1, 2)
int transpose_coo_03412(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 4, 1, 2)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 3, 4, 2, 1)
int transpose_coo_03421(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 3, 4, 2, 1)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 1, 2, 3)
int transpose_coo_04123(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 1, 2, 3)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 1, 3, 2)
int transpose_coo_04132(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 1, 3, 2)
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Fix and sort on [0, 4, 1]
	// Create buckets and quotient
	int *bucket_3041 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3041 = (int *)malloc(c_size*sizeof(int));
	int current_3041 = 0;
	bucket_3041[0] = 0;
	quotient_3041[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3041++;
			quotient_3041[current_3041] = i;
		}
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3041++;
			quotient_3041[current_3041] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_3041++;
			quotient_3041[current_3041] = i;
		}
		bucket_3041[i] = current_3041;
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
		perm[idx] = bucket_3041[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3041[bucket_3041[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3041[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	free(B3_count);
	free(bucket_3041);
	free(quotient_3041);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 2, 1, 3)
int transpose_coo_04213(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 2, 1, 3)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 2, 3, 1)
int transpose_coo_04231(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 2, 3, 1)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 3, 1, 2)
int transpose_coo_04312(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 3, 1, 2)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	return 0;
}
// transpose permutes the modes of the coordinates to be (0, 4, 3, 2, 1)
int transpose_coo_04321(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (0, 4, 3, 2, 1)
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_20[bucket_20[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_20[perm[i]] ++;
	}
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_30[bucket_30[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_30[perm[i]] ++;
	}
	// Fix and sort on [0]
	// Create buckets and quotient
	int *bucket_40 = (int *)malloc(c_size*sizeof(int));
	int *quotient_40 = (int *)malloc(c_size*sizeof(int));
	int current_40 = 0;
	bucket_40[0] = 0;
	quotient_40[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_40++;
			quotient_40[current_40] = i;
		}
		bucket_40[i] = current_40;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_40[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_40[bucket_40[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_40[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(bucket_20);
	free(quotient_20);
	free(B3_count);
	free(bucket_30);
	free(quotient_30);
	free(B4_count);
	free(bucket_40);
	free(quotient_40);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 3, 4)
int transpose_coo_10234(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 3, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 2, 4, 3)
int transpose_coo_10243(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 2, 4, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 0, 2]
	// Create buckets and quotient
	int *bucket_4102 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4102 = (int *)malloc(c_size*sizeof(int));
	int current_4102 = 0;
	bucket_4102[0] = 0;
	quotient_4102[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4102++;
			quotient_4102[current_4102] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4102++;
			quotient_4102[current_4102] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4102++;
			quotient_4102[current_4102] = i;
		}
		bucket_4102[i] = current_4102;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4102[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4102[bucket_4102[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4102[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(bucket_4102);
	free(quotient_4102);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 2, 4)
int transpose_coo_10324(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 2, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_310[bucket_310[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_310[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(bucket_310);
	free(quotient_310);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 3, 4, 2)
int transpose_coo_10342(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 3, 4, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 0]
	// Create buckets and quotient
	int *bucket_410 = (int *)malloc(c_size*sizeof(int));
	int *quotient_410 = (int *)malloc(c_size*sizeof(int));
	int current_410 = 0;
	bucket_410[0] = 0;
	quotient_410[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_410++;
			quotient_410[current_410] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_410++;
			quotient_410[current_410] = i;
		}
		bucket_410[i] = current_410;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_410[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_410[bucket_410[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_410[perm[i]] ++;
	}
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_310[bucket_310[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_310[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(bucket_410);
	free(quotient_410);
	free(B3_count);
	free(bucket_310);
	free(quotient_310);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 4, 2, 3)
int transpose_coo_10423(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 4, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 0]
	// Create buckets and quotient
	int *bucket_410 = (int *)malloc(c_size*sizeof(int));
	int *quotient_410 = (int *)malloc(c_size*sizeof(int));
	int current_410 = 0;
	bucket_410[0] = 0;
	quotient_410[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_410++;
			quotient_410[current_410] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_410++;
			quotient_410[current_410] = i;
		}
		bucket_410[i] = current_410;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_410[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_410[bucket_410[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_410[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(bucket_410);
	free(quotient_410);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 0, 4, 3, 2)
int transpose_coo_10432(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 0, 4, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_310[bucket_310[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_310[perm[i]] ++;
	}
	// Fix and sort on [1, 0]
	// Create buckets and quotient
	int *bucket_410 = (int *)malloc(c_size*sizeof(int));
	int *quotient_410 = (int *)malloc(c_size*sizeof(int));
	int current_410 = 0;
	bucket_410[0] = 0;
	quotient_410[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_410++;
			quotient_410[current_410] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_410++;
			quotient_410[current_410] = i;
		}
		bucket_410[i] = current_410;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_410[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_410[bucket_410[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_410[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(bucket_310);
	free(quotient_310);
	free(B4_count);
	free(bucket_410);
	free(quotient_410);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 3, 4)
int transpose_coo_12034(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 3, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 0, 4, 3)
int transpose_coo_12043(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 0, 4, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 2, 0]
	// Create buckets and quotient
	int *bucket_4120 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4120 = (int *)malloc(c_size*sizeof(int));
	int current_4120 = 0;
	bucket_4120[0] = 0;
	quotient_4120[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4120++;
			quotient_4120[current_4120] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4120++;
			quotient_4120[current_4120] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4120++;
			quotient_4120[current_4120] = i;
		}
		bucket_4120[i] = current_4120;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4120[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4120[bucket_4120[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4120[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B4_count);
	free(bucket_4120);
	free(quotient_4120);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 0, 4)
int transpose_coo_12304(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 0, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 3, 4, 0)
int transpose_coo_12340(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 3, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(B2_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 4, 0, 3)
int transpose_coo_12403(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 4, 0, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 2, 4, 3, 0)
int transpose_coo_12430(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 2, 4, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(B2_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 2, 4)
int transpose_coo_13024(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 2, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 0, 4, 2)
int transpose_coo_13042(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 0, 4, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 3, 0]
	// Create buckets and quotient
	int *bucket_4130 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4130 = (int *)malloc(c_size*sizeof(int));
	int current_4130 = 0;
	bucket_4130[0] = 0;
	quotient_4130[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4130++;
			quotient_4130[current_4130] = i;
		}
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4130++;
			quotient_4130[current_4130] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4130++;
			quotient_4130[current_4130] = i;
		}
		bucket_4130[i] = current_4130;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4130[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4130[bucket_4130[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4130[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	free(B4_count);
	free(bucket_4130);
	free(quotient_4130);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 0, 4)
int transpose_coo_13204(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 0, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 2, 4, 0)
int transpose_coo_13240(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 2, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(B3_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 4, 0, 2)
int transpose_coo_13402(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 4, 0, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 3, 4, 2, 0)
int transpose_coo_13420(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 3, 4, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(B3_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 0, 2, 3)
int transpose_coo_14023(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 0, 2, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 0, 3, 2)
int transpose_coo_14032(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 0, 3, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Fix and sort on [1, 4, 0]
	// Create buckets and quotient
	int *bucket_3140 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3140 = (int *)malloc(c_size*sizeof(int));
	int current_3140 = 0;
	bucket_3140[0] = 0;
	quotient_3140[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_3140++;
			quotient_3140[current_3140] = i;
		}
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3140++;
			quotient_3140[current_3140] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3140++;
			quotient_3140[current_3140] = i;
		}
		bucket_3140[i] = current_3140;
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
		perm[idx] = bucket_3140[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3140[bucket_3140[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3140[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	free(B3_count);
	free(bucket_3140);
	free(quotient_3140);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 2, 0, 3)
int transpose_coo_14203(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 2, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 2, 3, 0)
int transpose_coo_14230(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 2, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(B4_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 3, 0, 2)
int transpose_coo_14302(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 3, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (1, 4, 3, 2, 0)
int transpose_coo_14320(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (1, 4, 3, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(B4_count);
	free(B1_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 3, 4)
int transpose_coo_20134(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 3, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 1, 4, 3)
int transpose_coo_20143(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 1, 4, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 0, 1]
	// Create buckets and quotient
	int *bucket_4201 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4201 = (int *)malloc(c_size*sizeof(int));
	int current_4201 = 0;
	bucket_4201[0] = 0;
	quotient_4201[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4201++;
			quotient_4201[current_4201] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4201++;
			quotient_4201[current_4201] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4201++;
			quotient_4201[current_4201] = i;
		}
		bucket_4201[i] = current_4201;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4201[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4201[bucket_4201[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4201[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(bucket_4201);
	free(quotient_4201);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 1, 4)
int transpose_coo_20314(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 1, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_320[bucket_320[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_320[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(bucket_320);
	free(quotient_320);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 3, 4, 1)
int transpose_coo_20341(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 3, 4, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 0]
	// Create buckets and quotient
	int *bucket_420 = (int *)malloc(c_size*sizeof(int));
	int *quotient_420 = (int *)malloc(c_size*sizeof(int));
	int current_420 = 0;
	bucket_420[0] = 0;
	quotient_420[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_420++;
			quotient_420[current_420] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_420++;
			quotient_420[current_420] = i;
		}
		bucket_420[i] = current_420;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_420[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_420[bucket_420[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_420[perm[i]] ++;
	}
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_320[bucket_320[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_320[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(bucket_420);
	free(quotient_420);
	free(B3_count);
	free(bucket_320);
	free(quotient_320);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 4, 1, 3)
int transpose_coo_20413(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 4, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 0]
	// Create buckets and quotient
	int *bucket_420 = (int *)malloc(c_size*sizeof(int));
	int *quotient_420 = (int *)malloc(c_size*sizeof(int));
	int current_420 = 0;
	bucket_420[0] = 0;
	quotient_420[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_420++;
			quotient_420[current_420] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_420++;
			quotient_420[current_420] = i;
		}
		bucket_420[i] = current_420;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_420[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_420[bucket_420[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_420[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(bucket_420);
	free(quotient_420);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 0, 4, 3, 1)
int transpose_coo_20431(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 0, 4, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_320[bucket_320[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_320[perm[i]] ++;
	}
	// Fix and sort on [2, 0]
	// Create buckets and quotient
	int *bucket_420 = (int *)malloc(c_size*sizeof(int));
	int *quotient_420 = (int *)malloc(c_size*sizeof(int));
	int current_420 = 0;
	bucket_420[0] = 0;
	quotient_420[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_420++;
			quotient_420[current_420] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_420++;
			quotient_420[current_420] = i;
		}
		bucket_420[i] = current_420;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_420[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_420[bucket_420[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_420[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(bucket_320);
	free(quotient_320);
	free(B4_count);
	free(bucket_420);
	free(quotient_420);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 3, 4)
int transpose_coo_21034(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 3, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 0, 4, 3)
int transpose_coo_21043(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 0, 4, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 1, 0]
	// Create buckets and quotient
	int *bucket_4210 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4210 = (int *)malloc(c_size*sizeof(int));
	int current_4210 = 0;
	bucket_4210[0] = 0;
	quotient_4210[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4210++;
			quotient_4210[current_4210] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4210++;
			quotient_4210[current_4210] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4210++;
			quotient_4210[current_4210] = i;
		}
		bucket_4210[i] = current_4210;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4210[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4210[bucket_4210[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4210[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B4_count);
	free(bucket_4210);
	free(quotient_4210);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 0, 4)
int transpose_coo_21304(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 0, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 3, 4, 0)
int transpose_coo_21340(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 3, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(B1_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 4, 0, 3)
int transpose_coo_21403(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 4, 0, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 1, 4, 3, 0)
int transpose_coo_21430(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 1, 4, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(B1_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 1, 4)
int transpose_coo_23014(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 1, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 0, 4, 1)
int transpose_coo_23041(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 0, 4, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 3, 0]
	// Create buckets and quotient
	int *bucket_4230 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4230 = (int *)malloc(c_size*sizeof(int));
	int current_4230 = 0;
	bucket_4230[0] = 0;
	quotient_4230[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4230++;
			quotient_4230[current_4230] = i;
		}
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4230++;
			quotient_4230[current_4230] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4230++;
			quotient_4230[current_4230] = i;
		}
		bucket_4230[i] = current_4230;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4230[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4230[bucket_4230[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4230[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(B4_count);
	free(bucket_4230);
	free(quotient_4230);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 0, 4)
int transpose_coo_23104(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 0, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 1, 4, 0)
int transpose_coo_23140(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 1, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	free(B3_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 4, 0, 1)
int transpose_coo_23401(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 4, 0, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 3, 4, 1, 0)
int transpose_coo_23410(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 3, 4, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(B3_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 0, 1, 3)
int transpose_coo_24013(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 0, 1, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 0, 3, 1)
int transpose_coo_24031(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 0, 3, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Fix and sort on [2, 4, 0]
	// Create buckets and quotient
	int *bucket_3240 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3240 = (int *)malloc(c_size*sizeof(int));
	int current_3240 = 0;
	bucket_3240[0] = 0;
	quotient_3240[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_3240++;
			quotient_3240[current_3240] = i;
		}
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3240++;
			quotient_3240[current_3240] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3240++;
			quotient_3240[current_3240] = i;
		}
		bucket_3240[i] = current_3240;
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
		perm[idx] = bucket_3240[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3240[bucket_3240[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3240[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(B3_count);
	free(bucket_3240);
	free(quotient_3240);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 1, 0, 3)
int transpose_coo_24103(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 1, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 1, 3, 0)
int transpose_coo_24130(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 1, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	free(B4_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 3, 0, 1)
int transpose_coo_24301(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 3, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (2, 4, 3, 1, 0)
int transpose_coo_24310(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (2, 4, 3, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(B4_count);
	free(B2_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 2, 4)
int transpose_coo_30124(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 2, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 1, 4, 2)
int transpose_coo_30142(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 1, 4, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 0, 1]
	// Create buckets and quotient
	int *bucket_4301 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4301 = (int *)malloc(c_size*sizeof(int));
	int current_4301 = 0;
	bucket_4301[0] = 0;
	quotient_4301[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4301++;
			quotient_4301[current_4301] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4301++;
			quotient_4301[current_4301] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4301++;
			quotient_4301[current_4301] = i;
		}
		bucket_4301[i] = current_4301;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4301[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4301[bucket_4301[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4301[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(bucket_4301);
	free(quotient_4301);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 1, 4)
int transpose_coo_30214(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 1, 4)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_230[bucket_230[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_230[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(bucket_230);
	free(quotient_230);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 2, 4, 1)
int transpose_coo_30241(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 2, 4, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 0]
	// Create buckets and quotient
	int *bucket_430 = (int *)malloc(c_size*sizeof(int));
	int *quotient_430 = (int *)malloc(c_size*sizeof(int));
	int current_430 = 0;
	bucket_430[0] = 0;
	quotient_430[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_430++;
			quotient_430[current_430] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_430++;
			quotient_430[current_430] = i;
		}
		bucket_430[i] = current_430;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_430[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_430[bucket_430[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_430[perm[i]] ++;
	}
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_230[bucket_230[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_230[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(bucket_430);
	free(quotient_430);
	free(B2_count);
	free(bucket_230);
	free(quotient_230);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 4, 1, 2)
int transpose_coo_30412(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 4, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 0]
	// Create buckets and quotient
	int *bucket_430 = (int *)malloc(c_size*sizeof(int));
	int *quotient_430 = (int *)malloc(c_size*sizeof(int));
	int current_430 = 0;
	bucket_430[0] = 0;
	quotient_430[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_430++;
			quotient_430[current_430] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_430++;
			quotient_430[current_430] = i;
		}
		bucket_430[i] = current_430;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_430[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_430[bucket_430[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_430[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(bucket_430);
	free(quotient_430);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 0, 4, 2, 1)
int transpose_coo_30421(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 0, 4, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
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

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_230[bucket_230[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_230[perm[i]] ++;
	}
	// Fix and sort on [3, 0]
	// Create buckets and quotient
	int *bucket_430 = (int *)malloc(c_size*sizeof(int));
	int *quotient_430 = (int *)malloc(c_size*sizeof(int));
	int current_430 = 0;
	bucket_430[0] = 0;
	quotient_430[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_430++;
			quotient_430[current_430] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_430++;
			quotient_430[current_430] = i;
		}
		bucket_430[i] = current_430;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_430[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_430[bucket_430[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_430[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(bucket_230);
	free(quotient_230);
	free(B4_count);
	free(bucket_430);
	free(quotient_430);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 2, 4)
int transpose_coo_31024(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 2, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 0, 4, 2)
int transpose_coo_31042(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 0, 4, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 1, 0]
	// Create buckets and quotient
	int *bucket_4310 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4310 = (int *)malloc(c_size*sizeof(int));
	int current_4310 = 0;
	bucket_4310[0] = 0;
	quotient_4310[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4310++;
			quotient_4310[current_4310] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_4310++;
			quotient_4310[current_4310] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4310++;
			quotient_4310[current_4310] = i;
		}
		bucket_4310[i] = current_4310;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4310[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4310[bucket_4310[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4310[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(B4_count);
	free(bucket_4310);
	free(quotient_4310);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 0, 4)
int transpose_coo_31204(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 0, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 2, 4, 0)
int transpose_coo_31240(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 2, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(B1_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 4, 0, 2)
int transpose_coo_31402(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 4, 0, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 1, 4, 2, 0)
int transpose_coo_31420(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 1, 4, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(B1_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 1, 4)
int transpose_coo_32014(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 1, 4)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 0, 4, 1)
int transpose_coo_32041(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 0, 4, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 2, 0]
	// Create buckets and quotient
	int *bucket_4320 = (int *)malloc(c_size*sizeof(int));
	int *quotient_4320 = (int *)malloc(c_size*sizeof(int));
	int current_4320 = 0;
	bucket_4320[0] = 0;
	quotient_4320[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_4320++;
			quotient_4320[current_4320] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_4320++;
			quotient_4320[current_4320] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_4320++;
			quotient_4320[current_4320] = i;
		}
		bucket_4320[i] = current_4320;
	}

	// Histogram sort on mode 4 into the permutation array
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
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		int idx = B4_count[idx4] - 1;
		C_coords_scratch[idx] = C_coords[i];
		perm[idx] = bucket_4320[i];
		B4_count[idx4]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_4320[bucket_4320[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_4320[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(B4_count);
	free(bucket_4320);
	free(quotient_4320);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 0, 4)
int transpose_coo_32104(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 0, 4)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 1, 4, 0)
int transpose_coo_32140(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 1, 4, 0)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B1_count);
	free(B2_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 4, 0, 1)
int transpose_coo_32401(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 4, 0, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 2, 4, 1, 0)
int transpose_coo_32410(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 2, 4, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(B2_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 0, 1, 2)
int transpose_coo_34012(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 0, 1, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 0, 2, 1)
int transpose_coo_34021(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 0, 2, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Fix and sort on [3, 4, 0]
	// Create buckets and quotient
	int *bucket_2340 = (int *)malloc(c_size*sizeof(int));
	int *quotient_2340 = (int *)malloc(c_size*sizeof(int));
	int current_2340 = 0;
	bucket_2340[0] = 0;
	quotient_2340[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_2340++;
			quotient_2340[current_2340] = i;
		}
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_2340++;
			quotient_2340[current_2340] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_2340++;
			quotient_2340[current_2340] = i;
		}
		bucket_2340[i] = current_2340;
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
		perm[idx] = bucket_2340[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_2340[bucket_2340[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_2340[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(B2_count);
	free(bucket_2340);
	free(quotient_2340);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 1, 0, 2)
int transpose_coo_34102(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 1, 2, 0)
int transpose_coo_34120(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 1, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B4_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 2, 0, 1)
int transpose_coo_34201(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 2, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (3, 4, 2, 1, 0)
int transpose_coo_34210(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (3, 4, 2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B4_count);
	free(B3_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 1, 2, 3)
int transpose_coo_40123(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 1, 2, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 1, 3, 2)
int transpose_coo_40132(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 1, 3, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 0, 1]
	// Create buckets and quotient
	int *bucket_3401 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3401 = (int *)malloc(c_size*sizeof(int));
	int current_3401 = 0;
	bucket_3401[0] = 0;
	quotient_3401[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3401++;
			quotient_3401[current_3401] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3401++;
			quotient_3401[current_3401] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_3401++;
			quotient_3401[current_3401] = i;
		}
		bucket_3401[i] = current_3401;
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
		perm[idx] = bucket_3401[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3401[bucket_3401[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3401[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(bucket_3401);
	free(quotient_3401);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 2, 1, 3)
int transpose_coo_40213(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 2, 1, 3)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_240 = (int *)malloc(c_size*sizeof(int));
	int *quotient_240 = (int *)malloc(c_size*sizeof(int));
	int current_240 = 0;
	bucket_240[0] = 0;
	quotient_240[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_240++;
			quotient_240[current_240] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_240++;
			quotient_240[current_240] = i;
		}
		bucket_240[i] = current_240;
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
		perm[idx] = bucket_240[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_240[bucket_240[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_240[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(bucket_240);
	free(quotient_240);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 2, 3, 1)
int transpose_coo_40231(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 2, 3, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_340 = (int *)malloc(c_size*sizeof(int));
	int *quotient_340 = (int *)malloc(c_size*sizeof(int));
	int current_340 = 0;
	bucket_340[0] = 0;
	quotient_340[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_340++;
			quotient_340[current_340] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_340++;
			quotient_340[current_340] = i;
		}
		bucket_340[i] = current_340;
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
		perm[idx] = bucket_340[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_340[bucket_340[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_340[perm[i]] ++;
	}
	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_240 = (int *)malloc(c_size*sizeof(int));
	int *quotient_240 = (int *)malloc(c_size*sizeof(int));
	int current_240 = 0;
	bucket_240[0] = 0;
	quotient_240[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_240++;
			quotient_240[current_240] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_240++;
			quotient_240[current_240] = i;
		}
		bucket_240[i] = current_240;
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
		perm[idx] = bucket_240[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_240[bucket_240[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_240[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(bucket_340);
	free(quotient_340);
	free(B2_count);
	free(bucket_240);
	free(quotient_240);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 3, 1, 2)
int transpose_coo_40312(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 3, 1, 2)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_340 = (int *)malloc(c_size*sizeof(int));
	int *quotient_340 = (int *)malloc(c_size*sizeof(int));
	int current_340 = 0;
	bucket_340[0] = 0;
	quotient_340[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_340++;
			quotient_340[current_340] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_340++;
			quotient_340[current_340] = i;
		}
		bucket_340[i] = current_340;
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
		perm[idx] = bucket_340[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_340[bucket_340[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_340[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B3_count);
	free(bucket_340);
	free(quotient_340);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 0, 3, 2, 1)
int transpose_coo_40321(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 0, 3, 2, 1)

	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_240 = (int *)malloc(c_size*sizeof(int));
	int *quotient_240 = (int *)malloc(c_size*sizeof(int));
	int current_240 = 0;
	bucket_240[0] = 0;
	quotient_240[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_240++;
			quotient_240[current_240] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_240++;
			quotient_240[current_240] = i;
		}
		bucket_240[i] = current_240;
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
		perm[idx] = bucket_240[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_240[bucket_240[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_240[perm[i]] ++;
	}
	// Fix and sort on [4, 0]
	// Create buckets and quotient
	int *bucket_340 = (int *)malloc(c_size*sizeof(int));
	int *quotient_340 = (int *)malloc(c_size*sizeof(int));
	int current_340 = 0;
	bucket_340[0] = 0;
	quotient_340[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_340++;
			quotient_340[current_340] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_340++;
			quotient_340[current_340] = i;
		}
		bucket_340[i] = current_340;
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
		perm[idx] = bucket_340[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_340[bucket_340[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_340[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B4_count);
	free(B2_count);
	free(bucket_240);
	free(quotient_240);
	free(B3_count);
	free(bucket_340);
	free(quotient_340);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 0, 2, 3)
int transpose_coo_41023(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 0, 2, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 0, 3, 2)
int transpose_coo_41032(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 0, 3, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 1, 0]
	// Create buckets and quotient
	int *bucket_3410 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3410 = (int *)malloc(c_size*sizeof(int));
	int current_3410 = 0;
	bucket_3410[0] = 0;
	quotient_3410[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3410++;
			quotient_3410[current_3410] = i;
		}
		if(C_coords[i].idx1 != C_coords[i - 1].idx1) {
			current_3410++;
			quotient_3410[current_3410] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3410++;
			quotient_3410[current_3410] = i;
		}
		bucket_3410[i] = current_3410;
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
		perm[idx] = bucket_3410[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3410[bucket_3410[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3410[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B4_count);
	free(B3_count);
	free(bucket_3410);
	free(quotient_3410);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 2, 0, 3)
int transpose_coo_41203(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 2, 0, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 2, 3, 0)
int transpose_coo_41230(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 2, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(B1_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 3, 0, 2)
int transpose_coo_41302(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 3, 0, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 1, 3, 2, 0)
int transpose_coo_41320(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 1, 3, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(B1_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 0, 1, 3)
int transpose_coo_42013(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 0, 1, 3)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 0, 3, 1)
int transpose_coo_42031(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 0, 3, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 2, 0]
	// Create buckets and quotient
	int *bucket_3420 = (int *)malloc(c_size*sizeof(int));
	int *quotient_3420 = (int *)malloc(c_size*sizeof(int));
	int current_3420 = 0;
	bucket_3420[0] = 0;
	quotient_3420[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_3420++;
			quotient_3420[current_3420] = i;
		}
		if(C_coords[i].idx2 != C_coords[i - 1].idx2) {
			current_3420++;
			quotient_3420[current_3420] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_3420++;
			quotient_3420[current_3420] = i;
		}
		bucket_3420[i] = current_3420;
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
		perm[idx] = bucket_3420[i];
		B3_count[idx3]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_3420[bucket_3420[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_3420[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B4_count);
	free(B3_count);
	free(bucket_3420);
	free(quotient_3420);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 1, 0, 3)
int transpose_coo_42103(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 1, 0, 3)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 1, 3, 0)
int transpose_coo_42130(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 1, 3, 0)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B1_count);
	free(B2_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 3, 0, 1)
int transpose_coo_42301(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 3, 0, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B2_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 2, 3, 1, 0)
int transpose_coo_42310(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 2, 3, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(B2_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 0, 1, 2)
int transpose_coo_43012(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 0, 1, 2)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 0, 2, 1)
int transpose_coo_43021(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 0, 2, 1)

	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Fix and sort on [4, 3, 0]
	// Create buckets and quotient
	int *bucket_2430 = (int *)malloc(c_size*sizeof(int));
	int *quotient_2430 = (int *)malloc(c_size*sizeof(int));
	int current_2430 = 0;
	bucket_2430[0] = 0;
	quotient_2430[0] = 0;
	for(int i = 1; i < c_size; i ++)
	{
		if(C_coords[i].idx4 != C_coords[i - 1].idx4) {
			current_2430++;
			quotient_2430[current_2430] = i;
		}
		if(C_coords[i].idx3 != C_coords[i - 1].idx3) {
			current_2430++;
			quotient_2430[current_2430] = i;
		}
		if(C_coords[i].idx0 != C_coords[i - 1].idx0) {
			current_2430++;
			quotient_2430[current_2430] = i;
		}
		bucket_2430[i] = current_2430;
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
		perm[idx] = bucket_2430[i];
		B2_count[idx2]--;
	}

	// Move the items back to the buckets.
	for (int i = 0; i < c_size; i ++) {
		C_coords[quotient_2430[bucket_2430[perm[i]]]] = C_coords_scratch[perm[i]];
		quotient_2430[perm[i]] ++;
	}
	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B3_count);
	free(B4_count);
	free(B2_count);
	free(bucket_2430);
	free(quotient_2430);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 1, 0, 2)
int transpose_coo_43102(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 1, 0, 2)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B3_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 1, 2, 0)
int transpose_coo_43120(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 1, 2, 0)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B1_count);
	free(B3_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 2, 0, 1)
int transpose_coo_43201(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 2, 0, 1)

	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B2_count);
	free(B3_count);
	free(B4_count);
	return 0;
}
// transpose permutes the modes of the coordinates to be (4, 3, 2, 1, 0)
int transpose_coo_43210(struct coo_t *C_coords, int c_size, int order, int *dimensions) {
	struct coo_t* C_coords_scratch = (struct coo_t *)malloc(sizeof(struct coo_t) * c_size);
	int* perm = (int *)malloc(sizeof(int) * c_size);

	// Sort the coordinates to be in (4, 3, 2, 1, 0)

	// Histogram sort on mode 1
	int B1_size = dimensions[1];
	int32_t *B1_count = (int32_t *)calloc(B1_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx1 = C_coords[i].idx1;
		B1_count[idx1]++;
	}

	// Prefix sum over B1_count
	for(int idx1 = 1; idx1 <= B1_size; idx1 ++)
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


	// Histogram sort on mode 2
	int B2_size = dimensions[2];
	int32_t *B2_count = (int32_t *)calloc(B2_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx2 = C_coords[i].idx2;
		B2_count[idx2]++;
	}

	// Prefix sum over B2_count
	for(int idx2 = 1; idx2 <= B2_size; idx2 ++)
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


	// Histogram sort on mode 3
	int B3_size = dimensions[3];
	int32_t *B3_count = (int32_t *)calloc(B3_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx3 = C_coords[i].idx3;
		B3_count[idx3]++;
	}

	// Prefix sum over B3_count
	for(int idx3 = 1; idx3 <= B3_size; idx3 ++)
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


	// Histogram sort on mode 4
	int B4_size = dimensions[4];
	int32_t *B4_count = (int32_t *)calloc(B4_size, sizeof(int32_t));
	for( int i = 0; i < c_size; i++)
	{
		int32_t idx4 = C_coords[i].idx4;
		B4_count[idx4]++;
	}

	// Prefix sum over B4_count
	for(int idx4 = 1; idx4 <= B4_size; idx4 ++)
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

	// Free the scratch space.
	free(C_coords_scratch);
	free(perm);
	free(B1_count);
	free(B2_count);
	free(B3_count);
	free(B4_count);
	return 0;
}
