#include <stdio.h>

#define PUT(depth, FILE_POINTER, fmt, ...) do{ \
	for(int i = 0; i < depth; ++i) \
		fprintf(FILE_POINTER, "\t"); \
	fprintf(FILE_POINTER, fmt "\n", ##__VA_ARGS__); \
}while(0)

#define CREATE_K_FILE(x) do{\
	int value = x; \
	char buf[255] = {0}; \
	snprintf(buf, 255, "my_counter_%d.h", x); \
	FILE *fileitr = fopen(buf, "wb"); \
	PUT(0, fileitr, "#if MY_COUNTER == %d", value - 1000); \
		PUT(1, fileitr, "#undef MY_COUNTER"); \
		PUT(1, fileitr, "#define MY_COUNTER %d", value - 1000 + 1); \
	for(int i = 1; i < 1000; ++i) \
	{ \
		int value_itr = ((i) + (value) - (1000)); \
		PUT(0, fileitr, "#elif MY_COUNTER == %d", value_itr); \
			PUT(1, fileitr, "#undef MY_COUNTER"); \
			PUT(1, fileitr, "#define MY_COUNTER %d", value_itr + 1); \
	} \
	PUT(0, fileitr, "#endif"); \
	fclose(fileitr);\
}while(0)

#define MAKE_EMPTY_FILE(filename) do{ \
	FILE *file = fopen(filename, "wb"); \
	fprintf(file, "\n"); \
	fclose(file); \
}while(0)

int main()
{
	FILE *file;
	
	file = fopen("my_counter.h", "wb");
	
	PUT(0, file, "#ifndef MY_COUNTER");
		PUT(1, file, "#ifdef __COUNTER__");
			PUT(2, file, "#define MY_COUNTER __COUNTER__");
			PUT(2, file, "#define UPDATE_MY_COUNTER() \"my_counter_empty.h\"");
			PUT(2, file, "#define MY_COUNTER_TYPE \"__COUNTER__\"");
		PUT(1, file, "#else");
			PUT(2, file, "#define MY_COUNTER 0");
			PUT(2, file, "#define UPDATE_MY_COUNTER() \"my_counter.h\"");
			PUT(2, file, "#define MY_COUNTER_TYPE \"MY_COUNTER\"");
		PUT(1, file, "#endif");
		PUT(1, file, "#define MY_COUNTER_GET() \"my_counter_get.h\"");
	PUT(0, file, "#else");
	
		PUT(1, file, "#if MY_COUNTER < 1000");
			PUT(2, file, "#include \"my_counter_1000.h\"");
			CREATE_K_FILE(1000);
		for(int i = 2000; i < 10000; i+=1000)
		{
		PUT(1, file, "#elif MY_COUNTER < %d", i);
			PUT(2, file, "#include \"my_counter_%d.h\"\n", i);
			CREATE_K_FILE(i);
			printf("Created k-file for counter up to %d\n", i);
		}
		PUT(1, file, "#endif");
	
	PUT(0, file, "#endif");
	
	fclose(file);
	
	MAKE_EMPTY_FILE("my_counter_empty.h");
	
	file = fopen("my_counter_get.h", "wb");
	fprintf(file, "MY_COUNTER;\n#include UPDATE_MY_COUNTER()\n");
	fclose(file);
	
	return 0;
}
