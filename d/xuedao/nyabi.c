// nyabi.c

inherit ROOM;
void create()
{
        set("short","���±�");
        set("long",@long
������һ�����͵��±ڣ����ϵ����Ǳ��ȵúں����Ļ�ѩ��������
����м���Ѫ��������������
long );
        set("exits",([
                "south" : __DIR__"shandong2",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren" : 4,
        ]));
        set("outdoors", "xueshan");
        setup();
        replace_program(ROOM);
}
