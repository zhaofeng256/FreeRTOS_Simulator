#include "test.h"
#include <stdio.h>
#include "portmacro.h"
#include "projdefs.h"
#include "FreeRTOS.h"
#include "queue.h"

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
		printf("======================================\n");
		printf("%s\n", InfoBuffer);
		printf("======================================\n");

		memset(InfoBuffer, 0, 4000);
		vTaskGetRunTimeStats(InfoBuffer);
		printf("%s\n", InfoBuffer);
		printf("======================================\n");
	}
	//vPortFree(StatusArray);
	free(StatusArray);

}

void test_message_queue()
{
	char *msg = "hello";
	char buf[32] = {0};
	xQueueHandle q = xQueueCreate(4, 32);
	portBASE_TYPE ret = xQueueSend(q, msg, 32);
	if (errQUEUE_FULL == ret) {
		printf("send queue queue fail , it's full\n");
	}

	ret = xQueueReceive(q, buf, pdFALSE);
	if (pdTRUE == ret) {
		printf("recv from queue : %s\n", buf);
	}
	vQueueDelete(q);
}
