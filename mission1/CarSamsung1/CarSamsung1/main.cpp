#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

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

enum QuestionType
{
    CAR_TYPE = 1,
    ENGINE_TYPE,
    BRAKE_SYSTEM_TYPE,
    STEERING_SYSTEM_TYPE,
    RUN_TEST,
    QUESTION_TYPE_END,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    CAR_TYPE_END,
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    ENGIN_TYPE_END,
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    BRAKE_TYPE_END,
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    STEERING_TYPE_END,
};

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

void printMenuCarType(void)
{
    printf(CLEAR_SCREEN);
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printMenuEngine(void)
{
    printf(CLEAR_SCREEN);
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void printMenuBrakeSystem(void)
{
    printf(CLEAR_SCREEN);
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printMenuSteering(void)
{
    printf(CLEAR_SCREEN);
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printMenuRunTest(void)
{
    printf(CLEAR_SCREEN);
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
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

int main()
{
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
                printf("Engine : GM\n");
            if (QuestionTypeStack[ENGINE_TYPE] == 2)
                printf("Engine : TOYOTA\n");
            if (QuestionTypeStack[ENGINE_TYPE] == 3)
                printf("Engine : WIA\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 1)
                printf("Brake System : Mando\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 2)
                printf("Brake System : Continental\n");
            if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == 3)
                printf("Brake System : Bosch\n");
            if (QuestionTypeStack[STEERING_SYSTEM_TYPE] == 1)
                printf("SteeringSystem : Bosch\n");
            if (QuestionTypeStack[STEERING_SYSTEM_TYPE] == 2)
                printf("SteeringSystem : Mobis\n");

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