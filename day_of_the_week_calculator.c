#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int anchor_year_calculator(int y, int anchor_century) {
	//odd plus 11 algorithm
	y %= 100;
	y += 11 * (y % 2);
	y /= 2;
	y += 11 * (y % 2);
	y = 7 - (y % 7);
	y = (y + anchor_century) % 7;
	return y;
}

int anchor_century_calculator(int y) {
	int anchor_century;
	if (y >= 1600 && y <= 1699) {
		anchor_century = 2;
	}
	else if (y >= 1700 && y <= 1799) {
		anchor_century = 0;
	}
	else if (y >= 1800 && y <= 1899) {
		anchor_century = 5;
	}
	else if (y >= 1900 && y <= 1999) {
		anchor_century = 3;
	}
	else if (y >= 2000 && y <= 2099) {
		anchor_century = 2;
	}
	else if (y >= 2100 && y <= 2199) {
		anchor_century = 0;
	}
	else {
		anchor_century = 5;
	}
	return anchor_century;
}

bool is_leap_year(int y) {
	return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}

int anchor_month_day_calculator(int m, bool is_leap_year) {
	int day = 0;
	if (m == 0) {
		day = 3 + (is_leap_year);
	}
	else if (m == 1) {
		day = 7 - (is_leap_year * 6);
	}
	else if (m == 2) {
		day = 7;
	}
	else if (m == 3) {
		day = 4;
	}
	else if (m == 4) {
		day = 2;
	}
	else if (m == 5) {
		day = 6;
	}
	else if (m == 6) {
		day = 4;
	}
	else if (m == 7) {
		day = 1;
	}
	else if (m == 8) {
		day = 5;
	}
	else if (m == 9) {
		day = 3;
	}
	else if (m == 10) {
		day = 7;
	}
	else {
		day = 5;
	}
	return day;
}

bool is_valid_day_of_the_month(int m, int d, bool is_leap_year) {
	bool is_valid = true;
	if (m == 1 || m == 3 || m == 5 || m == 8 || m == 10) {
		if (d > 30) {
			is_valid = false;
		}
		else if ((d > 29 && is_leap_year) || (d > 28 && !(is_leap_year))) {
			is_valid = false;
		}
	}
	if (!(is_valid)) {
		printf("Please choose a valid day for this month\n");
	}
	return is_valid;
}

int answer_calculator(int d, int anchor_month_day, int anchor_year) {
	int answer = (7 + (anchor_year + ((d % 7) - anchor_month_day))) % 7;
	return answer;
}

int main() {
	int y = 0;
	while (y < 1600 || y > 2299 || y == '\n') {
		printf("Enter a year (1600 - 2299): ");
		scanf("%d", &y);
	}

	int anchor_century = anchor_century_calculator(y);
	int anchor_year = anchor_year_calculator(y, anchor_century);
	
	char *days[7];
	days[0] = "Sunday";
	days[1] = "Monday";
	days[2] = "Tuesday";
	days[3] = "Wednesday";
	days[4] = "Thursday";
	days[5] = "Friday";
	days[6] = "Saturday";
	
	int m = 13;
	while (m < 1 || m > 12 || m == '\n') {
		printf("Enter a month (1 - 12): ");
		scanf("%d", &m);
	}
	m -= 1;

	bool leap_year = is_leap_year(y);
	int anchor_month_day = anchor_month_day_calculator(m, leap_year);
	int d = 0;
	while (d < 1 || d > 31 || d == '\n' || !(is_valid_day_of_the_month(m, d, leap_year))) {
		printf("Enter a day: ");
		scanf("%d", &d);
	}

	int answer = answer_calculator(d, anchor_month_day, anchor_year);
	printf("%s\n", days[answer]);

}
