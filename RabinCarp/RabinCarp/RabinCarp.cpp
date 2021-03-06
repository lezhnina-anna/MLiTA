#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <locale.h>

/*
Лежнина Анна, пс-22.

Требуется найти все вхождения образца в текстовом файле методом Рабина. В файле нет
переноса слов. Образец может включать пробелы и переходить с одной строки файла на другую.
Конец строки файла может интерпретироваться как пробел. Результаты поиска не должны
зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так и
прописной.
Ввод из файла INPUT.TXT. Первая строка файла является образцом и имеет длину от 1 до 255.
Вторая строка задает имя текстового файла.
Вывод в файл OUTPUT.TXT. Вывести в каждой строке через пробел последовательность
номеров строк и позиций в строке, начиная с которых образец входит в текст. Нумерация строк и
позиций в строке начинается с 1. Если вхождений нет, вывести No.
*/


using namespace std;

int mod(int a, int strLen, int m)
{
	if (strLen == 0)
		return 1;
	int sqr = mod(a, strLen / 2, m) % m;

	if (strLen & 1)
		return ((a % m) * sqr) % m;
	else
		return sqr;
}

void FindString(std::ifstream & textFile, char *pattern, int d, int q)
{
	std::ofstream FOut("output.txt");
	int i, j, patternHash, textHash, patternLen, h, match, countStr = 1, prevCount;
	char ch;
	bool  found = false, first = false, wasFound = false;

	patternLen = strlen(pattern);
	h = mod(d, patternLen - 1, q);
	patternHash = textHash = 0;

	char start[255] = { 0 };
	i = patternLen;

	for (i = 0; i < patternLen; i++)
	{
		ch = tolower(textFile.get());
		if (ch == '\n')
		{
			countStr++;
			first = true;
			ch = ' ';
		}
		start[i] = ch;
		patternHash = (d*patternHash + (int)(pattern[i])) % q;
		textHash = (d*textHash + (int)(ch)) % q;
	}

	int size = strlen(start);

	char currCh, prevCh;

	while (textFile)
	{
		i++;
		if (patternHash == textHash)
		{
			found = 1;
			for (j = 0; j < patternLen; j++)
			{
				if (pattern[j] != start[j])
				{
					found = 0;
					break;
				}
			}

			if (found)
			{
				wasFound = true;
				if (i - patternLen > 0)
				{
					match = i - patternLen;
					
					if (first)
					{
						FOut << countStr - 1 << " " << match << endl;
						first = false;
					}
					else
						FOut << countStr << " " << match << endl;
					
				}
				else
				{
					match = prevCount - (patternLen - i);
					FOut << countStr - 1  << " " << match << endl;
				}
				
			}
		}

		prevCh = start[0];
		memmove(start, start + 1, size - 1);
		start[size - 1] = 0;
		currCh = tolower(textFile.get());
		if (currCh == '\n')
		{
			countStr++;
			prevCount = i;
			i = 0;
			currCh = ' ';
		}
		start[size - 1] = currCh;
		textHash = (d*(textHash - (((int)(prevCh)*h) % q)) + (int)(currCh)) % q;
	} 
	if (!wasFound)
		FOut << "No" << endl;

}

int main()
{
	setlocale(LC_ALL, "Rus");

	int d = 1, q = 10093;
	char pattern[255];

	std::ifstream inputFile("input.txt");
	inputFile.getline(pattern, 255);
	int patternLen = strlen(pattern);

	for (size_t i = 0; i < patternLen; i++)
	{
		pattern[i] = tolower(pattern[i]);
	}

	char fileName[255];
	inputFile.getline(fileName, 255);
	std::ifstream textFile(fileName);
    FindString(textFile, pattern, d, q);

	return 0;
}
