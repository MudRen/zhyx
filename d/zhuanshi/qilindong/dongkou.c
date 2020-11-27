//room: dongkou.c BY Yuchang

#include <ansi.h> 
inherit ROOM;

#define REBORND   "/adm/daemons/rebornd"

void create()
{
     set("short","����");
     set("long",@LONG
ɽ������ͻȻ��ʧ��������ǰ��һ�����ڣ����¿�ȥ�������ƣ����
���޷�����ȵס����ڱ��и�ɽ����hole)���Ա���һ��ʯ��(bei)��
LONG
     );
     set("exits", ([ 
                    "up" : "/d/city3/shudao14", 
             ])); 
     set("outdoors", "chengdu");     
     set("item_desc",([
         "bei" : "������ߡ����й��ޣ������������ڣ�\n" ,
         "hole" : "��������ߣ��㲻����˵Ļ����Խ�ȥ��(enter dong)\n" ,
     ]));
     setup();
}

void init()
{
     string id;
     object ob;
     object me = this_player();

     add_action("do_enter", "enter");

     if ( me->is_character() && ! userp(me) )
     {
        me->move("/d/city3/shudao8");
        return;
     }
     if ( ! me->query("reborn_start"))
     {
        tell_object(me, 
           BLINK HIR"���������������ܽ��ģ�Ī�����ò��ͷ���!\n\n"NOR);

        message_vision(HIY"һ�ɾ޴��������$N�Ƴ������붴�ڡ�\n\n"NOR, me);
        me->move("/d/city3/shudao8");
        return;
     }
  
     id = REBORND->query("qilindong");
     
     if ( stringp(id) && id != me->query("id") )
        ob = find_player(id);

     if (objectp(ob) && 
         base_name(environment(ob))[0..20] == "/d/zhuanshi/qilindong")
     {     
         tell_object(me, 
            HIY"�����������ڶ����ٵ������ɡ�\n\n"NOR);        
          message_vision(HIY"һ�ɾ޴��������$N�Ƴ������붴�ڡ�\n\n"NOR, me);
          me->move("/d/city3/shudao8");         
         return;
     }         
     REBORND->set("qilindong", me->query("id"));
     
}

int do_enter(string arg)
{
    object me, ob;    

    me = this_player();
 
    if( !arg || arg != "hole" )
       return notify_fail("��Ҫ������ȥ?\n"); 

    foreach (ob in deep_inventory(me)) 
    if (ob->is_character()) 
        return notify_fail("������ߣ��������죬�Ͳ�Ҫ�������˻����ȥ�ˣ�\n"); 

    message_vision("$Nһ�������������˽�ȥ��\n\n",me);
    
    me->move(__DIR__"dong1");

    message("vision", me->name() + "�Ӷ������˽�����\n",
            environment(me), ({me}) );

    return 1;   
}   
