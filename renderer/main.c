#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "core/api.h"
#include "shaders/cache_helper.h"
#include "tests/test_blinn.h"
#include "tests/test_pbr.h"

typedef void testfunc_t(int argc, char *argv[]);
/* 定义结构体：包含  测试项名称 和 测试函数指针 */
typedef struct {const char *testname; testfunc_t *testfunc;} testcase_t;

static testcase_t g_testcases[] = {
    /*渲染方式, 对应函数*/   
    {"blinn", test_blinn},
    {"pbr", test_pbr},
};

int main(int argc, char *argv[]) {
    int num_testcases = ARRAY_SIZE(g_testcases);
    const char *testname = NULL;  /*测试项名称*/ 
    testfunc_t *testfunc = NULL;  /*该项测试 对应的 函数指针*/ 
    int i;

    srand((unsigned int)time(NULL));
    platform_initialize();

    /*解析命令行参数*/
    if (argc > 1) {
        testname = argv[1];  /*用户输入的渲染类型*/
        for (i = 0; i < num_testcases; i++) {
            if (strcmp(g_testcases[i].testname, testname) == 0) {
                testfunc = g_testcases[i].testfunc;
                break;
            }
        }
    } else {
        i = rand() % num_testcases;  /*随机一个类型*/
        testname = g_testcases[i].testname;
        testfunc = g_testcases[i].testfunc;
    }

    if (testfunc) {
        printf("test项目: %s\n", testname);
        /*这也是具体的执行函数，是整个程序的核心*/
        testfunc(argc, argv);
    } else {
        printf("test not found: %s\n", testname);
        printf("available tests: ");
        for (i = 0; i < num_testcases; i++) {
            if (i != num_testcases - 1) {
                printf("%s, ", g_testcases[i].testname);
            } else {
                printf("%s\n", g_testcases[i].testname);
            }
        }
    }

    platform_terminate();
    cache_cleanup();

    return 0;
}
