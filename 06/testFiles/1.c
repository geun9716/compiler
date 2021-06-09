void sum(int a, int b){
    return a+b;
}

int func(int a[]){
    return a[0];
}

struct s{
    int a;
    float b;
    char c;
    void d;
    char e()[100];
    void sum();
};

int main()
{
    int num1;
    int num2;
    int arr[0];

    num1 = 1067;
    num2 = 1235346;

    sum(arr, func());

    printf("%d\n", num1);
    printf("%d\n", num2);
    printf("%d\n", num1 + num2);

    return 0;
}