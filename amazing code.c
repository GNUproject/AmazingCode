
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

static const char * const READ  = "r";
static const char * const OpenFileError = "打开文件%s失败!\n";
static const char * const CloseFileError = "关闭文件%s失败!\n";
static const char * const FileOperationError = "文件%s操作失败!\n";

#ifdef WINDOWS_VISUALSTUDIO
	#define LEN 225
#else
	#define LEN 256
#endif

void FileOperation(const char * const FileName, const char * const Mode);
void InputStream(FILE * const Stream);
static void UnusualToExit(const char * const str, const char * const FileName);

int main(void)
{
	const char FileName[LEN] = __FILE__;
	FileOperation(FileName, READ);

#ifdef WINDOWS_VISUALSTUDIO
	_getch();
#endif
	return 0;
}

void FileOperation(const char * const FileName, const char * const Mode)
{
#ifdef WINDOWS_VISUALSTUDIO
	FILE *FilePointer;
	const errno_t err = fopen_s(&FilePointer, FileName, Mode);

	// if (err == 0)
	if (!err)
#else
	FILE * const FilePointer = fopen(FileName, Mode);

	// if (FilePointer != NULL)
	if (FilePointer)
#endif
	{
		InputStream(FilePointer);

		// if (ferror(FilePointer) != 0)
		if (ferror(FilePointer))
			UnusualToExit(FileOperationError, FileName);

#ifdef WINDOWS_VISUALSTUDIO
		// if (FilePointer != NULL)
		if (FilePointer)
#endif
			// if (fclose(FilePointer) != 0)
			if (fclose(FilePointer))
				UnusualToExit(CloseFileError, FileName);
	}
	else
		UnusualToExit(OpenFileError, FileName);
}

void InputStream(FILE * const Stream)
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

static void UnusualToExit(const char * const str, const char * const FileName)
{
	// if (str != NULL)
	if (str)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, str, FileName);
		_getch();
#else
		fprintf(stderr, str, FileName);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}
}
