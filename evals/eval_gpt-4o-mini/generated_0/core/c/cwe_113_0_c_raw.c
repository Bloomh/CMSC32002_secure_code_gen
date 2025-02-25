#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// Function to find the index of a key in the header dictionary, returns -1 if not found
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/**
Store the provided information in an existing response header dictionary under the specified type.
This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
Information content is read from user requests.
If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header dictionary without any changes.

@param info_type The type of information to store in the header.
@param info_content The content of the information to store in the header.
@param header The existing response header dictionary.

@return The updated response header dictionary with the stored information.
*/
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // Check for NULL parameters
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }

    // Define valid information types and corresponding header keys
    const char *valid_types[] = {"lang", "encoding", "cache"};
    const char *header_keys[] = {"Accept-Language", "Accept-Encoding", "Cache-Control"};

    // Validate the info_type and find the corresponding header key
    int index = -1;
    for (int i = 0; i < 3; i++) {
        if (strcmp(info_type, valid_types[i]) == 0) {
            index = i;
            break;
        }
    }

    // If the information type is invalid or the header is full, return the original header
    if (index == -1 || header->count >= HEADER_SIZE) {
        return header;
    }

    // Check if the key already exists in the header
    int existing_index = find_header_index(header, header_keys[index]);
    if (existing_index != -1) {
        // Update existing entry safely
        strncpy(header->entries[existing_index].value, info_content, sizeof(header->entries[existing_index].value) - 1);
        header->entries[existing_index].value[sizeof(header->entries[existing_index].value) - 1] = '\0'; // Ensure null termination
    } else {
        // Add new entry safely
        if (header->count < HEADER_SIZE) {
            strncpy(header->entries[header->count].key, header_keys[index], sizeof(header->entries[header->count].key) - 1);
            header->entries[header->count].key[sizeof(header->entries[header->count].key) - 1] = '\0'; // Ensure null termination

            // Sanitize and truncate info_content if necessary
            char sanitized_value[100];
            strncpy(sanitized_value, info_content, sizeof(sanitized_value) - 1);
            sanitized_value[sizeof(sanitized_value) - 1] = '\0'; // Ensure null termination

            // Store sanitized value
            strncpy(header->entries[header->count].value, sanitized_value, sizeof(header->entries[header->count].value) - 1);
            header->entries[header->count].value[sizeof(header->entries[header->count].value) - 1] = '\0'; // Ensure null termination

            header->count++;
        }
    }

    return header;
}