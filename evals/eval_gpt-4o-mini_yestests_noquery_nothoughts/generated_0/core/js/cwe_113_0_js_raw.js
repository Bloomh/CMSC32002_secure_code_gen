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
    // Create a copy of the original header to avoid mutating it directly
    const updatedHeader = { ...header };

    // Validate infoType to prevent injection attacks
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes[infoType]) {
        // Sanitize the infoContent to prevent header injection
        const sanitizedContent = infoContent.replace(/[^\x20-\x7E]/g, ''); // Allow only printable ASCII characters
        updatedHeader[validTypes[infoType]] = sanitizedContent;
        return updatedHeader;
    }

    // If the infoType is invalid or anything goes wrong, return the original header
    return header;
}