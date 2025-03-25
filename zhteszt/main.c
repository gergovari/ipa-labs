#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned int uint;

struct Rectangle {
	uint a;
	uint b;
};

#define NUM_OF_RECTANGLE 10
#define MIN_SIZE 10
#define MAX_SIZE 50

void seed_rand()
{
	time_t seconds = 0;

	time(&seconds);
	srand((unsigned int)seconds);
}

void create_random_uint(uint *x, uint min, uint max) {
	(*x) = rand() % (max + 1 - min) + min;
}

void create_random_rectangle(struct Rectangle *rect) {
	uint a, b;
	
	create_random_uint(&a, MIN_SIZE, MAX_SIZE);
	create_random_uint(&b, MIN_SIZE, MAX_SIZE);

	(*rect).a = a;
	(*rect).b = b;
}

void fill_with_random_rectangles(struct Rectangle *rects, uint size) {
	for (uint i = 0; i < size; i++) {
		create_random_rectangle(&rects[i]);
	}
}

void get_rect_area(struct Rectangle rect, uint *area) {
	(*area) = rect.a * rect.b;
}

void print_rect_area(struct Rectangle rect) {
	uint area;

	get_rect_area(rect, &area);
	printf("Area of rectangle: %u\n", area);
}

void print_rects_area(struct Rectangle* rects, uint size) {
	for (uint i = 0; i < size; i++) {
		printf("%u: ", i + 1);
		print_rect_area(rects[i]);
	}
}

void print_rects_area_reversed(struct Rectangle* rects, uint size) {
	for (int i = (int)size - 1; i >= 0; i--) {
		printf("%u: ", i + 1);
		print_rect_area(rects[i]);
	}
}

void get_biggest_rect(struct Rectangle* rects, uint size, uint *max) {
	uint area = 0;

	for (uint i = 0; i < size; i++) {
		get_rect_area(rects[i], &area);
		(*max) = area > (*max) ? area : (*max);
	}
}

void get_smallest_rect(struct Rectangle* rects, uint size, uint *min) {
	uint area = 0;
	get_biggest_rect(rects, size, min);

	for (uint i = 0; i < size; i++) {
		get_rect_area(rects[i], &area);
		(*min) = area < (*min) ? area : (*min);
	}
}

void get_biggest_uint(uint* nums, uint size, uint *max) {
	(*max) = 0;

	for (uint i = 0; i < size; i++) {
		(*max) = nums[i] > (*max) ? nums[i] : (*max);
	}
}

void get_smallest_uint(uint* nums, uint size, uint *min) {
	get_biggest_uint(nums, size, min);

	for (uint i = 0; i < size; i++) {
		(*min) = nums[i] < (*min) ? nums[i] : (*min);
	}
}

void custom_transform_rect(struct Rectangle* rect) {
	(*rect).a *= 2;
	(*rect).b *= 3;
}

void custom_transform_rects(struct Rectangle* rects, uint size) {
	for (uint i = 0; i < size; i++) { 
		custom_transform_rect(&rects[i]);
	}
}

void get_rect_perimeter(struct Rectangle rect, uint *perimeter) {
	(*perimeter) = rect.a + rect.b;
}

void get_rect_perimeters(struct Rectangle* rects, uint size, uint* perimeters) {
	uint perimeter = 0;

	for (uint i = 0; i < size; i++) { 
		get_rect_perimeter(rects[i], &perimeter);
		perimeters[i] = perimeter;
	}
}

void get_average_uint(uint* nums, uint size, double *avg) {
	uint max = 0;
	uint min = 0;

	get_biggest_uint(nums, size, &max);
	get_smallest_uint(nums, size, &min);
	(*avg) = (min + max) / 2.;
}

void count_above_avg(uint *nums, uint size, uint *count) {
	double avg = 0;

	get_average_uint(nums, size, &avg);
	for (uint i = 0; i < size; i++) {
		if (nums[i] >= avg) {
			(*count)++;
		}
	}
}

void flush_buffer()
{
	int c; do c = getchar(); while (c != EOF && c != '\n');
}

void read_int_with_flush(int *input)
{
	if (scanf_s("%i", input) == 0)
	{
		flush_buffer();
	}
}

void read_uint_with_flush(uint *input)
{
	if (scanf_s("%u", input) == 0)
	{
		flush_buffer();
	}
}

void read_double_with_flush(double *input)
{
	if (scanf_s("%lf", input) == 0)
	{
		flush_buffer();
	}
}

struct DivisorNode {
	uint value;
	struct DivisorNode* next;
};

void collect_num_divisors(uint num, struct DivisorNode **node, uint *count) {
	if (num == 0 || num == 1) {
		(*node) = NULL;
		return;
	}

	for (uint i = 2; i <= pow(num, 1. / 2); i++) {
		if (num % i	 == 0) {
			if ((*node) == NULL) {
				(*node) = malloc(sizeof(struct DivisorNode));
			}
			else {
				(*node)->next = malloc(sizeof(struct DivisorNode));
				(*node) = (*node)->next;
			}

			(*node)->value = i;
			(*node)->next = NULL;

			(*count)++;
		}
	}
}

void free_divisors(struct DivisorNode *node) {
	struct DivisorNode* cur = node;

	while (cur != NULL) {
		cur = node->next;
		free(node);
	}
}

void get_biggest_divisor(struct DivisorNode *node, uint *biggest) {
	(*biggest) = 0;

	while (node != NULL) {
		(*biggest) = node->value > (*biggest) ? node->value : (*biggest);
		node = node->next;
	}
}

void get_smallest_divisor(struct DivisorNode *node, uint *smallest) {
	get_biggest_divisor(node, smallest);

	while (node != NULL) {
		(*smallest) = node->value < (*smallest) ? node->value : (*smallest);
		node = node->next;
	}
}

#define NUM_OF_MATRIX 5
#define MATRIX_SIZE 2

uint coords_to_index(uint n, uint x, uint y) {
	return n * (2 * 2) + x + (y * 2);
}

void create_random_int(int *x, int min, int max) {
	(*x) = rand() % (max + 1 - min) + min;
}

void get_matrix_det(int* matrices, uint n, double *det) {
	double a = matrices[coords_to_index(n, 0, 0)];
	double b = matrices[coords_to_index(n, 1, 0)];
	double c = matrices[coords_to_index(n, 0, 1)];
	double d = matrices[coords_to_index(n, 1, 1)];

	(*det) = a * d - b * c;
}

void print_matrices_det(int* matrices, uint size) {
	double det = 0;

	for (uint i = 0; i < size; i++) {
		get_matrix_det(matrices, i, &det);
		printf("det(A_%u) = %lf\n", i, det);
	}
}

void fill_up_matrices(int* matrices, uint size, uint width, uint height) {
	for (uint i = 0; i < size; i++) {
		for (uint j = 0; j < width; j++) {
			for (uint k = 0; k < height; k++) {
				create_random_int(&matrices[coords_to_index(i, j, k)], -10, 10);
			}
		}
	}
}

#define NUM_OF_NUMS 10
#define CHOSEN_NUM 42

void create_random_double(double *value, double from, double to) {
	(*value) = from + (rand() / (RAND_MAX / (to - from)));
	
}

void set_double_precision(double in, double* out, uint precision) {
	char format[7] = "%%.%ulf";
	char buf[40];
	char num[40];

	sprintf_s(buf, 40, format, precision);
	//sprintf_s(num, 40, format, in);
	//sscanf_s(num, "%lf", out);
}

void fill_with_random_doubles(double *nums, uint size) {
	for (uint i = 0; i < size; i++) {
		create_random_double(&nums[i], -1, 1);
		//set_double_precision(nums[i], &nums[i], 2);
	}
}

void print_doubles(double* nums, uint size) {
	for (uint i = 0; i < size; i++) {
		printf("%lf\n", nums[i]);
	}
}

void sum_doubles(double *nums, uint size, double *sum) {
	for (uint i = 0; i < size; i++) {
		(*sum) += nums[i];
	}
}

void split_doubles(double* nums, uint size, 
	double* positives, double* negatives, uint *p, uint *n) {
	
	for (uint i = 0; i < size; i++) {
		if (nums[i] >= 0) {
			positives[*p] = nums[i];
			(*p)++;
		}
		else {
			negatives[(*n)++] = nums[i];
		}
	}
}

void get_biggest_double(double* nums, uint size, double *max) {
	(*max) = 0;

	for (uint i = 0; i < size; i++) {
		(*max) = nums[i] > (*max) ? nums[i] : (*max);
	}
}

void get_smallest_double(double* nums, uint size, double *min) {
	get_biggest_double(nums, size, min);

	for (uint i = 0; i < size; i++) {
		(*min) = nums[i] < (*min) ? nums[i] : (*min);
	}
}

void sum_of_powers_double(double num, uint to, double *sum) {
	for (uint i = 1; i <= to; i++) {
		(*sum) += pow(num, i);
	}
}

void avg_of_doubles(double* nums, uint size, double* avg) {
	sum_doubles(nums, size, avg);
	(*avg) /= size;
}

void add_to_doubles(double* nums, uint size, double n) {
	for (uint i = 0; i < size; i++) {
		nums[i] += n;
	}
}

int coords_to_index_m3(uint x, uint y) {
	return x + y * 3;
}

void swap_doubles(double* arr, uint i, uint j) {
    double temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void swap_uints(uint* arr, uint i, uint j) {
    uint temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubble_sort_doubles(double* nums, uint size, bool ascending) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - i - 1; j++) {
			if (nums[ascending ? j : j+1] > nums[ascending ? j + 1 : j]) {
				swap_doubles(nums, j, j + 1);
			}
		}
	}
}

void bubble_sort_uints(uint* nums, uint size, bool ascending) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - i - 1; j++) {
			if (nums[ascending ? j : j+1] > nums[ascending ? j + 1 : j]) {
				swap_uints(nums, j, j + 1);
			}
		}
	}
}

void fill_up_m3(int *matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			create_random_int(&matrix[coords_to_index_m3(i, j)], -10, 10);
		}
	}
}

void print_m3(int *matrix) {
	for (int i = 0; i < 3; i++) {
		printf("%i %i %i\n", 
			matrix[coords_to_index_m3(i, 0)],
			matrix[coords_to_index_m3(i, 1)],
			matrix[coords_to_index_m3(i, 2)]
		);
	}
}

void get_m3_det(int *matrix, int *det) {
	int a = matrix[coords_to_index_m3(0, 0)];
	int b = matrix[coords_to_index_m3(0, 1)];
	int c = matrix[coords_to_index_m3(0, 2)];
	int d = matrix[coords_to_index_m3(1, 0)];
	int e = matrix[coords_to_index_m3(1, 1)];
	int f = matrix[coords_to_index_m3(1, 2)];
	int g = matrix[coords_to_index_m3(2, 0)];
	int h = matrix[coords_to_index_m3(2, 1)];
	int i = matrix[coords_to_index_m3(2, 2)];

	(*det) = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

void get_m3_trace(int *matrix, int *trace) {
	int a = matrix[coords_to_index_m3(0, 0)];
	int e = matrix[coords_to_index_m3(1, 1)];
	int i = matrix[coords_to_index_m3(2, 2)];
	
	(*trace) = a + e + i;
}

void get_m3_charpol(int *matrix, int *l3, int *l2, int *l1, int *l0) {
	(*l3) = -1;
	get_m3_trace(matrix, l2);
	(*l1) = 
		+ matrix[coords_to_index_m3(0, 0)] 
			* (matrix[coords_to_index_m3(1, 1)] + matrix[coords_to_index_m3(2, 2)])
		+ matrix[coords_to_index_m3(1, 1)] 
			* (matrix[coords_to_index_m3(2, 2)] + matrix[coords_to_index_m3(0, 0)])
		+ matrix[coords_to_index_m3(2, 2)] 
			* (matrix[coords_to_index_m3(0, 0)] + matrix[coords_to_index_m3(1, 1)]);
	get_m3_det(matrix, l0);
}

void print_char_polinomial(int l3, int l2, int l1, int l0) {
	printf("(%i)l^3 + (%i)l^2 + (%i)l + (%i)", l3, l2, l1, l0);
}

#define ACCELERATION 42

void calc_movement(int *velocities, double step, double *delta) {
	(*delta) = 42;
}

struct Function {
	double c4;
	double c3;
	double c2;
	double c1;
	double c0;
};

void eval_func(struct Function func, double x, double* y) {
	(*y) = 
		func.c4 * pow(x, 4)
		+ func.c3 * pow(x, 3) 
		+ func.c2 * pow(x, 2) 
		+ func.c1 * x 
		+ func.c0;
}

void rectangle_integrate(double a, double b, uint step, struct Function func, double point, double *result)
{
	double interval = (b - a) / step;
	double cur;

	(*result) = 0;
	for (uint i = 1; i <= step; i++) {
		eval_func(func, a + interval * (i - point), &cur);
		(*result) += cur;
	}
	(*result) *= interval;
}

void random_func(double x, double* y) {
	(*y) = pow(x, 4) + pow(x, 3) + 2 * x;
}

void generate_div(uint* div) {
	create_random_uint(div, 10, 100);
}

void read_step(uint* step) {
	uint old = *step;
	
	printf("Step: ");
	read_uint_with_flush(step);

	(*step) = *step == 0 ? old : *step;
}

void div_to_step(uint div, double a, double b, uint *step) {
	(*step) = b - a / div;
}

void read_coefficient(double* c) {
	printf("c_2 = ");
	read_double_with_flush(c);
}

#define UPPER_POINT 0
#define LOWER_POINT 0

//Készítsünk egy 2d-s tömböt, amely téglalapok oldalméreteit fogja tárolni.
//Töltsük fel 10-50-ig random számokkal
//A téglalapok területeit írassuk ki sorban és visszafele is
//A téglalapok közül a legnagyobb és legkisebb területûnek területét válasszuk ki - írassuk ki
//A téglalapok egyik oldalának hosszát változtassuk 2-szeresére, a másik oldalak hosszát 3-szorosára
//A téglalapok kerületeit olvassuk be egy tömbbe.
//A kerületeket tartalmazó tömböt vizsgáljuk meg, hány éri el legalább a legnagyobb és legkisebb kerületû téglalapok kerületének átlagát.
void exercise41() {
	struct Rectangle rects[NUM_OF_RECTANGLE];
	uint size = sizeof(rects) / sizeof(struct Rectangle);

	uint max = 0;
	uint min = 0;

	uint perimeters[NUM_OF_RECTANGLE];
	uint count = 0;

	seed_rand();
	fill_with_random_rectangles(rects, size);
	
	printf("Normally sorted:\n");
	print_rects_area(rects, size);
	printf("\n");

	printf("Reverse sorted:\n");
	print_rects_area_reversed(rects, size);
	printf("\n");
	
	get_biggest_rect(rects, size, &max);
	printf("Biggest rect: %u\n", max);

	get_smallest_rect(rects, size, &min);
	printf("Smallest rect: %u\n", min);
	printf("\n");

	get_rect_perimeters(rects, size, perimeters);
	count_above_avg(perimeters, size, &count);

	printf("Above average count: %u\n", count);
}

//Olvassunk be egy számot
//a) Döntsük el for ciklussal, hogy az adott szám prímszám-e
//b) Ha nem prím szám hány féle számmal oszható
//c) Melyik osztó szerepel benne a legtöbbször
void exercise42() {
	uint input = 0;

	struct DivisorNode *node = NULL;
	uint count = 0;
	uint smallest = 0;
	
	printf("Your number: ");
	read_int_with_flush(&input);
	collect_num_divisors(input, &node, &count);

	if (node == NULL) {
		printf("Your number is a prime.\n");
	}
	else {
		printf("Your number is not a prime.\n");

		get_smallest_divisor(node, &smallest);
		printf("The smallest divisor: %u.\n", smallest);
	}

	free_divisors(node);
}

//Csináljunk egy n*2*2-es tömböt, töltsük fel számokkal.
//Írassuk ki a tömböknek megfelelõ 2*2-es mátrixok determinánsait.
//Döntsük el sorban, hogy van-e valós gyöke a 2x2-es mátrixok karakterisztikus polinomjainak: lambda^2-Trace(M)+det(M)=0, diszkrimináns nemnegatív...
//Ha van intervallumfelezéssel keressük meg közelítõleg.
void exercise43() {
	int matrices[NUM_OF_MATRIX * MATRIX_SIZE * MATRIX_SIZE];
	
	seed_rand();

	fill_up_matrices(matrices, 
		NUM_OF_MATRIX, MATRIX_SIZE, MATRIX_SIZE);
	print_matrices_det(matrices, NUM_OF_MATRIX);

	// TODO: characteristic polinomials
	// TODO: intervallumfelezes
}

//b) 3*3-assal is csináljuk meg a determináns kiiratást
//c) Íjunk egy programot ami egy 3x3-as mátrixokhoz tartozó
//   karakterisztikus polinom gyökeibõl egyet meghatároz intervallumfelezéssel - Tippek: 1 vagy 3 valós gyök van mindig.
// 
//   lambdák - sajátértékek
//   det(M)=lambda1*lambda2*lambda3  (Determináns)
//   trace(M)=l1+l2+l3               (Nyom)
//   S(M): ae+ai+ei-(bd+cf+gh)       (Másodrendû fõminorok)
//        a b c
//  M:=   d e f  S(M) = ae+ai+ei-(bd+cf+gh)
//        g h i  
//   trace(M) = a+e+i
// 
//   karakterisztikus polinom:       -lambda^3+Trace(M)*lambda^2-S(M)*lambda+detM
// 
//   Extra tipp a lehetséges intervallumra: Gershgorin-tétel
void exercise44() {
	// TODO
}

/*
K´esz´ıts egy dinamikus t¨omb¨ot, t¨oltsd fel (-1, 1) k¨oz¨otti, legfeljebb sz´azados jeggyel rendelkez˝o
sz´amokkal.
Sz´amold meg a pozit´ıv sz´amok ¨osszeg´et.
Keresd meg a legkisebb sz´amot. Vedd az 1–5. hatv´anyait, majd ¨osszegezd ezeket.
Rendezd a negat´ıv sz´amokat cs¨okken˝o sorrendbe, ´ırasd ki ˝oket.
Sz´amold ki a t¨omb ´atlag´at.
Adj hozz´a a t¨omb minden elem´ehez egy ´altalad v´alasztott sz´amot.
*/
void exercisetzh1() {
	double* nums = malloc(NUM_OF_NUMS * sizeof(double));

	double* positives = malloc(NUM_OF_NUMS * sizeof(double));
	double* negatives = malloc(NUM_OF_NUMS * sizeof(double));
	uint p = 0;
	uint n = 0;

	double sum = 0;
	double min = 0;
	double avg = 0;
	
	seed_rand();

	fill_with_random_doubles(nums, NUM_OF_NUMS);
	printf("Nums:\n");
	print_doubles(nums, NUM_OF_NUMS);
	
	split_doubles(nums, NUM_OF_NUMS, positives, negatives, &p, &n);
	sum_doubles(positives, p, &sum);
	printf("Sum of positive nums: %lf\n", sum);
	
	printf("\n");

	get_smallest_double(nums, NUM_OF_NUMS, &min);
	sum_of_powers_double(min, 5, &sum);
	printf("Smallest num: %lf\n", min);
	printf("Sum of it's powers: %lf\n", sum);

	printf("\n");
	
	bubble_sort_doubles(negatives, n, false);
	printf("Negative nums sorted (descending):\n");
	print_doubles(negatives, n);

	printf("\n");

	avg_of_doubles(nums, NUM_OF_NUMS, &avg);
	printf("Avg. of nums: %lf\n", avg);

	printf("\n");

	add_to_doubles(nums, NUM_OF_NUMS, CHOSEN_NUM);
	printf("Nums after addition:\n");
	print_doubles(nums, NUM_OF_NUMS);

	free(nums);
	free(positives);
	free(negatives);
}

/*
Line´aris mozg´as modellez´ese: k´erj be egy eg´esz sz´amot (n), majd hozz l´etre egy dinamikus t¨omb¨ot
nÖ2-es m´eretben. K´erd be a mozg´as sebess´egkomponenseit (vx, vy), ´es t´arold el az n darab halad´asi
vektorban. K´erj be egy l´ep´esk¨ozt is, amelynek ´ert´eke 0,1 ´es 1 k¨oz¨otti. Adj meg egy tetsz˝oleges
gyorsul´ast az egyik ir´anyban. Sz´am´ıtsd ki ´es ´ırd ki a v´egs˝o elmozdul´ast.
*/

void exercisetzh2() {
	uint n = 0;
	int* velocities;
	double step = 1;
	double delta = 0;
	
	printf("Amount of velocities: ");
	read_uint_with_flush(&n);

	velocities = malloc(2 * n * sizeof(int));
	if (velocities != NULL) {
		for (uint i = 0; i < n; i++) {
			printf("v_%u_x = ", i);
			read_int_with_flush(&velocities[i * 2]);

			printf("v_%u_y = ", i);
			read_int_with_flush(&velocities[i * 2 + 1]);
		}

		printf("Step size: ");
		read_double_with_flush(&step);

		calc_movement(velocities, step, &delta);
		
		printf("The final delta movement is: %lf\n", delta);

		free(velocities);
	}
}

/*
Val´os´ıtsd meg egy 3Ö3-as m´atrixot:
T¨oltsd fel random sz´amokkal -5 ´es 5 k¨oz¨ott.
´Irasd ki a m´atrixot t¨obb soros, form´aban.
Sz´am´ıtsd ki a m´atrix determin´ans´at ´es nyom´at.
Hat´arozd meg a m´atrix karakterisztikus polinomj´at.
Vizsg´ald meg, hogy a karakterisztikus polinom gy¨okei val´osak vagy komplexek-e, valamint azt,
hogy egyszeresek vagy t¨obbsz¨or¨osek-e.
*/
void exercisezh3() {
	int matrix[3 * 3];

	int det = 0;
	int trace = 0;

	int l0 = 0;
	int l1 = 0;
	int l2 = 0;
	int l3 = 0;
	
	seed_rand();

	fill_up_m3(matrix);
	print_m3(matrix);
	
	printf("\n");

	get_m3_det(matrix, &det);
	printf("Det: %i\n", det);

	get_m3_trace(matrix, &trace);
	printf("Trace: %i\n", trace);
	
	get_m3_charpol(matrix, &l3, &l2, &l1, &l0);
	print_char_polinomial(l3, l2, l1, l0);
}

/*
Val´os´ıtsd meg az integr´alk¨ozel´ıt´est az al´abbi polinomra az als´o ´es fels˝o t´eglalapk¨ozel´ıt˝o m´odszerrel
a [0, 2] intervallumon:
x
4 + x
3 + 2x
a) A feloszt´asok sz´am´at v´eletlenszer˝uen v´alaszd ki 10 ´es 100 k¨oz¨ott, ´es ebb˝ol hat´arozd meg a
l´ep´esk¨ozt.
b) Biztos´ıtsd, hogy a l´ep´esk¨ozt a felhaszn´al´o is megadhassa.
c) Engedd meg, hogy a polinom valamelyik egy¨utthat´oj´at a felhaszn´al´ot´ol bek´erhesd, ´es az ´ıgy
kapott ´ert´ekkel is v´egezd el a k¨ozel´ıt´est.
*/
void exercisezh4() {
	struct Function func = {
		.c4 = 1,
		.c3 = 1,
		.c1 = 2
	};
	
	double a = 0;
	double b = 2;

	uint div = 10;
	uint step;

	double upper;
	double lower;

	double coefficient;
	
	seed_rand();
	generate_div(&div);
	
	div_to_step(div, a, b, &step);
	read_step(&step);

	rectangle_integrate(a, b, step, func, UPPER_POINT, &upper);
	rectangle_integrate(a, b, step, func, LOWER_POINT, &lower);

	printf("Upper: %lf\n", upper);
	printf("Lower: %lf\n", lower);
	printf("\n");

	read_coefficient(&coefficient);
	func.c2 = coefficient;

	rectangle_integrate(a, b, step, func, UPPER_POINT, &upper);
	rectangle_integrate(a, b, step, func, LOWER_POINT, &lower);
	
	printf("With custom coefficient:\n");
	printf("Upper: %lf\n", upper);
	printf("Lower: %lf\n", lower);
}

#define BASE_DRAWS 10
#define ONE_DRAW 6

bool is_containing(uint* nums, uint size, uint num) {
	for (uint i = 0; i < size; i++) {
		if (nums[i] == num) return true;
	}
	return false;
}

bool is_any_appear_twice(uint *nums, uint size) {
	uint* history = malloc(size * sizeof(uint));
	uint cur = 0;
	
	if (history != NULL) {
		for (uint i = 0; i < size; i++) {
			if (is_containing(history, size, nums[i])) {
				return true;
			}
			else {
				history[cur++] = nums[i];
			}
		}
		free(history);
	}

	return false;
}

bool is_contains_neighbour(uint *nums, uint size) {
	for (uint i = 1; i < size; i++) {
		if (nums[i] == nums[i - 1] - 1 || nums[i] == nums[i - 1] + 1) {
			return true;
		}
	}
	return false;
}

void print_uints_row(uint* row, uint size) {
	for (uint i = 0; i < size; i++) {
		printf("%d ", row[i]);
	}
	printf("\n");
}

void read_additional(uint *additional) {
	printf("Additional draws: ");
	read_uint_with_flush(additional);
}

void generate_draw(uint* draw, uint size) {
	for (uint i = 0; i < size; i++) {
		create_random_uint(&draw[i], 1, 20);
	}
}

/*
6-os lott´o szimul´aci´oja: v´egezz el 10 lott´oh´uz´ast, amelyeken 1-t˝ol 20-ig terjed˝o sz´amokat h´uzol.
Mindegyik h´uz´as sz´amait rendezd n¨ovekv˝o sorrendbe, majd ´ırasd ki ˝oket.
K´erj be a felhaszn´al´ot´ol egy sz´amot 0 ´es 10 k¨oz¨ott. Ez a sz´am hat´arozza meg, h´any h´uz´ast kell
´ujra megism´etelni.
Ellen˝orizd minden h´uz´asn´al, hogy van-e legal´abb k´et azonos sz´am b´armelyik h´uz´asban. Ha igen,
ezt jelezd ki.
Vizsg´ald meg, hogy van-e olyan h´uz´as, amelyben egym´as mellett l´ev˝o sz´amok ´ert´ekei a sz´amegyenesen
szomsz´edosak.
Ha igen, ´ırd ki az adott sor v´eg´ere: Szomsz´edos dob´asok!
*/
void exercisezh5() {
	uint n = BASE_DRAWS;
	uint additional = 0;
	uint* draws = NULL;
	

	read_additional(&additional);
	n += additional;

	draws = malloc(sizeof(uint) * ONE_DRAW * n);
	if (draws == NULL) {
		printf("Couldn't allocate memory!");
		return;
	}
	
	seed_rand();
	for (uint i = 0; i < n; i++) {
		uint* draw = &draws[i];

		generate_draw(draw, ONE_DRAW);
		bubble_sort_uints(draw, ONE_DRAW, true);

		printf("Draw %d:\n", i + 1);
		print_uints_row(draw, ONE_DRAW);

		if (is_any_appear_twice(draw, ONE_DRAW)) {
			printf("A num appears twice.\n");
		}

		if (is_contains_neighbour(draw, ONE_DRAW)) {
			printf("There are neighbouring numbers.\n");
		}

		printf("\n");
	}
}

struct Quadratic {
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

void scan_equation(struct Quadratic* equation)
{
	printf("ax^2 + bx + c = 0; x = ?\n");

	printf("a = ");
	read_double_with_flush(&equation->a);

	printf("b = ");
	read_double_with_flush(&equation->b);

	printf("c = ");
	read_double_with_flush(&equation->c);
}

int solve_equation(const struct Quadratic equation, struct Result* result)
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

void print_equation(struct Quadratic equation)
{
	printf("%.3lf * x^2 + %.3lf * x + %.3lf\n", equation.a, equation.b, equation.c);
}

void print_result(const struct Result result, const enum ResultType type)
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

/*
Val´os´ıts meg egy m´asodfok´u egyenlet megold´oprogramot:
Oldd meg a m´asodfok´u egyenletet dinamikus t¨omb¨ok haszn´alat´aval ´ugy, hogy a lehet˝o legkevesebb
statikus v´altoz´ot haszn´ald.
A program k´erje be az egy¨utthat´okat, majd hat´arozza meg ´es ´ırja ki a val´os vagy komplex gy¨ok¨oket.
Ugyelj arra, hogy a program ´attekinthet˝o legyen. 
*/
void exercisezh6() {
	struct Quadratic equation;

	scan_equation(&equation);
	print_equation(equation);
	
	struct Result result;
	
	int type = solve_equation(equation, &result);
	print_result(result, type);
}

int main(void)
{
	//exercise41();
	//exercise42();
	//exercise43();
	//exercise44();

	//exercisezh1();
	//exercisezh2();
	//exercisezh3();
	//exercisezh4();
	//exercisezh5();
	exercisezh6();
}