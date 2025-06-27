#include "gmock/gmock.h"
#include "CommandFactory.h"
#include "CarTypeSedanCommand.h"
#include "IMenuGroup.h"
#include "Menu.h"


TEST(CarSamsung, TC1) {
    EXPECT_EQ(1, 1);
}

TEST(CarSamsung, TC2) {
    CommandFactory factory;
    factory.Register("CarSedan", []() { return std::make_unique <CarTypeSedanCommand>(); });

    auto instance = factory.Create("CarSedan");
    EXPECT_NE(instance, nullptr);
}


TEST(CarSamsung, TC3) {
    CommandFactory factory;
    factory.Register("CarSedan", []() { return std::make_unique <CarTypeSedanCommand>(); });

    auto instance = factory.Create("CarSedan");
    EXPECT_NE(instance, nullptr);
}
