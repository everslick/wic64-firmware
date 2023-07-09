#ifndef WIC64_CLIENT_H
#define WIC64_CLIENT_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_http_client.h"
#include "WString.h"

#include "data.h"
#include "command.h"

namespace WiC64 {
    class Client {
        public: static const char* TAG;

        private:
            esp_http_client_handle_t m_client = NULL;
            QueueHandle_t m_queue = NULL;

            bool m_keepAlive = false;

            esp_http_client_handle_t handle() { return m_client; }
            QueueHandle_t queue() { return m_queue; }

            void keepAlive(bool keepAlive) { m_keepAlive = keepAlive; }

            void closeConnection(void);
            void closeConnectionUnlessKeptAlive();
            bool isConnectionClosed();

            static esp_err_t eventHandler(esp_http_client_event_t *evt);
            static void queueTask(void* content_length_ptr);

        public:
            Client();
            void get(Command *command, String url);
    };
}

#endif // WIC64_CLIENT_H