#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"������"NOR);
        set("long", @LONG
���������̹��������������ǽ�����������Χ����������ʱ�򣬶���
�����̵��Ĵ��������һ����⡰�����֡������İ��㣬�����˹�
���ˡ��ۿ��������ɼ������Ϲ����������̵���������ϵ������
��ʯ��һ˲���ˡ�
LONG );
        set("exits",([
            "down" : __DIR__"to_ding",
        ]));
        set("objects",([
            __DIR__"npc/xuan-ci":1,
            __DIR__"npc/miejue":1,
            __DIR__"npc/song":1,
            __DIR__"npc/hetaichong":1,
            __DIR__"npc/yuebuqun":1,
            __DIR__"npc/chengkun":1,
        ]));
                
        
        setup();

}


void init()
{
        add_action ("do_fight","fight");
        add_action ("do_fight","kill");
        add_action ("do_fight","hit");
        add_action ("do_work","quit");
        add_action ("do_work","halt");
}

int do_work()
{
        write("���ﲻ��ʹ�����ָ�\n");
        return 1;
}

int do_fight()
{
        write("���ﲻ��ʹ�����ָ�\n");
        return 1;
}

