typedef enum
{
	false,
	true
} BOOLEAN;

typedef struct node
{
	char *name;
	int value, level;
	struct node *link;
};

int i, j = 10;

int fun(int a)
{
	// static int x = 0;
	auto struct
	{
		int c;
		float *f;
	} s;
	float i, j, k;

	return true;
}

int main()
{
	int a = 3;
	float b = 4;
	struct d
	{
		int a;
		int b;
	};
	int i, j;
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	if (fun(10))
	{
		printf("test1\n");
	}
	else
	{
		printf("B");
	}

	for (i = 0; i < 10; i++)
	{

		j = 0;
	}

	printf("%d %d\n", i, j);

	return 0;
}