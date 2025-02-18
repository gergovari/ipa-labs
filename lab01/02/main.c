//2. Feladat
//   Kérj be egy tetszőleges számot, töltsd be a 256-al való maradékát egy char változóba.
//	 Írasd ki intként, charként, nézd meg mi történik ha nem ezekkel a type specifierekkel íratod ki

#include <stdio.h>

int main(void)
{
	int num;

	printf("Num: ");
	scanf_s("%u", &num);
	char c = num % 256; // Szerintem itt az ASCII-ra akarnak utalni
	
	// Direkt warning, hisz a feladat azt keri irassam ki massal is...
	printf("%u %c %f %lf", c, c, c, c);

	return 0;
}