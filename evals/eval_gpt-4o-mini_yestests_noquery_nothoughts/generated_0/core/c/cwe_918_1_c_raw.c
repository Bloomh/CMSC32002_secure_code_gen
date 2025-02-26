char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check for NULL or empty user_id
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Validate user_id to ensure it contains only valid characters (alphanumeric in this case)
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum(user_id[i])) {
            return NULL;
        }
    }
    
    // Calculate the length of the new URL
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t new_url_len = api_url_len + user_id_len + 2; // +1 for '/' and +1 for '\0' termination
    
    // Allocate memory for the new URL
    char* new_url = (char*)malloc(new_url_len);
    if (new_url == NULL) {
        return NULL; // Handle memory allocation failure
    }
    
    // Construct the new URL
    snprintf(new_url, new_url_len, "%s/%s", api_url, user_id);
    
    return new_url;
}