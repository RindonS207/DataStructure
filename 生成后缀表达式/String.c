#include<stdio.h>
#include<stdlib.h>
#include "BOOL_DEF.c"

typedef struct String String;
static String* new_string(char* str,int length);
static String* StringContact(String* main, String* sub);
static String* StringAppend(String* str,char c);
static BOOL SetCharAtString(String* str,int index,char c);
static char GetCharAtString(String* str, int index);
static void PrintString(String* s);

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
返回一个新的字符串 */
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
/* 获取指定索引位置的字符 */
static char GetCharAtString(String* str, int index)
{
	if (index >= str->length) {
		return -1;
	}
	return str->str[index];
}
/* 修改指定索引的字符 */
static BOOL SetCharAtString(String* str, int index, char c) {
	if (str == NULL || index >= str->length) {
		return false;
	}
	str->str[index] = c;
	return true;
}
/* 向字符串末尾追加字符值 */
static String* StringAppend(String* str, char c)
{
	
	int x, length = str->length;
	char* newstr = (char*)calloc(length + 1, sizeof(char)); 
	
	for (x = 0; x < length; x++) {
		newstr[x] = str->str[x];
	}
	
	newstr[length] = 'N';
	String* newreturn = new_string(newstr,str->length+1);
	if (newreturn == NULL) {
		return NULL;
	}
	free(str->str); free(str); free(newstr);
	newreturn->str[newreturn->length - 1] = c;
	return newreturn;
}