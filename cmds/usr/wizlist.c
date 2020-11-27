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

   str = HIW"�� "BLINK+HIR+MUD_NAME+"�������Ա. \n"NOR;
   str +=HIC"�ԡ�"HIB"������������������������������������������������������������������������"HIC
   "�ԡ�\n"NOR;
   str +=WHT"  ϵͳ����       ID       ����       ״       ̬           ��������˵�� \n"NOR;
   str +=HIB"��������������������������������������������������������������������������������\n"NOR;

   for(int i=0; i<sizeof(list); i++)
   {      
      wizlv = SECURITY_D->get_status(list[i]);      

      switch (wizlv) 
      { 

         case "(admin)":      msg =HIW"�������ܹܡ�" NOR;
                              n = adm_n++;break;
         case "(arch)":       msg =HIR"���� �� ʦ��" NOR;
                              n = arc_n++;break;
         case "(wizard)":     msg =HIG"����    ʦ��" NOR;
                              n = wiz_n++;break;
         case "(apprentice)": msg =HIC"��ʵϰ��ʦ��" NOR;
                              n = apr_n++;break;
         case "(immortal)":   msg =HIM"��������ʦ��" NOR;
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
        att = "���ߣ�" + query_time(ob->query("last_on")) + NOR;
     }
     else 
     { 
        if (!interactive(body)) 
            att=HIR"���ߣ������У�����    "NOR;
        else        
        if ( (query_idle(body)) > 300 ) 
            att=sprintf(HIM"���ߣ��ѷ���%5d ����"NOR,query_idle(body))+NOR;
        else 
            att=HIG"���ߣ�"+query_time(body->query_temp("scan_time"))+NOR;       
     }

     str1 = sprintf(YEL"%-9s%-10s"NOR "%-2s"NOR, 
                    list[i], body->name(), att); 
  
     str1 += spc[0..(42 - sizeof(filter_color(str1)))] + get_mission(list[i]) + "\n";
     str += str1;
     destruct(ob); 
     if ( on_ln == 0 ) destruct(body); 
   }

  str +=HIC"�ԡ�"HIB"������������������������������������������������������"HIY"�л�Ӣ����ʦ��"NOR HIB
  "����"HIC"�ԡ�\n"NOR;
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
        for(i=0; i<sizeof(mission); i++) 
        {
           if(sscanf(mission[i], "%s %s",
                        wname, wmin)!=2 ) continue;
                if(wname==wiz) return wmin;
        }
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

