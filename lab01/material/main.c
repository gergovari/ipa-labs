//VS téma: Tools --> Theme
//Jobb oldalt: Solution Explorer: View --> Solution Explorer / Ctrl+Alt+L (akár be is zárhatjuk) - Érdemes a bezárás melletti auto hideot a megfelelőre állítani
//Alul: Output/Error list:  View --> Output/Error list...
//		Ctrl+görgővel méretezhető a szöveg - általam ajánlott/használt: 100%
//
//Kommentek: //-ek után vagy /* között */ - A fordító nem veszi figyelembe - magunknak magyarázat/jelölés
/* példa köztes kommentre */
//
//Fejállományok helye: A 'c' nyelv saját könyvtárait <> közé,
//					   Az általunk írt "header"-eket "" közé.

//#include "sajat.h" 
#include <stdio.h>



//Definíciók - ha bizonyos dolgokra egyedi névvel szertnénk hivatkozni.
//Nem kell pontosvesszővel zárni ezen sorokat.
// 
//HASZNOS HOTKEYEK: Sor másolása kijelölés nélkül: Ctrl+D,
//				    Sor törlése kijelölés nélkül: RSHIFT+Delete
//				    Sor/Kijelölt szöveg cseréje egyel lejebbi/feljebbi sorba: Alt+le/fel nyíl
//					
#define PI 3.14159
#define jegy 5
#define pontosvesszo ;

//Saját névvel helyettesítés
typedef unsigned int uint;

//A programunk kezdete - main függvény hívódik meg. 
// () --> argumentum. void = típustalanság
//Program végén: return 0 = Visszatérítési érték - Jelentése: a program hibamentesen lefutott. 
int main(void){

//HASZNOS HOTKEYEK Formázáshoz/Egymáshoz igazításhoz:
//Több mint 1 sor kijelölése+Tab --> Jobbra tolás
//SHIFT+Tab <-- Balra tolás
	int egesz, Egesz;/*vesszővel elválasztva több deklaracio*/unsigned int pozitiv_egesz1;
	long int	  haszontalan_egesz;						  uint		   pozitiv_egesz2;
	long long int nagyobb_egesz;
	short int	  kisebb_egesz;


	float		lebegopontos;					//Elnevezés: a tizedespont helye nem fix,
	double		lebegopontosabb;				//hanem az értéket egy mantissza és egy exponens segítségével ábrázoljuk
	long double meglebegopontosabb;				//szám = mantissza	* alap^exponens - az exponens határozza meg hol lebeg a tizedespont 
												//A mantisszán belül - Nagyon kicsi és nagyon nagy számokat is ábrázolhatunk, pontosságban viszont kompromisszum

	char nagykarakter = 'A';
	char kiskarakter = 'a';

//Kiíratás - C nyelv alapfüggvénye- printf()
//"" között szöveg '%' szimbólumok segítségével különböző típusok kiíratása - bitminták értelmezésére szolgál - 0 bitmintája általában típusfüggetlen.
// ','-kkel argumentumba változók sorban amelyeket a ""-ben elhelyezett '%'-okkal íratunk ki.
// \n = újsor, \t tabulátor, \' a macskaköröm karakter kiiratasa   
	printf("HELLO L07!\n\n");


	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("TAROLASI MERETEK:\n");	//byteban
	printf("\
			int merete: %i\t\
			unsigned int es \"uint\" merete: %u, %u\n\
			long int merete: %i\t\
		long long int merete: %i\n\
			short int erteke: %i\t\
		float erteke: %i\n\
			double erteke: %i\t\
		long double erteke: %i\n\
			Char erteke: %i\n\n",
			sizeof(int),
			sizeof(unsigned int), sizeof(uint),
			sizeof(long int),
			sizeof(long long int),
			sizeof(short int),
			sizeof(float),
			sizeof(double),
			sizeof(long double),
			sizeof(char));


	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("DEFINE HASZNALAT - jegy: %i\n\n", jegy) pontosvesszo


	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("KARAKTEREK KIIRATASA: %c\t%c\n",										  nagykarakter, kiskarakter);	//Külön-külön printf()
	printf("A es a karakterek erteke: %i\t%i\n",								   	  nagykarakter, kiskarakter);	//ha a sor elejétől akarjuk kiírni
	printf("Nagybetuve valtoztatas - kiskarakter es 32-t kivonva belole: %c\t%c\n", kiskarakter, (kiskarakter-32));	//szövegünket. Előző blokknál
																													//egy printf()-en belül \ jelekkel
																													//elválasztva 1-1 sorban
	egesz = nagykarakter;																	// char -> int automatikus tipuskonverzio.
	printf("integer izomorfizmusa: %i\t%c %c\n\n", (egesz+1), egesz, (egesz+1));			//Nem változtatja meg az értékét a paraméterlistán
																							// belüli művelet.

	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("SZAMRENDSZERVALTAS:\n\
					Az egesz valtozo erteke decimalisan: %d\n\
					oktalisan: %o\n\
					hexadecimalisan: 0x%x\n\n", 
					egesz, egesz, egesz);


	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("HELYIERTEKEK:\n");

	lebegopontos = PI; 
	lebegopontosabb = (double)339 / 108;	//"Rákényszerítjük", hogy double legyen + olvashatóság

	printf("\t pi erteke: %f\t \"pontosabban\" %lf\n",			 lebegopontos, lebegopontosabb);	//%f - float, %lf - long float
	printf("\t Tobb helyiertek (defineolt):\" %8.9lf\n",		 lebegopontos);						//Hogy lehetséges? 
	printf("\t Tobb helyiertek (kozelito tort):\" %8.9lf\n",	 lebegopontosabb);					//Erre számítottunk.
	printf("\t Normalalak (kozelito tort):\" %8elf\n\n",		 lebegopontosabb);

																				  
//Konverziók
//Debug mód - Breakpoint - Autos, Locals (Ctrl+Alt+V ... A/L)
//Step into(F11)/Step over(F10) = következő breakpointra vonatkozik
	egesz = lebegopontos;				//Autosba látjuk - implicit típuskonverezió
	Egesz = (int)lebegopontosabb;		//Explicit konverzió

	lebegopontosabb = (float)(1 / 7);
	lebegopontos = lebegopontosabb;	    //Localsba látjuk


printf("-----------------------------------------------------------------------------------------------------\n");
printf("ALAPVETO MUVELETEK ELVEGZESE, OPERATOROK HASZNALATA:\n");
	egesz = 0;
	egesz = Egesz + 10;		printf("\t egesz erteke: %i\n", egesz);
	egesz += 10;			printf("\t egesz erteke: %i\n", egesz);
	egesz *= 10;			printf("\t egesz erteke: %i\n", egesz);
	egesz /= 2;				printf("\t egesz erteke: %i\n\n", egesz);


	egesz = egesz%10;		printf("\t egesz erteke: %i\n\n", egesz);		//Maradékos osztás!


	egesz = ((egesz * 1) + 0)/1;	printf("\t egesz erteke: %i\n", egesz); //Precedenciaszabályok...
	egesz = ((egesz * 8) + 20)
					/ 
					4;				printf("\t egesz erteke: %i\n\n", egesz);
									

	egesz *= 10 + 20;			    printf("\t egesz erteke: %i\n", egesz); //Mi fog történni?
	(egesz *= 10) + 20;			    printf("\t egesz erteke: %i\n", egesz);
	egesz = (egesz *= 10) + 20;	    printf("\t egesz erteke: %i\n", egesz); //kijelölt szöveg + jobb/bal oldali zárójel --> gyorszárójelezés

	
	egesz++;						printf("\t egesz erteke: %i\n", egesz);	//Egy-egy műveletet parancson belül is akár 
									printf("\t egesz erteke: %i\n", egesz+=9);
									printf("\t egesz erteke: %i\n", ++egesz);
									printf("\t egesz erteke: %i\n", egesz++);
									printf("\t egesz erteke: %i\n", ++egesz);

printf("-----------------------------------------------------------------------------------------------------\n");
printf("ADATBEKERES:\n");

//Egyszerű Input - Ha nem megfelelő formátum könnyen "eltörik a program"
//HASZNOS SHORTCUTOK: Kikommentelés/Uncommentelés:
//Comment:	 Ctrl+K+C - Ctrl végig nyomva utána egyesével K és C karakterek leütése :-)
//Uncomment: Ctrl+K+U
	printf("Fejes csapszeg atmeroje: [mm] d= ");	//Megkérdezzuk
	double d;										//Deklaráljuk
													//Breakpoint - Memóriaszemét
	//scanf("%lf", &d);								//Bekérjük. - változó cimére (&) - Sima scanf "veszélyes" memóriatúlcsordulás - nem ellenőrzi automatikusan,
	scanf_s("%lf", &d);//<locale.h> és setelocale(LC_ALL, "") nélkül csak .-al elválasztott törtet olvas be jól						hogy a beolvasott adatok beleférnek-e
													//Biztonságos. nem csordul túl a buffer.										megadott változóba vagy tömbbe,
	double kerulet = d * PI;						//Hibás működés, biztonsági rések											  //a ezért ha a felhasználó nagyobb	
	printf("A fejes csapszeg  kerulete: %.5lf mm\n", kerulet);																	  //adatmennyiséget ad meg, mint amire
																																  //a változó számít, az túlcsordulást okozhat.
	//Bemeneti puffer ürítése - a \n-et olvasná be az előző scanf_s miatt... űríteni kell - while ciklus: következő laborokon bővebben...
	int clear;
	while ((clear = getchar()) != '\n');

	printf("Adjon meg egy karaktert: ");
	char karakter = getchar();
	int karakterke = karakter;
	printf("A megadott karakter %c volt. szamkent reprezentalva: %i", karakter, karakterke);

	return 0;
}



//Gyakorló feladatok:
//1. Feladat
//Kérj egy unsigned intet (db ~ [1]), és két unsigned doublet (h ~ [m]) és (R ~ [m]).
//a) Számítsd ki az aritmetikai, harmonikus közepüket.
//	 Írasd ki őket 5 tizedesjegy pontossággal.
// 
//b) A sugár, és a magasság alapján számítsd ki egy henger felületét, 
//	 Írasd ki konzolra a következőket:
//	 Mennyi felülete lesz összesen a hengereknek? - 5 tizedesjegy pontossággal
//	 Az összfelületekből számítsd ki mennyi festéket kell venni,
//	 és mennyi pénzre van szükséged,
//	 ha egy liter festék 10 m^2-re elegendő,
//	 és csak ez a kiszerelés kapható 550Ft-ért. -> Irányított megvalósítás: 
//	 10-el való maradékos osztásal, felfele kerekítés double változó int-be töltésével és inkrementálásával! 
//
//c) Csináld meg teljesen printf() függvényen belüli műveletekkel ha azok rövidek.
//	 A hosszabb műveleteknél használj gyorszárójelezést.
//
//2. Feladat
//   Kérj be egy tetszőleges számot, töltsd be a 256-al való maradékát egy char változóba.
//	 Írasd ki intként, charként, nézd meg mi történik ha nem ezekkel a type specifierekkel íratod ki
// 
//3. Feladat
//   Add hozzá a <locale.h> könyvtárat, hívd meg a setlocale(LC_ALL, ""); parancsot, a korábbi programokban használj ékezetes betűket.
//	 Teszteld le egy double változón a scanf_s függvényt. (. helyett , használható lesz (elméletileg) - windows nyelvi beállítás függő...)
//
//4. Feladat
//	 Teszteld le breakpoint lerakásával, hogy mi történik, tetszőleges bemenet esetén
//	 a scanf() és a getchar() függvények használata során.
//	 helyezz el egymás után több scanf()-et, getchart()-t ehhez. - Puffer...

