#include <gtest/gtest.h>
#include <memory>
#include <chrono>

#include "Dispatcher.hpp"
#include "QtGuiSubscriber.hpp"
#include "TelemetrySnapshot.hpp"
#include "Enum.hpp"
#include "scada_core_testing_utils.hpp"

TEST(DispatcherUnitTest, PublishValidSnapshot)
{
    TelemetrySnapshot snapshot;
    snapshot.lastValue = 100.0;
    snapshot.id = "100";
    snapshot.valid = ValidData::YES;
    snapshot.currentState = State::OK;
    snapshot.timestamp = std::chrono::system_clock::now();

    Dispatcher dispatcher;

    auto subcriber =
        std::make_unique<scada_core_testing_utils::FakeSubscriber>();  

    dispatcher.addSubscriber(subcriber.get());
    dispatcher.publishetValid(snapshot);

    EXPECT_TRUE(subcriber->getCall());
    auto result_snapshot = subcriber->getSnapshot();

    EXPECT_EQ(result_snapshot.id, "100");
    EXPECT_EQ(result_snapshot.lastValue, 100.0);
    EXPECT_EQ(result_snapshot.valid, ValidData::YES);
    EXPECT_EQ(result_snapshot.currentState, State::OK);
    EXPECT_EQ(result_snapshot.timestamp, snapshot.timestamp);
}