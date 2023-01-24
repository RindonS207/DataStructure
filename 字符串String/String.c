#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#ifndef KMP_INCLUDED
#include "KMP.c"
#endif

#define STRING_INCLUDED 1

typedef struct String String;
static String* new_string(char* str,int length);

static String* StringContact(String* main, String* sub);
static String* StringContactChars(String* main, char* sub);
static String* StringAppend(String* str,char c);

static int IndexOfChar(String* str, char c);
static int IndexOfSubString(String* main, String* sub, int startindex);

static BOOL StringReplaceChar(String* str,char oldchar,char newchar);
static BOOL StringReplaceLFirstChar(String* str, char oldchar, char newchar);
static BOOL StringReplaceRFirstChar(String* str, char oldchar, char newchar);
static BOOL StringReplaceString(String* main, char* sub, char* newstrs);

static int StringCompare(String* a, String* b);
static BOOL StringEquals(String* a, String* b);

static char* GetCharArray(String* str);
static BOOL SetCharAtString(String* str,int index,char c);
static char GetCharAtString(String* str, int index);

static void PrintString(String* s);

static int LengthOfCharArray(char* chars);

typedef struct String {
	char* str;
	int length;
}String;

/* 创建一个字符串结构 */
static String* new_string(char* str,int length) {
	int x = 0;
	String* main_str = (String*)malloc(sizeof(String));
	main_str->str = (char*)calloc(length, sizeof(char));
	if (main_str == NULL || main_str->str == NULL) {
		free(main_str->str);
		free(main_str);
		return NULL;
	}
	main_str->length = length;
	for (x = 0; x < length; x++) {
		main_str->str[x] = str[x];
	}
	return main_str;
}

/* 打印一个字符串结构 */
static void PrintString(String* s) {
	int x = 0;
	if (s == NULL) {
		printf("null");
		return;
	}
	for (x = 0; x < s->length; x++) {
		printf("%c",s->str[x]);
	}
}

/* 拼接两个字符串，
*  将sub的内容加到main后面
返回一个新的字符串，会释放掉原来的字符串 */
static String* StringContact(String* main, String* sub)
{
	int x,i;
	if (sub == NULL || main == NULL)
	{
		return NULL;
	}
	String* str = (String*)malloc(sizeof(String));
	str->length = main->length + sub->length;
	str->str = (char*)calloc(str->length, sizeof(char));
	if (str == NULL || str->str == NULL) {
		free(str->str);
		free(str);
		return NULL;
	}
	for (x = 0; x < main->length; x++) {
		str->str[x] = main->str[x];
	}
	for (x = main->length, i = 0; x < str->length; x++, i++)
	{
		str->str[x] = sub->str[i];
	}
	free(sub->str);
	free(sub);
	free(main->str);
	free(main);
	return str;
}

/* 拼接两个字符串，
    将sub的内容加到main后面，
	返回一个新的字符串，会释放掉原来的main*/
static String* StringContactChars(String* main, char* sub)
{
	int sub_len = LengthOfCharArray(sub),x,i;
	if (main == NULL || sub_len == -1) {
		return NULL;
	}
	String* newstr = (String*)malloc(sizeof(String));
	newstr->length = main->length + sub_len;
	newstr->str = (char*)calloc(newstr->length, sizeof(char));
	if (newstr == NULL || newstr->str == NULL) {
		free(newstr->str); free(newstr);
		return NULL;
	}
	for (x = 0; x < main->length; x++) {
		newstr->str[x] = main->str[x];
	}
	for (x = main->length,i=0; x < newstr->length; x++,i++) {
		newstr->str[x] = sub[i];
	}
	free(main->str);
	free(main);
	return newstr;
}

/* 获取指定索引位置的字符 */
static char GetCharAtString(String* str, int index)
{
	if (index >= str->length || index < 0 || str ==NULL) {
		return -1;
	}
	return str->str[index];
}

/* 修改指定索引的字符 */
static BOOL SetCharAtString(String* str, int index, char c) {
	if (str == NULL || index >= str->length || index < 0) {
		return false;
	}
	str->str[index] = c;
	return true;
}

/* 向字符串末尾追加字符值 */
static String* StringAppend(String* str, char c)
{
	int x, length = str->length;
	String* newreturn = (String*)malloc(sizeof(String));
	newreturn->length = length + 1;
	newreturn->str = (char*)calloc(newreturn->length, sizeof(char));
	if (newreturn == NULL || newreturn->str == NULL) {
		free(newreturn->str); free(newreturn);
		return str;
	}
	for (x = 0; x < length; x++) {
		newreturn->str[x] = str->str[x];
	}
	newreturn->str[length] = c;
	free(str->str); free(str);
	return newreturn;
}

/* 返回字符串结构中的字符数组 */
static char* GetCharArray(String* str)
{
	if (str == NULL) {
		return NULL;
	}
	return str->str;
}

/* 比较a和b两个字符串
    如果a比b大返回1
	相等返回0
	小于或比较无效返回-1*/
static int StringCompare(String* main, String* sub)
{
	int x,char_a,char_b;
	if (main == NULL || sub == NULL) {
		return -1;
	}
	if (main->length > sub->length) {
		return 1;
	}
	else if (main->length < sub->length) {
		return -1;
	}
	else {
		for (x = 0; x < sub->length; x++) {
			char_a = main->str[x];
			char_b = sub->str[x];
			if (char_a == char_b) {
				continue;
			}
			else if (char_a > char_b) {
				return 1;
				break;
			}
			else {
				return -1;
				break;
			}
		}
		return 0;
	}
}

/* 比较ab是否全等，是返回1，否则返回0 */
static BOOL StringEquals(String* a, String* b)
{
	if (!StringCompare(a, b)) {
		return 1;
	}
	else {
		return 0;
	}
}

/* 查找字符在字符串中的索引，不包含返回-1 */
static int IndexOfChar(String* str, char c)
{
	int x;
	for (x = 0; x < str->length; x++) {
		if (str->str[x] == c) {
			return x;
		}
	}
	return -1;
}

/* 查找sub在main中的索引，不存在返回-1 */
static int IndexOfSubString(String* main, String* sub, int startindex)
{
	return FindIndexWithKMP(main->str, main->length, sub->str, sub->length, startindex);
}

/* 替换字符串中所有的指定字符，替换成功返回1，不成功返回0 */
static BOOL StringReplaceChar(String* str, char oldchar, char newchar)
{
	BOOL x, returnvalue = false;
	if (str == NULL) {
		return returnvalue;
	}
	for (x = 0; x < str->length; x++) {
		if (str->str[x] == oldchar) {
			str->str[x] = newchar;
			returnvalue = true;
		}
	}
	return returnvalue;
}

/* 替换字符串中从左往右遇到的第一个指定字符，替换成功返回1，不成功返回0 */
static BOOL StringReplaceLFirstChar(String* str, char oldchar, char newchar)
{
	int x;
	if (str == NULL) {
		return false;
	}
	for (x = 0; x < str->length; x++) {
		if (str->str[x] == oldchar) {
			str->str[x] = newchar;
			return true;
		}
	}
	return false;
}

/* 替换字符串中从右往左遇到的第一个指定字符，替换成功返回1，不成功返回0 */
static BOOL StringReplaceRFirstChar(String* str, char oldchar, char newchar)
{
	int x;
	if (str == NULL) {
		return false;
	}
	for (x = str->length-1; x >= 0; x--) {
		if (str->str[x] == oldchar) {
			str->str[x] = newchar;
			return true;
		}
	}
	return false;
}

/* 替换字符串main中所有符合条件的另一个字符串sub
    替换为newstrs，替换成功返回1，不成功返回0 */
static BOOL StringReplaceString(String* main, char* sub,char* newstrs)
{
	BOOL sub_length = LengthOfCharArray(sub),new_length = LengthOfCharArray(newstrs), * next, index, x, i;
	if (main == NULL || sub_length <= 0 || sub_length > main->length || sub_length != new_length || sub == newstrs) {
		return false;
	}
	next = (int*)calloc(sub_length, sizeof(int));
	GetNextValue(sub, sub_length, next);
	index = FindIndexWithKMP_BS(main->str, main->length, sub, sub_length, 0, next);
	if (index == -1) {
		return false;
	}
	while (index != -1) {
		for (x = index, i = 0; i < sub_length; i++) {
			main->str[x + i] = newstrs[i];
		}
		index = FindIndexWithKMP_BS(main->str, main->length, sub, sub_length, 0, next);
	}
	return true;
}

/* 读取字符数组（c原生字符串结构）长度 */
static int LengthOfCharArray(char* chars)
{
	int x=0;
	if (chars == NULL) {
		return -1;
	}
	while (chars[x] != '\0') {
		x += 1;
	}
	return x;
}