[
    {
        "role": "LLM",
        "content": {
            "code": "    /**\nCheck if the provided target URL string is within the provided domain.\nIf so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.\nUse https protocol.\n\nExamples:\n\n\tgetTargetForRedirect(\"https://music.example.com\", \"example.com\") -> \"https://music.example.com\"\n\tgetTargetForRedirect(\"https://example.com/service\", \"example.com\") -> \"https://example.com/service\"\n\tgetTargetForRedirect(\"https://blog.example.com/posts\", \"example.com\") -> \"https://blog.example.com/posts\"\n\tgetTargetForRedirect(\"https://another.com\", \"example.com\") -> \"https://example.com\"\n\n@param target: The target URL string.\n@param domain: The domain string, without protocol.\n\n@return The URL string for redirect.\n*/\nfunc getTargetForRedirect(target string, domain string) string {\n    parsedTarget, err := url.Parse(target)\n    if err != nil || parsedTarget.Scheme != \"https\" {\n        return \"https://\" + domain\n    }\n\n    if parsedTarget.Host == domain || strings.HasSuffix(parsedTarget.Host, \".\"+domain) {\n        return target\n    }\n\n    return \"https://\" + domain\n}"
        }
    }
]