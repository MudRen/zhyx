inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������������ľ۾����ģ�������������Ĵ󲿣������ģ�����
�͵ĵ顢���ۡ��͸���������������һ��ʯ��С�ǣ��˿ڲ��࣬����
ɢ�������Ӹ�������������Ҫ��һЩ���̺ͼ�������
LONG);
	set("outdoors", "dali");
	set("exits", ([
                "south"     : __DIR__"badidian",
                "north"     : __DIR__"gelucheng",
                "northeast" : __DIR__"minadian",
                "east"      : __DIR__"titian1",
                "west"      : __DIR__"wuyiminju3",
	]));
	set("objects", ([
                __DIR__"npc/muyangnu" : 1,
                __DIR__"npc/wshangfan" : 1,
                "/clone/npc/walker" : 1,
	]));
	setup();
	//replace_program(ROOM);
}
