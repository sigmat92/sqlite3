#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "esp_tls.h"
#include "driver/uart.h"
#include "cJSON.h"
#include "esp_crt_bundle.h"
#include "esp_netif.h"

#define TAG "KIOSK"

#define UART1_PORT UART_NUM_1

#define UART1_TX_PIN    17
#define UART1_RX_PIN    18
#define UART_BAUD_RATE 115200

//#define UART0_PORT      UART_NUM_0
/*
#define UART0_PORT     UART_NUM_0
#define UART0_TX_PIN   15
#define UART0_RX_PIN   16

#define UART1_PORT     UART_NUM_1
#define UART1_TX_PIN   43
#define UART1_RX_PIN   44

#define UART_BAUD_RATE 115200
*/
#define BUF_SIZE 2048
#define WIFI_CONNECTED_BIT BIT0

static EventGroupHandle_t wifi_event_group;
static bool wifi_ready = false;
static char jwt_token[1024] = {0};

// Local Server URLs
//static const char *AUTH_URL =
//    "https://coddleonline.com/example/user/login";
//static const char *VITALS_URL =
//    "https://coddleonline.com/HISIntegrationMachine/api/v1/vital-details";
//CDAC Server
static const char *AUTH_URL =
    "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/authenticate/UserId/Password";
static const char *VITALS_URL =
    "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/api/v1/vital-details";

/* ================= UART ================= */
static void uart_send(const char *msg)
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s\n\r", msg);
    //uart_write_bytes(UART_PORT, buffer, strlen(buffer));
    uart_write_bytes(UART1_PORT, buffer, strlen(buffer));
}

/* ================= WIFI ================= */
static void wifi_event_handler(void* arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
        esp_wifi_connect();
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_ready = false;
        uart_send("WIFI_DN");
        esp_wifi_connect();
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        wifi_ready = true;
        uart_send("WIFI_UP");
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

static void wifi_connect(const char *ssid, const char *pass)
{
    wifi_event_group = xEventGroupCreate();

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL);

    wifi_config_t wifi_config = {0};
    strcpy((char*)wifi_config.sta.ssid, ssid);
    strcpy((char*)wifi_config.sta.password, pass);

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    uart_send("CONNECTING");

    xEventGroupWaitBits(wifi_event_group,
                        WIFI_CONNECTED_BIT,
                        pdFALSE,
                        pdFALSE,
                        portMAX_DELAY);
}

/* ================= HTTP ================= */
static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    if (evt->event_id == HTTP_EVENT_ON_DATA && evt->user_data)
    {
        size_t len = evt->data_len;
        strncat((char*)evt->user_data, (char*)evt->data, len);
    }
    return ESP_OK;
}

static bool authenticate()
{
    char response[2048] = {0};

    esp_http_client_config_t config = {
        .url = AUTH_URL,
        .method = HTTP_METHOD_POST,
        .event_handler = http_event_handler,
        .user_data = response,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 10000,
        .buffer_size = 8192,
        .buffer_size_tx = 4096,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "username", "Tnhmis_VitalMachine");
    cJSON_AddStringToObject(root, "password", "1234567");

    char *post_data = cJSON_PrintUnformatted(root);

    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    bool success = false;

    if (esp_http_client_perform(client) == ESP_OK)
    {
        cJSON *resp_json = cJSON_Parse(response);
        if (resp_json)
        {
            cJSON *token_item = cJSON_GetObjectItem(resp_json, "token");
            if (token_item && cJSON_IsString(token_item))
            {
                strncpy(jwt_token, token_item->valuestring, sizeof(jwt_token)-1);
                jwt_token[sizeof(jwt_token)-1] = '\0';
                uart_send("AUTH_SUCCESS");
                success = true;
            }
            else
            {
                uart_send("AUTH_FAIL");
            }
            cJSON_Delete(resp_json);
        }
        else
        {
            uart_send("AUTH_FAIL");
        }
    }
    else
    {
        uart_send("AUTH_FAIL");
    }

    esp_http_client_cleanup(client);
    cJSON_Delete(root);
    free(post_data);
    return success;
}

static void post_vitals(const char *json_data)
{
    if (!wifi_ready)
    {
        uart_send("WIFI_DN");
        return;
    }

    if (strlen(jwt_token) == 0)
    {
        if (!authenticate()) return;
    }

    char response[2048] = {0};

    esp_http_client_config_t config = {
        .url = VITALS_URL,
        .method = HTTP_METHOD_POST,
        .event_handler = http_event_handler,
        .user_data = response,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_http_client_set_header(client, "Content-Type", "application/json");

    char auth_header[1200];
    snprintf(auth_header, sizeof(auth_header), "Bearer %s", jwt_token);
    esp_http_client_set_header(client, "Authorization", auth_header);

    esp_http_client_set_post_field(client, json_data, strlen(json_data));

    if (esp_http_client_perform(client) == ESP_OK)
        uart_send("DATA_SUCCESS");
    else
        uart_send("DATA_FAILURE");

    esp_http_client_cleanup(client);
}

/* ================= MAIN TASK ================= */
static void kiosk_task(void *arg)
{
    uint8_t *data = malloc(BUF_SIZE);
    if (!data) {
        ESP_LOGE(TAG, "Malloc failed");
        vTaskDelete(NULL);
    }

    uart_send("ESP_1.0.3");

    TickType_t last_status = xTaskGetTickCount();

    while (1)
    {
        // Periodic WiFi status every 5 seconds
        if (xTaskGetTickCount() - last_status > pdMS_TO_TICKS(5000))
        {
            if (wifi_ready)
                uart_send("WIFI_UP");
            else
                uart_send("NO_WIFI_INFO");
            last_status = xTaskGetTickCount();
        }

        //int len = uart_read_bytes(UART_PORT, data, BUF_SIZE-1, pdMS_TO_TICKS(200));
        int len = uart_read_bytes(UART1_PORT, data, BUF_SIZE-1, pdMS_TO_TICKS(200));
        if (len > 0)
        {
            data[len] = 0;
            char *json = (char*)data;

            if (strstr(json, "SSID"))
            {
                cJSON *root = cJSON_Parse(json);
                if (root)
                {
                    const char *ssid = cJSON_GetObjectItem(root, "SSID")->valuestring;
                    const char *pass = cJSON_GetObjectItem(root, "Security_Key")->valuestring;

                    wifi_connect(ssid, pass);
                    authenticate();
                    cJSON_Delete(root);
                }
            }
            else if (strstr(json, "mId"))
            {
                post_vitals(json);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
//swap uarts

static void uart1_init(void)
{
    uart_config_t config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(UART1_PORT, 8192, 0, 0, NULL, 0);
    uart_param_config(UART1_PORT, &config);

    uart_set_pin(UART1_PORT,
                 UART1_TX_PIN,
                 UART1_RX_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);
}

/* ================= APP MAIN ================= */
void app_main(void)
{
    nvs_flash_init();

//    uart0_init();
    uart1_init();

    uart_write_bytes(UART1_PORT, "ESP_1.0.3", 12);

    BaseType_t res = xTaskCreate(
        kiosk_task,
        "kiosk_task",
        12288,
        NULL,
        5,
        NULL
    );

    if (res != pdPASS) {
        ESP_LOGE(TAG, "Task creation failed");
        while (1) { vTaskDelay(portMAX_DELAY); }
    }

    while (1) {
        vTaskDelay(portMAX_DELAY);
    }
}
