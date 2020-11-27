#include <ansi.h>
inherit ROOM;

#define REBORND   "/adm/daemons/rebornd"

void create()
{
	set("short", WHT"���㹬����"NOR);
	set("long", @LONG
ͻȻ����ǰһ����һ���޴�Ĺ������������
ǰ�����Ǵ�˵�еľ��㹬���ù�ռ�ؼ��㣬���ͤ
̨������ɭȻ��ȫ����ɽ��������������壬����
�й�����֮���ɣ����㹬������ǧ�����ɽ���£�
Ψһ;����һ��ֱͨ���ŵĴ�ʯ�ţ�ʯ�ſ�㣬��
�������ۣ����񹤣����ư��磬ʹ������һ��
�������Ī�еĸ�̾��
LONG
        );
        set("outdoors", "qianhuigu");
             
        set("exits", ([ 
                "north" : __DIR__"migong2",
        ]));
        setup();       
}

void init()
{
     string id, out;
     object ob, room;
     object me = this_player();   

     out = REBORND->query("jingyan/out");

     if ( ! stringp(out) ) return; 

     if ( ! objectp(room = find_object(out)) )
        room = load_object(out); 

     if ( me->is_character() && ! userp(me) )
     {
        me->move(room);
        return;
     }

     if ( ! me->query("reborn_start"))
     {
        tell_object(me, 
           BLINK HIR"���㹬�ɲ���˭���ܽ��ģ��㻹��������ȥ��!\n\n"NOR);

        message_vision(HIY"һ�ɾ޴��������$N���˳�ȥ��\n\n"NOR, me);
        me->move(room);
        return;
     }
  
     id = REBORND->query("jingyan/id");
     
     if ( stringp(id) && id != me->query("id") )
        ob = find_player(id);

     if (objectp(ob) && 
         base_name(environment(ob))[0..18] == "/d/zhuanshi/jingyan")
     {             
         message_vision(HIY"һ�ɾ޴��������$N���˳�ȥ��\n\n"NOR, me);         
         tell_object(me, 
            HIY"�����������ھ��㹬���ٵ������ɡ�\n\n"NOR);
         me->move(room);
         return;
     }         
     REBORND->set("jingyan/id", me->query("id"));
     
}



