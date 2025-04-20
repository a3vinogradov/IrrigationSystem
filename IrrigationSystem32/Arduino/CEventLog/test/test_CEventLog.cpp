#include <unity.h>
#include "CEventLog.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_log_aftercreate_empty() {
    CEventLog Log(5);

    TEST_ASSERT_TRUE(Log.Empty());
    TEST_ASSERT_EQUAL(0, Log.Size());
    TEST_ASSERT_EQUAL(5, Log.Capacity());
}

void test_log_afterwrite_notempty() {
    CEventLog Log(5);
    EventLogType event;
    event.Millis = 100;
    event.eventType = LoadSystem;
    Log.Write(event);

    TEST_ASSERT_FALSE(Log.Empty());
    TEST_ASSERT_EQUAL(1, Log.Size());
    TEST_ASSERT_EQUAL(5, Log.Capacity());
}

void test_log_read_loadSystem() {
    // arrange
    CEventLog Log(5);
    EventLogType actualEvent;
    actualEvent.Millis = 100;
    actualEvent.eventType = LoadSystem;
    Log.Write(actualEvent);

    // act
    EventLogType expectedEvent;
    expectedEvent = Log.Read(0);

    // assert
    TEST_ASSERT_EQUAL(actualEvent.Millis, expectedEvent.Millis);
    TEST_ASSERT_EQUAL(actualEvent.eventType, expectedEvent.eventType);
}

void test_log_read_irrigateStart() {
    // arrange
    CEventLog Log(5);
    EventLogType actualEvent;
    actualEvent.Millis = 100;
    actualEvent.eventType = LoadSystem;
    Log.Write(actualEvent);

    // act
    EventLogType expectedEvent;
    expectedEvent = Log.Read(0);

    // assert
    TEST_ASSERT_EQUAL(actualEvent.Millis, expectedEvent.Millis);
    TEST_ASSERT_EQUAL(actualEvent.eventType, expectedEvent.eventType);
}
int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_log_aftercreate_empty);
    RUN_TEST(test_log_afterwrite_notempty);    
    RUN_TEST(test_log_read_loadSystem);    
    RUN_TEST(test_log_read_irrigateStart);
    UNITY_END();
}