//shangu7
#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short", "ɽ���Ե�");
        set("long", @LONG
���Ǹ���Ͽ�ȣ������������������㵨���ľ�����ǰ�����ţ�������һЩ
��·�˵�ʬ������á���ʱ����һ�������˺���������ʲô�����ڰ���
�����ţ��㲻�ɵļӿ��˽Ų���
LONG );
        set("outdoors", "ajszhuang");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __DIR__"shangu8",
                "north" : __FILE__,
        ]));             
}

int valid_leave(object me, string dir)
{     

        if ( me->query_skill("dodge") < 1000 )   
        {
                me->receive_damage("qi", 100);
                me->receive_wound("qi", 100);
                message_vision(HIW "\nͻȻɽ��һ����ʯ�����"
                               "����$N" HIW "��\n\n" NOR, me);               
        }
       return 1;

}
