/*
프로그램설명: 파일을 이용한 합병정렬 구현
개발자: 소예찬, 김재경
실습일: 2023-05-06
*/
#include <stdio.h>
#define MAX_SIZE_ARRAY 10
void Read_File(int array[], int size)
{
	int i, num;
	FILE* fp = NULL;
	fp = fopen("data.txt", "r"); //읽기용 파일 열기 

	if (fp == NULL)
		printf("파일열기 실패");

	for (i = 0; i < size; i++)
	{
		if (fscanf(fp, "%d", &num) == 1) // 파일에서 정수 읽기
		{
			array[i] = num;
		}
		else
		{
			printf("읽기 실패\n");
			break;
		}
	}

	printf("파일읽기 성공!\n");

	fclose(fp);
}
void Copy_File(int array[], int size)
{
	int i;
	FILE* fp = NULL;
	fp = fopen("result.txt", "w"); //쓰기용 파일열기 

	if (fp == NULL)
		printf("파일열기 실패");

	for (i = 0; i < size; i++) 	// 배열의 값을 파일에 저장
		fprintf(fp, "%d ", array[i]);

	printf("파일복사 성공!\n");

	fclose(fp);
}

void Merge(int array[], int left, int mid, int right)
{
	int i, j, k;
	int size_L = mid - left + 1;	//좌측배열 크기 
	int size_R = right - mid;		//우측배열 크기 
	int L[size_L], R[size_R]; 		//임시 배열 생성

	for (i = 0; i < size_L; i++)	//좌측배열만큼 임시배열에 복사 
		L[i] = array[left + i];
	for (j = 0; j < size_R; j++)	//우측배열만큼 임시배열에 복사 
		R[j] = array[mid + j + 1];

	i = 0;
	j = 0;
	k = left;
	while (i < size_L && j < size_R) // 임시 배열을 합병하여 원래 배열에 저장
	{
		if (L[i] <= R[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = R[j];
			j++;
		}
		k++;
	}

	// 남은 값들을 복사
	while (i < size_L)
	{
		array[k] = L[i];
		i++;
		k++;
	}
	while (j < size_R)
	{
		array[k] = R[j];
		j++;
		k++;
	}
}
void Merge_Sort(int array[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2; 		// 중간 위치를 계산하여 배열을 반으로 분할 
		Merge_Sort(array, left, mid); 	// 좌측부분에 대한 재귀함수  
		Merge_Sort(array, mid + 1, right); //우측부분에 대한 재귀함수 
		Merge(array, left, mid, right); 	//배열을 다시 병합 
	}

}
int main()
{
	int array[MAX_SIZE_ARRAY];

	Read_File(array, MAX_SIZE_ARRAY);
	Merge_Sort(array, 0, MAX_SIZE_ARRAY - 1);
	Copy_File(array, MAX_SIZE_ARRAY);

	return 0;
}