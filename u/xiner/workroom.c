// Room of wizard that haven't modify own workroom
// Updated by Lonely

#include <ansi.h>
#include <room.h> 
inherit CREATE_CHAT_ROOM; 

int is_chat_room() { return 1; } 

void create()
{
          set("short", HIW"ܰ���Ĺ�����"NOR);
        set("long",HIG @LONG
����һ������ͨͨ�İ칫�ң�͸�����ʽ�Ĵ������Կ���
Զ��Ⱥɽ֮���Ͽ�ȴ��̵���������Զ����һƬ�����֣����
�ӻ���̬���ˣ�������ɫ����֬��㣬ռ�����硣
LONG NOR);

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down"  : "/d/city/kedian",
		"sky1"  : "/d/zhuanshi/sky/sky1",
        ]));

        set("objects", ([ 
                  "/u/xiner/npc/shuanger": 1, 
           ]));

        set("valid_startroom", 1);
        set("no_fight",1);
        set("sleep_room", "1");
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");              
        return ::valid_leave(me, dir);
}