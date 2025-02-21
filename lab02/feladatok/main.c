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

static void flush_buffer()
{
	while (getchar() != '\n') {}
}

static void scan_equation(struct Quadratic* equation)
{
	printf("ax^2 + bx + c = 0; x = ?\n");

	printf("a = ");
	scanf_s("%lf", &equation->a);

	printf("b = ");
	scanf_s("%lf", &equation->b);

	printf("c = ");
	scanf_s("%lf", &equation->c);

	flush_buffer();
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

static void print_equation(struct Quadratic equation)
{
	printf("%.3lf * x^2 + %.3lf * x + %.3lf\n", equation.a, equation.b, equation.c);
}

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

/* Mertani is same as Geometric */
enum AverageType {
	Arithmetic = 65, Harmonic = 72, Geometric =	71, Cubic = 75,
	Mertani = 77
};

static void handle_equation(struct Quadratic *equation)
{
	scan_equation(equation);
	print_equation(*equation);

	struct Result result;

	int type = solve_equation(*equation, &result);
	print_result(result, type);
}

static enum AverageType get_type()
{
	printf("Average types: (A)rithmetic, (G)eometric/(M)ertani, (K)Cubic\n");
	printf("Your choice: ");
	return getchar();
}

static void arithmetic_average(
	double *nums, unsigned int len, double *result)
{
	for (unsigned int i = 0; i < len; i++)
	{
		*result += nums[i];
	}
	*result /= len;
}

static void harmonic_average(
	double* nums, unsigned int len, double* result)
{
	for (unsigned int i = 0; i < len; i++)
	{
		*result += 1 / nums[i];
	}
	*result = len / *result;
}

static void geometric_average(
	double* nums, unsigned int len, double* result)
{
	*result = nums[0];
	for (unsigned int i = 1; i < len; i++)
	{
		*result *= nums[i];
	}
	*result = pow(*result, 1./len);
}

static void cubic_average(
	double* nums, unsigned int len, double* result)
{
	for (unsigned int i = 0; i < len; i++)
	{
		*result += pow(nums[i], 3);
	}
	*result = pow(*result / len, 1./3);
}

static int average_nums(
	double *nums, 
	unsigned int len, 
	enum AverageType type,
	double *result)
{
	if (len == 0) { return -1; }

	switch (type) {
	case Arithmetic:
		arithmetic_average(nums, len, result);
		break;
	case Harmonic:
		harmonic_average(nums, len, result);
		break;
	case Geometric:
	case Mertani:
		geometric_average(nums, len, result);
		break;
	case Cubic:
		cubic_average(nums, len, result);
		break;
	default:
		return -1;
	}
	return 0;
}

static void handle_average(double *nums, unsigned int len)
{
	int error = -1;
	double result = 0;

	while (error != 0) {
		enum AverageType type = get_type();
		
		error = average_nums(nums, len, type, &result);
	}

	printf("Average with your chosen method: %lf\n", result);
}

int main(void)
{
	struct Quadratic equation;

	handle_equation(&equation);
	
#define LEN 3
	double nums[LEN] = { equation.a, equation.b, equation.c };

	handle_average(nums, LEN);

	return 0;
}