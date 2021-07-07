
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

static const char* const ReadTextFile		= "r";
static const char* const NullPointer		= "空指针!\n";
static const char* const OpenFileError		= "打开文件%s失败!\n";
static const char* const CloseFileError		= "关闭文件%s失败!\n";
static const char* const FileOperationError	= "文件%s操作失败!\n";

void FileOperation(const char* const FileName, const char* const Mode);
void InputStream(FILE* const Stream);
static void UnusualToExit(const char* const str, const char* const FileName);

int main(void)
{
	const char * const FileName = __FILE__;
	FileOperation(FileName, ReadTextFile);

#ifdef WINDOWS_VISUALSTUDIO
	_getch();
#endif
	return 0;
}

void FileOperation(const char* const FileName, const char* const Mode)
{
	// if (FileName == NULL || Mode == Mode)
	if (!FileName || !Mode)
	{
		UnusualToExit(NullPointer, NULL);
	}

#ifdef WINDOWS_VISUALSTUDIO
	FILE *FilePointer = NULL;
	const errno_t Error = fopen_s(&FilePointer, FileName, Mode);

	// if (Error != 0)
	if (Error)
#else
	FILE * restrict const FilePointer = fopen(FileName, Mode);

	// if (FilePointer == NULL)
	if (!FilePointer)
#endif
	{
		UnusualToExit(OpenFileError, FileName);
	}

	// if (strcmp(Mode, ReadTextFile) == 0)
	if (!strcmp(Mode, ReadTextFile)) // 若执行读操作
	{
		// if (strrchr(Mode, 'b') == NULL)
		if (!strrchr(Mode, 'b')) // 若为文本文件
		{
			InputStream(FilePointer);
		}
	}

	// if (ferror(FilePointer) != 0)
	if (ferror(FilePointer))
	{
		UnusualToExit(FileOperationError, FileName);
	}

#ifdef WINDOWS_VISUALSTUDIO
	// if (FilePointer != NULL)
	if (FilePointer)
#endif
	{
		// if (fclose(FilePointer) != 0)
		if (fclose(FilePointer))
		{
			UnusualToExit(CloseFileError, FileName);
		}
	}
}

void InputStream(FILE* const Stream)
{
	// if (Stream == NULL)
	if (!Stream)
	{
		UnusualToExit(NullPointer, NULL);
	}

	char ch;

	// while (feof(Stream) == 0)
	while (!feof(Stream))
	{
		ch = getc(Stream);
		if (ch != EOF)
		{
			fputc(ch, stdout);
		}
	}
}

static void UnusualToExit(const char* const str, const char* const FileName)
{
	// if (str == NULL)
	if (!str)
	{
		UnusualToExit(NullPointer, NULL);
	}

#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(stderr, str, FileName);
	_getch();
#else
	fprintf(stderr, str, FileName);
#endif
	exit(EXIT_FAILURE); // exit (1);
}
