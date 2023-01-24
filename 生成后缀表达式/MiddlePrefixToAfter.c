#include<stdio.h>
#include "LinkStack--string.c"
#include "String.c"
#include "Queue.c"


static String* GetAfterPrefix(char* string);

static String* GetAfterPrefix(char* string) {
	LinkStack* stack = CreateLinkStack(); 
	BOOL have_kuohao = false; 
	Queue* Number_que = CreateQueue();
	int x = 0; 
	char tempChar; 
	Element* tempValue = (Element*)malloc(sizeof(Element));
	Q_Element* temp_number = (Q_Element*)malloc(sizeof(Q_Element));
	String* str = new_string(" ", 1);
	while (string[x] != '\0') {
		tempChar = string[x];
		if (tempChar == ' ') {
			str = StringAppend(str, ' ');
			x += 1;
			continue;
		}/* À¨ºÅ */
		else if (tempChar == '(') {
			Element e = { tempChar };
			AddElementToLinkStack(stack, e);
			have_kuohao = true;
			x += 1;
			continue;
		}
		x += 1;
		/* Êý×Ö */
		if (tempChar <= 57 && tempChar >= 48) {
			Q_Element e = { -1,tempChar };
			AddElementToQueue(Number_que,e);
			continue;
		}
		else {
			str = StringAppend(str, ' ');
			while (RemoveElementFromQueue(Number_que, temp_number)) {
				str = StringAppend(str, temp_number->value);
			}
		}
		/* Ð¡Ð´µÄx */
		/* ³Ë³ý */
		if (tempChar == 'x' || tempChar == '/') {
			Element value = { 'v' };
			if (tempChar == 'x') {
				value.c = '*';
			}
			else {
				value.c = '/';
			}
			AddElementToLinkStack(stack, value);
		}
		/* ¼Ó¼õ */
		else if (tempChar == '+' || tempChar == '-') {
			Element value = { tempChar };
			if (GetTopElementFromLinkStack(stack, tempValue) && (tempValue->c == '*' || tempValue->c == '/')) {
				while (GetTopElementFromLinkStack(stack, tempValue)) {
					if (have_kuohao && tempValue->c == '(') {
						break;
					}
					RemoveElementFromLinkStack(stack, tempValue);
					str = StringAppend(str, ' ');
					str = StringAppend(str, tempValue->c);
				}
			}
			AddElementToLinkStack(stack, value);
		}
		/* ÓÒÀ¨ºÅ */
		else {
			while (RemoveElementFromLinkStack(stack, tempValue))
			{
				if (tempValue->c == '(') {
					have_kuohao = false;
					break;
				}
				str = StringAppend(str, ' ');
				str = StringAppend(str, tempValue->c);
			}
		}
	}
	if (GetQueueHeadElement(Number_que, temp_number)) {
		str = StringAppend(str, ' ');
		while (RemoveElementFromQueue(Number_que, temp_number))
		{
			str = StringAppend(str, temp_number->value);
		}
	}
	if (GetTopElementFromLinkStack(stack, tempValue)) {
		while (RemoveElementFromLinkStack(stack, tempValue))
		{
			str = StringAppend(str, ' ');
			str = StringAppend(str, tempValue->c);
		}
	}
	free(tempValue);
	free(temp_number);
	return str;
}