Action()
{
	int vuserid;
	// comment
	int scid;
	char groupName[256];
	char* p = groupName;

	lr_whoami (&vuserid,&p,&scid);

	lr_log_message("vuserid=%d groupName=%s scid=%d",vuserid,groupName,scid);

	lr_log_message("P_Tab1='%s'",lr_eval_string("{P_Tab1}"));
	lr_log_message("P_Tab2='%s'",lr_eval_string("{P_Tab2}"));

	// Save the value 3 to parameter "Sum"
	web_js_run("Code= myFunc(1, 2);",
		"ResultParam=Sum",
		"ActionStep=NO",					
		SOURCES,
		"Code= var myFunc = function(x,y) { return x+y; }", ENDITEM,
		LAST);

		{
			char temp[10];

			itoa(10,temp,10);
			lr_log_message("temp=%s",temp);
		}

	// Simple string manipulation
	web_js_run("Code= myFunc('abc', 'def');",
		// myFunc was defined in the previous step.
		// No need to redefine, unless web_js_reset() was called.
		"ResultParam=ConcatStr",
		LAST);
	
	// Running autorun.js
	web_js_run(
		"File=autorun.js",
		LAST);

	// 1) Loading code.js
	// 2) Calling function F(a,b), which is defined in code.js
	// 3) Writing the return value of the call to F(a,b) to param1
	web_js_run(
		"Code=F(a , b)",
		"ResultParam=param1",
		SOURCES,
		"File=code.js", ENDITEM,
		LAST);
	
    lr_save_string("HELLO WORLD","Test");
    
	web_js_run("Code=LR.getParam('Test');",
			"ResultParam=param2",
		   LAST);
		
    web_add_auto_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36");

    web_add_cookie ("client_id=China127B; path=/; expires=Wednesday, 09–Nov–2001 23:12:40 GMT; domain=www.cnn.com");

    web_reg_save_param("C_Pre",
        "LB=<email>",
        "RB=</email>",
        "ORD=ALL",
        LAST);

	web_reg_save_param_ex(
		"ParamName=C_Regex", 
		"LB/RE=<[eE]mail>",
		"RB/RE=</[eE]mail>",
		"Ordinal=1",
		"SaveLen=-1",
		SEARCH_FILTERS,
			"Scope=body",
		LAST);

    lr_start_transaction("portal_action");

	addDynatraceHeaderTest("TSN=portal_action;PC=apps_inventory");
    web_custom_request("apps_inventory",
		"URL=http://localhost:4545/customers/123?test3",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		"Body=this is a"
        "very long"
        "body body {Test} "
        "body P_Custom='{P_Custom}' "
		"P_Date='{P_Date}' "
		"P_LG='{P_LG}' "
		"P_VuserID='{P_VuserID}' "
		"P_Rand='{P_Rand}' "
		"P_Iter='{P_Iter}' "
		"P_Unique='{P_Unique}' "
		"P_Second='{P_Second}' ",
		LAST);
	
	lr_end_transaction("portal_action",LR_AUTO);
	
	lr_think_time(3);

	lr_log_message("This is a lr_log_message");

    // web_reg_find("Text=Copyright The Closure Library Authors", LAST );
    
    // web_add_header("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
    // web_add_header("Accept-Encoding","gzip, deflate, br");
    // web_add_header("Upgrade-Insecure-Requests","1");

    // lr_start_transaction("https_test");

    // web_custom_request("https_test_req",
	// 	"URL=https://www.google.ca/",
	// 	"Method=GET",
	// 	"TargetFrame=",
	// 	"Resource=0",
	// 	"Referer=",
	// 	LAST);
	
	// lr_end_transaction("https_test",LR_AUTO);
	
	// lr_think_time(3);

    //web_reg_find("Text=THIS WONT BE FOUND", LAST );
    
    lr_start_transaction("redirect_test");

    web_custom_request("redirect_test_req",
		"URL=http://localhost:4545/customers/123",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
        "Body=test",
		LAST);

	lr_end_transaction("redirect_test",LR_AUTO);
	
	lr_think_time(3);

	web_set_option("MaxRedirectionDepth","0",LAST);
    
    lr_start_transaction("stopredirect_test");

    web_custom_request("stopredirect_test_req",
		"URL=http://localhost:4545/customers/123",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
        "Body=test",
		LAST);

	lr_end_transaction("stopredirect_test",LR_AUTO);
	
	web_set_option("MaxRedirectionDepth","20",LAST);

	lr_think_time(3);
    
    lr_start_transaction("concurrent_group_test");

    web_concurrent_start("g1",NULL);

    web_custom_request("c1",
		"URL=http://localhost:4545/customers/123?c1",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);

    web_custom_request("c2",
		"URL=http://localhost:4545/customers/123?c2",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);

    web_custom_request("c3",
		"URL=http://localhost:4545/customers/123?c3",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);
        
    web_concurrent_end(NULL);
	
	lr_end_transaction("concurrent_group_test",LR_AUTO);
	
	lr_think_time(3);

    lr_start_transaction("web_submit_data");

    web_submit_data("default.aspx",
        "Action=http://localhost:4545/customers/123?test4",
        "Method=POST",
        "TargetFrame=",
        "RecContentType=text/html",
        "Referer=http://lazarus/flightnet/",
        "Snapshot=t7.inf",
        "Mode=HTML",
        ITEMDATA,
        "Name=grpType", "Value=radRoundtrip", ENDITEM,
        "Name=lstDepartingCity", "Value=DEN", ENDITEM,
        "Name=lstDestinationCity", "Value=LAX", ENDITEM,
        "Name=txtDepartureDate", "Value=8/19/2003", ENDITEM,
        "Name=txtReturnDate", "Value=8/19/2003", ENDITEM,
        "Name=txtQuantity", "Value=1", ENDITEM,
        "Name=radClass", "Value=1", ENDITEM,
        "Name=radSeat", "Value=1", ENDITEM,
        "Name=btnAvailableFlights", "Value=Next >", ENDITEM,
        LAST );

	lr_end_transaction("web_submit_data",LR_AUTO);
	
	lr_think_time(3);

    lr_start_transaction("html_mode");

	web_url("html_mode",
		"URL=http://localhost:4545/html/mode",
		"Mode=HTML",
		LAST);

	lr_end_transaction("html_mode",LR_AUTO);
	
	lr_think_time(3);

	// web_reg_async_attributes("ID=Push_0",
	// 	"Pattern=Push",
	// 	"URL=http://localhost:4545/customers/123",
	// 	"PollIntervalMs=500",
	// 	"RequestCB=Push_0_RequestCB",
	// 	"ResponseHeadersCB=Push_0_ResponseHeadersCB",
	// 	"ResponseBodyBufferCB=Push_0_ResponseBodyBufferCB",
	// 	"ResponseCB=Push_0_ResponseCB",
	// 	LAST);

	// web_url("async_req",
	// 	"URL=http://localhost:4545/customers/123",
	// 	LAST);

	// lr_think_time(3);

	// web_stop_async("ID=Push_0",
	// 	LAST);

}

// Does adding comments after the last } break the conversion
/***
 * Let's see!!
 * 
 * 
 * !!!
*/


/*

    web_custom_request("redirect_test_req",
		"URL=http://localhost:4545/customers/123",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
        "Body=test",
		LAST);

	lr_end_transaction("redirect_test",LR_AUTO);
	
	lr_think_time(3);

	web_set_option("MaxRedirectionDepth","0",LAST);
    
    lr_start_transaction("stopredirect_test");

    web_custom_request("stopredirect_test_req",
		"URL=http://localhost:4545/customers/123",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
        "Body=test",
		LAST);

	lr_end_transaction("stopredirect_test",LR_AUTO);
	
	web_set_option("MaxRedirectionDepth","20",LAST);

	lr_think_time(3);
    
    lr_start_transaction("concurrent_group_test");

    web_concurrent_start("g1",NULL);

    web_custom_request("c1",
		"URL=http://localhost:4545/customers/123?c1",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);

    web_custom_request("c2",
		"URL=http://localhost:4545/customers/123?c2",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);

    web_custom_request("c3",
		"URL=http://localhost:4545/customers/123?c3",
		"Method=GET",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);
        
    web_concurrent_end(NULL);
	
	lr_end_transaction("concurrent_group_test",LR_AUTO);
	
	lr_think_time(3);

    lr_start_transaction("web_submit_data");

    web_submit_data("default.aspx",
        "Action=http://localhost:4545/customers/123?test4",
        "Method=POST",
        "TargetFrame=",
        "RecContentType=text/html",
        "Referer=http://lazarus/flightnet/",
        "Snapshot=t7.inf",
        "Mode=HTML",
        ITEMDATA,
        "Name=grpType", "Value=radRoundtrip", ENDITEM,
        "Name=lstDepartingCity", "Value=DEN", ENDITEM,
        "Name=lstDestinationCity", "Value=LAX", ENDITEM,
        "Name=txtDepartureDate", "Value=8/19/2003", ENDITEM,
        "Name=txtReturnDate", "Value=8/19/2003", ENDITEM,
        "Name=txtQuantity", "Value=1", ENDITEM,
        "Name=radClass", "Value=1", ENDITEM,
        "Name=radSeat", "Value=1", ENDITEM,
        "Name=btnAvailableFlights", "Value=Next >", ENDITEM,
        LAST );

	lr_end_transaction("web_submit_data",LR_AUTO);
	
	lr_think_time(3);

    lr_start_transaction("html_mode");

	web_url("html_mode",
		"URL=http://localhost:4545/html/mode",
		"Mode=HTML",
		LAST);

	lr_end_transaction("html_mode",LR_AUTO);
	
	lr_think_time(3);


*/