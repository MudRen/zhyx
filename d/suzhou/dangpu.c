// Room: /d/suzhou/dangpu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "���ͼ�");
	set("long", @LONG
����һ����������ƽ���Ƶĵ��̣�һ����߸ߵĹ�̨����
�����ǰ����̨�ϰ���һ������(sign)����̨������λ�ϰ壬
һ˫�������۾��������´������㡣
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("no_clean_up", 0);
	set("exits", ([
		"north"  : __DIR__"dongdajie1",
	]));
	set("item_desc", ([
		"sign" : "��ƽ����\n
sell        �� 
buy         ��
value       ����
",
	]));
	set("objects", ([
		__DIR__"npc/wang" : 1,
	]));
	set("coor/x",210);
        set("coor/y",-155);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

