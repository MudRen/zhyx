inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ׯ�ڵ�һ��ľ�Ƶ����ȣ����������ǹ⻬������
���ȱ�������һ����Ⱦ���㲻ʱ�ܹ���������ؤ��ĵ����ڴ�
�߶���æµ����ͣ��
LONG);
        set("exits", ([
                "south"  : __DIR__"ma_zhengting",
                "north"  : __DIR__"ma_zoulang2",
        ]));
        set("objects", ([
		"/d/gaibang/npc/1dai" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x",-20);
	set("coor/y",50);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}
