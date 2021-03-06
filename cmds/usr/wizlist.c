#include <ansi.h>
inherit F_CLEAN_UP;
string query_time(int time);

string *mission;  

int level(mixed, mixed);
string get_mission( string );
void create() { seteuid( getuid() ); }

int main(object me)
{
   string *list, wizlv, msg, str, str1, att, spc;
   int n, adm_n, arc_n, wiz_n, apr_n, imm_n, on_ln;
   object ob, body;

   spc = "                                            ";
   mission = explode(read_file("/adm/etc/wizmission"), "\n");
   list = sort_array(SECURITY_D->query_wizlist(), (: level :));

   str = HIW"★ "BLINK+HIR+MUD_NAME+"管理组成员. \n"NOR;
   str +=HIC"≡≡"HIB"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIC
   "≡≡\n"NOR;
   str +=WHT"  系统级别       ID       名字       状       态           工作动向说明 \n"NOR;
   str +=HIB"────────────────────────────────────────\n"NOR;

   for(int i=0; i<sizeof(list); i++)
   {      
      wizlv = SECURITY_D->get_status(list[i]);      

      switch (wizlv) 
      { 

         case "(admin)":      msg =HIW"【天神总管】" NOR;
                              n = adm_n++;break;
         case "(arch)":       msg =HIR"【大 巫 师】" NOR;
                              n = arc_n++;break;
         case "(wizard)":     msg =HIG"【巫    师】" NOR;
                              n = wiz_n++;break;
         case "(apprentice)": msg =HIC"【实习巫师】" NOR;
                              n = apr_n++;break;
         case "(immortal)":   msg =HIM"【初级巫师】" NOR;
                              n = imm_n++;break;        
      }

     if(n == 0) str += msg + HIW"--- "NOR;        
        else   str += HIW"             |_ "NOR;    

     ob = new(LOGIN_OB);
     ob->set("id", list[i]);
     ob->restore();     

     if (objectp(body = find_player(list[i])) ) 
        on_ln = 1;
     else 
     {     
        on_ln = 0; 
        body = LOGIN_D->make_body(ob);
        body->restore();              
     }         
  
     if ( on_ln == 0 || ! me->visible(body) ) 
     {
        att = "离线：" + query_time(ob->query("last_on")) + NOR;
     }
     else 
     { 
        if (!interactive(body)) 
            att=HIR"在线：断线中．．．    "NOR;
        else        
        if ( (query_idle(body)) > 300 ) 
            att=sprintf(HIM"在线：已发呆%5d 秒钟"NOR,query_idle(body))+NOR;
        else 
            att=HIG"在线："+query_time(body->query_temp("scan_time"))+NOR;       
     }

     str1 = sprintf(YEL"%-9s%-10s"NOR "%-2s"NOR, 
                    list[i], body->name(), att); 
  
     str1 += spc[0..(42 - sizeof(filter_color(str1)))] + get_mission(list[i]) + "\n";
     str += str1;
     destruct(ob); 
     if ( on_ln == 0 ) destruct(body); 
   }

  str +=HIC"≡≡"HIB"━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIY"中华英雄巫师组"NOR HIB
  "━━"HIC"≡≡\n"NOR;
  str += HIR"★ "HIW+MUD_NAME+HIC" 目前共有 " + HIR + chinese_number(sizeof(list)) +HIC+ " 位维护管理巫师。\n"NOR;


   me->start_more(str); 
   return 1;
}
   
int level(mixed ob1, mixed ob2)
{
        if (wiz_level(ob1) != wiz_level(ob2))
                return wiz_level(ob2) - wiz_level(ob1);
        return ob1 < ob2?-1:1;
}

string get_mission( string wiz)
{
        int i;
        string wname,wmin;
        for(i=0; i<sizeof(mission); i++) 
        {
           if(sscanf(mission[i], "%s %s",
                        wname, wmin)!=2 ) continue;
                if(wname==wiz) return wmin;
        }
       return CYN" [任务未定]"NOR;
}

string query_time(int time)
{
        string msg;
        int day, hour, min;
        
        time=time()-time;
        
        msg="";
        day=time/86400;
        hour=time%86400/3600;
        min=time/60%60;

        if(min<1)
                min=1;
        if(day)
                msg+=sprintf("%s天", chinese_number(day));
        if(day<10 && hour)
                msg+=sprintf("%s小时", chinese_number(hour));
        if(!day && hour<20 && min )
                msg+=sprintf("%s分", chinese_number(min));

        return msg;
}

int help(object me)
{
write(@HELP

指令格式 : wizlist

用途 : 列出目前本站巫师组成员系统级别以及当前工作分配状态。

HELP
     );
     return 1;
}

