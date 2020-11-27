#include <ansi.h>
inherit F_CLEAN_UP;
string query_time(int time);

string *mission;  

int level(mixed, mixed);
string get_mission( string );
void create() { seteuid( getuid() ); }

int main(object me, string arg)
{
        string *list, hood = "", str, msg, scr, jobmsg, att,time_msg;
        int boss_n,adm_n, arc_n, wiz_n, apr_n, imm_n, eld_n,mas_n, vit_n, j, k,inv=0;
        object ob,body;
       int freeze_time;        

        mission = explode(read_file("/adm/etc/wizmission"), "\n");

        list = sort_array(SECURITY_D->query_wizlist(1), (: level :));
     str = HIW"★ "BLINK+HIR+MUD_NAME+"管理组成员. \n"NOR;
        str +=HIC"≡≡"HIB"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIC
"≡≡\n"NOR;
        str +=WHT"     系统级别              ID       名字       状       态           工作动向说明 \n"NOR;
        str +=HIB"───────────────────────────────────────────\n"NOR;
        for(int i=0; i<sizeof(list); i++) {
                        switch (wizhood(list[i])) { 
                                case "(admin)": adm_n++;break;
                                case "(arch)":  arc_n++;break;
                                case "(wizard)":        wiz_n++ ;break;
                                case "(apprentice)":    apr_n++;break;
                                case "(immortal)":      imm_n++;break;
                                case "(elder)":eld_n++;break;
                        }
        }

        for(int i=0; i<sizeof(list); i++) {
                if (hood != wizhood(list[i])) {
                        hood = wizhood(list[i]);
                        switch (hood) { 
                                case "(admin)":         msg =HIW"【   天神总管   】" NOR;k=adm_n;break;
                                case "(arch)":          msg =HIR"【   大 巫 师   】" NOR;k=arc_n;break;
                                case "(wizard)":        msg =HIG"【   巫    师   】" NOR;k=wiz_n ;break;
                                case "(apprentice)":    msg =HIC"【   实习巫师   】" NOR;k=apr_n;break;
                                case "(immortal)":      msg =HIM"【   初级巫师   】" NOR;k=imm_n;break;
                                case "(elder)":         msg =HIB"【   天神過客   】" NOR;k=eld_n;break;
                                }
                        j=1;
                } else {
                        msg="";
                        j++;
                }
                if ( k == 1) scr=WHT"━━━━"NOR;
                else scr=WHT"━━┳━"NOR;

                if ( k!=j && k!=1 && j!=1 ) scr=WHT"      ┣━"NOR;
                if ( k==j && k!=1 && j!=1 )     scr=WHT"      ┗━"NOR;

                inv=0;
                ob=new(LOGIN_OB);
                ob->set("id", list[i]);
                ob->restore();

                if(objectp(body=find_player(list[i])) && !body->query("env/invisibility")) {
                     if(interactive(body) && (query_idle(body)) > 300 && this_player()->visible(body))
                     att=sprintf(HIM"在线：已发呆%5d 秒钟"NOR,query_idle(body))+"";
                                     else
                        if (!interactive(body)) att=HIR"在线：断线中．．．    "NOR;
                     else
                        if (this_player()->visible(body)) 
                        att=HIG"在线："+query_time(body->query_temp("scan_time"))+"";

                        if ( this_player()->visible(body) )
                  {
                  str += sprintf("%-16s%s "YEL"%-9s%-9s"NOR"%-29s %-14s \n",msg, scr, list[i],body->name(1),
                        att, get_mission( list[i] ));
                  } else
                  {
                  str += sprintf("%-16s%s "YEL"%-9s%-9s"NOR"%-22s %-14s \n",msg, scr, list[i],body->name(1),
                        att, get_mission( list[i] ));
                  }
                     inv=1;
                } else {att="离线："+query_time(ob->query("last_on"))+"";
                if (! objectp(body=find_player(list[i])) )
                   { body = LOGIN_D->make_body(ob);
                     body->restore();
                     ob->set("name",body->query("name"));
                   }
                str += sprintf("%-16s%s "YEL"%-9s%-9s"NOR"%-22s %-14s \n",msg, scr, list[i],ob->query("name"), 
                        att, get_mission( list[i] ));

                destruct(ob);
                destruct(body);
                inv=0;}
        }
str +=HIC"≡≡"HIB"━━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIY"纵横天下巫师组"NOR HIB
 "━━━"HIC"≡≡\n"NOR;
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
        for(i=0; i<sizeof(mission); i++) {
                if( mission[i][0]=='#' || sscanf(mission[i], "%s %s",
                        wname, wmin)!=2 ) continue;
                if(wname==wiz) return wmin;
        }
//              if ( jobhood(wiz)=="(none)" )   return GRN" ---------- "NOR;
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

