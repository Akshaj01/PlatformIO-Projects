#include <Arduino.h>


#define LED_PIN 2
#define RATE_1 500
#define RATE_2 900


// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

void task1(void * paramater){
  while (1){
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(RATE_1 / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(RATE_1 / portTICK_PERIOD_MS);
  }
}

void task2(void * paramater){
  while (1){
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(RATE_2 / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(RATE_2 / portTICK_PERIOD_MS);
  }
}


void setup() {
  pinMode(LED_PIN, OUTPUT);
  xTaskCreatePinnedToCore(
      task1,           // function to be called
      "TOGGLE LED R1", // name of task
      1024,            // stack size
      NULL,            // paramater to pass to function
      1,               // Priority
      NULL,            // Handle
      app_cpu         // run on one core
  );
  xTaskCreatePinnedToCore(
      task2,           // function to be called
      "TOGGLE LED R2", // name of task
      1024,            // stack size
      NULL,            // paramater to pass to function
      1,               // Priority
      NULL,            // Handle
      app_cpu         // run on one core
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}





