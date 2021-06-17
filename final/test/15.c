int a[9];

void sort(int l, int r)
{
    int i, j, x, w;
    int k;

    i = 1;
    j = r;

    x = a[(l + r) / 2];
    do
    {
        while (a[i] < x)
            i++;

        while (x < a[j])
            j--;

        if (i <= j)
        {
            w = a[i];
            a[i] = a[j];
            a[j] = w;
            i++;
            j--;
        }

    } while (i <= j);

    if (i < j)
        sort(i, j);

    if (i < r)
        sort(i, r);
}

void main()
{
    int k;
    a[0] = 0, a[1] = 1;
    a[2] = 3;
    a[4] = 7;
    for (k = 0; k < 10; k++)
        printf("%d ", a[k]);
    printf("\n");

    sort(0, 9);

    for (k = 0; k < 10; k++)
        printf("%d ", a[k]);
    printf("\n");
}