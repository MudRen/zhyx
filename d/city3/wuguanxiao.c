inherit ROOM;

void create()
{
	set("short", "��ţ�������");
	set("long", @LONG
�����ǽ�ţ��ݽ���������ʦ�����ɽ��ڻ����Ṧ������
�ڹ��������мܣ�����ָ��������������
LONG);
	set("objects", ([
		__DIR__"npc/xiaofei" : 1,
	]));
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);
	set("no_clean_up", 0);
	set("exits", ([
		"east" : __DIR__"wuguan",
	]));
	setup();
	//replace_program(ROOM);
}