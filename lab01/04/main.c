//4. Feladat
//	 Teszteld le breakpoint lerakásával, hogy mi történik, tetszőleges bemenet esetén
//	 a scanf() és a getchar() függvények használata során.
//	 helyezz el egymás után több scanf()-et, getchart()-t ehhez. - Puffer...

#include <stdio.h>
int main(void)
{
	double d;

	scanf_s("%lf", &d);
	char c = getchar();
	scanf_s("%lf", &d);
	c = getchar();
	scanf_s("%lf", &d);
	c = getchar();
	
	// Bent marad a pufferban a newline hisz a scanf_s nem olvassa ki
	// Neten van jopar workaround pick your fav

	return 0;
}