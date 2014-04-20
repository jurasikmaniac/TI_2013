// Zadacha_1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <cmath>
#include <cstdio>
#include <ctype.h> 
#include <clocale>
#include <Windows.h>

#pragma warning (once : 4996)
#define AlfabetN 256	

//B Visual studio 2012 ��� ��������� log2
//inline float log2(float n) {
//	if (n==0)
//	{
//		return 0;
//	}
//	return log(n) / log(2.0);
//}



//��������������� ��������� ����������
inline void SetApp(void)
{
	//setlocale( LC_ALL, "ru_RU.cp1251" );

	SetConsoleCP(1251);					// ������� ������
	SetConsoleOutputCP(1251);
}


struct result // �������� �������� ����������
{
	float freq[AlfabetN];
	float H,Hmax;
}res;

//������ ��������, ��������� �������
float entropy_1 (char *fn)
{
	FILE *fi;
	float freq[AlfabetN] = {0};
	float H=0,Hmax=0; 
	int K=0;
	int ch=EOF;
	long total=0;
	puts("����:");	
	puts(fn);
	fi = fopen(fn, "r");
	if(fi == NULL)
    {
        puts("����� ���� �� ������!");
		system("Pause");
        return -1;
    }
	
	
	while((ch = fgetc(fi)) != EOF)
    {
		//���� ���� ��� ��� �������
        if(isalpha(ch)||strchr("��������������������������������޸��������������������������������", ch))
        {
			if (strchr("���������������������������������", ch))//���� ��������� ���
			{
				if ( ch == 0xA8)								//�������� ��� �
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//� � � ���
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
			if (ch == ' ')										//������
			{
				freq[ch]++;
				total++;            
			}else
			{
				 if (strchr("-.,:!?;", ch))						//����� ����������
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
	printf("����� �������� � �����: %d\n",total);
	printf("����� �������� � ��������: %d\n",K);
	printf("�������� �����: %3.3f\n",(-1)*H);	
	printf("������������ �������� �����: %3.3f\n",Hmax);
	
	printf("������������ ������ ���������: %3.3f\n",1 + H/Hmax);
	
	fclose(fi);
	system("PAUSE");
	return 0;
}

//������ ��������, ���� ��������
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
        puts("����� ���� �� ������!");
		system("Pause");
        return -1;
    }
	while((ch = fgetc(fi)) != EOF)
	{
		sum++;
	}
	if (sum<2||sum==0)
	{
		puts("� ����� ��� ��� ��������");
		system("Pause");
        return -2;
	}
	rewind(fi);
	lastch= fgetc(fi);
	//���� ���� ��� ��� �������
	if(isalpha(lastch)||strchr("��������������������������������޸��������������������������������", lastch))
        {
			if (strchr("���������������������������������", lastch))	//���� ��������� ���
			{
				if ( lastch == 0xA8)									//�������� ��� �
				{
					lastch=0xB8;
				}else
				{
					lastch=lastch-0xC0+0xE0;							//� � � ���
				}				            
			}else{
				lastch = tolower(lastch);           				        
			}
        }
        else 
        {
			
				 if (strchr("-.,:!?;", lastch))							//����� ����������
				 {
					lastch = '.';									        
				 }
			
        }

	while((ch = fgetc(fi)) != EOF)
    {
		//���� ���� ��� ��� �������
        if(isalpha(ch)||strchr("��������������������������������޸��������������������������������", ch))
        {
			if (strchr("���������������������������������", ch))//���� ��������� ���
			{
				if ( ch == 0xA8)								//�������� ��� �
				{
					ch=0xB8;
				}else
				{
					ch=ch-0xC0+0xE0;							//� � � ���
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
			if (ch == ' ')										//������
			{
				freq2[lastch][ch]++;
				lastch=ch;
			}else
			{
				 if (strchr("-.,:!?;", ch))						//����� ����������
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
	
	
	printf("�������� ����� ��� ��� ��������: %3.3f\n",(-1)*H2);	
	printf("������������ �������� �����: %3.3f\n",res.Hmax);
	if (res.Hmax==0)res.Hmax=1;
	printf("������������ ������ ��� ��� �������� ���������: %3.3f\n",1 + H2/res.Hmax);
	
	fclose(fi);
	system("PAUSE");


	return 0;
}

//���� ���������, type - ������ ������ ������ ����.
inline wchar_t Menu(unsigned char type)
{
	wchar_t c;
	switch (type)
	{
		case 1:	system("CLS");
				puts("########################");
				puts("1. ������ ��� �����");
				puts("2. ������ ��������, ��������� �������");
				puts("3. ������ ��������, ���� ��������");
				puts("4. ����� �� ���������");
				puts("\n########################");
				puts("������� ����� ���� �: ");
				c=getchar();
				fflush(stdin);
				return c;
		default:puts("Err, ��� ������ ����");
				system("PAUSE");
				break;
	}
	
	return 0;
} 




				// ���������� �������� � ��������
int _tmain(int argc, _TCHAR* argv[])
{
	
	float freq2[AlfabetN][AlfabetN] = {0};
	char FILENAME[200]={NULL};


	SetApp ();
	while (1)
	{
		switch (Menu(1))
		{
			case '1': fflush(stdin); system("DIR /a:-d"); puts("������� ��� �����\n"); gets(FILENAME);
				break;
			case '2': entropy_1( FILENAME);break;
			case '3': entropy_2( FILENAME);break;
			case '4': return 0;
			default:break;
		}
	}
	
	
	
	/*����� ����� ASCII, ��� �������� ������������ �� �����������
	for (int i = 0; i < AlfabetN; i++)
	{
		puts("P[%c-%3d] = %4d\n",i,i,P1[i]);
	}*/
	
	system("PAUSE");
	return 0;
}

