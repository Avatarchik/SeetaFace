#include <stdio.h>
#include <stdlib.h>

//接口声明
void face_detection_test(int argc, char* argv[]);
void face_alignment_test(int argc, char* argv[]);
void face_recognizer_test(int argc, char* argv[]);

//
typedef void (*test_item_func)(int argc, char* argv[]);

struct test_item
{
	char description[128];
	test_item_func func;
};

test_item g_test_item[]=
{
	{"face_detection_test []:", face_detection_test},
	{"face_alignment_test []:", face_alignment_test},
	{"face_recognizer_test []:", face_recognizer_test},
	{"", NULL},
};

int main(int argc, char* argv[])
{
	//打印
	printf("test cmdline=");
	for (int i = 0;i < argc;i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");

	if (argc < 2)
	{
		printf("help info:\n");
		for (int i = 0;g_test_item[i].func != NULL;i++)
		{
			printf("  [%d]%s\n", i, g_test_item[i].description);
		}
		printf("  [ ]all\n");
		printf("print test item:");

		static char buf[64] = {0};
		static char* bufv[10] = {0};
		gets(buf);

		bufv[0] = argv[0];
		argv = bufv;
		argc = 1;

		argv[argc] = (char*)buf;
		argc++;

		//cstrtok tok(buf, " ");

		//const char* str;
		//while ((str = tok.next()))
		//{
		//	bt::trim((char*)str, strlen(str));
		//	if (strlen(str) > 0)
		//	{
		//		argv[argc] = (char*)str;
		//		argc++;
		//	}
		//}
	}

	printf("begin\n");

	if (argc >= 2)
	{
		int index = atoi(argv[1]);
		(*g_test_item[index].func)(argc - 2, argv + 2);
	}
	else
	{
		for (int i = 0;g_test_item[i].func != NULL;i++)
		{
			(*g_test_item[i].func)(0, NULL);
		}
	}

	printf("end\n");

	getchar();

	return 0;
}

