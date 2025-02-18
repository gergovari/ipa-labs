//3. Feladat
//   Add hozzá a <locale.h> könyvtárat, hívd meg a setlocale(LC_ALL, ""); parancsot, a korábbi programokban használj ékezetes betűket.
//	 Teszteld le egy double változón a scanf_s függvényt. (. helyett , használható lesz (elméletileg) - windows nyelvi beállítás függő...)

#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");
	
	double d;

	printf("lolÉÉÉÁÁÁÁ: "); 
	scanf_s("%lf", &d);
	
	printf("na?: %lf", d);

	return 0;
}