inherit ROOM;

string look_gaoshi();

void create()
{
    	set("short", "���Ŵ��");
	set("long", @LONG
������������������������ͨ�����ǣ��򶫾��������ˡ�
�ϱߣ��¿��˸������᳡��ÿ������֮�ڣ��������У��㲻
����ȥ��ʶһ�µ���ĳ������
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"ximen",
  		"west"  : "/d/changan/road8",
                "south" : __DIR__"wudao4",
                "southwest" : "/d/jingzhou/road1",
	]));
        set("objects", ([
                "/d/village/npc/boy" : 3,
        ]));
	set("coor/x",-40);
        set("coor/y",1);
	set("coor/z",0);
	setup();
}

int valid_leave(object me, string dir)
{
	object obj;
	if (dir == "south") me->set_temp("view_leitai", 1);
        return ::valid_leave(me, dir);
}
