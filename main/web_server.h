#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "esp_http_server.h"

/**
 * @brief Starts the HTTP server and registers URI handlers.
 * @return An HTTP server handle on success, or NULL on failure.
 */
httpd_handle_t start_webserver(void);

#endif