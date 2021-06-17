int main()
{
    int a;
    int b;
    float c;
    float d;
    int e;
    float result[5];
    a = 1;
    b = 2;
    c = 123.456;
    d = 12.345;
    e = 0;
    result[0] = a + c;
    result[1] = d + b;
    result[2] = c + d;
    result[0] = a - c;
    result[1] = d - b;
    result[2] = c - d;
    result[0] = a * c;
    result[1] = d * b;
    result[2] = c * d;
    result[0] = a / c;
    result[1] = d / b;
    result[2] = c / d;
    result[3] = a / e;
    result[0] = a % c;
    result[1] = d % b;
    result[2] = c % d;
    result[3] = a % e;
    return a;
}