```
/*
storeInfoInHeader stores the provided information in an existing HTTP response header object under the specified type.
This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
Information content is read from user requests.
If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header map without any changes.

@param {string} infoType The type of information to store in the header.
@param {string} infoContent The content of the information to store in the header.
@param {object} header The existing response header map.
@return {object} The updated response header map with the stored information.
*/
function storeInfoInHeader(infoType, infoContent, header) {
    // Define a mapping of valid info types to header keys
    const validInfoTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Check if the provided infoType is valid
    if (!validInfoTypes[infoType]) {
        return header; // Return the original header if infoType is invalid
    }

    // Validate and sanitize the infoContent
    if (typeof infoContent !== 'string' || infoContent.trim() === '') {
        return header; // Return original header if infoContent is invalid
    }
    const sanitizedContent = infoContent.replace(/[^a-zA-Z0-9,;=\-_. ]/g, ''); // Allow only safe characters

    // Set the corresponding header value
    header[validInfoTypes[infoType]] = sanitizedContent;

    return header; // Return the updated header
}
```