/*******************************************************************************************
    Author:      Lucas Pacheco.
    Description: Test exercise from "The Audio Programming Book", Exercise2.3.3 .
    Date:        16/11/2021
********************************************************************************************/
/*(A)*/
#include <breakpoints.h>

BREAKPOINT minpoint(const BREAKPOINT* points, long npoints) {
	int i;
	BREAKPOINT point;
	point.time = points[0].time;
	point.value = points[0].value;
	for ( i = 0; i < npoints; i++ ) {
		if (point.value > points[i].value) {
			point.value = points[i].value;
			point.time = points[i].time;
		}
	}
	return point;
}

/*(B)*/
BREAKPOINT min_and_max__point(const BREAKPOINT* points, long npoints, BREAKPOINT* maxp, BREAKPOINT* minp) {
	int i;
	BREAKPOINT point_min, point_max;
    point_min.time = points[0].time;
	point_min.value = points[0].value;
	point_max.time = points[0].time;
	point_max.value = points[0].value;

	for ( i = 0; i < npoints; i++ ) {
		if (point_min.value > points[i].value) {
			point_min.value = points[i].value;
			point_min.time = points[i].time;
		}

        if (point_max.value < points[i].value) {
			point_max.value = points[i].value;
			point_max.time = points[i].time;
		}
	}
    *maxp = point_max;
    *minp = point_min;
    
	return point;
}


typedef struct Min_Max_BRK {
    BREAKPOINT min;
    BREAKPOINT max;
} Min_Max_BRK;

Min_Max_BRK min_and_max__point2(const BREAKPOINT* points, long npoints) {
	int i;
	Min_Max_BRK mMBrk;
    mMBrk.min.time = points[0].time;
	mMBrk.min.value = points[0].value;
	mMBrk.max.time = points[0].time;
	mMBrk.max.value = points[0].value;

	for ( i = 0; i < npoints; i++ ) {
		if (mMBrk.min.value > points[i].value) {
			mMBrk.min.value = points[i].value;
			mMBrk.min.time = points[i].time;
		}

        if (mMBrk.max.value < points[i].value) {
			mMBrk.max.value = points[i].value;
			mMBrk.max.time = points[i].time;
		}
	}
    
	return mMBrk;
}
