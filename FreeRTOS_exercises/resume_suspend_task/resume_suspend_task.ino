#include <Arduino_FreeRTOS.h>

//Print to serial monitor with two tasks

void first_task_print(void *param);
void second_task_print(void *param);
void task_controlled(void *param);
void print_task(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
int counter = 0;

void setup() {
  Serial.begin(9600);
  xTaskCreate(first_task_print, "Task 1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(second_task_print, "Task 2", 100, NULL, 1, &Task_Handle2);
}

void loop() {
  //No code necessary

}

void first_task_print(void *param) {
  (void) param;
  TickType_t getTick = xTaskGetTickCount(); // the getTick will get the system tick of the OS

  for (;;) {
    counter++; // increase the counter with every task run
    if (counter == 15) {
      vTaskResume(Task_Handle2);
    }
    Serial.println("Task 1");
    //vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for 1 second
    vTaskDelayUntil(&getTick, 1000 / portTICK_PERIOD_MS);
  }
}

void second_task_print(void *param) {
  (void) param;

  for (;;) {
    counter++; // increase the counter with every task run
    if (counter == 10) {
      vTaskSuspend(Task_Handle2);
    }
    Serial.println("Task 2");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for 1 second
  }



}
