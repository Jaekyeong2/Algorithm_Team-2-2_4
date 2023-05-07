/*
���α׷�����: ������ �̿��� �պ����� ����
������: �ҿ���, �����
�ǽ���: 2023-05-06
*/
#include <stdio.h>
#define MAX_SIZE_ARRAY 10
void Read_File(int array[], int size)
{
	int i, num;
	FILE* fp = NULL;
	fp = fopen("data.txt", "r"); //�б�� ���� ���� 

	if (fp == NULL)
		printf("���Ͽ��� ����");

	for (i = 0; i < size; i++)
	{
		if (fscanf(fp, "%d", &num) == 1) // ���Ͽ��� ���� �б�
		{
			array[i] = num;
		}
		else
		{
			printf("�б� ����\n");
			break;
		}
	}

	printf("�����б� ����!\n");

	fclose(fp);
}
void Copy_File(int array[], int size)
{
	int i;
	FILE* fp = NULL;
	fp = fopen("result.txt", "w"); //����� ���Ͽ��� 

	if (fp == NULL)
		printf("���Ͽ��� ����");

	for (i = 0; i < size; i++) 	// �迭�� ���� ���Ͽ� ����
		fprintf(fp, "%d ", array[i]);

	printf("���Ϻ��� ����!\n");

	fclose(fp);
}

void Merge(int array[], int left, int mid, int right)
{
	int i, j, k;
	int size_L = mid - left + 1;	//�����迭 ũ�� 
	int size_R = right - mid;		//�����迭 ũ�� 
	int L[size_L], R[size_R]; 		//�ӽ� �迭 ����

	for (i = 0; i < size_L; i++)	//�����迭��ŭ �ӽù迭�� ���� 
		L[i] = array[left + i];
	for (j = 0; j < size_R; j++)	//�����迭��ŭ �ӽù迭�� ���� 
		R[j] = array[mid + j + 1];

	i = 0;
	j = 0;
	k = left;
	while (i < size_L && j < size_R) // �ӽ� �迭�� �պ��Ͽ� ���� �迭�� ����
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

	// ���� ������ ����
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
		int mid = (left + right) / 2; 		// �߰� ��ġ�� ����Ͽ� �迭�� ������ ���� 
		Merge_Sort(array, left, mid); 	// �����κп� ���� ����Լ�  
		Merge_Sort(array, mid + 1, right); //�����κп� ���� ����Լ� 
		Merge(array, left, mid, right); 	//�迭�� �ٽ� ���� 
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