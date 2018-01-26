#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "portmacro.h"
#include "projdefs.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

void test_kernel_api()
{
	void *StatusArray;
	char InfoBuffer[4000] = { 0 };

	portTickType TotalRunTime =  xTaskGetTickCount();
	printf("get tick count %d\n", TotalRunTime);

	portBASE_TYPE ArraySize = uxTaskGetNumberOfTasks();
	printf("get task count %ld\n", ArraySize);
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
	xQueueHandle q = NULL;
	q = xQueueCreate(4, 32);
	if(q == 0) {
		printf("create queue failed\n");
		return;
	}

	portBASE_TYPE ret = xQueueSend(q, msg, 32);
	if (errQUEUE_FULL == ret) {
		printf("send queue queue fail , it's full\n");
		return;
	}

	ret = xQueueReceive(q, buf, pdFALSE);
	if (pdTRUE == ret) {
		printf("recv from queue : %s\n", buf);
	}

	vQueueDelete(q);
}

void test_semaphore()
{
	xSemaphoreHandle BinarySemaphore = xSemaphoreCreateCounting(2, 0);
	if (NULL == BinarySemaphore) {
		printf("create semaphore failed\n");
		return;
	}
	xSemaphoreGive(BinarySemaphore);
	portBASE_TYPE ret = xSemaphoreTake(BinarySemaphore, portMAX_DELAY);
	if (pdTRUE == ret) {
		printf("take semaphore success\n");
	}
}
