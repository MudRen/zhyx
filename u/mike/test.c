int test()
{
    int *a;

    a = allocate(17);
    a[0] = 0;
    a[1] = 1;

    for (int i = 2; i <= 16; i++)
        a[i] = a[i - 1] + a[i - 2];

    return a[16];
}

