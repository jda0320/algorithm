/*
 * 주어진 배열에서 가장 많이 등장하는 숫자 출력
 * MAX_ARRAY_SIZE: 배열 크기
 * MAX_ARRAY_RANGE: 랜덤 수 범위, 배열크기의 반(1 ~ MAX_ARRAY_SIZE / 2)
 * 가장 많이 등장하는 숫자와 등장하는 횟수 출력
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DEBUG(fmt, args...)	printf("[%s]: " fmt "\n", __FUNCTION__, ##args)
#define ERROR(fmt, args...)	printf("[%s.%d]: " fmt "\n", __FUNCTION__, __LINE__, ##args)

#define MAX_ARRAY_SIZE		100
#define MAX_ARRAY_RANGE		(MAX_ARRAY_SIZE / 2)


void
set_rand_array(unsigned int *array, unsigned int array_len)
{
	unsigned int idx;

	if (array == NULL || array_len == 0) {
		ERROR("invaid args");
		return;
	}

	memset(array, 0, sizeof(array));
	srand(time(NULL));

	for (idx = 0; idx < array_len; idx++) {
		array[idx] = (rand() % MAX_ARRAY_RANGE) + 1;

		if (idx == 0) {
			printf("[%d]", array[idx]);
		} else if (idx == array_len - 1) {
			printf(" [%d]\n", array[idx]);
		} else {
			printf(" [%d]", array[idx]);
		}
	}
}

/*
 * 배열의 크기 N
 * 수행시간: N * N
 */
void
majority_1(unsigned int *array, unsigned int array_len)
{
	unsigned int 	majority = 0;
	unsigned int 	majority_count = 0;
	unsigned int 	i, j;

	DEBUG("start");

	if (array == NULL || array_len == 0) {
		ERROR("invaid args");
		return;
	}

	for (i = 0; i < array_len; i++) {
		unsigned int	v = array[i];
		unsigned int	count = 0;

		for (j = 0; j < array_len; j++) {
			if (v == array[j]) {
				count++;
			}
		}

		if (count > majority_count) {
			majority = v;
			majority_count = count;
		}
	}

	DEBUG("majority_count=%d, majority_count=%d", majority, majority_count);
	DEBUG("end");
}

/*
 * 배열의 크기 N
 * 수행시간: N + 수 범위
 * N이 커질수록 수 범위 반복문이 차지하는 비중은 줄어들게 되면서 궁극적으로 수행시간은 N
 */
void
majority_2(unsigned int *array, unsigned int array_len)
{
	unsigned int	count[MAX_ARRAY_RANGE + 1];
	unsigned int 	majority = 0;
	unsigned int 	i;

	DEBUG("start");

	if (array == NULL || array_len == 0) {
		ERROR("invaid args");
		return;
	}

	memset(count, 0, sizeof(count));

	for (i = 0; i < array_len; i++) {
		count[array[i]]++;
	}

	for (i = 1; i < MAX_ARRAY_RANGE + 1; i++) {
		if (count[i] > count[majority]) {
			majority = i;
		}
	}

	DEBUG("majority_count=%d, majority_count=%d", majority, count[majority]);
	DEBUG("end");
}

int
main(int argc, char **argv)
{
	unsigned int 	rand_array[MAX_ARRAY_SIZE];
	unsigned int 	array_len;

	array_len = sizeof(rand_array) / sizeof(unsigned int);
	set_rand_array(rand_array, array_len);

	majority_1(rand_array, array_len);
	majority_2(rand_array, array_len);

	return 0;
}
