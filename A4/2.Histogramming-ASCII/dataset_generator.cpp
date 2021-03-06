// 16CO145 Sumukha PK
// 16CO234 Prajval M

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

static char *base_dir;
const size_t NUM_BINS = 128;

int *compute(int *bins, const char *input, int num)
{
	for (int i = 0; i < num; ++i)
		++bins[(int)input[i]];

	return bins;
}

static char *generate_data(size_t n)
{
	char *data = (char *)malloc(n + 1);
	for (unsigned int i = 0; i < n; i++)
	{
		data[i] =  (rand() % (128 - 32)) + 32; // random printable character
	}
	data[n] = 0; // null-terminated
	return data;
}

static void write_data_str(char *file_name, const char *data, int num)
{
	FILE *handle = fopen(file_name, "w");
	for (int ii = 0; ii < num; ii++)
	{
		fprintf(handle, "%c", *data++);
	}
	fflush(handle);
	fclose(handle);
}

void write_data_int(char *file_name, int *data, int num)
{
	std::ofstream handle(file_name);
	handle << num << std::endl;
	for(int ii = 0; ii <NUM_BINS; ii++)
	{
		handle << data[ii] << std::endl;
	}
}

static void create_dataset_fixed(int datasetNum, const char *str)
{
	const char *dir_name = base_dir;

	char *input_file_name = (char *)"input.raw";
	char *output_file_name = (char *)"output.raw";

	int *output_data = (int *)calloc(NUM_BINS, sizeof(int));

	for (int i = 0; i < NUM_BINS; i++)
		output_data[i] = 0;

	output_data = compute(output_data, str, strlen(str));

	write_data_str(input_file_name, str, strlen(str));
	write_data_int(output_file_name, output_data, NUM_BINS);

	free(output_data);
	free(input_file_name);
	free(output_file_name);
}

static void create_dataset_random(int datasetNum, size_t input_length)
{

	const char *dir_name = base_dir;

	char *input_file_name = (char *)"input.raw";
	char *output_file_name = (char *)"output.raw";

	char *str = generate_data(input_length);
	int *output_data = (int *)calloc(NUM_BINS, sizeof(int));

	for(int i=0; i < NUM_BINS; i++)
		output_data[i] = 0;

	output_data = compute(output_data, str, input_length);

	write_data_str(input_file_name, str, input_length);
	write_data_int(output_file_name, output_data, NUM_BINS);

	free(str);
	free(output_data);
	free(input_file_name);
	free(output_file_name);
}

int main()
{
	base_dir = (char *)"";

	// create_dataset_fixed(0, "the quick brown fox jumps over the lazy dog");
	// create_dataset_fixed(1, "gpu teaching kit - accelerated computing");
	// create_dataset_random(2, 16);
	create_dataset_random(3, 513);
	// create_dataset_random(4, 511);
	// create_dataset_random(5, 1);
	return 0;
}
