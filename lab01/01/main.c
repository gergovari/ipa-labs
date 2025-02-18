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

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define LEN 3

double arithmetic_avg(double* nums, unsigned int len)
{
	double sum = 0;
	for (unsigned int i = 0; i < len; i++)
	{
		sum += nums[i];
	}
	return sum / len;
}

double harmonic_avg(double* nums, unsigned int len)
{
	double divSum = 0;
	for (int i = 0; i < len; i++)
	{
		divSum += 1/nums[i];
	}
	return len / divSum;
}

static void fill_values(unsigned int *db, double *h, double *r)
{
	printf("DB [1]: ");
	scanf_s("%d", db);

	printf("h [m]: ");
	scanf_s("%lf", h);

	printf("r [m]: ");
	scanf_s("%lf", r);
}

static void print_avg(double *nums, unsigned int len)
{
	printf("aritmetikai: %.5lf\nharmonikus: %.5lf\n", 
		arithmetic_avg(nums, len), harmonic_avg(nums, len));
}

struct Cylinder
{
	double h;
	double r;
};

static double cylinder_surface(struct Cylinder cylinder)
{
	return 2 * M_PI * cylinder.h * cylinder.r;
}

int main(void)
{
	unsigned int db = 0;
	struct Cylinder cylinder;

	fill_values(&db, &cylinder.h, &cylinder.r);
	double nums[LEN] = {db, cylinder.h, cylinder.r};

	print_avg(nums, LEN);
	
#define SURFACE_FOR_LITER 10
#define PRICE_PER_LITER 550
	double surface_sum = db * cylinder_surface(cylinder);
	unsigned int liter_sum = (unsigned int)ceil(surface_sum / SURFACE_FOR_LITER);
	unsigned int price = liter_sum * PRICE_PER_LITER;

	printf("Surface sum: %.5lf [m^2]\nPaint needed: %u [l]\nPrice of paint: %u [HUF]\n", 
		surface_sum, liter_sum, price);
	
	/* c)-nek nem látom értelmét az én kódomnál,
	 * good luck have fun */

	return 0;
}