//Automatically generated file for implementing async callback functions.
//You may modify the added callback implementations or add new ones.
//Async callback functions may be registered in web_reg_async_attributes steps.
int Push_0_RequestCB()
{
	lr_log_message("Push_0_RequestCB");
	//enter your implementation for RequestCB() here

	//call web_util_request_set_url() here to modify request url:
	web_util_set_request_url("http://localhost:4545/customers/123");

	//call web_util_set_request_body() here to modify request body:
	// web_util_set_request_body("<request body>");
	//call web_util_set_request_header() here to set request header:
	// web_util_set_request_header("<header_name>", "<header_value>");

	return WEB_ASYNC_CB_RC_OK;
}

int Push_0_ResponseHeadersCB(
	int		aHttpStatusCode,
	const char *	aAccumulatedHeadersStr,
	int		aAccumulatedHeadersLen)
{
	//Enter your implementation for ResponseHeadersCB() here.
	lr_log_message("Push_0_ResponseHeadersCB");

	return WEB_ASYNC_CB_RC_OK;
}

int Push_0_ResponseBodyBufferCB(
	const char *    aLastBufferStr,
	int             aLastBufferLen,
	const char *    aAccumulatedStr,
	int             aHttpStatusCode)
{
	//enter your implementation for ResponseBodyBufferCB() here
	lr_log_message("Push_0_ResponseBodyBufferCB");

	return WEB_ASYNC_CB_RC_OK;
}

int Push_0_ResponseCB(
	const char *    aResponseHeadersStr,
	int             aResponseHeadersLen,
	const char *    aResponseBodyStr,
	int             aResponseBodyLen,
	int             aHttpStatusCode)
{
	//enter your implementation for ResponseCB() here
	lr_log_message("Push_0_ResponseCB");

	return WEB_ASYNC_CB_RC_OK;
}
