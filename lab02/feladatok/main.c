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

#include <stdio.h>
#include <math.h>

struct Quadratic
{
	double a, b, c;
};

static void scan_equation(struct Quadratic* equation)
{
	printf("ax^2 + bx + c = 0; x = ?\n");

	printf("a = ");
	scanf_s("%lf", &equation->a);

	printf("b = ");
	scanf_s("%lf", &equation->b);

	printf("c = ");
	scanf_s("%lf", &equation->c);
}

static void print_equation(struct Quadratic equation)
{
	printf("%.3lf * x^2 + %.3lf * x + %.3lf\n", equation.a, equation.b, equation.c);
}

struct ResultPart
{
	double real;
	double comp;
};

struct Result
{
	struct ResultPart first;
	struct ResultPart second;
};

enum ResultType {SINGLE, REAL, COMPLEX};

static void print_result(const struct Result result, const enum ResultType type)
{
	switch (type) {
	case SINGLE:
		printf("x = %.3lf\n", 
			result.first.real);
		break;
	case REAL:
		printf("x_1 = %.3lf, x_2 = %.3lf\n", 
			result.first.real, result.second.real);
		break;
	case COMPLEX:
		printf("x_1 = (%.3lf) + (%.3lf)i, x_2 = (%.3lf) + (%.3lf)i\n", 
			result.first.real, result.first.comp,
			result.second.real, result.second.comp);
		break;
	}
}


static int solve_equation(const struct Quadratic equation, struct Result* result)
{
	double a = equation.a;
	double b = equation.b;
	double c = equation.c;
	double d = pow(b, 2) - 4 * a * c;

	if (d == 0) {
		result->first.real = (-b + sqrt(d)) / 2 * a;

		return 0;
	} else if (d > 0) {
		double a_twice = 2 * a;
		double d_sqrt = sqrt(d);

		result->first.real = (-b + d_sqrt) / a_twice;
		result->second.real = (-b - d_sqrt) / a_twice;

		return 1;
	} else {
		double a_twice = 2 * a;

		result->first.real = (-b) / a_twice;
		result->second.real = result->first.real;
		
		result->first.comp = sqrt(fabs(d)) / a_twice;
		result->second.comp = -result->first.comp;

		return 2;
	}
}

int main(void)
{
	struct Quadratic equation;

	scan_equation(&equation);
	print_equation(equation);

	struct Result result;

	int type = solve_equation(equation, &result);
	print_result(result, type);

	return 0;
}