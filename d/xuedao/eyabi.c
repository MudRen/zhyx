// eyabi.c

inherit ROOM;

void create()
{
        set("short","���±�");
        set("long",@long
������һ���ǳ����͵��±ڣ����ڵط�̫��խ�����������������
�˲����࣬����Ѫ���ŵ���Ҳ���治�����ĺ���֮ͽ���˼���ľ������
��������
long );
        set("exits",([
                "west" : __DIR__"shandong2",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren" : 3,
        ]));
        set("outdoors", "xueshan");
        setup();
        replace_program(ROOM);
}
