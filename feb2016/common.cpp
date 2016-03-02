#include "common.h"

double clamp(double x, double a, double b)
{
	if (x < a) return a;
	else if (x > b) return b;
	else return x;
}

int randint(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

double randdbl(double a, double b)
{
	return (b - a) * random() + a;
}

double random()
{
	return rand() / (1.0 * RAND_MAX);
}

int rand_value_dict(int *count, int n)
{
	int total = 0;
	for (int v = 0; v < n; ++v)
		total += count[v];
	if (total <= 0)
		return -1;
	
	int k = randint(1, total);
	int val = -1;
	total = 0;
	for (int v = 0; v < n; ++v)
	{
		if (total < k)
			val = v;
		total += count[v];
	}
	
	return val;
}

int avg_value(int *vals, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += vals[i];
	return sum / n;
}

int avg_theta(int *theta, int n)
{
	int top_avg = 0, top_n = 0;
	int bot_avg = 0, bot_n = 0;

	for (int i = 0; i < n; ++i)
	{
		if (theta[i] < 180)
		{
			top_n++;
			top_avg += theta[i];
		}
		else
		{
			bot_n++;
			bot_avg += theta[i];
		}
	}
	
	if (top_n > 0)
		top_avg /= top_n;
	if (bot_n > 0)
		bot_avg /= bot_n;

	int diff = 0;
	if (bot_avg - top_avg >= 180)
	{
		diff = 360 - bot_avg;
		bot_avg = 0;
		top_avg = (top_avg + diff) % 360;
	}

	int avg = (bot_avg * bot_n + top_avg * top_n);
	avg /= top_n + bot_n;
	avg = (avg + 360 - diff) % 360;
	
	return avg;
}

double geometric(double p)
{
	return log(1 - random()) / log(1 - p);
}
