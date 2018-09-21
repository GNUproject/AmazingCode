
// 程序运行结果即该程序源代码的程序

// 当前平台
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>

static void FileOperation(void);
static void InputStream(FILE * const Stream);
static void UnusualToExit(const char * const str);

int main(void)
{
	FileOperation();

#ifdef WINDOWS_VISUALSTUDIO
	_getch();
#endif
	return 0;
}

static void FileOperation(void)
{
#ifdef WINDOWS_VISUALSTUDIO
	FILE *FilePointer;
	const errno_t err = fopen_s(&FilePointer, __FILE__, "r");

	// if (err == 0)
	if (!err)
#else
	FILE * const FilePointer = fopen(__FILE__, "r");

	// if (FilePointer != NULL)
	if (FilePointer)
#endif
	{
		InputStream(FilePointer);

		// if (ferror(FilePointer) != 0)
		if (ferror(FilePointer))
			UnusualToExit("文件%s操作失败!\n");

#ifdef WINDOWS_VISUALSTUDIO
		// if (FilePointer != NULL)
		if (FilePointer)
#endif
			fclose(FilePointer);
	}
}

static void InputStream(FILE * const Stream)
{
	char ch;
	// while (feof(Stream) == 0)
	while (!feof(Stream))
	{
		ch = getc(Stream);
		if (ch != EOF)
			fputc(ch, stdout);
	}
}

static void UnusualToExit(const char * const str)
{
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(stderr, str, __FILE__);
	_getch();
#else
	fprintf(stderr, str, __FILE__);
#endif
	exit(EXIT_FAILURE); // exit (1);
}
