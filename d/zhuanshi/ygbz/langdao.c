#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "�ȵ�");
        set("long", @LONG
��һ�߽�����о����ռ���������һ��С����
��ɿ�����ֱ�����ߵ��ȵ�����ֱ�������죬����
��������⡣
LONG );        
       set("exits", ([
           "north"  : __DIR__"jingduan",                                
       ]));
       setup();
       replace_program(ROOM);
}
