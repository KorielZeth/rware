#include "toprequest.h"


int toprequest() {

    HINTERNET  hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    BOOL  bResults = FALSE;

    // Use WinHttpOpen to obtain an HINTERNET handle.

    hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession)
        hConnect = WinHttpConnect(hSession, L"domain.com", INTERNET_DEFAULT_HTTPS_PORT, 0);

    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

    if (hRequest)
        bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);


    return 0;
}

//non functional DNS query that i'll fix later
/*int dnsrequ() {

    DNS_STATUS Status = NULL;
    if (Status)
        DnsQuery_W(L"domain.com", DNS_TYPE_PTR, DNS_QUERY_STANDARD, NULL, NULL, NULL);


    return 0;
}*/