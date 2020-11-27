//Room: gaotai.c ���ҹ���̨
//Date: Sep 29 1997
//Modified by haiyan

#include <ansi.h>
inherit ROOM;

string *zhen = ({
"���ֳ�$w��ǰ����һ���裬����$w������Ȼ�̳���\n", 
"���ŵ�һ��������$w����бб�̳���\n",  
"�㷴����ס$w������һ���׻�������$w�����졣\n", 
"����ǰһ�ݣ����˰벽��ͻȻһ������������$wֱ�̹�ȥ��\n", 
"����$w�϶�Ϊһ����������˽���һ�����¼��̡�\n", 
"��������һ������������$w�������´̳���\n",  
"������һԾ������$w�������죬�������������\n",  
"������$w���ӣ������������⣬����һת������$w���̳���\n" 
}); 

int do_caoyan(); 
int do_exit(); 
int caoyan(object me); 
int halt_caoyan(object me); 

void create()
{
      set("short","���ҹ���̨");
      set("long",@LONG
�����Ǿ������ҹ���̨����̨�����²࣬������Ԩ����ɲ⡣ɽ���
����������棬�پ����ϴ󿪡�
    �䵱���佣�����������佣�����������е��Ӱ������ϱ��е�ľ��
�𡢻�ˮ������λ���������Ե��Ӱ�Ǭ�����������롢�㡢���ޡ��Ұ�
���졢�ء�ˮ���𡢷硢�ס�ɽ�������С�
LONG);
      set("objects", ([
           CLASS_D("wudang") +"/wuxing": 5,
           CLASS_D("wudang") +"/bagua": 8,
           CLASS_D("wudang") +"/yan": 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
          "northdown" : __DIR__"nanyangong",
      ]));
      set("outdoors", "wudang");
      setup();
}

void init()   
{  
      add_action("do_caoyan", "caoyan");
      add_action("do_exit", "quit");
      add_action("do_exit", "exit");
}   

int do_caoyan() 
{
     object me, weapon; 
     me = this_player(); 
     weapon = me->query_temp("weapon"); 
     if (!me->query_temp("lianzhen")) 
        return notify_fail("�����������ס�㣺�����ǲ��������Խ������������\n");

     if (me->query_temp("lianzhen") > 1) 
        return notify_fail("�㲻���������\n");

     if (!objectp(weapon) || (string)weapon->query("skill_type") != "sword") 
        return notify_fail("�������޽�����ô������\n"); 

     me->add_temp("lianzhen", 1);
     message_vision("$N������" + weapon->name() + "һ��������Ծ�뽣�󣬿�ʼ�����󷨡�\n", me); 
     me->set_short_desc("��ִ" + weapon->name() + "�����ڲ������佣��"); 
     me->start_busy((:call_other, __FILE__, "caoyan" :), 
                    (:call_other, __FILE__, "halt_caoyan" :)); 
     return 1; 
}

int caoyan(object me) 
{ 
    string msg; 
    object weapon; 
    int i, lvl; 

    weapon = me->query_temp("weapon");
    lvl = me->query_skill("zhenwu-array");

    if (!objectp(weapon) || (string)weapon->query("skill_type") != "sword")
    {
       halt_caoyan(me); 
       return 0;
    }
    for( i = 0; i <= 8; i++ ) 
    {
        if (random(10) == 0) 
        {  
            msg = zhen[random(sizeof(zhen))]; 
            msg = replace_string(msg,"$w",weapon->name()); 
            write(msg); 
        } 
    }
    if (me->can_improve_skill("zhenwu-array")) 
       me->improve_skill("zhenwu-array", 500); 
    return 1; 
} 

int halt_caoyan(object me) 
{ 
    object ob, weapon;
    ob = present("yu daiyan"); 
    weapon = me->query_temp("weapon"); 
    message_vision( HIY "$N" HIY "������" + weapon->name() +  
                    HIY "һ����Ծ���˽��󡣱�ȭ�������������������и��ˡ�\n" NOR, me); 
    tell_object(me, "����ֹ�˲��ݡ�\n");  
    me->delete_temp("lianzhen"); 
    me->set_short_desc(0); 
    ob->add_temp("count", -1);
    return 1; 
} 

int valid_leave(object me, string dir)  
{  
    if (objectp(present("yu daiyan", environment(me))) && 
        dir == "northdown" && me->query_temp("lianzhen"))
            return notify_fail("�����һ����ס�㣺���ú���������󷨣���Ҫ���ܡ���\n"); 
    return ::valid_leave(me, dir); 
}  

int do_exit() 
{
     object me; 
     me = this_player(); 
     if (me->query_temp("lianzhen")) 
     {
        tell_object(me, "�������ݽ���������뿪��\n");  
        return 1;
     }
     return 0; 
}

