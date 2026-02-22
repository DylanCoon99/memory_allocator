#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "allocator.h"

static int tests_run = 0;
static int tests_passed = 0;

#define RUN_TEST(test) do { \
    printf("Running %s... ", #test); \
    tests_run++; \
    test(); \
    tests_passed++; \
    printf("PASSED\n"); \
} while (0)

void test_basic_alloc() {
    void *ptr = my_malloc(100);
    assert(ptr != NULL);
    my_free(ptr);
}

void test_alloc_write_read() {
    int *buf = my_malloc(10 * sizeof(int));
    assert(buf != NULL);

    for (int i = 0; i < 10; i++) {
        buf[i] = i * i;
    }

    for (int i = 0; i < 10; i++) {
        assert(buf[i] == i * i);
    }

    my_free(buf);
}

void test_multiple_allocs() {
    void *a = my_malloc(64);
    void *b = my_malloc(64);
    void *c = my_malloc(64);

    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a != b);
    assert(b != c);
    assert(a != c);

    my_free(a);
    my_free(b);
    my_free(c);
}

void test_alloc_after_free() {
    void *a = my_malloc(100);
    assert(a != NULL);
    my_free(a);

    void *b = my_malloc(100);
    assert(b != NULL);
    my_free(b);
}

void test_different_sizes() {
    void *small = my_malloc(8);
    void *medium = my_malloc(256);
    void *large = my_malloc(4096);

    assert(small != NULL);
    assert(medium != NULL);
    assert(large != NULL);

    my_free(small);
    my_free(medium);
    my_free(large);
}

void test_string_storage() {
    char *str = my_malloc(32);
    assert(str != NULL);

    strcpy(str, "Hello, allocator!");
    assert(strcmp(str, "Hello, allocator!") == 0);

    my_free(str);
}

void test_no_corruption_after_free() {
    int *a = my_malloc(10 * sizeof(int));
    int *b = my_malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i * 10;
    }

    my_free(a);

    // b should still be intact
    for (int i = 0; i < 10; i++) {
        assert(b[i] == i * 10);
    }

    my_free(b);
}

int main() {
    printf("\n=== Allocator Tests ===\n\n");

    RUN_TEST(test_basic_alloc);
    RUN_TEST(test_alloc_write_read);
    RUN_TEST(test_multiple_allocs);
    RUN_TEST(test_alloc_after_free);
    RUN_TEST(test_different_sizes);
    RUN_TEST(test_string_storage);
    RUN_TEST(test_no_corruption_after_free);

    printf("\n=== Results: %d/%d tests passed ===\n\n", tests_passed, tests_run);

    return tests_run - tests_passed;
}
