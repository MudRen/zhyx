// By yuchang 
inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "����");
        set("long", @LONG  
����һ�������ķ��䣬�Ҷ��ĽǾ���ͨ���ڣ����� 
ƽ�ŷ��ù����ٸ�����װ�������챦������(xiang)����
ǽ�м��ٸ��Żƽ������(xiangzi)!
LONG
        ); 
        set("item_desc", ([       
"xiang" : "���������һЩ�ַ���������һ���书���㲻������ϸ��(think)һ��!\n",          
   "xiangzi" : "�������кܶ�ƽ�,��Ҫ�ó�����??\n",      

                          ]));
        set("exits", ([
                "east" : __DIR__"baokudt",
                      ]));
       set("no_clean_up", 1);
        set("no_stab", 1);
        setup();
}
void init()
{
  object me = this_player(); 
    add_action("do_pick", "pick");  
    add_action("do_push", "push");     } 

int do_pick(string arg)
{
        object money, me=this_player();

        if( !arg || arg=="" ) return 0;

 if(me->query_temp("ygbz_money"))
return notify_fail("���Ѿ��ù�Ǯ��,��Ҫ��˼������!\n");
      if( arg=="xiangzi" )
                             {  
if(query_temp("nasword")){ 
   message_vision("$N��ȥ�ûƽ�,�����Ѿ���������\n", this_player());
     return 1;
 }
                                message_vision(
HIY"$N���������ó��ƽ�!\n"NOR, this_player());
                        money = new("/clone/money/cash"); 
                            money->move(me);    
set_temp("nasword",1); 
me->set_temp("ygbz_money",1);
 message("channel:chat", HBRED HIB"�����ء�"+me->query("name")+"��������﷢���˴����Ļƽ���!\n"NOR,users()); 
return 1;
                }
        return 1;
}
int do_push(string arg)
{
  object me = this_player();
        if(!arg || arg!="door")
                return notify_fail("��Ҫ��ʲô��\n");
   if(query("exits/west"))
           return notify_fail("���Ѿ�����,���Ƹ�ͷ��\n");
  message_vision(HIG"$N�����ƿ�ǽ�ڣ������е�����!\n"NOR,me);
   set("exits/west", "/d/changan/xi-chengmen"); 
  call_out("on_guanmen", 5);
return 1;
}
void on_guanmen(object room)
{
      message_vision(HIG"ͻȻ�������ǵ�����,ǽ���ֺ�����!\n"NOR, this_player());
delete("exits/west");
}

