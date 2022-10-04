#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int sort_entered(const void* p1, const void* p2);
int check_entered(const unsigned int* arr);
void print_numbers_entered(const unsigned int* arr);
void print_array(const unsigned int* arr);
void sleep(double sec);
void check_bingo(const unsigned int* nbrs, const unsigned int* nbrs_arr);

unsigned int cnt_nbr[90];
int bng1, bng2, bng3; //used for checking bingo

int main(int argc, char* argv[])
{
    int i;
    int n;
    int cnt_in_array;
    int cnt_rnd_nbr;
    unsigned int rnd_nbr;
    FILE *f;

    cnt_in_array = cnt_rnd_nbr = 0;

    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments...\n");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);

    srand((unsigned)time(NULL));

    while (n) {
        unsigned int numbers[15];
        unsigned int numbers_array[90] = { 0 };
        unsigned int random_nbr[90] = { 0 };

        printf("please enter the number:\n");
        scanf("%d%d%d%d%d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]);
        scanf("%d%d%d%d%d", &numbers[5], &numbers[6], &numbers[7], &numbers[8], &numbers[9]);
        scanf("%d%d%d%d%d", &numbers[10], &numbers[11], &numbers[12], &numbers[13], &numbers[14]);

        if (check_entered(numbers)) //
            continue;

        for (i = 1; i < 15; ++i)
            numbers_array[numbers[i] - 1] = 1;

        print_numbers_entered(numbers);

        while (1) {
            rnd_nbr = rand() % 90;
            if (!random_nbr[rnd_nbr]) {
                random_nbr[rnd_nbr] = 1;
                ++cnt_rnd_nbr;
                //sleep(1);
                if (numbers_array[rnd_nbr]) {
                    printf("%2u true\n", rnd_nbr + 1);
                    ++cnt_nbr[rnd_nbr];
                    ++cnt_in_array;
                    check_bingo(numbers, cnt_nbr);
                }
                else
                    printf("%2u false\n", rnd_nbr + 1);
            }

            if (cnt_rnd_nbr == 90) {
                printf("Sorry, there are no numbers remaining in the bag!!! See you next time!\n\n");
                break;
            }


            if (cnt_in_array == 15) {
                printf("tombola!!!!!!\n\n");
                break;
            }
        }
        cnt_in_array = cnt_rnd_nbr = 0;
        n--;
    }

    if ((f = fopen("extractions.dat", "wb")) == NULL) {
        fprintf(stderr, "can't create the %s file...\n", "extractions.dat");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 90; ++i) {
        fprintf(f, "%2d %-2d\n", i + 1, cnt_nbr[i]);
    }

    fclose(f);

    return 0;
}

int sort_entered(const void* p1, const void* p2)
{
    return *(unsigned int*)p1 - *(unsigned int*)p2;
}

int check_entered(const unsigned int* arr)
{
    int i;
    int cnt;
    unsigned int sort_array[15];

    cnt = 0;

    memcpy(sort_array, arr, sizeof(unsigned int) * 15);
    qsort(sort_array, 15, sizeof(unsigned int), sort_entered);

    for (i = 1; i < 15; ++i) {
        if (sort_array[i] == sort_array[i - 1]) {
            fprintf(stderr, "can't enter same values! please try again...\n");
            return 1;
        }
    }

    for (i = 0; i < 90; ++i) {
        if (sort_array[i] <= 10 && cnt == 0)
            ++cnt;
        if (sort_array[i] <= 20 && sort_array[i] > 10 &&  cnt == 1)
            ++cnt;
        if (sort_array[i] <= 30 && sort_array[i] > 20 &&  cnt == 2)
            ++cnt;
        if (sort_array[i] <= 40 && sort_array[i] > 30 &&  cnt == 3)
            ++cnt;
        if (sort_array[i] <= 50 && sort_array[i] > 40 &&  cnt == 4)
            ++cnt;
        if (sort_array[i] <= 60 && sort_array[i] > 50 &&  cnt == 5)
            ++cnt;
        if (sort_array[i] <= 70 && sort_array[i] > 60 &&  cnt == 6)
            ++cnt;
        if (sort_array[i] <= 80 && sort_array[i] > 70 &&  cnt == 7)
            ++cnt;
        if (sort_array[i] <= 90 && sort_array[i] > 80 &&  cnt == 8)
            ++cnt;
    }

    if (cnt != 9) {
        fprintf(stderr, "at least one coloumn is empty!...please try again...\n");
        return 1;
    }

    for (i = 0; i < 15; ++i) {
        if (sort_array[i] > 90 || sort_array[i] == 0) {
            fprintf(stderr, "entered numbers must be between 1 to 90! please try again...\n");
            return 1;
        }
    }

    return 0;
}

void print_numbers_entered(const unsigned int* arr)
{
    unsigned int sorting_first_five[5];

    memcpy(sorting_first_five, arr, sizeof(unsigned int) * 5);
    qsort(sorting_first_five, 5, sizeof(unsigned int), sort_entered);
    print_array(sorting_first_five);
    putchar('\n');

    memcpy(sorting_first_five, arr + 5, sizeof(unsigned int) * 5);
    qsort(sorting_first_five, 5, sizeof(unsigned int), sort_entered);
    print_array(sorting_first_five);
    putchar('\n');

    memcpy(sorting_first_five, arr + 10, sizeof(unsigned int) * 5);
    qsort(sorting_first_five, 5, sizeof(unsigned int), sort_entered);
    print_array(sorting_first_five);
    putchar('\n');

}

void print_array(const unsigned int* arr)
{
    int i;
    int k;
    int cnt;
    unsigned int mod;

    mod = cnt = 0;

    for (i = 0, k = 0, mod = 0; i < 9; ++i, mod += 10) {
        if (arr[k] > mod && arr[k] <= mod + 10) {
            printf("%2d ", arr[k]);
            k++;
            ++cnt;
        }
        else
            printf("-- ");
    }

    if (cnt < 5) {
        fprintf(stderr, "improper number.\nPlease re-enter the correct numbers...\n");
        exit(EXIT_FAILURE);
    }
}

void sleep(double sec)
{

    clock_t now = clock();

    while ((((double)clock() - now) / CLOCKS_PER_SEC) < sec)
        ;

}

void check_bingo(const unsigned int* nbrs, const unsigned int* nbrs_arr)
{
    int i;
    int cnt;

    if (!bng1) {
        for (i = 0, cnt = 0; i < 5; ++i)
            if (nbrs_arr[nbrs[i] - 1])
                ++cnt;

        if (cnt == 5) {
            bng1 = 1;
            printf("BINGOOOO\n");
            for (i = 0; i < 5; ++i)
                printf("%2d ", nbrs[i]);
            putchar('\n');
            return;
        }
    }

    if (!bng2) {
        for (i = 5, cnt = 0; i < 10; ++i)
            if (nbrs_arr[nbrs[i] - 1])
                ++cnt;

        if (cnt == 5) {
            bng2 = 1;
            printf("BINGOOOO\n");
            for (i = 5; i < 10; ++i)
                printf("%2d ", nbrs[i]);
            putchar('\n');
            return;
        }
    }
    if (!bng3) {
        for (i = 10, cnt = 0; i < 15; ++i)
            if (nbrs_arr[nbrs[i] - 1])
                ++cnt;

        if (cnt == 5) {
            bng3 = 1;
            printf("BINGOOOO\n");
            for (i = 10; i < 15; ++i)
                printf("%2d ", nbrs[i]);
            putchar('\n');
        }
    }
}
