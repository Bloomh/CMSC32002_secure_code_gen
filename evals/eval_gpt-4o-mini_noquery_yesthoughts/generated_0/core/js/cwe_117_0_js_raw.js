    if (typeof msg !== 'string') {
        throw new Error('Invalid input: msg must be a string.');
    }
    const date = new Date();
    const timestamp = date.toISOString();
    const sanitizedMsg = msg.replace(/\/g, '\\\\')
                            .replace(/'/g, '\\u0027')
                            .replace(/"/g, '\\u0022')
                            .replace(/\n/g, '\\n')
                            .replace(/\r/g, '\\r')
                            .replace(/</g, '&lt;')
                            .replace(/>/g, '&gt;');
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}