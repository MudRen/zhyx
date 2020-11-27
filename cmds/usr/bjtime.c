// [1;31m´ËÎÄ¼ş½ûÖ¹ËæÒâÒÆ¶¯ºÍ¸ü¸Ä[0m
// CMDS  /cmds/usr/bjtime.c
// Created by waiwai@ 2000/11/13
// Modified by waiwai@ 2000/12/15
// 7 µÄ¸ñÊ½Ö÷ÒªÓÃÓÚÁôÑÔ°å¼°ÏµÍ³µÄlog_time()
// 5 µÄÉèÖÃÖ÷ÒªÓÃÓÚlogind.cµ÷ÓÃ
// 10 µÄÉèÖÃÖ÷ÒªÓÃÓÚ»áÔ±ÆÚÏŞµÇ¼Ç
// 1 µÄÉèÖÃÖ÷ÒªÓÃÓÚshutdown£¬rebootÊ±¼äÏÔÊ¾

#include <ansi.h>

#include <localtime.h>
inherit F_CLEAN_UP;

/*
 * if like chinese's time show ,can list here type to return
 * type = 5 , return string like ¶şÁãÁã¶şÄêÈıÔÂ¶şÊ®°ËÈÕ ÉÏÎç Ê®Ò»µãÈıÊ®°Ë·ÖÊ®ËÄÃë ĞÇÆÚËÄ
 * type = 2 , return string like ¶şÁãÁãÒ»ÄêÈıÔÂ¶şÊ®°ËÈÕ ÉÏÎç Ê®Ò»µãÈıÊ®Æß·Ö¶şÊ®Ãë
 * type = 3 , return string like ÈıÔÂ¶şÊ®°ËÈÕ ÉÏÎç Ê®Ò»µãÈıÊ®Æß·ÖËÄÊ®ËÄÃë ĞÇÆÚËÄ
 * type = 4 , return string like ÈıÔÂ¶şÊ®°ËÈÕ ÉÏÎç Ê®Ò»µãÈıÊ®°Ë·Ö¶şÃë
 * type = 1 , return string like 1998Äê10ÔÂ31ÈÕ ÉÏÎç 11µã20·Ö23Ãë
 * type = 6 , return string like 3ÔÂ28ÈÕ11µã38·Ö
 * type = 7 , return string like 2001/03/28 11:38
 * type = 8 , return string like 2001Äê03ÔÂ28ÈÕ 11:39
 * type = 9 , return string like 3ÔÂ28ÈÕ
 * type = 10 , return string like 2001Äê3ÔÂ28ÈÕ
 * if not define type, default return string like define type =1
 * if need conversion time not now() can define string get_time
 * but get_time must like "Sun May  3 00:52:12 1998"
 * example chinese_time(1,ctime(time())
*/

string chinese_time(int type,string get_time)
{
        string e_time, week, month, year,time99;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
		"Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());

        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);

        c_month = chinese_number(member_array(month, month_name) + 1);
      
        if(week=="Mon") c_week=YEL" ĞÇÆÚÒ»"; 
        else if(week=="Tue") c_week=YEL" ĞÇÆÚ¶ş";  
        else if(week=="Wed") c_week=YEL" ĞÇÆÚÈı";      
        else if(week=="Thu") c_week=YEL" ĞÇÆÚËÄ";        
        else if(week=="Fri") c_week=YEL" ĞÇÆÚÎå";      
        else if(week=="Sat") c_week=RED" ĞÇÆÚÁù";      
        else if(week=="Sun") c_week=RED" ĞÇÆÚÌì";


	  if(hour<6 && hour>0)               time99=MAG" Áè³¿ "NOR;  
	     else if(hour<8 && hour >=6)     time99=YEL" ÔçÉÏ "NOR;    
	     else if(hour<12 && hour>=8)     time99=YEL" ÉÏÎç "NOR;   
	     else if(hour==12)               time99=YEL" ÖĞÎç "NOR;     
	     else if(hour<19 && hour>12)     time99=YEL" ÏÂÎç "NOR;    
	     else if(hour<24 && hour>=19)    time99=BLU" ÍíÉÏ "NOR;    
	     else if (hour==24 || hour==0)   time99=BLU" ×ÓÒ¹ "NOR;   
    
	  if(hour>12) {               
	    if(hour==13)            hour=1;      
	    else    if(hour==14)            hour=2;     
	    else    if(hour==15)            hour=3;    
	    else    if(hour==16)            hour=4;    
	    else    if(hour==17)            hour=5;     
	    else    if(hour==18)            hour=6;      
	    else    if(hour==19)            hour=7;      
	    else    if(hour==20)            hour=8;    
	    else    if(hour==21)            hour=9;   
	    else    if(hour==22)            hour=10;     
	    else    if(hour==23)            hour=11;    
	    else    if(hour==24)            hour=0;    
	     }

        c_year  = sprintf("%s%s%s%s",
                         chinese_number(year[0]-48),
                         chinese_number(year[1]-48),
                         chinese_number(year[2]-48),
                         chinese_number(year[3]-48));

        c_year = c_year + "Äê";
        c_month  = c_month + "ÔÂ";

        c_time = chinese_number(day) + "ÈÕ";
        c_time += time99;
        c_time += chinese_number(hour) + "µã";
        c_time += chinese_number(minute) + "·Ö";
        c_time += chinese_number(second) + "Ãë";

        if (type) {
                switch( type ) {
                        case 5: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 1: return NOR YEL+year+"Äê"+(member_array(month, month_name) + 1)+
				"ÔÂ"+day+"ÈÕ"+time99+NOR YEL+hour+"µã"+minute+"·Ö"+second+"Ãë"NOR;
                        case 6: return (member_array(month, month_name) + 1)+
				"ÔÂ"+day+"ÈÕ"+hour+"µã"+minute+"·Ö";
                        case 7: 
                                return replace_string(sprintf("%s/%2d/%2d",
 year, (member_array(month, month_name) + 1), day), " ", "0") 
                                       + " " + e_time[11..15]; 
                        case 8: 
                                return replace_string(sprintf("%sÄê%2dÔÂ%2dÈÕ",
 year, (member_array(month, month_name) + 1), day), " ", "0") 
                                       + " " + e_time[11..15]; 
                        case 9: return (member_array(month, month_name) + 1)+
				"ÔÂ"+day+"ÈÕ";

                        case 10: 
                                return replace_string(sprintf("%s%2d%2d",
 year, (member_array(month, month_name) + 1), day), " ", "0"); 

                        default: return c_year+c_month+c_time+c_week;
                        }
                }
        return c_year+c_month+c_time+c_week;
}

int main(object me, string arg)
{
	int i;

	if(!arg||sscanf(arg,"%d",i)!=1)
		write("ÏÖÔÚ±ê×¼±±¾©Ê±¼ä£º" + chinese_time(5,(string)localtime(time())) + "\n"NOR);
	else
		write(NOR"ÏÖÔÚ±ê×¼±±¾©Ê±¼ä£º" + chinese_time(i,(string)localtime(time())) + "\n"NOR);
	return 1;
}

int help(object me)
{
     write(@HELP

Ö¸Áî¸ñÊ½: bjtime

Õâ¸öÖ¸ÁîÈÃÄãÖªµÀÏÖÔÚÏÖÊµÖĞµÄÊµ¼ÊÊ±¼ä¡£
¿ÉÒÔ´ø²ÎÊı1-10ÒÔ²»Í¬µÄ¸ñÊ½ÏÔÊ¾¡£
Ä¬ÈÏÏÔÊ¾Îªbjtime 5

ÑùÀı£º
[bjtime  1]£º2003Äê2ÔÂ24ÈÕ ÍíÉÏ 7µã17·Ö11Ãë
[bjtime  2]£º¶şÁãÁãÈıÄê¶şÔÂ¶şÊ®ËÄÈÕ ÍíÉÏ ÆßµãÊ®Æß·ÖÈıÊ®¶şÃë
[bjtime  3]£º¶şÔÂ¶şÊ®ËÄÈÕ ÍíÉÏ ÆßµãÊ®Æß·ÖËÄÊ®ÈıÃë ĞÇÆÚÒ»
[bjtime  4]£º¶şÔÂ¶şÊ®ËÄÈÕ ÍíÉÏ ÆßµãÊ®Æß·ÖÎåÊ®ÈıÃë
[bjtime  5]£º¶şÁãÁãÈıÄê¶şÔÂ¶şÊ®ËÄÈÕ ÍíÉÏ ÆßµãÊ®°Ë·ÖÎåÃë ĞÇÆÚÒ»
[bjtime  6]£º2ÔÂ24ÈÕ7µã18·Ö
[bjtime  7]£º2003/02/24 19:18
[bjtime  8]£º2003Äê02ÔÂ24ÈÕ 19:18
[bjtime  9]£º2ÔÂ24ÈÕ
[bjtime 10]£º20030224

HELP
    );
    return 1;
}

