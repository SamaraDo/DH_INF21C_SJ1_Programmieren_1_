#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "lib_hausaufgabe02.h"

int main ()
{
    double x0, x1, x0h, f0, f1, df0, fh, f0h;
    double h = pow(10,-10);
    int max_iterationen = 1000;
    int count = 0;
    int wahl;

    printf("Bitte Startwert x0 eingeben.\n");
    scanf("%lf", &x0);
    printf("Wählen Sie 1, wenn die Funktion analytisch abgeleitet werden soll. Wählen Sie 2, wenn die Ableitung numerisch approximiert werden soll.\n ");
    scanf("%d", &wahl);

    if (wahl == 1)
    {
    for(int i = 0; i < max_iterationen; i++)
    {
     f0=f(x0);
     df0=df(x0);
     x1=x0-(f0/df0);
     f1=f(x1);
     x0=x1;
     count ++;
     printf("xn = %lf            |Itarationen = %d\n", x1, count);
      if (f1 < 0.0000000001)
       {
        printf("\nVorzeitig beendet. Die Nullstelle liegt an x = %lf. Anzahl der benötigten Iterationen: %d", x1, count);
        return 0;
       } 
    }
    
    printf("\nDie Nullstelle liegt an x = %lf. Anzahl der benötigten Iterationen: %d", x1, count);

    }
    else if (wahl == 2)
    {
    for(int i = 0; i < max_iterationen; i++)
    {
     f0=f(x0);
     x0h = x0 + h;
     f0h = f(x0h);
     df0= (f0h - f0) / h;
     x1=x0-(f0/df0);
     f1=f(x1);
     x0=x1;
     count ++;
     printf("xn = %lf            |Itarationen = %d\n", x1, count);
      if (f1 < 0.0000000001)
       {
        printf("\nVorzeitig beendet. Die Nullstelle liegt an x = %lf. Anzahl der benötigten Iterationen: %d", x1, count);
        return 0;
       } 
    }
    printf("\nDie Nullstelle liegt an x = %lf. Anzahl der benötigten Iterationen: %d", x1, count);

    }
    else 
    {
        printf("Error! Bitte 1 oder 2 eingeben. Wählen Sie 1 um das Programm neu zu starten. Wählen Sie eine andere Taste zum Beenden.\n---------------------------------------------\n");
        fflush(stdin);
        main();    
    }

        return 0; 

} 



