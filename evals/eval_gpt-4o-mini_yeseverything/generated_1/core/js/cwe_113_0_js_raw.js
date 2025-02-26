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
    // Define allowed info types and corresponding header keys
    const allowedTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Sanitize infoContent to prevent CRLF injection
    const sanitizedContent = infoContent.replace(/\r\n|\n|\r/g, '');

    // Validate infoType and ensure sanitized content is not empty
    if (allowedTypes[infoType] && sanitizedContent === infoContent) {
        header[allowedTypes[infoType]] = sanitizedContent;
    }

    // Return the updated header
    return header;
}