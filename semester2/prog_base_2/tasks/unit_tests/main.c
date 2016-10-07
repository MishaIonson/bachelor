#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "module.h"

static void new_void_zeroCount(void **state){
    array_t * arr = array_new(10);
    assert_int_equal(array_getStatus(arr), ARRAY_OK);
    array_free(arr);
}

static void getFirstNegative_arrayWithCurrentValueInCurrentPos_valuePassed(void **state){
    array_t * arr = array_new(10);
    int current = -7;
    array_edit(arr, 0, 1);
    array_edit(arr, 1, current);
    assert_int_equal(array_getFirstNegative(arr), 1);
    array_free(arr);
}

static void getFirstNegative_badIndexes_nothingPassed(void **state){
    array_t * arr = array_new(10);
    array_edit(arr, -1, 1);
    assert_int_equal(array_getStatus(arr), ARRAY_BADINDEX);
    array_edit(arr, 10, 1);
    assert_int_equal(array_getStatus(arr), ARRAY_BADINDEX);
    array_free(arr);
}

static void getFirstNegative_arrayWithPositiveNumbers_NegOneReturned(void **state){
    array_t * arr = array_new(1);
    array_edit(arr, 0, 1);
    assert_int_equal(array_getFirstNegative(arr), -1);
    array_free(arr);
}

static void getMostPopular_arrayWith3analogyNumbers_currentReturned(void **state){
    array_t * arr = array_new(4);
    int current = 13;
    array_edit(arr, 0, current);
    array_edit(arr, 1, current);
    array_edit(arr, 2, current);
    assert_int_equal(array_getMostPopular(arr), current);
    array_free(arr);
}

static void getSize_arrayWithSizeOf10_tenCount(void **state){
    array_t * arr = array_new(10);
    assert_int_equal(array_getSize(arr), 10);
    array_free(arr);
}

static void getValueAt_arrayWithCurrentIndexAndValue_currentValueReturned(void **state){
    array_t * arr = array_new(10);
    int current = 17;
    array_edit(arr, 0, current);
    assert_int_equal(array_getValueAt(arr, 0) , current);
    array_free(arr);
}

static void getValueAt_tryToShowIncorrectIndex_nothingPassed(void **state){
    array_t * arr = array_new(10);
    int current = 17;
    array_edit(arr, 0, current);
    array_getValueAt(arr, -1);
    assert_int_equal(array_getStatus(arr), ARRAY_BADINDEX);
    array_getValueAt(arr, 10);
    assert_int_equal(array_getStatus(arr), ARRAY_BADINDEX);
    array_free(arr);
}

int main(){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(getFirstNegative_arrayWithCurrentValueInCurrentPos_valuePassed),
        cmocka_unit_test(getFirstNegative_badIndexes_nothingPassed),
        cmocka_unit_test(getFirstNegative_arrayWithPositiveNumbers_NegOneReturned),
        cmocka_unit_test(getMostPopular_arrayWith3analogyNumbers_currentReturned),
        cmocka_unit_test(getSize_arrayWithSizeOf10_tenCount),
        cmocka_unit_test(getValueAt_arrayWithCurrentIndexAndValue_currentValueReturned),
        cmocka_unit_test(getValueAt_tryToShowIncorrectIndex_nothingPassed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

