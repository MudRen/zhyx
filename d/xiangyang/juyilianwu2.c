// Room: /d/xiangyang/juyilianwu2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ǿ���������������ĵط����м���������ר������
�����䣬�м����ֱֳ������ڻ�����С����鶯�����紩��
����һ�㣬�㲻���������ۣ�����������ڵ��ϵ������Ͽ���
������
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"east" : __DIR__"juyiyuan",
	]));
	set("coor/x",-505);
	set("coor/y",-405);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}

