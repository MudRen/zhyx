inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
����һ��������ֱ����������Ĵ�ٵ�������ݵ���ʮ�����ۡ��ϱ�
�Ƕ��������ųǣ�����ֱ�Ͽ��Ե��ﻪɽ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"north" : __DIR__"guandaon3",
  		"south" : __DIR__"guandaon1",
	]));

	setup();
	//replace_program(ROOM);
}