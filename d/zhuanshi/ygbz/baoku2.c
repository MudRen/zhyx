// by yuchang
#include <ansi.h>  
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG  
����һ���������ܷ���ң��Ҷ��ĽǾ���ͨ���ڣ����� 
ƽ�ŷ��ù���ʮ�����ӣ���ǽ�м�ʮ��������(jia)������
���ֱ��� ,�㹻װ��һ����ǧ�˵ľ�����!
LONG); 
        set("item_desc", ([           
          "jia" : "���������м���ʯͷ�ر������ˣ���Ҫ��(pick)����������?\n",  
        ]));
        set("exits", ([
                "up" : __DIR__"baoku",
        ]));
        
        setup();
}
void init()
{    
     add_action("do_pick", "pick"); 
 } 


int do_pick(string arg)
{
    object stone, me = this_player();

     

    if( !arg || arg != "stone" )
        return notify_fail("������(pick stone)��?\n");
                             
    if( me->query("reborn_start/ygbz/stone") )
        return notify_fail("�㲻���Ѿ��õ�һ��Ů�ʯ����?\n");

    message_vision(HIY"$N�ӱ�����������һ��ʯͷ!\n\n"NOR, me);
    stone = new(__DIR__"obj/kaitian-jian");
    stone->move(me);   
    me->set("reborn_start/ygbz/stone", 1);

    message("visione", HBRED HIW"�����ش��š�" + me->query("name") + 
              "����������ҵ���Ů�ʯ��!\n"NOR,users()); 

    remove_call_out("get_out");
    call_out("get_out", 2, me);
    return 1; 
}

void get_out(object me)
{
     message_vision(HIC"ͻȻ$N�Ľŵ����ѿ�һ������$N������ȥ��\n"NOR, me); 
     me->move("/d/changan/bei-chengmen"); 

}