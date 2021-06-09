typedef struct s{
    int num;
    char * name;
    struct s * next;
} S;

int sum(int a, int b)
{
    return a + b;
}

int sum_arr(int a[], int b)
{
    return a[0] + b;
}

int main(char * argv){

    int var;
    int * p;
    int arr[10];
    int c, d;
    
    arr = 10;
    var = 20;
    sum(3.5, 'b');
    sum_arr(3.5, 'a');
    p = -arr;
    sum(1,2) = 10;
    argv = "120";
    c++ = d + 1;
    * p = 123;
    -p = 12435;
    p = &sum_arr(arr, 1.1);
    p = ++sum(3,4);
    sum(1,2,3,4);
    sum(1);
    return 0;
}