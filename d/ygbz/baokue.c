// By yuchang
inherit ROOM;
#include <ansi.h>  

void create()
{
        set("short", "����");
        set("long", @LONG  
����һ�������ķ��䣬�Ҷ��ĽǾ���ͨ���ڣ����� 
ƽ�ŷ��ù����ٸ�����װ�������챦������(xiang)����
ǽ�м��ٸ�������(jia)���������֣����� ,�㹻װ��һ
�����˵ľ�����!
LONG
        ); 
        set("item_desc", ([       
"xiang" : "���������һЩ�ַ���������һ���书���㲻������ϸ��(think)һ��!\n",          
   "jia" : "��������������һ�����ر������ˣ���Ҫ��(pick)����������?\n",      

                          ]));
        set("exits", ([
               "west" : __DIR__"baokudt",
                      ]));
        set("no_clean_up", 0);
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
        object sword, me=this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="jia" )
                             {  
if(query_temp("nasword")){ 
   message_vision("$N��ȥ�ù��ӽ�������Ѿ���������\n", this_player());
     return 1;
 }
                                message_vision(
HIY"$N�ڱ�������������һ������!\n"NOR, this_player());
                    sword = new(__DIR__"obj/zhenmo-club");
                        sword->move(me);   
set_temp("nasword",1);
 message("channel:chat", HBRED HIW"�����ء�"+me->query("name")+"��������﷢������ħ����!\n"NOR,users()); 
return 1;
                }
        return 1;
}
int do_push(string arg)
{
  object me = this_player();
        if(!arg || arg!="door")
                return notify_fail("��Ҫ��ʲô��\n");
    if(query("exits/east"))
           return notify_fail("���Ѿ�����,���Ƹ�ͷ��\n");
  message_vision(HIG"$N�����ƿ�ǽ�ڣ������е�����!\n"NOR,me);
   set("exits/east", "/d/changan/dong-chengmen"); 
  call_out("on_guanmen", 5);
return 1;
}
void on_guanmen(object room)
{
      message_vision(HIG"ͻȻ�������ǵ�����,ǽ���ֺ�����!\n"NOR, this_player());
delete("exits/east");
}

