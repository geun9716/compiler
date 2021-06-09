typedef struct s1 {char *name; int value;} STR;
STR chang[5];

int * print(int a)
{
    int i[100];
    for(i[0] = 0; i[0] < a; i[0]++)
        printf("Hello");
    return *i;
}

int main(){
    int a, b, c, d;
    float e, f, g, h;
    int * p;

    (a+b) = 203;
    (e-f) = 10.1;
    if (e >= a)
        break;

    while(p <= print){
        a = 1;
        a--;
        printf("%d", a);
        continue;
    }
    
    switch(a){
        h = e + f--;
        case 0 : 
            a++;
            break;
        default : 
            printf("Error");
            break;
    }
    
    // case 10 :
    //     b++;
    //     break;
    // dafault :
    //     continue;

}