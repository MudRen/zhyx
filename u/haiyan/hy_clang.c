:// hy_clang.c 
#include <ansi.h>
inherit ROOM; 
void create() 
{ 
     set("short", "��  ��"); 
     set("long", @LONG 
�����Ǻ�Ժ��һ�����������ĳ��ȣ����߲�ʱ���������������
�����У�������΢����ҡҷ��СϪ�������ʡ�������Լ�ɼ���һƬ
��԰���㲻���ӿ��˽Ų���
LONG); 
     set("exits", ([ 
         "south"    : __DIR__"hy_houyuan",  
         "north"    : __DIR__"hy_hy01",
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
}

int valid_leave(object me, string dir)
{
    if (! userp(me) && dir == "south")
        return notify_fail("���������\n");
    return ::valid_leave(me, dir);
}

