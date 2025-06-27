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
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}

void printMenuEngine(void)
{
    printf(CLEAR_SCREEN);
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void printMenuBrakeSystem(void)
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void printMenuSteering(void)
{
    printf(CLEAR_SCREEN);
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void printMenuRunTest(void)
{
    printf(CLEAR_SCREEN);
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void getInput(char* inputBuf)
{
    printf("INPUT > ");
    fgets(inputBuf, sizeof(inputBuf), stdin);

    // ���� ���๮�� ����
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
            printf("���̹���\n");
            break;
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(inputBuf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

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
    // ó������ ���ư���
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
    // �������� ���ư���
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
    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
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
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
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
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
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
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
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
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
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
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    QuestionTypeStack[ENGINE_TYPE] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    QuestionTypeStack[BRAKE_SYSTEM_TYPE] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    QuestionTypeStack[STEERING_SYSTEM_TYPE] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (QuestionTypeStack[ENGINE_TYPE] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (QuestionTypeStack[CAR_TYPE] == SEDAN && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == SUV && QuestionTypeStack[ENGINE_TYPE] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[ENGINE_TYPE] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (QuestionTypeStack[CAR_TYPE] == TRUCK && QuestionTypeStack[BRAKE_SYSTEM_TYPE] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (QuestionTypeStack[BRAKE_SYSTEM_TYPE] == BOSCH_B && QuestionTypeStack[STEERING_SYSTEM_TYPE] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

#endif