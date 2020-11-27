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
     str = HIW"�� "BLINK+HIR+MUD_NAME+"�������Ա. \n"NOR;
        str +=HIC"�ԡ�"HIB"����������������������������������������������������������������������������"HIC
"�ԡ�\n"NOR;
        str +=WHT"     ϵͳ����              ID       ����       ״       ̬           ��������˵�� \n"NOR;
        str +=HIB"��������������������������������������������������������������������������������������\n"NOR;
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
                                case "(admin)":         msg =HIW"��   �����ܹ�   ��" NOR;k=adm_n;break;
                                case "(arch)":          msg =HIR"��   �� �� ʦ   ��" NOR;k=arc_n;break;
                                case "(wizard)":        msg =HIG"��   ��    ʦ   ��" NOR;k=wiz_n ;break;
                                case "(apprentice)":    msg =HIC"��   ʵϰ��ʦ   ��" NOR;k=apr_n;break;
                                case "(immortal)":      msg =HIM"��   ������ʦ   ��" NOR;k=imm_n;break;
                                case "(elder)":         msg =HIB"��   �����^��   ��" NOR;k=eld_n;break;
                                }
                        j=1;
                } else {
                        msg="";
                        j++;
                }
                if ( k == 1) scr=WHT"��������"NOR;
                else scr=WHT"�����ש�"NOR;

                if ( k!=j && k!=1 && j!=1 ) scr=WHT"      �ǩ�"NOR;
                if ( k==j && k!=1 && j!=1 )     scr=WHT"      ����"NOR;

                inv=0;
                ob=new(LOGIN_OB);
                ob->set("id", list[i]);
                ob->restore();

                if(objectp(body=find_player(list[i])) && !body->query("env/invisibility")) {
                     if(interactive(body) && (query_idle(body)) > 300 && this_player()->visible(body))
                     att=sprintf(HIM"���ߣ��ѷ���%5d ����"NOR,query_idle(body))+"";
                                     else
                        if (!interactive(body)) att=HIR"���ߣ������У�����    "NOR;
                     else
                        if (this_player()->visible(body)) 
                        att=HIG"���ߣ�"+query_time(body->query_temp("scan_time"))+"";

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
                } else {att="���ߣ�"+query_time(ob->query("last_on"))+"";
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
str +=HIC"�ԡ�"HIB"��������������������������������������������������������"HIY"�ݺ�������ʦ��"NOR HIB
 "������"HIC"�ԡ�\n"NOR;
        str += HIR"�� "HIW+MUD_NAME+HIC" Ŀǰ���� " + HIR + chinese_number(sizeof(list)) +HIC+ " λά��������ʦ��\n"NOR;
        
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
                return CYN" [����δ��]"NOR;
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
                msg+=sprintf("%s��", chinese_number(day));
        if(day<10 && hour)
                msg+=sprintf("%sСʱ", chinese_number(hour));
        if(!day && hour<20 && min )
                msg+=sprintf("%s��", chinese_number(min));

        return msg;
}

int help(object me)
{
write(@HELP

ָ���ʽ : wizlist

��; : �г�Ŀǰ��վ��ʦ���Աϵͳ�����Լ���ǰ��������״̬��

HELP
     );
     return 1;
}

