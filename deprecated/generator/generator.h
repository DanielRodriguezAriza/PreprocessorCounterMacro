#ifndef DRA_COUNTER_GENERATOR
#define DRA_COUNTER_GENERATOR

#include <stdio.h>
#include <string.h>

#define PUT_INTERNAL(depth, file, fmt, tab, end, ...) do{ \
	for(int i = 0; i < depth; ++i) \
		fprintf(file, tab); \
	fprintf(file, fmt, ##__VA_ARGS__); \
	fprintf(file, end); \
}while(0)

#define PUT(depth, file, fmt, ...) PUT_INTERNAL(depth, file, fmt, "\t", "", ##__VA_ARGS__)

#define PUT_LN(depth, file, fmt, ...) PUT_INTERNAL(depth, file, fmt, "\t", "\n", ##__VA_ARGS__)

typedef struct {
	char const *name;
	int max_value;
	int iterations_per_file;
} counter_info;


void generate_counter_main_file(counter_info *info);
void generate_counter_main_file(counter_info *info);
void generate_counter_update_file(counter_info *info);
void generate_counter_segment_file(counter_info *info, int segment);
void generate_counter_segment_files(counter_info *info);
void generate_counter_empty_file(counter_info *info);
void generate_counter_files(counter_info *info);


#ifdef DRA_COUNTER_GENERATOR_IMPLEMENTATION

void generate_counter_main_file(counter_info *info)
{
	char filename[255] = {0};
	snprintf(filename, 255, "%s_counter.h", info->name);
	
	FILE *file;
	file = fopen(filename, "wb");
	
	PUT_LN(0, file, "#define %s_USE_COMPILER_COUNTER %d", info->name, 0);
	PUT_LN(0, file, "#ifndef %s", info->name);
		PUT_LN(1, file, "#if (%s_USE_COMPILER_COUNTER) && defined(__COUNTER__)", info->name);
			PUT_LN(2, file, "#define %s __COUNTER__", info->name);
			PUT_LN(2, file, "#define %s_UPDATE() \"%s_counter_empty.h\"", info->name, info->name);
			PUT_LN(2, file, "#define %s_TYPE \"__COUNTER__\"", info->name);
		PUT_LN(1, file, "#else");
			PUT_LN(2, file, "#define %s 0", info->name);
			PUT_LN(2, file, "#define %s_UPDATE() \"%s_counter_update.h\"", info->name, info->name);
			PUT_LN(2, file, "#define %s_TYPE \"DRA_COUNTER\"", info->name);
		PUT_LN(1, file, "#endif");	
	PUT_LN(0, file, "#endif");
	
	fclose(file);
}

void generate_counter_update_file(counter_info *info) // generates the file my_counter_update.h
{
	char filename[255] = {0};
	snprintf(filename, 255, "%s_counter_update.h", info->name);
	
	FILE *file;
	file = fopen(filename, "wb");
	
	PUT_LN(0, file, "#ifdef %s", info->name);
	
	int i = info->iterations_per_file;
	
	PUT_LN(1, file, "#if %s < %d", info->name, i);
	PUT_LN(2, file, "#include \"%s_counter_%d.h\"", info->name, i);
	
	for(i = info->iterations_per_file * 2; i < info->max_value; i+=info->iterations_per_file)
	{
		PUT_LN(1, file, "#elif %s < %d", info->name, i);
		PUT_LN(2, file, "#include \"%s_counter_%d.h\"", info->name, i);
	}
	
	PUT_LN(1, file, "#elif %s <= %d", info->name, i);
	PUT_LN(2, file, "#include \"%s_counter_%d.h\"", info->name, i);
	
	PUT_LN(1, file, "#endif");
	
	PUT_LN(0, file, "#endif");
	
	fclose(file);
}

void generate_counter_segment_file(counter_info *info, int segment) // generates the files my_counter_1000.h
{
	char filename[255] = {0};
	snprintf(filename, 255, "%s_counter_%d.h", info->name, segment);
	
	FILE *file;
	file = fopen(filename, "wb");
	
	int first_value = segment - info->iterations_per_file;
	
	PUT_LN(0, file, "#if %s == %d", info->name, first_value); // #if MY_COUNTER == 0
	PUT_LN(1, file, "#undef %s", info->name);
	PUT_LN(1, file, "#define %s %d", info->name,  first_value + 1);
	
	for(int i = first_value + 1; i < segment; ++i)
	{
		PUT_LN(0, file, "#elif %s == %d", info->name, i); // #if MY_COUNTER == 0
		PUT_LN(1, file, "#undef %s", info->name);
		PUT_LN(1, file, "#define %s %d", info->name,  i + 1);
	}
	
	PUT_LN(0, file, "#endif");
	
	fclose(file);
}

void generate_counter_segment_files(counter_info *info)
{
	for(int i = info->iterations_per_file; i <= info->max_value; i+=info->iterations_per_file)
		generate_counter_segment_file(info, i);
}

void generate_counter_empty_file(counter_info *info) // generates the file my_counter_empty.h
{
	char filename[255] = {0};
	snprintf(filename, 255, "%s_counter_empty.h", info->name);
	
	FILE *file;
	file = fopen(filename, "wb");
	
	fprintf(file, "\n");
	
	fclose(file);
}

void generate_counter_files(counter_info *info)
{
	generate_counter_main_file(info);
	generate_counter_update_file(info);
	generate_counter_empty_file(info);
	generate_counter_segment_files(info);
}

#endif /* DRA_COUNTER_GENERATOR_IMPLEMENTATION */

#endif /* DRA_COUNTER_GENERATOR */
