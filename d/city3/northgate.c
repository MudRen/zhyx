inherit ROOM;
string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���ǳɶ������ţ��������Ϸ����ű�������������֣���
ǽ�����ż��Źٸ���ʾ(gaoshi)��һ����ֱ����ʯ������
���졣������ȥ��һƬ�����͵���Ұ�������ҡҷ�ĸ�������
�񡣳��ű����йٱ���ϸ�̲�����˵ȡ�
LONG);
        set("outdoors", "chengdu");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("no_fight",1);
	set("exits", ([
		"south"  : __DIR__"northroad2",
		"north"  : __DIR__"fuheqiaon",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));
	setup();

        //replace_program(ROOM);
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n�ɶ��ᶽ\n�����\n";
}
