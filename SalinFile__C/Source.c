#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

int file_copy(char* oldname, char* newname, long bytes1, long bytes2);
long get_bytes(float percent, char* source);

main()
{
	char source[80], destination[80];
	float percent1, percent2;

	/* Mendapatkan Nama File */
	puts("Enter source file:");
	printf("\t");

	gets(source);

	puts("\nEnter destination file \(WARNING: If the file exists, it will be OVERWRITTEN\): ");
	printf("\t");
	
	gets(destination);

	puts("\nEnter start percentage (recommended: 0): ");
	printf("\t");

	scanf_s("%f", &percent1);
	
	do
	{
		puts("\nEnter end percentage:");
		printf("\t");
		scanf_s("%f", &percent2);
	} while (percent2 < percent1);


	if (file_copy(source, destination, get_bytes(percent1, source), get_bytes(percent2, source)) == 1)
		puts("\nCopy operation SUCCESSFUL");
	else
		fprintf(stderr, "\nError during copy operation");

	fflush(stdin);

	puts("\nPress any key to exit . . . ");
	getchar();
	return(0);
}

int file_copy(char* oldname, char* newname, long bytes1, long bytes2)
{
	FILE* fold, * fnew;
	int c;

	if ((fold = fopen(oldname, "rb")) == NULL)
		return 0;

	if ((fnew = fopen(newname, "wb")) == NULL)
	{
		fclose(fold);
		return 0;
	}

	if ((fseek(fold, bytes1, SEEK_SET) != 0))
	{
		fprintf(stderr, "\nError using fseek().");
		exit(1);
	}

	while (1)
	{
		c = fgetc(fold);

		if (!feof(fold) && ftell(fold) <= bytes2)
			fputc(c, fnew);
		else
			break;
	}

	fclose(fnew);
	fclose(fold);

	return 1;
}

long get_bytes(float percent, char* source)
{
	long bytes;
	FILE* fold;

	if (percent <= 100)
	{
		if ((fold = fopen(source, "rb")) == NULL)
		{
			puts("Error opening source file");
			exit(1);
		}
		if ((fseek(fold, 0, SEEK_END)) != 0)
		{
			fprintf(stderr, "\nError using fseek().");
			exit(1);
		}

		bytes = ftell(fold);
		bytes *= (percent / 100);
	}
	else
	{
		fprintf(stderr, "Error in input");
		exit(1);
	}

	fclose(fold);
	return bytes;
}
