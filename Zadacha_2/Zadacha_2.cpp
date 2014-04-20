// Zadacha_2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <ctype.h> 
#include <clocale>
#include <Windows.h>

//������� ������� ���������
#define rusUp "��������������������������������"
//������� ������� ���������
#define rusDown "��������������������������������"
//���������� ������� ���������
#define engUp "QWERTYUIOPASDFGHJKLZXCVBNM"
//���������� ������� ���������
#define engDown "qwertyuiopasdfghjklzxcvbnm"
//���������� �������� � ��������
#define n_Alfa 256
//����� ������������������ ����
#define length_code 26
//��������� �� ����������� �����
FILE *fi;
FILE *fcode;
//���������� �������� � ������
UINT32 lengthText=0;
//�������� �����
float H		=	(float)0;
//������������ �������� �����
float Hmax	=	(float)0;
//������� ����� �������� �����
float Lmean	=	(float)0;





void	readFilename();
UINT8	PaintMainMenu();
void	Gilbert_Mur();
void	FreqOne();
void	WriteCodeFile();
void	entropyBinOne();

//��������� ��� �������� ������ � ����� ��������
struct arrayAlfabeth
{
	//ASCII ��� �������
	UINT8 simbol;
	//������� ������� � ������������� ������
	float p;
	//����� �������� �����
	UINT8 length;
	//������� ������������������ ��������-����
	UINT8 code[length_code];
}ArrAlfa[n_Alfa];



//������������� ����������� �������
inline void ArrayInit(arrayAlfabeth *a)
{
	for (size_t i = 0; i < n_Alfa; i++)
	{
		a[i].simbol = i;
		a[i].p = (float)0;
		a[i].length = 0;
		memset(a[i].code, 0, length_code);
	}
}

//��������� ������� ������
inline void SetLoc(UINT loc)
{
	//setlocale( LC_ALL, "ru_RU.cp1251" );
	//������� ������
	SetConsoleCP(loc);					
	SetConsoleOutputCP(loc);
}
//������ ���������������� ����
UINT8 PaintMainMenu()
{
	UINT8 index;
	system("CLS");
	puts("########################");
	puts("1. �������-���");
	puts("2. �������� ������� ������������������ � ����(code.txt)");
	puts("3. ������ �������� �������� ������������������");
	puts("4. �����");
	puts("########################");
	puts("������� ����� ���� �: ");
	index = getchar();
	fflush(stdin);
	return index;


}
//������� �������� ������, ��������� ������� ����� ��� �������� �������� �����
void FreqOne()
{
	UINT8 ch = 0;
	UINT8 K = 0;
	lengthText = 0;
	H = 0;
	Lmean = 0;
	readFilename();
	
	
	
	ArrayInit(ArrAlfa);
	
	while (!feof(fi))
	{
		
			fscanf_s(fi, "%c", &ch);
			if (feof(fi))
			{
				break;
			}
			if (strchr(rusUp, ch))
			{
				ch = ch - 0xC0 + 0xE0;
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (strchr(rusDown, ch))
			{
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (strchr(engUp, ch))
			{
				ch = ch - 'A' + 'a';
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (strchr(engDown, ch))
			{
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (strchr("-.,:!?;", ch))
			{
				ch = '.';
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (ch == ' ')
			{
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
			else
			if (ch == 0xA8 || ch == 0xB8)
			{
				ch = 0xE5;
				ArrAlfa[ch].p += 1.0;
				lengthText++;
			}
		
	}
	fclose(fi);
	
	printf_s("The file was closed\n");
	for (int i = 0; i < n_Alfa; i++)
	{

		if (ArrAlfa[i].p != (float)0)
		{			
			ArrAlfa[i].p = ArrAlfa[i].p / lengthText;
			printf_s("P[%c] = %1.4f\n", i, ArrAlfa[i].p);
			H = H + ArrAlfa[i].p * log2(ArrAlfa[i].p);
			K++;
		}
	}
	Hmax = log2((float)K);
	if (Hmax == 0)Hmax = 1;
	printf_s("����� �������� � �����: %d\n", lengthText);
	printf("����� �������� � ��������: %d\n", K);
	printf("�������� �����: %3.3f\n", (-1)*H);
	printf("������������ �������� �����: %3.3f\n", Hmax);
	printf("������������ ������ ���������: %3.3f\n", (float)1 + H / Hmax);

	Gilbert_Mur();

	system("pause");
	for (int i = 0; i < n_Alfa; i++)
	{

		if (ArrAlfa[i].p != (float)0)
		{			
			printf_s("P[%c] = %1.4f kod = ", i, ArrAlfa[i].p);
			for (int j = 0; j<ArrAlfa[i].length; j++) printf("%c", ArrAlfa[i].code[j]);
			printf_s("\n");
		}
	}
	printf("������� ����� �������� �����: %3.3f\n", Lmean);
	printf("������������ ����������� ���������: %3.3f\n", Lmean - (-1.0)*H);
	system("pause");
}
//��� �������-���
void Gilbert_Mur()
{
	float q[n_Alfa], pr = 0.0;
	
	q[0] = ArrAlfa[0].p / 2; 
	ArrAlfa[0].length = (UINT8)(-log2(ArrAlfa[0].p) + 2);
	pr = ArrAlfa[0].p;
	for (int i = 1; i<n_Alfa; i++)
	{
		if (ArrAlfa[i].p!=(float)0)
		{
			q[i] = pr + ArrAlfa[i].p / 2;
			ArrAlfa[i].length = (UINT8)(-log2(ArrAlfa[i].p) + 2);
			pr += ArrAlfa[i].p;
		}
	}
	
	for (int i = 0; i < n_Alfa; i++)
	{
		if (ArrAlfa[i].p != (float)0)
		{
			for (int j = 0; j<ArrAlfa[i].length; j++)
			{
				q[i] *= 2.0;
				ArrAlfa[i].code[j] = (int)(q[i])+0x30;//��������� 0 � 1 � ������� ASCII, ��� �������� ���������� �������� ������������������
				if (q[i]>=1.0) q[i]--;	//���� ������� �������� ������� > �� ���  q=0.75 � p = 0.009 ���������� ���������� 11222222!!!!
			}							//� ��������� ������� >
		}
	}
	
	
	for (int i = 0; i<n_Alfa; i++)
	{		
		Lmean += ArrAlfa[i].length*ArrAlfa[i].p;
	}
}

void WriteCodeFile()
{
	int numclosed;
	errno_t err;
	UINT8 ch = 0;
	readFilename();
		
	err = fopen_s(&fcode, "code.txt", "wb");
	if (err == 0)
	{
		printf_s("The file CODE.txt was opened\n");		
	}
	else
	{
		printf_s("The file CODE.txt was not opened\n");
		numclosed = _fcloseall();
	}
	while (!feof(fi))
	{

		fscanf_s(fi, "%c", &ch);
		if (feof(fi))
		{
			break;
		}
		if (strchr(rusUp, ch))
		{
			ch = ch - 0xC0 + 0xE0;
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
			
		}
		else
		if (strchr(rusDown, ch))
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr(engUp, ch))
		{
			ch = ch - 'A' + 'a';
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr(engDown, ch))
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr("-.,:!?;", ch))
		{
			ch = '.';
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (ch == ' ')
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (ch == 0xA8 || ch == 0xB8)
		{
			ch = 0xE5;
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}

	}
	numclosed = _fcloseall();
	
	system("pause");
}


//���������� �������� ����� �� ������
void readFilename()
{
	errno_t err;	
	char FileName[200];
	fflush(stdin); 
	system("DIR /a:-d"); 
	puts("������� ��� �����\n"); 
	while (true)
	{
		gets_s(FileName,200);
		err = fopen_s(&fi, FileName, "r");
		if (err == 0)
		{
			printf_s("The file ""%s"" was opened\n",FileName);
			break;
		}
		else
		{
			printf_s("The file ""%s"" was not opened, try again\n",FileName);
		}		
	}
}
//������� �������� �������� ������������������ � ����� code.txt �������={0,1}
void entropyBinOne()
{
	errno_t err;
	float p1[2] = { 0 };
	float p2[2][2] = { 0 };
	long total = 0;
	long sum = 0;
	float entr = 0;
	float entr2 = 0;
	UINT8 ch = 0;
	UINT8 lastch = 0;

	err = fopen_s(&fi, "code.txt", "r");
	if (err == 0)
	{
		printf_s("The file code.txt was opened\n");
	}
	else
	{
		printf_s("The file code.txt was not opened, try again\n");
	}
	
	while (!feof(fi))
	{

		fscanf_s(fi, "%c", &ch);
		if (feof(fi))
		{
			break;
		}
		ch = ch - 0x30;
		p1[ch]++;
		total++;
	}	

	p1[0] = p1[0] / total;
	printf_s("p[0]=%1.4f\n",p1[0]);
	p1[1] = p1[1] / total;
	printf_s("p[1]=%1.4f\n", p1[1]);
	entr = p1[0] * log2f(p1[0]) + p1[1] * log2f(p1[1]);
	entr = entr*(float)(-1);
	
	ch = 0;
	rewind(fi);
	fscanf_s(fi, "%c", &lastch);
	lastch = lastch - 0x30;
	
	while (!feof(fi))
	{
		fscanf_s(fi, "%c", &ch);
		if (feof(fi))
		{
			break;
		}
		ch = ch - 0x30;
		p2[lastch][ch]++;
		lastch = ch;
	}
	for (int i = 0; i < 2; i++)
	{
		sum = 0;
		for (int j = 0; j < 2; j++)
		{
			sum = sum + p2[i][j];
		}

		for (int j = 0; j < 2; j++)
		{
			p2[i][j] = p2[i][j] / sum;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (p2[i][j]>0)
			{
				entr2 = entr2 + p1[i] * p2[i][j] * log2(p2[i][j]);
				printf("P2[%c][%c]= %f\n", i+0x30, j+0x30, p2[i][j]);
			}
		}
	}
	entr2 = entr2*(float)(-1);

	printf_s("�������� ������� ������������������(������� ��������� ��������) ����� = %1.4f\n", entr);
	printf_s("�������� ������� ������������������(������� ��� ��������) ����� = %1.4f\n", entr2);
	system("pause");
	fclose(fi);
}

//���� �������� ������� ���������
int _tmain(int argc, _TCHAR* argv[])
{	
	int numclosed;
	SetLoc(1251);
	
	
	while (true)
	{
		switch (PaintMainMenu())
		{
		case '1':FreqOne();			break;
		case '2':WriteCodeFile();	break;
		case '3':entropyBinOne();	break;
		case '4':numclosed = _fcloseall();return 0;			
		default:	break;
		}
	}

	
	numclosed = _fcloseall();
	return 0;
}

