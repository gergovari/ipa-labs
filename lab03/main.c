//1.Feladat
//Készíts egy számkitalálós játékot.
//Generálj egy véletlen számot, és kérj be számokat a felhasználótól.
//Minden egyes megadásnál mondja meg a program, hogy kisebb vagy nagyobb a random számnál a begépelt.
//Ha eltalálta a felhasználó, írd ki hanyadikra sikerült.
//
//2. Feladat
//a) Készíts egy programot ami 0,5-ösével haladva egy bekért [a;b] intervallumon belül
//	 kiszámolja egy harmadfokú polinom értékeit.
//b) Ha előjelet vált a függvény, írja ki a konzol
//c) Legyenek a polinom együtthatói is tetszőlegesek, a felhasználó által megadottak
//d) a Lépésköz is legyen tetszőleges ( a) részben a 0,5 volt a lépésköz...)
//
//3. Feladat
//a) Készíts egy integrálközelítő programot az előző feladatra alapozva	
//b) Építsd bele a feladatot egy karaktervezérelt menü-be
//
//4. Feladat
//Az ascii kódtábla alapján generálj a nagybetűk illetve a számok tartományában karaktereket.
//Készíts ezt alapul véve Neptun kódokat.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define NEPTUN_ID_LEN 6
#define MAX_MSG 14

static void seed_rand()
{
	time_t seconds;

	time(&seconds);
	printf("(Current seed: %lli)\n", seconds);
	srand((unsigned int)seconds);
}

static void flush_buffer()
{
	int c; do c = getchar(); while (c != EOF && c != '\n');
}

static void read_num_with_flush(unsigned int *input)
{
	if (scanf_s("%u", input) == 0)
	{
		flush_buffer();
	}
}

static void read_double_with_flush(double *input)
{
	if (scanf_s("%lf", input) == 0)
	{
		flush_buffer();
	}
}

static void take_guess(unsigned int* input)
{
	printf("Your guess: ");
	read_num_with_flush(input);
}

static void guess_cmp(unsigned int input, unsigned int target)
{
	char msg[MAX_MSG] = "";

	if (input < target) {
		strncpy_s(msg, 14, "smaller than ", MAX_MSG);
	}
	else if (input > target) {
		strncpy_s(msg, 14, "greater than ", MAX_MSG);
	}

	printf("Your guess was %sthe target number.\n", msg);
}

static void guess_loop(unsigned int target, unsigned int* attempts)
{
	unsigned int input;

	do {
		take_guess(&input);
		(*attempts)++;

		guess_cmp(input, target);

	} while (input != target);
}

static void guess_game()
{
	unsigned int target;
	unsigned int attempts = 0;
	int err = 0;
	
	target = rand();
	printf("(The number will be %u)\n", target);

	guess_loop(target, &attempts);

	printf("You needed %u attempts to guess said number.\n", attempts);
}

#define ASCII_NUM_LOW 48
#define ASCII_NUM_HIGH 57
#define ASCII_UPPER_LOW 65
#define ASCII_UPPER_HIGH 90

static void generate_neptun_char(char *cur)
{
	unsigned int numRange = ASCII_NUM_HIGH - ASCII_NUM_LOW + 1;
	unsigned int upperRange = ASCII_UPPER_HIGH - ASCII_UPPER_LOW + 1;
	unsigned int range = numRange + upperRange;

	unsigned int num = rand() % range;
	
	if (num < numRange)
	{
		*cur = ASCII_NUM_LOW + num;
	}
	num -= numRange;
	if (num < upperRange)
	{
		*cur = ASCII_UPPER_LOW + num;
	}
}

static void generate_neptun_id(char id[7])
{
	for (int i = 0; i < NEPTUN_ID_LEN; i++)
	{
		char cur;

		generate_neptun_char(&cur);
		id[i] = cur;
	}

	id[NEPTUN_ID_LEN] = '\0';
}

static void neptun_utility()
{
	char id[NEPTUN_ID_LEN + 1];
	unsigned int num = 20;
	
	printf("Generated neptun codes:\n");
	for (int i = 0; i < 20; i++)
	{
		printf("%u: ", i + 1);
		generate_neptun_id(id);
		printf("%s\n", id);
	}
}

struct ListNode
{
	double x;
	double y;
	struct ListNode* next;
};

static void calc_polinomial(double x, double *y)
{
	*y = pow(x, 3) + pow(x, 2) + x + 0;
}

struct Polinomial
{
	double a, b, c, d;
};

struct PolinomialScan
{
	double low, high, step;
};

static void print_polinomial_scan(
	const struct Polinomial polinomial, 
	const struct PolinomialScan scan)
{
	const double a = polinomial.a;
	const double b = polinomial.b;
	const double c = polinomial.c;
	const double d = polinomial.d;

	const double low = scan.low;
	const double high = scan.high;
	const double step = scan.step;

	printf("(%lf)x^3+(%lf)x^2+(%lf)x+(%lf), on range [%lf:%lf] with step %lf:\n", 
		a, b, c, d,
		low, high, step);
}

static int scan_polinomial(
	struct ListNode **first,
	struct Polinomial polinomial,
	struct PolinomialScan scan)
{
	const double a = polinomial.a;
	const double b = polinomial.b;
	const double c = polinomial.c;
	const double d = polinomial.d;

	const double low = scan.low;
	const double high = scan.high;
	const double step = scan.step;

	unsigned int range = (unsigned int)(fabs(high - low) / step) + 1;
	struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
	*first = node;

	if (node == NULL)
	{
		printf("Not enough memory, aborting.\n");
		return -1;
	} else {
		for (unsigned int i = 0; i < range; i++)
		{
			node->next = NULL;
			node->x = low + step * i;
			calc_polinomial(node->x, &(node->y));
			
			if (i != range - 1) {
				node->next = (struct ListNode*)malloc(sizeof(struct ListNode));
				if (node->next == NULL)
				{
					printf("Not enough memory, aborting.\n");
					return -1;
				}
				node = node->next;
			}
		}
	}
	return 0;
}

static void print_polinomial_values(struct ListNode* first)
{
	struct ListNode* node = first;

	bool positive = true;
	if (node->y < 0)
	{
		positive = false;
	}

	while (true) {
		if ((positive && node->y < 0) || (!positive && node->y > 0))
		{
			printf("The sign was changed midway.\n");
			positive = !positive;
		}

		printf("x = %lf -> y = %lf\n", node->x, node->y);

		if (node->next == NULL)
		{
			break;
		} else {
			node = node->next;
		}
	};
}

static void request_polinomial(struct Polinomial *polinomial)
{
	printf("Specify the 3rd order polinomial coefficients:\n");

	printf("a = ");
	read_double_with_flush(&polinomial->a);

	printf("b = ");
	read_double_with_flush(&polinomial->b);

	printf("c = ");
	read_double_with_flush(&polinomial->c);

	printf("d = ");
	read_double_with_flush(&polinomial->d);
}

static void request_polinomial_scan(struct PolinomialScan *scan)
{
	printf("Specify the scan values: ([low:high] with step)\n");

	printf("low = ");
	read_double_with_flush(&scan->low);

	printf("high = ");
	read_double_with_flush(&scan->high);

	printf("step = ");
	read_double_with_flush(&scan->step);

}

static void polinomial_utility()
{
	struct Polinomial polinomial;
	struct PolinomialScan scan;

	request_polinomial(&polinomial);
	printf("\n");
	
	request_polinomial_scan(&scan);
	printf("\n");
	
	struct ListNode *first;
	scan_polinomial(&first, polinomial, scan);
	print_polinomial_scan(polinomial, scan);
	print_polinomial_values(first);
}

static void integral_utility()
{

}

struct MenuItem {
	void (*func)();
	char name[21];
};

static struct MenuItem items[] = {
	{ guess_game, "GUESS" },
	{ polinomial_utility, "POLINOMIAL" },
	{ integral_utility, "INTEGRAL" },
	{ neptun_utility, "NEPTUN CODES" }
};

static void show_menu()
{
	for (int i = 0; i < sizeof(items) / sizeof(struct MenuItem); i++)
	{
		printf("%u: %s\n", i + 1, items[i].name);
	}
}

static void request_menu(unsigned int *input)
{
	printf("Pick your utility (or send 0 to quit): ");
	read_num_with_flush(input);
	(*input)--;
}

static int call_utility(unsigned int input)
{
	if (input < sizeof(items) / sizeof(struct MenuItem)) {
		items[input].func();
		return 0;
	}
	return -1;
}

static void menu_loop()
{
	int input = -2;

	do {
		if (input >= 0) {
			int err = call_utility(input);
			if (err != 0)
			{
				printf("That utility doesn't exist.\n");
			}
			printf("\n");
		}

		show_menu();
		request_menu(&input);
		printf("\n");
	} while (input != -1);
}

int main(void)
{
	seed_rand();
	printf("\n");

	menu_loop();
	printf("\nGoodbye!\n");

	return 0;
}