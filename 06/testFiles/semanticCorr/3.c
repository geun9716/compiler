int main()
{
    int a = 1;
    int b = 3;
    while(a > 10){
        if(a >= 7){
            break;
        } else if (a == 2){
            a = a + 2;
        } else {
            a++;
        }
    }

    switch(a){
        case 1 : 
            b--;
            break;
        case 10 : 
            b = 10;
            break;
        default :
            b = 1;
            break;
    }

    if (b <= 1 && a < b){
        a++;
    } else if (a > b || b == 10){
        b--;
    } else {
        ;
    }

    do{
        int c = a + b;
        a++;
    } while (b > 10);

    for(;b > 1; b--){
        a++;
    }
}
