    try {
        const url = new URL(apiUrl);
        if (url.protocol !== 'https:') {
            return null;
        }
        if (typeof userId !== 'string' || userId.trim() === '') {
            return null;
        }
        return `${url.toString()}/${encodeURIComponent(userId)}`;
    } catch (e) {
        return null;
    }