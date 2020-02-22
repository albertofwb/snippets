#define  _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>


/*
*	@success return epoch time
*	@failed: return -1
*/
time_t ConvertStrtimeToEpoch(const char* strTime)
{
	struct tm t = { 0 };
	int ret = sscanf(strTime, "%d-%d-%d %d:%d:%d",
		&t.tm_year, &t.tm_mon, &t.tm_mday,
		&t.tm_hour, &t.tm_min, &t.tm_sec);
	if (ret < 0) {
		fprintf(stderr, "invalid time str %s", strTime);
		return -1;
	}
	t.tm_year -= 1900;
	t.tm_mon -= 1;
	// if you do not understand why above calculate is necessary, check this
	// https://stackoverflow.com/questions/14127013/mktime-returns-1-when-given-a-valid-struct-tm
	// https://bytes.com/topic/c/answers/761775-mktime-returns-negative-value

	return mktime(&t);
}
