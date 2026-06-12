#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifndef __NR_my_op
#define __NR_my_op 470
#endif

#define MY_OP_ITERATIONS 100000

static uint64_t nsec_now(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static int do_op_user(int a, int b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return b == 0 ? 0 : a / b;
    default:
        return 0;
    }
}

int main(void) {
    int a = 0;
    int b = 0;
    char op = 0;
    int result = 0;
    volatile int sink = 0;

    printf("Please enter the first operand: ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Invalid first operand.\n");
        return 1;
    }

    printf("Please enter the second operand: ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid second operand.\n");
        return 1;
    }

    printf("Please enter the operator (+ - * /): ");
    if (scanf(" %c", &op) != 1) {
        fprintf(stderr, "Invalid operator input.\n");
        return 1;
    }
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        fprintf(stderr, "Invalid operator: %c\n", op);
        return 1;
    }

    {
        uint64_t start = nsec_now();
        long ret = syscall(__NR_my_op, &result, a, b, &op);
        if (ret != 0) {
            perror("syscall my_op");
            return 1;
        }
        uint64_t end = nsec_now();
        double elapsed_ms = (double)(end - start) / 1000000.0;
        printf("kernel %d %c %d (x%d): %.3f ms (result=%d)\n",
               a, op, b, MY_OP_ITERATIONS, elapsed_ms, result);
    }

    {
        uint64_t start = nsec_now();
        for (int i = 0; i < MY_OP_ITERATIONS; ++i) {
            sink += do_op_user(a, b, op);
        }
        uint64_t end = nsec_now();
        double elapsed_ms = (double)(end - start) / 1000000.0;
        printf("user   %d %c %d (x%d): %.3f ms \n",a, op, b, MY_OP_ITERATIONS, elapsed_ms);
    }

    return 0;
}
