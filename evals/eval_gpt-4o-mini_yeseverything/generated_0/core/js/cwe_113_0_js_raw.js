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
    if (validInfoTypes[infoType]) {
        // Sanitize infoContent to prevent header injection
        const sanitizedContent = infoContent.replace(/[\r\n]+/g, ''); // Remove CRLF characters

        // Check if sanitized content is empty
        if (sanitizedContent === '' || sanitizedContent.trim() === '') {
            return header; // Return original header if sanitized content is empty
        }

        // Update the header with the sanitized content
        header[validInfoTypes[infoType]] = sanitizedContent;
        return header;
    }

    // If the infoType is not valid or any other issue occurs, return the original header
    return header;
}
```