// Zadacha_1.cpp: определ¤ет точку входа дл¤ консольного приложени¤.
//

#include "stdafx.h"

#include <cmath>
#include <cstdio>
#include <ctype.h> 
#include <clocale>
#include <Windows.h>

#pragma warning (once : 4996)
#define AlfabetN 256	

//B Visual studio 2012 нет поддержки log2 Ќо в 2013 есть
//inline float log2(float n) {
//	if (n==0)
//	{
//		return 0;
//	}
//	return log(n) / log(2.0);
//}



//ѕредварительные настройки приложени¤
inline void SetApp(void)
{
	//setlocale( LC_ALL, "ru_RU.cp1251" );

	SetConsoleCP(1251);					// –усска¤ локаль
	SetConsoleOutputCP(1251);
}


struct result // —руктура хранени¤ информации
{
	float freq[AlfabetN];
	float H,Hmax;
}res;

//ќценка энтропии, одиночные символы
float entropy_1 (char *fn)
{
	FILE *fi;
	float freq[AlfabetN] = {0};
	float H=0,Hmax=0; 
	int K=0;
	int ch=EOF;
	long total=0;
	puts("‘айл:");	
	puts(fn);
	fi = fopen(fn, "r");
	if(fi == NULL)
    {
        puts("“акой файл не найден!");
		system("Pause");
        return -1;
    }
	
	
	while((ch = fgetc(fi)) != EOF)
    {
		//≈сли англ или рус алфавит
        if(isalpha(ch)||strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№ЅёЄйцукенгшщзхъфывапролджэ¤чсмитьбю", ch))
        {
			if (strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё", ch))//≈сли «аглавные рус
			{
				if ( ch == 0xA8)								//ќтдельно дл¤ ®
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//ј и а рус
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
				 if (strchr("-.,:!?;", ch))						//знаки препинани¤
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
	printf("¬сего символов в файле: %d\n",total);
	printf("¬сего символов в алфавите: %d\n",K);
	printf("Ёнтропи¤ файла: %3.3f\n",(-1)*H);	
	printf("ћаксимальна¤ Ёнтропи¤ файла: %3.3f\n",Hmax);
	
	printf("»збыточность текста составила: %3.3f\n",1 + H/Hmax);
	
	fclose(fi);
	system("PAUSE");
	return 0;
}

//ќценка энтропии, пары символов
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
        puts("“акой файл не найден!");
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
	//≈сли англ или рус алфавит
	if(isalpha(lastch)||strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№ЅёЄйцукенгшщзхъфывапролджэ¤чсмитьбю", lastch))
        {
			if (strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё", lastch))	//≈сли «аглавные рус
			{
				if ( lastch == 0xA8)									//ќтдельно дл¤ ®
				{
					lastch=0xB8;
				}else
				{
					lastch=lastch-0xC0+0xE0;							//ј и а рус
				}				            
			}else{
				lastch = tolower(lastch);           				        
			}
        }
        else 
        {
			
				 if (strchr("-.,:!?;", lastch))							//знаки припинани¤
				 {
					lastch = '.';									        
				 }
			
        }
	//—читаем количество повторений всех пар символов
	while((ch = fgetc(fi)) != EOF)
    {
		//≈сли англ или рус алфавит
        if(isalpha(ch)||strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№ЅёЄйцукенгшщзхъфывапролджэ¤чсмитьбю", ch))
        {
			if (strchr("®…÷” ≈Ќ√Ўў«’Џ‘џ¬јѕ–ќЋƒ∆Ёя„—ћ»“№Ѕё", ch))//≈сли «аглавные рус
			{
				if ( ch == 0xA8)								//ќтдельно дл¤ ®
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//ј и а рус
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
				 if (strchr("-.,:!?;", ch))						//знаки припинани¤
				 {
					ch = '.';				
					freq2[lastch][ch]++;
					lastch=ch;
				 }
			}
        }
 
    }

	
	//¬ычистл¤ем частоту(веро¤тность) пар символов
	for (int i = 0; i < AlfabetN; i++)
	{
		sum=0;
		//вычисл¤ем число повторений пар с фиксированной i буквой
		for (int j = 0; j < AlfabetN; j++)
		{
			sum=sum+freq2[i][j];
		}
		//вычисл¤ем веро¤тность по¤вление j символа после i символа
		for (int j = 0; j < AlfabetN; j++)
		{
			
			
				freq2[i][j]=freq2[i][j]/sum;
			//if(freq2[i][j]>0)	printf("P2[%c][%c]= %f\n",i,j,freq2[i][j]);
			
		}
	}
	
	H2=0;
	//—читаем энтропию дл¤ пар символов
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
	
	
	printf("Ёнтропи¤ файла дл¤ пар символов: %3.3f\n",(-1)*H2);	
	printf("ћаксимальна¤ Ёнтропи¤ файла: %3.3f\n",res.Hmax);
	if (res.Hmax==0)res.Hmax=1;
	printf("»збыточность текста дл¤ пар символов составила: %3.3f\n",1 + H2/res.Hmax);
	
	fclose(fi);
	system("PAUSE");


	return 0;
}

//ћеню программы, type - задает нужные пункты меню.
inline wchar_t Menu(unsigned char type)
{
	wchar_t c;
	switch (type)
	{
		case 1:	system("CLS");
				puts("########################");
				puts("1. ¬вести им¤ файла");
				puts("2. ќценка энтропии, одиночные символы");
				puts("3. ќценка энтропии, пары символов");
				puts("4. ¬ыход из программы");
				puts("\n########################");
				puts("¬ыбрать пункт меню є: ");
				c=getchar();
				fflush(stdin);
				return c;
		default:puts("Err, нет такого меню");
				system("PAUSE");
				break;
	}
	
	return 0;
} 




				//  оличество символов в алфавите
int _tmain(int argc, _TCHAR* argv[])
{
	
	float freq2[AlfabetN][AlfabetN] = {0};
	char FILENAME[200]={NULL};


	SetApp ();
	while (1)
	{
		switch (Menu(1))
		{
			case '1': fflush(stdin); system("DIR /a:-d"); puts("¬ведите им¤ файла\n"); gets(FILENAME);
				break;
			case '2': entropy_1( FILENAME);break;
			case '3': entropy_2( FILENAME);break;
			case '4': return 0;
			default:break;
		}
	}
	
	
	
	/*¬ывод кодов ASCII, дл¤ проверки правильности их определени¤
	for (int i = 0; i < AlfabetN; i++)
	{
		puts("P[%c-%3d] = %4d\n",i,i,P1[i]);
	}*/
	
	system("PAUSE");
	return 0;
}

