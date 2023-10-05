#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ClassThatUsesDB.h"
#include "MockDBConnection.h"

using ::testing::Return;

TEST(ClassThatUsesDBTest, OpenConnectionSuccess) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open()).WillOnce(Return(true));

    bool result = classUnderTest.openConnection();

    ASSERT_TRUE(result);
}

TEST(ClassThatUsesDBTest, OpenConnectionFailure) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open()).WillOnce(Return(false));

    bool result = classUnderTest.openConnection();

    ASSERT_FALSE(result);
}

TEST(ClassThatUsesDBTest, UseConnectionSuccess) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open()).WillOnce(Return(true));

    EXPECT_CALL(mockConnection, execQuery("SELECT * FROM table")).WillOnce(Return(2));

    classUnderTest.openConnection();

    int result = classUnderTest.useConnection("SELECT * FROM table");

    ASSERT_EQ(result, 2);
}

TEST(ClassThatUsesDBTest, UseConnectionFailure) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    bool result = classUnderTest.useConnection("SELECT * FROM table");

    ASSERT_EQ(result, false);
}

TEST(ClassThatUsesDBTest, CloseConnection) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open()).WillOnce(Return(true));

    EXPECT_CALL(mockConnection, close());

    classUnderTest.openConnection();
    classUnderTest.closeConnection();
}

TEST(ClassThatUsesDBTest, CloseConnectionFailure) {
    MockDBConnection mockConnection;
    ClassThatUsesDB classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open()).WillOnce(Return(true));

    EXPECT_CALL(mockConnection, close()).Times(0);

    classUnderTest.openConnection();
}