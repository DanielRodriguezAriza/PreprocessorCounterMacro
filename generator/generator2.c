#include <stdio.h>
#include <string.h>

/*
	HELPER MACROS
*/

#define PUT_INTERNAL(depth, file, fmt, tab, end, ...) do{ \
	for(int i = 0; i < depth; ++i) \
		fprintf(file, tab); \
	fprintf(file, fmt, ##__VA_ARGS__); \
	fprintf(file, end); \
}while(0)

#define PUT(depth, file, fmt, ...) PUT_INTERNAL(depth, file, fmt, "\t", "", ##__VA_ARGS__)

#define PUT_LN(depth, file, fmt, ...) PUT_INTERNAL(depth, file, fmt, "\t", "\n", ##__VA_ARGS__)





typedef struct {
	char *text;
	void (*function)(int argc, char **argv, int idx, int parameters);
	int parameters;
} argument_t;

/*
	It has been considered whether counter_min and counter_increment parameters should be added, but it has been decided against due to the fact that these are features that most users will not require, and those who do require it can implement them easily on their own.
	
	This generator is designed to give a basis for customizing user defined compiletime macro counters.
	
	For instance:
		-Min value:
			Call the counter macro and add a value to it. This value will be the min value.
			This can be wrapped around yet another user defined macro, allowing for easier use.
		
		-Custom Increment:
			Manually calculate the increment by multiplying or operating over the value returned by the macro. 
*/

#define MAKE_ARGS_FUNCTION(name, body) void name(int argc, char **argv, int idx, int parameters) body

MAKE_ARGS_FUNCTION(fn_help,
{
	fprintf(stdout, "--help : show this text.\n");
	fprintf(stdout, "--counter_name : define a custom name for the generated counter.\n");
	fprintf(stdout, "--counter_max : define a custom value for the max value the counter can count to.\n");
	fprintf(stdout, "--iterations_per_file : define a custom number of iterations that will be stored on each generated file.\n");
})

MAKE_ARGS_FUNCTION(fn_set_counter_name, {
	
})

MAKE_ARGS_FUNCTION(fn_set_counter_max, {
	
})

MAKE_ARGS_FUNCTION(fn_set_iterations_per_file, {
	
})

static argument_t arguments[] = {
	{"--help", fn_help, 0},
	{"--counter_name", fn_set_counter_name, 1},
	{"--counter_max", fn_set_counter_max, 1},
	{"--iterations_per_file", fn_set_iterations_per_file, 1}
};
static size_t const arguments_length = sizeof(arguments) / sizeof(argument_t); /* ironically, a counter could be used on insertion within the array to actually count the elements lol. Not worth it imo, but a funny idea nonetheless... */

int match_arg(int argc, char **argv, int idx)
{
	for(int i = 0; i < arguments_length; ++i)
	{
		if(!strcmp(arguments[i].text, argv[idx]))
		{
			arguments[i].function(argc, argv, idx, arguments[i].parameters);
			return arguments[i].parameters;
		}
	}
	printf("ERROR: Unknown argument...");
	return -1;
}

int iterate_args(int argc, char **argv)
{
	for(int i = 1; i < argc; ++i)
	{
		int val = match_arg(argc, argv, i);
		if(val < 0)
			return 1;
		i += val;
	}
	return 0;
}

/*
	IDEAS : __COUNTER__ is global, so...
	make it so that there's a parameter that allows you to define if you want to make a global counter
	another that allows you to define if you want to allow the counter to use __COUNTER__ if available for your compiler (only happens if the counter is global)
	change code gen to include custom counter names and user defined info.
	
	idea (OLD):
	to create your own counter, make it one of 2 ways:

	1) use the code generator with a custom name

	2) modify the code generator to do the following:
		have it so that within a file you include itself, allowing for a second preprocessor pass, and then use that to translate CAT2(MY_COUNTER, USER_DEFINED_NAME) to a proper token that can be used in a #define, allowing you to have code gen with macros, without having to re-generate anything through the code generation program.

	MAYBE YOU HAVE TO CREATE YET ANOTHER CUSTOM LIBRARY, ONE FOR MAKING ARGS PARSING LESS OF A PAIN IN THE BUTT, LIKE WHAT YOU'RE DOING RIGHT NOW... OR YOU COULD JUST USE A LARGE SWITCH CASE...


*/

enum COUNTER_TYPE
{
	COUNTER_TYPE_GLOBAL = 0,
	COUNTER_TYPE_UNIQUE
};

char const *counter_name = "MY_COUNTER_NEW";
int counter_max = 10000;
int counter_iterations_per_file = 1000;
int counter_type = COUNTER_TYPE_UNIQUE;



typedef struct {
	char const *name;
	int max_value;
	int iterations_per_file;
} counter_info;

void generate_counter_main_file(counter_info *info) // generates the file my_counter.h
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


/*
	- counter file name
	- counter macro name
	- counter update macro name
	- counter min value
	- counter max value
	- counter increment
	- counter iterations per file

*/

/*
	- counter name
	- counter max
	- counter iterations per file
*/


int main(int argc, char **argv) {
	/*
	int success = iterate_args(argc, argv);
	if(success != 0)
		return 1;
	*/
	
	counter_info info;
	info.name = "MY_COUNTER";
	info.max_value = 10000;
	info.iterations_per_file = 1000;
	generate_counter_files(&info);
	
	return 0;
}
