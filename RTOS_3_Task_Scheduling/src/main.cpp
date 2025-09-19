#include <Arduino.h>
#include <stdlib.h>

#define LED_BUILTIN 2

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

  TaskHandle_t input_handle = nullptr;
  TaskHandle_t blink_LED_handle = nullptr;

  volatile int User_Rate = 500;
  void task_input(void *paramater)
  {
    Serial.println("--FreeRTOS--");
    Serial.println("Input LED Blinking Rate (ms): ");
    char input_buffer[20];
    while (1)
    {
        int len = Serial.readBytesUntil('\n', input_buffer, sizeof(input_buffer) - 1);
        if (len > 0){
          input_buffer[len] = '\0';
          User_Rate = atoi(input_buffer);
          int users_input = User_Rate;
          Serial.printf("\nRate Recieved: %d\n", users_input);
          memset(input_buffer, 0, 20);
        }
    }
}

void task_blink_LED(void * paramater){
  while (1){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(User_Rate/ portTICK_PERIOD_MS);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(User_Rate/ portTICK_PERIOD_MS);
  }
}


  void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore(
        task_input,     // task func
        "Serial Input", // name for debugging
        4096,           // stack size
        nullptr,        // paramaters
        1,              // priority
        &input_handle,  // task handle
        app_cpu         // which cpu
    );

    xTaskCreatePinnedToCore(
        task_blink_LED,
        "Blink LED",
        4096,
        nullptr,
        1,
        &blink_LED_handle,
        app_cpu 
      );
  }

void loop() {
  // Not used because we run FreeRTOS tasks instead
}
