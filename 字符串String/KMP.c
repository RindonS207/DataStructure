#include<stdio.h>
#include<stdlib.h>

#define KMP_INCLUDED 1

static void GetNext(char* string, int string_leng, int* next);
static void GetNextValue(char* string, int string_length, int* next);
static int FindIndexWithKMP(char* Main_string, int main_length, char* sub_string, int sub_length, int start_index);
static int FindIndexWithKMP_BS(char* Main_string, int main_length, char* sub_string, int sub_length, int start_index, int* next);

/* 生成改进式next分析式 */
static void GetNextValue(char* string, int string_length, int* next) {
	int index = 0, loop_index = -1;
	next[index] = loop_index;
	while (index < string_length - 1) {
		if (loop_index == -1 || string[index] == string[loop_index]) {
			index += 1;
			loop_index += 1;
			if (string[index] != string[loop_index]) {
				next[index] = loop_index;
			}
			else {
				next[index] = next[loop_index];
			}
		}
		else {
			loop_index = next[loop_index];
		}
	}
}

/* 生成next分析式 */
static void GetNext(char* string, int string_leng, int* next)
{
	int index = 0, loop_index = -1;
	next[0] = -1;
	while (index < string_leng)
	{
		if (loop_index == -1 || string[index] == string[loop_index])
		{
			loop_index += 1;
			index += 1;
			next[index] = loop_index;
		}
		else
		{
			loop_index = next[loop_index];
		}
	}
}
/* 查找索引，自动生成next推导式 */
static int FindIndexWithKMP(char* Main_string, int main_length, char* sub_string, int sub_length, int start_index)
{
	int index = start_index, loop_index = 0, * next = (int*)calloc(sub_length, sizeof(int));
	GetNextValue(sub_string, sub_length, next);
	while (index < main_length && loop_index < sub_length)
	{
		if (loop_index == -1 || Main_string[index] == sub_string[loop_index])
		{
			loop_index += 1;
			index += 1;
		}
		else
		{
			loop_index = next[loop_index];
		}
	}
	if (loop_index == sub_length)
	{
		return index - sub_length;
	}
	else {
		return -1;
	}
}
/* 查找索引，使用指定next推导式 */
static int FindIndexWithKMP_BS(char* Main_string, int main_length, char* sub_string, int sub_length, int start_index, int* next)
{
	int index = start_index, loop_index = 0;
	while (index < main_length && loop_index < sub_length)
	{
		if (loop_index == -1 || Main_string[index] == sub_string[loop_index])
		{
			loop_index += 1;
			index += 1;
		}
		else
		{
			loop_index = next[loop_index];
		}
	}
	if (loop_index == sub_length)
	{
		return index - sub_length;
	}
	else {
		return -1;
	}
}