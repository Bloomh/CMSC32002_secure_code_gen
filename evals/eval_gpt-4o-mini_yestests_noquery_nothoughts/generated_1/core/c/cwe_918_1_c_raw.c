    char* get_url_for_query(const char* api_url, const char* user_id) {
        // Check if api_url or user_id is NULL
        if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
            return NULL;
        }

        // Validate user_id to ensure it contains only safe characters
        for (int i = 0; user_id[i] != '\0'; i++) {
            if (!isalnum(user_id[i])) {
                return NULL; // Invalid user_id
            }
        }

        // Calculate the length of the new URL
        size_t api_url_len = strlen(api_url);
        size_t user_id_len = strlen(user_id);
        size_t new_url_len = api_url_len + user_id_len + 2; // +2 for '/' and '\0'

        // Allocate memory for the new URL
        char* new_url = (char*)malloc(new_url_len);
        if (new_url == NULL) {
            return NULL; // Memory allocation failed
        }

        // Construct the new URL
        snprintf(new_url, new_url_len, "%s/%s", api_url, user_id);

        return new_url;
    }