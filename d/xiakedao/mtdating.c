//room: mtdating.c
inherit ROOM;
void create()
{
        set("short","����");
        set("long",@LONG
�����Ħ�����ˡ������ͺͺ�ģ���һ��С��Ҳû�У��嶥��
Ҳʮ�ֿ������������������ƣ������������ƶ�֮�У�ʹ���ľ���
����������һ��Сľ�ݡ�
LONG );
        set("outdoors", "xiakedao");
        set("exits",([
                "east" : __DIR__"mtxiaowu",
                "down" : __DIR__"mtyadi",
        ]));
        set("objects",([
                __DIR__"npc/xieyan" : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if ((dir == "east") && objectp(present("xie yanke", environment(me))) )
        return notify_fail
                ("л�̿Ͱ���һ�������һ�����\n");
        return ::valid_leave(me, dir);
}

