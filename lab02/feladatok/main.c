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

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdbool.h>
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
		double aTwice = 2 * a;
		double dSqrt = sqrt(d);

		result->first.real = (-b + dSqrt) / aTwice;
		result->second.real = (-b - dSqrt) / aTwice;

		return 1;
	} else {
		double aTwice = 2 * a;

		result->first.real = (-b) / aTwice;
		result->second.real = result->first.real;
		
		result->first.comp = sqrt(fabs(d)) / aTwice;
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

/* MERTANI is same as GEOMETRIC */
enum AverageType {
	ARITHMETIC = 65, HARMONIC = 72, GEOMETRIC =	71, CUBIC = 75,
	MERTANI = 77
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
	case ARITHMETIC:
		arithmetic_average(nums, len, result);
		break;
	case HARMONIC:
		harmonic_average(nums, len, result);
		break;
	case GEOMETRIC:
	case MERTANI:
		geometric_average(nums, len, result);
		break;
	case CUBIC:
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

	printf("Average with your chosen method: %.3lf\n", result);
}

struct Triangle {
	double a, b, c;
};

enum TriangleSidesType {EQUILATERAL, ISOSCELES, SCALENE};
enum TriangleAnglesType {RIGHT, OBTUSE, ACUTE};

static bool is_triangle_positive(const struct Triangle triangle)
{
	return triangle.a > 0 && triangle.b > 0 && triangle.c > 0;
}

static bool is_triangle_inequality(const struct Triangle triangle)
{
	double a = triangle.a;
	double b = triangle.b;
	double c = triangle.c;

	return a + b > c && a + c > b && b + c > a;
}

static bool is_triangle_valid(const struct Triangle triangle)
{
	return is_triangle_positive(triangle) && is_triangle_inequality(triangle);
}

static double _calculate_rad_angle(double a, double b, double c)
{
    return acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c));
}

static int triangle_angles(const struct Triangle triangle, double *angles)
{
	if (is_triangle_valid(triangle))
	{
		double a = triangle.a;
		double b = triangle.b;
		double c = triangle.c;
		double radAngles[3] = {
			_calculate_rad_angle(b, c, a),
			_calculate_rad_angle(c, b, a),
		};

		radAngles[2] = M_PI - (radAngles[0] + radAngles[1]);

		for (int i = 0; i < 3; i++)
		{
			angles[i] = radAngles[i] * (180 / M_PI);
		}
		return 0;
	}
	return -1;
}

static int triangle_perimeter(const struct Triangle triangle, double *perimeter)
{
	if (is_triangle_valid(triangle)) 
	{
		*perimeter = triangle.a + triangle.b + triangle.c;
		return 0;
	}
	return -1;
}

static int triangle_area(const struct Triangle triangle, double *area)
{
	if (is_triangle_valid(triangle)) 
	{
		double perimeter = 0;
		if (triangle_perimeter(triangle, &perimeter) == 0) {
			double s = perimeter / 2;

			*area = sqrt(s * (s - triangle.a) * (s - triangle.b) * (s - triangle.c));
			return 0;
		}
	}
	return -1;
}

#define EPSILON 1e-2

static bool is_double_equal(double a, double b)
{
	/* Don't leave commented code as it's ugly, 
	but if the epsilon value isn't good on your machine 
	feel free to debug with this.*/
	//printf("\n\n%.3lf == %.3lf => %lf (%d)\n\n", a, b, fabs(a - b), fabs(a - b) < EPSILON);
	return fabs(a - b) < EPSILON;
}

static int triangle_sides_type(const struct Triangle triangle, enum TriangleSidesType* type)
{
	if (is_triangle_valid(triangle))
	{
		double a = triangle.a;
		double b = triangle.b;
		double c = triangle.c;
		if (is_double_equal(a, b) && is_double_equal(b, c))
		{
			*type = EQUILATERAL;
		} else if (is_double_equal(a, b) || is_double_equal(a, c) || is_double_equal(b, c)) {
			*type = ISOSCELES;
		} else {
			*type = SCALENE;
		}
		return 0;
	}
	return -1;
}

static int triangle_angles_type(const struct Triangle triangle, enum TriangleAnglesType* type)
{
	if (is_triangle_valid(triangle))
	{
		double angles[3];
		
		int error = triangle_angles(triangle, angles);
		if (error == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (is_double_equal(angles[i], 90))
				{
					*type = RIGHT;
					return 0;
				}
				
				if (angles[i] > 90)
				{
					*type = OBTUSE;
					return 0;
				}
			}
			*type = ACUTE;
		} else {
			return -1;
		}

		return 0;
	}
	return -1;
}

static void print_triangle_sides_type(const enum TriangleSidesType type)
{
	switch (type) {
	case EQUILATERAL:
		printf("The triangle is equilateral.\n");
		break;
	case ISOSCELES:
		printf("The triangle is isosceles.\n");
		break;
	case SCALENE:
		printf("The triangle is scalene.\n");
		break;
	default:
		printf("The triangle's side type couldn't be determined.\n");
	}
}

static void print_triangle_angles_type(const enum TriangleAnglesType type)
{
	switch (type) {
	case RIGHT:
		printf("It's a right triangle.\n");
		break;
	case OBTUSE:
		printf("It's an obtuse triangle.\n");
		break;
	case ACUTE:
		printf("It's an acute triangle.\n");
		break;
	default:
		printf("The triangle's side type couldn't be determined.\n");
	}
}

static void handle_triangle(double *nums)
{
	struct Triangle triangle = {nums[0], nums[1], nums[2]};
	
	if (is_triangle_valid(triangle))
	{
		double perimeter;
		double area;
		double angles[3];
		enum TriangleSidesType side; 
		enum TriangleAnglesType angle; 

		int error = triangle_perimeter(triangle, &perimeter);

		if (error != 0)
		{
			printf("There was an unexpected error while calculating the triangle's perimeter!");
			return;
		}

		error = triangle_area(triangle, &area);
		if (error != 0)
		{
			printf("There was an unexpected error while calculating the triangle's area!");
			return;
		}

		error = triangle_angles(triangle, &angles);
		if (error != 0)
		{
			printf("There was an unexpected error while calculating the triangle's angles!");
			return;
		}

		error = triangle_sides_type(triangle, &side);
		if (error != 0)
		{
			printf("There was an unexpected error while deciding the side type of the triangle!");
			return;
		}

		error = triangle_angles_type(triangle, &angle);
		if (error != 0)
		{
			printf("There was an unexpected error while deciding the angle type of the triangle!");
			return;
		}

		printf("Triangle's perimeter: %.3lf\n", perimeter);
		printf("Triangle's area: %.3lf\n", area);
		printf("Triangle's angles: %.3lfdeg, %.3lfdeg, (%.3lfdeg)\n", 
			angles[0], angles[1], angles[2]);
		
		print_triangle_sides_type(side);
		print_triangle_angles_type(angle);

	} else {
		printf("The resulting triangle is invalid.\n");
	}
}

int main(void)
{
	struct Quadratic equation;

	handle_equation(&equation);
	printf("\n");

	double nums[3] = { equation.a, equation.b, equation.c };

	handle_average(nums, 3);
	printf("\n");
	
	handle_triangle(nums);
	printf("\n");

	return 0;
}