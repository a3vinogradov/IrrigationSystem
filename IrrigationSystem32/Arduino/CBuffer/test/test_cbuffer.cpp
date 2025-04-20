#include <unity.h>
#include "cbuffer.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_cbuffer_afterinit_empty() {
    CBuffer<int> buffer(5);
    TEST_ASSERT_TRUE(buffer.Empty());
    TEST_ASSERT_EQUAL(0, buffer.Size());
    TEST_ASSERT_EQUAL(5, buffer.Capacity());
}

void test_cbuffer_afterpush_notEmpty() {
    CBuffer<int> buffer(5);
    buffer.Push(1);
    TEST_ASSERT_FALSE(buffer.Empty());
    TEST_ASSERT_EQUAL(1, buffer.Size());
    TEST_ASSERT_EQUAL(5, buffer.Capacity());

    buffer.Push(2);
    TEST_ASSERT_FALSE(buffer.Empty());
    TEST_ASSERT_EQUAL(2, buffer.Size());
    TEST_ASSERT_EQUAL(5, buffer.Capacity());
}

void test_cbuffer_index_ifEmpty() {
    CBuffer<int> buffer(3);
    int result = buffer[0]; // буфер пуст. должен возвратиться нулевой элемент буфера с неинициализированным значением
    result = buffer[2]; // то же, но индекс в диапазоне (0..capasity)
    result = buffer[3]; // то же, но индекс равен capasity
    result = buffer[4]; // то же, но индекс больше capasity
    TEST_ASSERT_MESSAGE(true, "обращение к не существующему индексу");
}

void test_cbuffer_index_IfSizeIsOne() {
    CBuffer<int> buffer(3);
    buffer.Push(5);
    int buf0 = buffer[0]; // первая запись буфера
    TEST_ASSERT_EQUAL(5, buf0);
    int buf1 = buffer[1]; // циклически повторенный индекс
    TEST_ASSERT_EQUAL(5, buf1);
}
 
void test_cbuffer_index_IfSizeLessThenCapacity() {
    CBuffer<int> buffer(3);
    buffer.Push(5);
    buffer.Push(6);
    TEST_ASSERT_EQUAL(6, buffer[0]);
    TEST_ASSERT_EQUAL(5, buffer[1]);
}

void test_cbuffer_index_IfSizeEqualToCapacity() {
    CBuffer<int> buffer(3);
    buffer.Push(5);
    buffer.Push(6);
    buffer.Push(7);
    TEST_ASSERT_EQUAL(7, buffer[0]);
    TEST_ASSERT_EQUAL(6, buffer[1]);
    TEST_ASSERT_EQUAL(5, buffer[2]);
}

void test_cbuffer_index_IfSizeGeaterThenCapacity() {
    CBuffer<int> buffer(2);
    buffer.Push(5); // index = 0
    buffer.Push(6); // index = 1
    buffer.Push(7); // index = 0
    TEST_ASSERT_EQUAL(7, buffer[0]);
    TEST_ASSERT_EQUAL(6, buffer[1]);
    TEST_ASSERT_EQUAL(7, buffer[2]);
    TEST_ASSERT_EQUAL(6, buffer[3]);
    TEST_ASSERT_EQUAL(7, buffer[4]);
    TEST_ASSERT_EQUAL(6, buffer[5]);
}

void test_cbuffer_Clear() {
    CBuffer<int> buffer(2);
    buffer.Push(5); // index = 0
    buffer.Push(6); // index = 1
    buffer.Push(7); // index = 0
    buffer.Clear();
    TEST_ASSERT_TRUE(buffer.Empty());
    TEST_ASSERT_EQUAL(0, buffer.Size());
    TEST_ASSERT_EQUAL(2, buffer.Capacity());
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_cbuffer_afterinit_empty);
    RUN_TEST(test_cbuffer_afterpush_notEmpty);
    RUN_TEST(test_cbuffer_index_ifEmpty);
    RUN_TEST(test_cbuffer_index_IfSizeIsOne);
    RUN_TEST(test_cbuffer_index_IfSizeLessThenCapacity);
    RUN_TEST(test_cbuffer_index_IfSizeEqualToCapacity);
    RUN_TEST(test_cbuffer_index_IfSizeGeaterThenCapacity);
    RUN_TEST(test_cbuffer_Clear);
    UNITY_END();
}