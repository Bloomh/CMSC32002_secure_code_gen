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
    // Validate input parameters
    if (header == NULL || info_content == NULL || strlen(info_content) == 0 || strlen(info_content) >= 100) {
        return header; // Return original header if invalid
    }

    char key[50];

    // Determine the key based on info_type
    if (strcmp(info_type, "lang") == 0) {
        snprintf(key, sizeof(key), "Accept-Language");
    } else if (strcmp(info_type, "encoding") == 0) {
        snprintf(key, sizeof(key), "Accept-Encoding");
    } else if (strcmp(info_type, "cache") == 0) {
        snprintf(key, sizeof(key), "Cache-Control");
    } else {
        return header; // Return original header if info_type is invalid
    }

    // Check if the header already contains this key
    int index = find_header_index(header, key);
    if (index >= 0) {
        // Update existing entry
        snprintf(header->entries[index].value, sizeof(header->entries[index].value), "%s", info_content);
    } else {
        // Check if there's space for a new entry
        if (header->count < HEADER_SIZE) {
            // Add new entry
            snprintf(header->entries[header->count].key, sizeof(header->entries[header->count].key), "%s", key);
            snprintf(header->entries[header->count].value, sizeof(header->entries[header->count].value), "%s", info_content);
            header->count++;
        } else {
            // No space left to add new entry, return original header
            return header;
        }
    }

    return header; // Return the updated header
}