
#include <ansi.h>
inherit ITEM;
void set_out(object me);

void create()
{
      set_name("������",({"mache"}));
      set_weight(20000); 
      set("short","������");
      set("id","mache");
set("long","������ʦ�����õ������ֽ��췣�\n");  
      set_max_encumbrance (1000000000);
      if (clonep()) {
           set_default_object(__FILE__);
                    }
      else {
      set("material", "wood");
      set("no_sell",1); 
      set("sleep_room",1);
      set("if_bed",1);
      set("no_get",1);
      set("unit", "��"); 
      set("power",1000);
      set("value",100);
            }
      setup();
}

void init()
{
           add_action("do_jump","jump");    
           add_action("do_out","out");
           add_action("do_look","look"); 
           add_action("do_move","drive"); 

}

int do_jump(string str)
{
     object me = this_player();
     object who = this_object(); 

     if (!objectp(environment(who)) || environment(who)==me) {
            return 0;
              }
     if (!str||str!="biaoche") {
      return notify_fail("��������ʲô��\n");
                           }
     message_vision("$N������������˽�ȥ������漴�ִ���������\n",me);
     remove_call_out("set_out");
     call_out("set_out",1,me);
     me->move(who);
     message_vision("�������$N���˽�����\n",me);
     return 1;
}

void set_out(object me)
{
     tell_room(environment(this_object()),"��������һ����˻��˦˦���䣬׼�������ˡ�\n");
     tell_object(me,"׼����ϣ����Գ����ˣ�\n");
}

int do_out(string arg)
{
     object me = this_player();
     object who = this_object();

     if (environment(me)!=who) {
           return 0;
               }
     if (!environment(who)) {
           return 0;
               } 
     message_vision("$N��������������˳���\n",me);     me->move(environment(who));
     message_vision("�����������������$N�ӳ����������ϡ�\n",me);
     return 1;     
} 

int do_rob(string arg)
{
     object me = this_player();
     object who = this_object(); 
     object *humen;
     int i, end;
     if (environment(me)==who) {
           return 0;
               } 
        if (me->query_temp("get_mission"))
      return notify_fail("������ͷҮ��\n");

     if (!arg||arg!="biaoche") {
      return notify_fail("������ʲô��\n");
                           }

     message_vision("$N��ס�ڳ��������е�������٣����ϵ���ͳͳ������������\n",me);
     who->set_temp("stopped",1); 
     if (arrayp(all_inventory(who)))  humen = all_inventory(who);
     end = sizeof(all_inventory(who));
     for (i=0; i<end; i++) {
         if (!interactive(humen[i])) continue;
         else {
             tell_object(humen[i],(string)humen[i]->query("name")+"������������ˣ����³���æ�ɣ�\n");
             humen[i]->move(environment(who));       
                 }  
    }
     tell_object(environment(who),"���ϵ��������������ڿ���ʽӭս��\n"NOR,me);
        return 1;     
}

int do_look(string arg)
{
     object me = this_player();
     object who = this_object();
     object room,*sth,*outsth;
     string str,*str2;
     mapping str1;
     int i, exitcon,objcon,obcon;

     str = "";
     if (arg)  return 0;       
     if (environment(me)!=who)   return 0;
     if (!environment(who))      return 0;
     
     else { 
tell_object(me,"        ______________________\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |                      |\n");
tell_object(me,"       |----------------------|\n");
tell_object(me,"       |______________________|\n");
           tell_object(me,(string)environment(who)->query("long"));
 
           room = environment(who);
           if (!room->query("exits")) {
                    str += "\n    �����Ѿ�û��·�ˡ�\n";
                             }
           else {
           str1 = room->query("exits");
           str2 = keys(str1);
           exitcon = sizeof(str2);
           if (exitcon==1) {
                   str += "\n    ǰ��Ψһ�ĳ����ǣ�"+HIG+str2[0]+"��\n"+NOR;
                           }
           else {
              str += "\n    ǰ��ĳ����У�";
              for (i=0; i<exitcon; i++) {
                    if (i==exitcon-1) {
                       str += "��"+str2[i]+"��\n"+NOR;
                           }
                    else {
                       str += HIG+str2[i]+"��";
                         }
                     }
                 }
           objcon = sizeof(all_inventory(who));
           sth = all_inventory(who);
           str += WHT"    �ڳ������У�\n"NOR;
           for (i=0; i<objcon; i++) {
                if (!objectp(sth[i])) {
                        continue;
                         }
                else  str += "    "+HIG+sth[i]->query("name")+"\t"+HIG+"("+sth[i]->query("id")+")"+"\n"NOR;
                   }
          str += HIW"    �ڳ������У�\n"NOR;
          obcon = sizeof(all_inventory(environment(who)));
          outsth = all_inventory(environment(who));
          for (i=0; i<obcon; i++) {
                if (!objectp(outsth[i])) continue;
                if (outsth[i]->query("id")=="biaoche") continue;
                else str += HIG+"    "+outsth[i]->query("name")+"\t("+outsth[i]->query("id")+")\n"+NOR;
                  }
           write(str);
           return 1;
               }
            }

}
  
int do_move(string arg)
{
     object me = this_player();
     object who = this_object();
     object end;
     mapping exi;
     string *key,*val;
     string filename;
     int i,count;
     
     if (environment(me)!=who) {
             return 0;
                } 
     if (!me->query_temp("get_mission")) {
             return notify_fail("�㲻����ͷ����Ҫ�ҽ��͡�\n");
                }
     if (who->query_temp("stopped")) {
             return notify_fail("�����ڽ����أ��커�ڰɡ�\n");
                }
     if (!arg) {
             return notify_fail("��Ҫȥ�Ķ���\n");
               }
     if (!environment(who)->query("exits")) {
             return notify_fail("�����Ѿ�û��·�ˣ����Ķ�Ҳȥ���ˡ�\n");
               }
      exi = environment(who)->query("exits");
     key = keys(exi);
     val = values(exi);
     count = sizeof(val);
     for (i=0; i<count; i++) {
          if (arg==key[i]) {
                filename = val[i] + ".c";
                if (file_size(filename)<=0) continue;
                end = load_object(filename);
                tell_room(environment(who),"��������һ����˻���ſ����㣬������֮���������"+end->query("short")+"��ȥ����\n\n"+NOR);
                tell_room(who,"����΢����һ�£�������֮���������"+end->query("short")+"��ȥ����\n\n");
                who->move(end);
                if (environment(who)!=end) return 0;
                tell_room(who,"�ܿ죬���ѵ���Ŀ�ĵء� ("+end->query("short")+")\n"+NOR);
                            tell_room(environment(who),"ֻ������������һ���ڳ����˹�����\n"+NOR);
                return 1;
                   }
           else continue;
             }
           return notify_fail("��ȷ��������ط���\n"); 
}
 
int do_open(string arg)
{
     object me = this_player();
     object who = this_object();  
     object silver, env;
     env=environment(who);

        if (me->query_temp("get_mission")) return 0;
     if (!who->query_temp("stopped")) return 0;

     if (!arg||arg!="biaoche") 
      return notify_fail("�����ʲô��\n"); 

       if (objectp(who=present("biaotou",environment())))
       return notify_fail("����ͷ������һ�ۺȵ�����"+RANK_D->query_self_rude(me)+"����Ҫ��ʲô����\n");
      silver=new(SILVER_OB);
      silver->set("name","����"); 
      silver->set_weight(0); 
    message_vision("$N���ڳ���ȡ����"+silver->query("name")+"��\n",me);
      silver->set_amount(20000+random(20000));
      silver->move(me);  
    message("vision",HIM"\n��ҥ�ԡ�ĳ�ˣ���˵"+HIM+me->query("name")+HIM"��"+HIM+env->query("short")+HIM"��������������\n\n"NOR,users());

      return 1;
}

