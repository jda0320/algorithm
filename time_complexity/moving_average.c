/*
 * 주어진 배열 각 위치에서 이동 평균 값 출력
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DEBUG(fmt, args...)	printf("[%s]: " fmt "\n", __FUNCTION__, ##args)
#define ERROR(fmt, args...)	printf("[%s.%d]: " fmt "\n", __FUNCTION__, __LINE__, ##args)

#define MAX_ARRAY_SIZE		12
#define AVERAGE				3


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
		array[idx] = (rand() % 10) + 50;

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
 * N개의 측정치가 주어질 때 M달 간의 이동 평균 계산
 * M(N - M + 1)
 */
void
moving_average_1(unsigned int *array, unsigned int array_len)
{
	unsigned int 	i, j;
	unsigned int 	sum;

	DEBUG("start");

	if (array == NULL || array_len == 0) {
		ERROR("invaid args");
		return;
	}

	for (i = AVERAGE - 1; i < array_len; i++) {
		sum = 0;

		for (j = 0; j < AVERAGE; j++) {
			sum += array[i - j];
		}

		DEBUG("[%d ~ %d]: %.2f", i - 1, i + 1, (double)sum / (double)AVERAGE);
	}

	DEBUG("end");
}

/*
 * N개의 측정치가 주어질 때 M달 간의 이동 평균 계산
 * M - 1 + (N - M + 1) = N
 */
void
moving_average_2(unsigned int *array, unsigned int array_len)
{
	unsigned int 	i;
	unsigned int 	sum;

	DEBUG("start");

	if (array == NULL || array_len == 0) {
		ERROR("invaid args");
		return;
	}
	
	sum = 0;
	for (i = 0; i < AVERAGE - 1; i++) {
		sum += array[i];
	}

	for (i = AVERAGE - 1; i < array_len; i++) {
		sum += array[i];
		DEBUG("[%d ~ %d]: %.2f", i - 1, i + 1, (double)sum / (double)AVERAGE);
		sum -= array[i - AVERAGE + 1];
	}

	DEBUG("end");
}

int
main(int argc, char **argv)
{
	unsigned int 	rand_array[MAX_ARRAY_SIZE];
	unsigned int 	array_len;

	array_len = sizeof(rand_array) / sizeof(unsigned int);
	set_rand_array(rand_array, array_len);

	moving_average_1(rand_array, array_len);
	moving_average_2(rand_array, array_len);

	return 0;
}
