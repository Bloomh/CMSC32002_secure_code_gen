
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
    if (header->count >= HEADER_SIZE) {
        return header; // No space to add new entry
    }

    char key[50];
    if (strcmp(info_type, "lang") == 0) {
        strncpy(key, "Accept-Language", sizeof(key));
    } else if (strcmp(info_type, "encoding") == 0) {
        strncpy(key, "Accept-Encoding", sizeof(key));
    } else if (strcmp(info_type, "cache") == 0) {
        strncpy(key, "Cache-Control", sizeof(key));
    } else {
        return header; // Invalid info_type, return original header
    }

    // Validate info_content to prevent HTTP response splitting
    if (strpbrk(info_content, "\r\n") != NULL) {
        return header; // Invalid content, return original header
    }

    // Check for buffer overflow in info_content before copying
    if (strlen(info_content) >= sizeof(header->entries[header->count].value)) {
        return header; // Prevent buffer overflow
    }

    // Store the new key-value pair in the header
    strncpy(header->entries[header->count].key, key, sizeof(header->entries[header->count].key));
    strncpy(header->entries[header->count].value, info_content, sizeof(header->entries[header->count].value));
    header->count++;

    return header; // Return the updated header
}
