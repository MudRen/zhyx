//      caoyuan.c ��ԭ
//      Designed by secret (����)
//      97/04/08

inherit ROOM;

void create()
{
        set("short","��ԭ");
        set("long",@LONG
������ѩɽ���µ�һƬ��ԭ�������������Ⱥɽ��ɽ
���ϻ������겻����ѩ��������һ����·��
LONG );
        set("outdoors","xueshan");
        set("exits",([
                "north"      : __DIR__"caoyuan",
        ]));
        set("objects",([
                __DIR__"npc/maoniu" : 2 ,
        ]));
        setup();
        replace_program(ROOM);
}
