#include "HttpRequest.h"
#include "TimeUtils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <regex>
#include <iostream>
#include <boost/regex.hpp>
#include <pcre.h>

const char *data =
        "GET /gallery/album/flowers%202016/1?album-view=3 HTTP/1.1\r\n"
        "Host: 127.0.0.1:7000\r\n"
        "User-Agent: Mozilla Firefox\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml\r\n"
        "Accept-Language: en-US,en\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Connection: keep-alive\r\n"
        "If-Modified-Since: Mon, 26 Sep 2016 10:15:30 GMT\r\n"
        "Cache-Control: max-age=0\r\n\r\n";

// repeated capture group (for headers). std stores only last capture. boost has a flag to store all captures.
const char * const regexStringFull = "^(GET|POST)\\s+([^ ]+)\\s+HTTP[^\r\n]+\r\n(([^:]+):\\s+([^\r\n]+)\r\n)+\r\n$";
const char * const regexStringHeader = "([^:\r\n]+):\\s+([^\r\n]+)\r\n";

struct HttpRequestData {
    int urlStart, urlLength;

    struct Field
    {
        int start = 0;
        int length = 0;
    };

    struct Header
    {
        Field key;
        Field value;
    };

    std::vector<Header> headers;
};


std::regex rexFull(regexStringFull);
std::regex rexHeader(regexStringHeader);

boost::regex rexFullBoost(regexStringFull);
boost::regex rexHeaderBoost(regexStringHeader);

bool parseHttpRequestStdRegex(const char *data, HttpRequestData &rq)
{
    rq.headers.clear();

    std::cmatch match;

    if (std::regex_search(data, match, rexFull))
    {
        rq.urlStart = match[2].first - data;
        rq.urlLength = match[2].length();
    }
    else
    {
        return false;
    }

    const char *text = data;

    while (std::regex_search(text, match, rexHeader))
    {
        HttpRequestData::Header h;
        h.key.start = match[1].first - data;
        h.key.length = match[1].length();

        h.value.start = match[2].first - data;
        h.value.length = match[2].length();

        rq.headers.push_back(h);

        text = match.suffix().first;
    }

    return true;
}

bool parseHttpRequestBoostRegex(const char *data, HttpRequestData &rq)
{
    rq.headers.clear();

    boost::cmatch match;

    if (boost::regex_search(data, match, rexFullBoost))
    {
        rq.urlStart = match[2].first - data;
        rq.urlLength = match[2].length();
    }
    else
    {
        return false;
    }

    const char *text = data;

    while (boost::regex_search(text, match, rexHeaderBoost))
    {
        HttpRequestData::Header h;
        h.key.start = match[1].first - data;
        h.key.length = match[1].length();

        h.value.start = match[2].first - data;
        h.value.length = match[2].length();

        rq.headers.push_back(h);

        text = match.suffix().first;
    }

    return true;
}

pcre *reFull = nullptr;
pcre_extra *reFullExtra = nullptr;
pcre *reHeader = nullptr;
pcre_extra *reHeaderExtra = nullptr;

int initPcre()
{
    const char *error;
    int errorOffset;

    reFull = pcre_compile (regexStringFull,
                           PCRE_MULTILINE,
                           &error,
                           &errorOffset,
                           0);             // use default character tables
    if (!reFull)
    {
        printf("pcre_compile failed (offset: %d), %s\n", errorOffset, error);
        return -1;
    }

    reFullExtra = pcre_study(reFull, 0, &error);

    reHeader = pcre_compile (regexStringHeader,
                             PCRE_MULTILINE,
                             &error,
                             &errorOffset,
                             0);             // use default character tables
    if (!reHeader)
    {
        printf("pcre_compile failed (offset: %d), %s\n", errorOffset, error);
        return -1;
    }

    reHeaderExtra = pcre_study(reHeader, 0, &error);

    return 0;
}

bool parseHttpRequestPcre(const char *data, HttpRequestData &rq)
{
    static int unused = initPcre();
    (void)unused;

    const char *text = data;

    int dataLength = strlen(data);

    const size_t OVEC_SIZE = 50;
    int ovector[OVEC_SIZE];

    int pcreExecRet = pcre_exec(reFull,
                                reFullExtra,
                                text,
                                dataLength,  // length of string
                                0,           // first index
                                0,           // options
                                ovector,
                                OVEC_SIZE);  // length of ovector

    if(pcreExecRet < 0)
    {
        printf("pcre_exec failed\n");
        return false;
    }

    rq.urlStart = ovector[4];
    rq.urlLength = ovector[5] - ovector[4];

    int offset = 0;


    while (offset < dataLength && (pcreExecRet = pcre_exec(reHeader, reHeaderExtra, data, dataLength, offset, 0, ovector, OVEC_SIZE)) >= 0)
    {
        HttpRequestData::Header h;
        h.key.start = ovector[2];
        h.key.length = ovector[3] - ovector[2];
        h.value.start = ovector[4];
        h.value.length = ovector[5] - ovector[4];

        rq.headers.push_back(h);

        offset = ovector[1];
    }

    return true;
}

void testHttpRequestStdRegex()
{
    HttpRequestData rq;
    parseHttpRequestStdRegex(data, rq);

    std::cout << "[" << std::string(data + rq.urlStart, rq.urlLength) << "]" << std::endl;
    for (auto &h : rq.headers)
    {
        std::cout << "{" << std::string(data + h.key.start, h.key.length) << "}" << std::endl;
    }
}

void testHttpRequestBoostRegex()
{
    HttpRequestData rq;
    parseHttpRequestBoostRegex(data, rq);

    std::cout << "[" << std::string(data + rq.urlStart, rq.urlLength) << "]" << std::endl;
    for (auto &h : rq.headers)
    {
        std::cout << "{" << std::string(data + h.key.start, h.key.length) << "}" << std::endl;
    }
}

void testHttpRequestPcre()
{
    HttpRequestData rq;
    parseHttpRequestPcre(data, rq);

    std::cout << "[" << std::string(data + rq.urlStart, rq.urlLength) << "]" << std::endl;
    for (auto &h : rq.headers)
    {
        std::cout << "{" << std::string(data + h.key.start, h.key.length) << "}:{" <<
            std::string(data + h.value.start, h.value.length) << "}" << std::endl;
    }
}


const int iterCount = 10000;

void testHttpRequestPerformance()
{
    int dataLen = strlen(data);

    HttpRequest request;

    unsigned long long int millisStart = getMilliseconds();

    for(int i = 0; i < iterCount; ++i)
    {
        if(request.parse(data, dataLen) != HttpRequest::ParseResult::finishOk)
        {
            printf("parse failed!\n");
            exit(-1);
        }
    }

    unsigned long long int millisDif = getMilliseconds() - millisStart;

    printf("performance test milliseconds: %llu\n", millisDif);
}

void testStdRegexPerformance()
{
    HttpRequestData rq;

    unsigned long long int millisStart = getMilliseconds();

    for(int i = 0; i < iterCount; ++i)
    {
        if(!parseHttpRequestStdRegex(data, rq))
        {
            printf("parse failed!\n");
            exit(-1);
        }
    }

    unsigned long long int millisDif = getMilliseconds() - millisStart;

    printf("std::regex performance test milliseconds: %llu\n", millisDif);

}

void testBoostRegexPerformance()
{
    HttpRequestData rq;

    unsigned long long int millisStart = getMilliseconds();

    for(int i = 0; i < iterCount; ++i)
    {
        if(!parseHttpRequestBoostRegex(data, rq))
        {
            printf("parse failed!\n");
            exit(-1);
        }
    }

    unsigned long long int millisDif = getMilliseconds() - millisStart;

    printf("boost::regex performance test milliseconds: %llu\n", millisDif);

}

void testPcreRegexPerformance()
{
    HttpRequestData rq;

    unsigned long long int millisStart = getMilliseconds();

    for(int i = 0; i < iterCount; ++i)
    {
        if(!parseHttpRequestPcre(data, rq))
        {
            printf("parse failed!\n");
            exit(-1);
        }
    }

    unsigned long long int millisDif = getMilliseconds() - millisStart;

    printf("pcre performance test milliseconds: %llu\n", millisDif);
}

