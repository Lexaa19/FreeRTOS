#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void first_task_print(void *param);
void second_task_print(void *param);
void task_controlled(void *param);
void print_task(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
SemaphoreHandle_t myMutex;

volatile int a;

void setup() {
  Serial.begin(9600);
  myMutex = xSemaphoreCreateMutex();
  // guard condition
  if(myMutex==NULL){
    Serial.println("Mutex cannot be created");
  }
  xTaskCreate(first_task_print, "Task 1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(second_task_print, "Task 2", 100, NULL, 1, &Task_Handle2);

  vTaskStartScheduler();
}

void loop() {
  //No code necessary

}

void first_task_print(void *param) {
  (void) param;

  for (;;) {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    for(int i=0; i< 5;i ++){
      Serial.println(i);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    // release mutex so that the other task doesn't wait forever
    xSemaphoreGive(myMutex);
  }
}

void second_task_print(void *param) {
  (void) param;

  for (;;) {
    xSemaphoreTake(myMutex, portMAX_DELAY);
   for(int i=0; i< 5;i ++){
      Serial.println(i);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    // release mutex so that the other task doesn't wait forever
    xSemaphoreGive(myMutex);
  }
}
