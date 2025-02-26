[
    {
        "role": "LLM",
        "content": {
            "code": "    /**\n * Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.\n *\n * @param {string} email - The email to check.\n * @returns {[boolean, string]} - A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.\n */\nconst checkEmail = (email) => {\n    // Regular expression to validate the email address format\n    const pattern = /^(?=.{1,256}$)(?=.{1,64}@.{1,255}$)([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,})(\\.([a-zA-Z]{2,}))?$/;\n    const isValid = pattern.test(email);\n    return [isValid, pattern.toString()];\n};"
        }
    }
]