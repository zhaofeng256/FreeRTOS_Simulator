#include "test.h"
#include <stdio.h>
#include "portmacro.h"

void test_kernel_api()
{

	portTickType TotalRunTime;
	long ArraySize, x;
	void *StatusArray;
	char InfoBuffer[4000] = { 0 };

	TotalRunTime =  xTaskGetTickCount();
	printf("get tick count %d\n", TotalRunTime);

	ArraySize = uxTaskGetNumberOfTasks();
	//StatusArray = pvPortMalloc(10);
	StatusArray = malloc(10);
	if (NULL == StatusArray) {
		printf("malloc failed \n");
		return;
	} else {
		vTaskList(InfoBuffer);
		printf("%s\n", InfoBuffer);
	}
	//vPortFree(StatusArray);
	free(StatusArray);

}
