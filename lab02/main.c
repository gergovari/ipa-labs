#define _USE_MATH_DEFINES					//Könyvtári Matematikai konstansok definicióinak használata <math.h> elött
#define PI 3.14159

#include <stdio.h>	
#include <math.h>							//Matematikai készlet - alapműveletek kibővítése
#include <locale.h>

#define DUPLA(x) x*2						//Függvényszerű

int egesz;									//main() függvény előtti globális változók									
double tort = PI;							//kezdeti érték nélkül is használható
const unsigned int konstans = 3;			//const előtag: nem lehet módosítani

int main(void){

	setlocale(LC_ALL, "");					//op. rsz. által konf. területi beállítások

	printf("-----------------------------------------------------------------------------------------------\n");
	printf("egész értéke: %i\n", egesz);	//Automatikusan kinullázza a fordító

	int i = 1;

	printf("külső i értéke: %i\n", i);

//Belső blokkok - blokkon belüli változók, blokk végén megszűnnek létezni.
	{
		int i = 5;
		int z = 10;							// z változó a hatókörön kívül nem lesz használható
		printf("belső i értéke: %i és z = %i\n", i, z);
	}
											//itt már nincs z változó, és i is a külsõ változó lesz
	printf("külső i érteke megint: %i\n\n", i);

	// bal érték, jobb érték fogalma
	tort = (double)1 / 2;	//vagy  1 / 2.0 - Lásd: EA1/első labor - kerülendő, olvasáshatóságot rontja...


// matematikai műveletek <math.h>
// sin/cos/tan/asin/atan/stb... - szinusz/koszinusz/... rendes függvények radiánban, inverzek [0;1] intervallumon...
// pow - hatványozás pow(alap, kitevõ) - n. gyök is ezzel számítható
// sqrt - gyökvonás - nincs külön n. gyök, de megírható függvényként - lásd következő laborok...
// exp - e^x
// log - természetes alapú logaritmus (ln)
// log10 - 10-es alapú logaritmus
// abs(), fabs() - lebegőpontosokhoz

	printf("-----------------------------------------------------------------------------------------------\n");
	double szamolas = pow(sin(M_PI / 3), (double)2 / 3);
	printf("számolás 1: %.10lf\n", szamolas);	

	printf("számolás 2: %.10lf\n\n", pow((sin(PI / 3)), (2 / 3.0)));

	double szam_tort;
	printf("Adjon meg egy tört számot: ");							//Vesszővel kell ha magyar a rendszered, különben eltörik a program
	scanf_s("%lf", &szam_tort);			
	printf("A megadott szám: %lf\n", szam_tort);

	int ora, perc;
	printf("Kérem adja meg a pontos időt óra:perc alakban: ");		//Több elem beolvasása pl.
	
	scanf_s("%i:%i", &ora, &perc);									//Ha nem megfelelő alakban adjuk meg
	printf("A pontos idő: %i:%i\n\n", ora, perc);					//eltörHET a program. - breakpointtal érdemes tesztelni
																	//Formázott input - később
																	
//Változók felcserélése
	int a = 10;
	int b = 20;

	//1. Példa: segédváltozóval (mindig működik)
	int c = a;
	a = b;
	b = a;

	//2. Példa: csere segédváltozó nélkül (számoknál és elromolhat pl.: túlcsordulás)
	a = a + b;
	b = a - b;
	a = a - b;

	//3. Példa 'érdekesség': csere segédváltozó nélkül (egész számoknál)
	a ^= b;		// a = a ^ b;	^ bitenkénti kizáró vagy (XOR művelet)   
	b ^= a;
	a ^= b;



//Bitműveletek - Jövőben lesz érdekes - Mikrovezérlők, áramkörök stb. pl. led villogtatása
//1 byte = 8 bit --> bináris = decimális - 00000000 = 0, 00000001 = 1, 00000010 = 2, 00000011 = 3, ...
//4 bytenál pl. 4 = 00000000 00000000 00000000 00000100 
//<< >> - bitenkénti eltolás  

	printf("-----------------------------------------------------------------------------------------------\n");

	int kettes = 2;
	printf("%i\n", kettes); //2

	kettes = kettes << 1;
	printf("%i\n", kettes);	//4

	kettes = kettes << 3;
	printf("%i\n\n", kettes);	//Mennyi lesz?

// & - logikai és
	int négyes = 4;
	int nyolcas = 8;
	printf("%i\n", (négyes & nyolcas));

	int ötös = 5;
	printf("%i\n\n", (négyes & ötös));

// | -  vagy
	printf("%i\n", (négyes | nyolcas));
	printf("%i\n\n", (négyes | ötös));

//  ^ - kizáró vagy (ekvivalencia)
	printf("%i\n", (négyes ^ négyes));
	printf("%i\n", (nyolcas ^ négyes));
	printf("%i\n\n", (négyes ^ ötös));

//  ~ - Negálás
	printf("%i\n", (~ négyes));		//Kettes komplementes / Kétkomplementes ábrázolás...
	printf("%i\n", (~ nyolcas));	//unsigned intekkel mi újság?
	printf("%i\n\n", (~ ötös));

	unsigned int négyeske = 4;
	unsigned int nyolcaska = 8;

	printf("%i\n", (~négyeske));	//printf()...
	printf("%i\n\n", (~nyolcaska));

	printf("%u\n", (~négyes));		//Így is értelmezhetjük... 
	printf("%u\n", (~nyolcas));
	printf("%u\n\n", (~ötös));

	printf("%u\n", (~négyeske));	//sima és unsigned valójában ugyanannyitt foglal...
	printf("%u\n\n", (~nyolcaska));


printf("-----------------------------------------------------------------------------------------------\n");

//Elágazások
//
//if, if... else, else if...

	int p1, p2, 
		pv,
		osszpont, jegy;



	printf("Első dolgozat pont (0-20): \n");											scanf_s("%i", &p1);

		if (p1 < 8) {
			printf("Elsőre nem sikerült, semmi gond, első pótló pont (0-20): \n");		scanf_s("%i", &p1);
		}
		else if (p1 > 20) { //akkor fut le ha előtte lévő if hamis volt.
			printf("Bekamuztad...\n");
		}

	printf("Második dolgozat pont (0-30): \n");		
	scanf_s("%i", &p2);

		if (p2 < 12) {
			printf("Elsőre nem sikerült a második, semmi gond, pótló pont (0-30): \n");		
			scanf_s("%i", &p2);
		}
		if (p2 > 30) { //Ha nem teszünk else-t elé, akkor ... "plusz munka"
			printf("Egy élő legenda vagy...\n");
		}

		if (p1 < 8 || p2 < 12) {	//Logikai vagy
			printf("Pótpótlásra szorulsz. \n");
			
			if (p1 < 8) {
				printf("Első pótpót (0-20): \n");			scanf_s("%i", &p1);
			}
			if (p2 < 12) {
				printf("Második pótpót (0-20): \n");		scanf_s("%i", &p2);
			}
		}



	if (p1 >= 8 && p2 >= 12) {	//Logikai és

		printf("Aláírva.\n");
		printf("Vizsga pontszám (0-50): "); scanf_s("%i", &pv);

		if (pv >= 20) {
			osszpont = p1 + p2 + pv;

			if (osszpont >= 40 && osszpont < 55) jegy = 2;
			if (osszpont >= 55 && osszpont < 70) jegy = 3;
			if (osszpont >= 70 && osszpont < 85) jegy = 4;
			if (osszpont >= 85) jegy = 5;
		}
		else jegy = 1;

		printf("A jegyed: %i\n", jegy);
	}
	else {
		printf("Aláíras megtagadva.\n");
		jegy = 0;
	}

	switch (jegy) {
	//case 5: printf("Jeles");			//case-ek belépési pontok break;-ek nélkül lefut az első utáni összes.
	//case 4: printf("Jó");
	//case 3: printf("Közepes");
	//case 2: printf("Elégséges");
	//case 1: printf("Elégtelen");
	//default: printf("Aláírás megtagadva");

	case 5:		printf("Jeles");				break;
	case 4:		printf("Jó");					break;
	case 3:		printf("Közepes");				break;
	case 2:		printf("Elégséges");			break;
	case 1:		printf("Elégtelen");			break;
	default:	printf("Aláírás megtagadva");	break;
	}

	return 0;
}

//Gyakorló feladatok:
//Kérj be 3 doublet
//(1)-----------------------------------------------------------------------------------------------------------------------------
//	a) Csináld meg hozzájuk a másodfokú megoldóképletet ha azok ax^2+bx+c együtthatók.
//	b) a komplex esetet is valósítsd meg, a különböző nevezetes eseteket if-ekkel írasd ki - valós gyökök, komplex gyökök, ...
//	c) írasd ki a polinomot gyöktényezős alakban
// 
//(2)-----------------------------------------------------------------------------------------------------------------------------
//	kérd be az alábbi karakterek közül az egyiket: A, H, G/M, N, K								(\n-ek előző bemenetek végéről!?)
//	a beírt betű alapján írasd ki a számok adott karakter szerinti közepét: 
//	A - Aritmetikai, H - Harmonikus, G/M - Geometriai/Mértani, K - Köbös						  (Típuskonverziók, zárójelezés!)
//
//(3)-----------------------------------------------------------------------------------------------------------------------------
//	A bekért double-k abszolút értékét vedd.
//	Ezek legyenek egy háromszög oldalai.
//	Számítsd ki a háromszögek szögeit, területét, kerületét.
//	A szögek és oldalak alapján írasd ki, hogy milyen típusú háromszögről van szó:				  (Egymásba ágyazott elágazások,
//	(i)  szabályos, egyenlő szárú, általános,													   logikai egyszerűsítések?!)
//	(ii) derákszögű, tompaszögű, hegyesszügű