#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DRA_COUNTER_GENERATOR_IMPLEMENTATION
#include "generator.h"

void counter_set_default(counter_info *info)
{
	info->name = "MY_COUNTER";
	info->max_value = 10000;
	info->iterations_per_file = 1000;
}

/*
typedef struct {
	char *text;
	void (*function)(int argc, char **argv, int idx, int parameters);
	int parameters;
} argument_t;

#define MAKE_ARGS_FUNCTION(name, body) void name(int argc, char **argv, int idx, int parameters) body // these funcitons should maybe also take a pointer to he info object so that they can modify it.

MAKE_ARGS_FUNCTION(fn_help,
{
	printf("--help               : show this message.\n");
	printf("--name <value>       : define a custom name for the generated counter.\n");
	printf("--max <value>        : define a custom value for the max value the counter can count to.\n");
	printf("--iterations <value> : define a custom number of iterations that will be stored on each generated file.\n");
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
static size_t const arguments_length = sizeof(arguments) / sizeof(argument_t);

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
*/

void counter_generate(counter_info *info)
{
	printf("Counter Configuration:\n");
	printf(" - CounterName       : %s\n", info->name);
	printf(" - MaxValue          : %d\n", info->max_value);
	printf(" - Iterations/File   : %d\n", info->iterations_per_file);
	
	generate_counter_files(info);
}

void parse_args(int argc, char **argv)
{
	counter_info info;
	counter_set_default(&info);
	
	if(argc <= 1)
	{
		fprintf(stderr, "Usage : %s --run <args>\nUse --help for more information.\n", argv[0]);
		return;
	}
	
	int args_have_been_issued;
	
	for(int i = 1; i < argc; ++i)
	{
		if(!strcmp(argv[i], "--run"))
		{
			fprintf(stdout, "Generating files for counter macro...\n");
			counter_generate(&info);
			
			args_have_been_issued = 0;
			counter_set_default(&info);
		}
		else
		if(!strcmp(argv[i], "--help"))
		{
			printf("--help               : show this message.\n");
			printf("--run                : run the generator with the selected configuration.\n");
			printf("--name <value>       : define a custom name for the generated counter.\n");
			printf("--max <value>        : define a custom value for the max value the counter can count to.\n");
			printf("--iterations <value> : define a custom number of iterations that will be stored on each generated file.\n");
			
			printf("\n\n");
			
			printf("The generator allows creating multiple counters within the same call to the generator program.\n");
			printf("Example: ./generator --name COUNTER_A --max 1000 --iterations 500 --run --name COUNTER_B --max 12000 --iterations 1200 --run\n");
			printf("This command will generate 2 counters in a single call to the generator program.\n");
		}
		else
		if(!strcmp(argv[i], "--name"))
		{
			if(i + 1 < argc)
			{
				info.name = argv[i + 1];
				++i;
				args_have_been_issued = 1;
			}
			else
			{
				fprintf(stderr, "ERROR : Parameter missing for argument \"--name\".\n");
			}
		}
		else
		if(!strcmp(argv[i], "--max"))
		{
			if(i + 1 < argc)
			{
				int max_value = atoi(argv[i + 1]);
				info.max_value = max_value;
				++i;
				args_have_been_issued = 1;
			}
			else
			{
				fprintf(stderr, "ERROR : Parameter missing for argument \"--max\".\n");
			}
		}
		else
		if(!strcmp(argv[i], "--iterations"))
		{
			if(i + 1 < argc)
			{
				int itrs = atoi(argv[i + 1]);
				info.iterations_per_file = itrs;
				++i;
				args_have_been_issued = 1;
			}
			else
			{
				fprintf(stderr, "ERROR : Parameter missing for argument \"--iterations\".\n");
			}
		}
		else
		{
			fprintf(stderr, "ERROR : Uknown argument issued \"%s\".\n", argv[i]);
		}
	}
	
	if(args_have_been_issued) /* The args have been issued but not consumed by a call to --run */
	{
		fprintf(stderr, "Warning : Arguments issued but not consumed. Did you forget a call to --run?\n");
	}
}

int main(int argc, char **argv)
{
	parse_args(argc, argv);
	
	return 0;
}
