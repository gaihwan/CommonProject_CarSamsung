#ifdef _RELEASE

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

#include "ICommand.h"
#include "Command.h"
#include "CommandFactory.h"
#include "Menu.h"

#if 1
int main() {

    CommandFactory factory;
    factory.Register("CarSedan", []() { return std::make_unique <CarTypeSedanCommand>(); });
    factory.Register("CarSUV", []() { return std::make_unique <CarTypeSUVCommand>(); });
    factory.Register("CarTruck", []() { return std::make_unique <CarTypeTruckCommand>(); });
    factory.Register("BrakeBosch", []() { return std::make_unique<BrakeTypeBoschCommand>(); });
    factory.Register("BrakeContinental", []() { return std::make_unique <BrakeTypeContinentalCommand>(); });
    factory.Register("BrakeMando", []() { return std::make_unique <BrakeTypeMandoCommand>(); });
    factory.Register("EngineBroken", []() { return std::make_unique <EngineTypeBrokenCommand>(); });
    factory.Register("EngineGM", []() { return std::make_unique <EngineTypeGMCommand>(); });
    factory.Register("EngineToyota", []() { return std::make_unique <EngineTypeToyotaCommand>(); });
    factory.Register("EngineWia", []() { return std::make_unique <EngineTypeWiaCommand>(); });
    factory.Register("SteeringBosch", []() { return std::make_unique <SteeringTypeBoschCommand>(); });
    factory.Register("SteeringMobis", []() { return std::make_unique <SteeringTypeMobisCommand>(); });

    //// 2. 메뉴 구성 (Composite 구조)
    auto root = std::make_unique<MenuGroup>("Main Menu");

    auto menuLevel1 = std::make_unique<MenuGroup>("CAR_TYPE");
    menuLevel1->Add(std::make_unique<MenuItem>("CarSedan", factory.Create("CarSedan")));
    menuLevel1->Add(std::make_unique<MenuItem>("CarSUV", factory.Create("CarSUV")));
    menuLevel1->Add(std::make_unique<MenuItem>("CarTruck", factory.Create("CarTruck")));


    //////fileMenu->Add(std::make_unique<MenuItem>("SteeringType", factory.Create("Steering")));
    ////

    ////// 2. 메뉴 구성 (Composite 구조)
    root->Add(std::move(menuLevel1));

    ////// 3. 메뉴 출력
    root->Display();
}

#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BrakeTypeMenuGroup.h"
#include "EngineTypeMenuGroup.h"
#include "SteeringTypeMenuGroup.h"
#include "CarTypeMenuGroup.h"
#include "RunTestMenuGroup.h"
#include "RootMenuGroup.h"


const int QUESTION_TYPE_STACKS = 10;
int QuestionTypeStack[QUESTION_TYPE_STACKS];

bool needToGoVeryFirst(int& questionTypeStep, int answer);
bool needToGoPrevious(int& questionTypeStep, int answer);

bool isExitRequested(char  inputBuf[100]);
bool isNumeric(char* checkNumber);


bool isCarTypeValidity(int questionTypeStep, int answer);
bool isEngineTypeValidity(int questionTypeStep, int answer);
bool isBrakeTypeValidity(int questionTypeStep, int answer);
bool isSteeringTypeValidity(int questionTypeStep, int answer);
bool isRunTestValidity(int questionTypeStep, int answer);

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);

void runProducedCar(void);
void testProducedCar(void);

void printMenuCarType(void);
void printMenuEngine(void);
void printMenuBrakeSystem(void);
void printMenuSteering(void);
void printMenuRunTest(void);

void getInput(char* inputBuf);
void setNextQuestionTypeStep(int answer, int& questionTypeStep);
void doTimeDelayInMsec(int ms);


void doTimeDelayInMsec(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}


void getInput(char* inputBuf)
{
    printf("INPUT > ");
    fgets(inputBuf, sizeof(inputBuf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(inputBuf, "\r", &context);
    strtok_s(inputBuf, "\n", &context);
}

static MenuGroup root;

int main()
{
    SteeringTypeMenuGroup steeringType;
    BrakeTypeMenuGroup brakeType;
    CarTypeMenuGroup carType;
    EngineTypeMenuGroup engineType;

    root->Add(steeringType);

    const int maximumInputChars = 100;
    char inputBuf[maximumInputChars];
    int questionTypeStep = CAR_TYPE;

    while (1)
    {
        if (questionTypeStep == CAR_TYPE)
        {
            printMenuCarType();
        }
        else if (questionTypeStep == ENGINE_TYPE)
        {
            printMenuEngine();
        }
        else if (questionTypeStep == BRAKE_SYSTEM_TYPE)
        {
            printMenuBrakeSystem();
        }
        else if (questionTypeStep == STEERING_SYSTEM_TYPE)
        {
            printMenuSteering();
        }
        else if (questionTypeStep == RUN_TEST)
        {
            printMenuRunTest();
        }
        printf("===============================\n");

        getInput(inputBuf);

        if (isExitRequested(inputBuf))
        {
            printf("바이바이\n");
            break;
        }

        // 숫자로 된 대답인지 확인
        char* checkNumber;
        int answer = strtol(inputBuf, &checkNumber, 10); // 문자열을 10진수로 변환

        int retFlag;
        if (false == isNumeric(checkNumber))
            continue;

        if (false == isCarTypeValidity(questionTypeStep, answer))
            continue;

        if (false == isEngineTypeValidity(questionTypeStep, answer))
            continue;

        if (false == isBrakeTypeValidity(questionTypeStep, answer))
            continue;

        if (false == isSteeringTypeValidity(questionTypeStep, answer))
            continue;

        if (false == isRunTestValidity(questionTypeStep, answer))
            continue;

        if (false == needToGoVeryFirst(questionTypeStep, answer))
            continue;

        if (false == needToGoPrevious(questionTypeStep, answer))
            continue;

        setNextQuestionTypeStep(answer, questionTypeStep);
    }
}

void setNextQuestionTypeStep(int answer, int& questionTypeStep)
{
    if (questionTypeStep < RUN_TEST)
    {
        selectCarType(answer);
        doTimeDelayInMsec(800);
        questionTypeStep++;
    }
    if (questionTypeStep == RUN_TEST)
    {
        if (answer == 1) {
            runProducedCar();
            doTimeDelayInMsec(2000);
        }
        else if (answer == 2) {
            printf("Test...\n");
            doTimeDelayInMsec(1500);
            testProducedCar();
            doTimeDelayInMsec(2000);
        }
    }
}

bool needToGoVeryFirst(int& questionTypeStep, int answer)
{
    bool bRet = true;
    // 처음으로 돌아가기
    if (answer == 0 && questionTypeStep == RUN_TEST)
    {
        questionTypeStep = CAR_TYPE;
        bRet = false;
    }
    return bRet;
}

bool needToGoPrevious(int& questionTypeStep, int answer)
{
    bool bRet = true;
    // 이전으로 돌아가기
    if (answer == 0 && questionTypeStep >= CAR_TYPE)
    {
        questionTypeStep -= 1;
        bRet = false;
    }
    return bRet;
}

bool isNumeric(char* checkNumber)
{
    bool bRet = true;
    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isCarTypeValidity(int questionTypeStep, int answer)
{
    bool bRet = true;
    if (questionTypeStep == CAR_TYPE && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isEngineTypeValidity(int questionTypeStep, int answer)
{
    bool bRet = true;
    if (questionTypeStep == ENGINE_TYPE && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isBrakeTypeValidity(int questionTypeStep, int answer)
{
    bool bRet = true;
    if (questionTypeStep == BRAKE_SYSTEM_TYPE && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isSteeringTypeValidity(int questionTypeStep, int answer)
{
    bool bRet = true;
    if (questionTypeStep == STEERING_SYSTEM_TYPE && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isRunTestValidity(int questionTypeStep, int answer)
{
    bool bRet = true;
    if (questionTypeStep == RUN_TEST && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        doTimeDelayInMsec(800);
        bRet = false;
    }
    return bRet;
}

bool isExitRequested(char  inputBuf[100])
{
    return !strcmp(inputBuf, "exit");
}

void selectCarType(int answer)
{
    QuestionTypeStack[CAR_TYPE] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    QuestionTypeStack[ENGINE_TYPE] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    QuestionTypeStack[BRAKE_SYSTEM_TYPE] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    QuestionTypeStack[STEERING_SYSTEM_TYPE] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isPartsCombinationValid(void)
{
    if (QuestionTypeStack[CAR_TYPE] == SEDAN && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == CONTINENTAL)
    {
        return false;
    }
    else if (QuestionTypeStack[CAR_TYPE] == SUV && QuestionTypeStack[ENGINE_TYPE] == TOYOTA)
    {
        return false;
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[ENGINE_TYPE] == WIA)
    {
        return false;
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == MANDO)
    {
        return false;
    }
    else if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == BOSCH_B && QuestionTypeStack[STEERING_SYSTEM_TYPE] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isPartsCombinationValid() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (QuestionTypeStack[ENGINE_TYPE] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (QuestionTypeStack[CAR_TYPE] == 1)
                printf("Car Type : Sedan\n");
            if (QuestionTypeStack[CAR_TYPE] == 2)
                printf("Car Type : SUV\n");
            if (QuestionTypeStack[CAR_TYPE] == 3)
                printf("Car Type : Truck\n");
            if (QuestionTypeStack[ENGINE_TYPE] == 1)
                printf("ENGINE_TYPE : GM\n");
            if (QuestionTypeStack[ENGINE_TYPE] == 2)
                printf("ENGINE_TYPE : TOYOTA\n");
            if (QuestionTypeStack[ENGINE_TYPE] == 3)
                printf("ENGINE_TYPE : WIA\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 1)
                printf("Brake System : Mando\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 2)
                printf("Brake System : Continental\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 3)
                printf("Brake System : Bosch\n");
            if (QuestionTypeStack[STEERING_SYSTEM_TYPE] == 1)
                printf("STEERING_TYPE : Bosch\n");
            if (QuestionTypeStack[STEERING_SYSTEM_TYPE] == 2)
                printf("STEERING_TYPE : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (QuestionTypeStack[CAR_TYPE] == SEDAN && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == SUV && QuestionTypeStack[ENGINE_TYPE] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[ENGINE_TYPE] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == BOSCH_B && QuestionTypeStack[STEERING_SYSTEM_TYPE] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}
#endif
#endif