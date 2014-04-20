// Zadacha_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <cmath>
#include <cstdio>
#include <ctype.h> 
#include <clocale>
#include <Windows.h>

#pragma warning (once : 4996)
#define AlfabetN 256	

//B Visual studio 2012 нет поддержки log2
//inline float log2(float n) {
//	if (n==0)
//	{
//		return 0;
//	}
//	return log(n) / log(2.0);
//}



//Предварительные настройки приложения
inline void SetApp(void)
{
	//setlocale( LC_ALL, "ru_RU.cp1251" );

	SetConsoleCP(1251);					// Русская локаль
	SetConsoleOutputCP(1251);
}


struct result // Сруктура хранения информации
{
	float freq[AlfabetN];
	float H,Hmax;
}res;

//Оценка энтропии, одиночные символы
float entropy_1 (char *fn)
{
	FILE *fi;
	float freq[AlfabetN] = {0};
	float H=0,Hmax=0; 
	int K=0;
	int ch=EOF;
	long total=0;
	puts("Файл:");	
	puts(fn);
	fi = fopen(fn, "r");
	if(fi == NULL)
    {
        puts("Такой файл не найден!");
		system("Pause");
        return -1;
    }
	
	
	while((ch = fgetc(fi)) != EOF)
    {
		//Если англ или рус алфавит
        if(isalpha(ch)||strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮёйцукенгшщзхъфывапролджэячсмитьбю", ch))
        {
			if (strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ", ch))//Если Заглавные рус
			{
				if ( ch == 0xA8)								//Отдельно для Ё
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//А и а рус
				}
				freq[ch]++;
				total++;            
			}else{
				ch = tolower(ch);           
				freq[ch]++;
				total++;            
			}
        }
        else 
        {
			if (ch == ' ')										//пробел
			{
				freq[ch]++;
				total++;            
			}else
			{
				 if (strchr("-.,:!?;", ch))						//знаки припинания
				 {
					ch = '.';				
					freq[ch]++;
					total++;            
				 }
			}
        }
 
    }
	
	for (int i = 0; i < AlfabetN; i++)
	{
		
		if (freq[i]!=0)
		{
			//printf("freq =%3.0f ",freq[i]);
			freq[i] = freq[i]/total;
			printf("P[%c] = %1.3f\n",i,freq[i]);			
			H = H + freq[i]*log2(freq[i]);
			K++;
		}
	}
	for (int i = 0; i < AlfabetN; i++)
	{
		res.freq[i]=0;
		res.freq[i]=freq[i];
	}
	res.H = H;
	
	
	Hmax=log2(K);
	
	if (Hmax==0)Hmax=1;
	
	res.Hmax =  Hmax;
	printf("Всего символов в файле: %d\n",total);
	printf("Всего символов в алфавите: %d\n",K);
	printf("Энтропия файла: %3.3f\n",(-1)*H);	
	printf("Максимальная Энтропия файла: %3.3f\n",Hmax);
	
	printf("Избыточность текста составила: %3.3f\n",1 + H/Hmax);
	
	fclose(fi);
	system("PAUSE");
	return 0;
}

//Оценка энтропии, пары символов
float entropy_2 (char *fn)
{
	FILE *fi;
	float freq2[AlfabetN][AlfabetN] = {0};
	float H2=0; 
	
	int ch=EOF,lastch=EOF;;
	long sum=0;
	
	entropy_1(fn);

	fi = fopen(fn, "r");
	if(fi == NULL)
    {
        puts("Такой файл не найден!");
		system("Pause");
        return -1;
    }
	while((ch = fgetc(fi)) != EOF)
	{
		sum++;
	}
	if (sum<2||sum==0)
	{
		puts("в файле нет пар символов");
		system("Pause");
        return -2;
	}
	rewind(fi);
	lastch= fgetc(fi);
	//Если англ или рус алфавит
	if(isalpha(lastch)||strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮёйцукенгшщзхъфывапролджэячсмитьбю", lastch))
        {
			if (strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ", lastch))	//Если Заглавные рус
			{
				if ( lastch == 0xA8)									//Отдельно для Ё
				{
					lastch=0xB8;
				}else
				{
					lastch=lastch-0xC0+0xE0;							//А и а рус
				}				            
			}else{
				lastch = tolower(lastch);           				        
			}
        }
        else 
        {
			
				 if (strchr("-.,:!?;", lastch))							//знаки припинания
				 {
					lastch = '.';									        
				 }
			
        }

	while((ch = fgetc(fi)) != EOF)
    {
		//Если англ или рус алфавит
        if(isalpha(ch)||strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮёйцукенгшщзхъфывапролджэячсмитьбю", ch))
        {
			if (strchr("ЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ", ch))//Если Заглавные рус
			{
				if ( ch == 0xA8)								//Отдельно для Ё
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//А и а рус
				}
				freq2[lastch][ch]++;
				lastch=ch;
			}else{
				ch = tolower(ch);           
				freq2[lastch][ch]++;				            
				lastch=ch;
			}
        }
        else 
        {
			if (ch == ' ')										//пробел
			{
				freq2[lastch][ch]++;
				lastch=ch;
			}else
			{
				 if (strchr("-.,:!?;", ch))						//знаки припинания
				 {
					ch = '.';				
					freq2[lastch][ch]++;
					lastch=ch;
				 }
			}
        }
 
    }

	

	for (int i = 0; i < AlfabetN; i++)
	{
		sum=0;
		for (int j = 0; j < AlfabetN; j++)
		{
			sum=sum+freq2[i][j];
		}
		
		for (int j = 0; j < AlfabetN; j++)
		{
			
			
				freq2[i][j]=freq2[i][j]/sum;
			//if(freq2[i][j]>0)	printf("P2[%c][%c]= %f\n",i,j,freq2[i][j]);
			
		}
	}
	
	H2=0;
	
	for (int i = 0; i < AlfabetN; i++)
	{
		for (int j = 0; j < AlfabetN; j++)
		{
			
			if(freq2[i][j]>0 )
			{
				H2=H2+res.freq[i]*freq2[i][j]*log2(freq2[i][j]);
			}
		}
	}
	
	
	printf("Энтропия файла для пар символов: %3.3f\n",(-1)*H2);	
	printf("Максимальная Энтропия файла: %3.3f\n",res.Hmax);
	if (res.Hmax==0)res.Hmax=1;
	printf("Избыточность текста для пар символов составила: %3.3f\n",1 + H2/res.Hmax);
	
	fclose(fi);
	system("PAUSE");


	return 0;
}

//Меню программы, type - задает нужные пункты меню.
inline wchar_t Menu(unsigned char type)
{
	wchar_t c;
	switch (type)
	{
		case 1:	system("CLS");
				puts("########################");
				puts("1. Ввести имя файла");
				puts("2. Оценка энтропии, одиночные символы");
				puts("3. Оценка энтропии, пары символов");
				puts("4. Выход из программы");
				puts("\n########################");
				puts("Выбрать пункт меню №: ");
				c=getchar();
				fflush(stdin);
				return c;
		default:puts("Err, нет такого меню");
				system("PAUSE");
				break;
	}
	
	return 0;
} 




				// Количество символов в алфавите
int _tmain(int argc, _TCHAR* argv[])
{
	
	float freq2[AlfabetN][AlfabetN] = {0};
	char FILENAME[200]={NULL};


	SetApp ();
	while (1)
	{
		switch (Menu(1))
		{
			case '1': fflush(stdin); system("DIR /a:-d"); puts("Введите имя файла\n"); gets(FILENAME);
				break;
			case '2': entropy_1( FILENAME);break;
			case '3': entropy_2( FILENAME);break;
			case '4': return 0;
			default:break;
		}
	}
	
	
	
	/*Вывод кодов ASCII, для проверки правильности их определения
	for (int i = 0; i < AlfabetN; i++)
	{
		puts("P[%c-%3d] = %4d\n",i,i,P1[i]);
	}*/
	
	system("PAUSE");
	return 0;
}

