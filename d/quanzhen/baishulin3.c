inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���߽��˰����ֵ�������²��ź�����Ҷ������������
����Ĺ��߷ǳ��������㼸��ʲô���������ˡ�ͻȻһֻ����
������ǰ����֦���͵����˹�ȥ��������һ����
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "northup" : __DIR__"cuipingfeng",
                "east" : __DIR__"baishulin4",
                "southdown" : __DIR__"baishulin1",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        //replace_program(ROOM);
}