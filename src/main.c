#include <stdio.h>

#define putln(file, fmt, ...) (fprintf(file, fmt, ##__VA_ARGS__), fprintf(file, "\n"))
#define put(file, fmt, ...) (fprintf(file, fmt, ##__VA_ARGS__))

// TODO : Maybe merge the properties into a counter data struct and have a name and num digits properties within it?

void write_file_counter(char const *counter_name, int num_digits)
{
	++num_digits; // Fucking hack to overcome the fact that numbers with leading 0s are interpreted as octal in C.
	FILE *file = fopen("./counter.h", "wb");
	
	putln(file, "#ifndef DRA_COUNTER_%s_H", counter_name);
	putln(file, "#define DRA_COUNTER_%s_H", counter_name);
	
	for(int i = 0; i < num_digits; ++i)
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_VALUE 0", counter_name, i);
	
	for(int i = 0; i < num_digits; ++i)
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_UPDATE 0", counter_name, i);
	
	putln(file, "#ifndef DRA_COUNTER_CAT_DEFINED");
	putln(file, "#define DRA_COUNTER_CAT_DEFINED");
	putln(file, "#define DRA_COUNTER_CAT_INTERNAL(x0, x1) x0##x1");
	putln(file, "#define DRA_COUNTER_CAT_1(x0) x0");
	putln(file, "#define DRA_COUNTER_CAT_2(x0, x1) DRA_COUNTER_CAT_INTERNAL(x0, x1)");
	for(int i = 3; i <= num_digits; ++i)
	{
		put(file, "#define DRA_COUNTER_CAT_%d(x0", i);
		for(int j = 1; j < i; ++j)
		{
			put(file, ", x%d", j);
		}
		put(file, ") DRA_COUNTER_CAT_2(x0, DRA_COUNTER_CAT_%d(x1", i - 1, i - 1);
		
		for(int j = 2; j < i; ++j)
		{
			put(file, ", x%d", j);
		}
		
		putln(file, "))");
	}
	putln(file, "#endif");
	
	put(file, "#define %s (DRA_COUNTER_CAT_%d(1, DRA_COUNTER_%s_DIGIT_%d_VALUE", counter_name, num_digits, counter_name, num_digits - 1);
	for(int i = num_digits - 3; i >= 0; --i)
		put(file, ", DRA_COUNTER_%s_DIGIT_%d_VALUE", counter_name, i);
	put(file, ") ");
	// This is where the hack continues.
	put(file, "- DRA_COUNTER_CAT_%d(1", num_digits);
	for(int i = 1; i < num_digits; ++i)
		put(file, ", 0");
	putln(file, "))");
	
	putln(file, "#endif");
	
	fclose(file);
}

void write_file_update(char const *counter_name, int num_digits)
{
	FILE *file = fopen("./update.h", "wb");
	
	putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_UPDATE", counter_name, 0);
	putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_UPDATE 1", counter_name, 0);
	
	for(int i = 0; i < num_digits; ++i)
	{
		putln(file, "#if DRA_COUNTER_%s_DIGIT_%d_UPDATE", counter_name, i);
		putln(file, "#if DRA_COUNTER_%s_DIGIT_%d_VALUE == %d", counter_name, i, 0);
		putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_VALUE", counter_name, i);
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_VALUE %d", counter_name, i, 1);
		for(int j = 1; j < 9; ++j)
		{
			putln(file, "#elif DRA_COUNTER_%s_DIGIT_%d_VALUE == %d", counter_name, i, j);
			putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_VALUE", counter_name, i);
			putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_VALUE %d", counter_name, i, j + 1);
		}
		putln(file, "#elif DRA_COUNTER_%s_DIGIT_%d_VALUE == %d", counter_name, i, 9);
		putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_VALUE", counter_name, i);
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_VALUE %d", counter_name, i, 0);
		int target = (i + 1) % num_digits;
		putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_UPDATE", counter_name, target);
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_UPDATE 1", counter_name, target);
		putln(file, "#endif");
		putln(file, "#endif");
	}
	
	for(int i = 0; i < num_digits; ++i)
	{
		putln(file, "#undef DRA_COUNTER_%s_DIGIT_%d_UPDATE", counter_name, i);
		putln(file, "#define DRA_COUNTER_%s_DIGIT_%d_UPDATE 0", counter_name, i);
	}
	
	fclose(file);
}

int main()
{
	char const *counter_name = "MY_COUNTER";
	int num_digits = 4;
	write_file_counter(counter_name, num_digits);
	write_file_update(counter_name, num_digits);
	return 0;
}
