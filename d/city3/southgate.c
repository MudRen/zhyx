inherit ROOM;
string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���ǳɶ��ϳ��ţ��������Ϸ����š����š������������
��ǽ�����ż��Źٸ���ʾ(gaoshi)��һ����ֱ����ʯ������
�����졣�ϱ��ǽ��⣬������˽�����ˡ������ǳ��
LONG);
        set("outdoors", "chengdu");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"south"  : __DIR__"nanheqiaos",
		"north"  : __DIR__"southroad2",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));

	set("coor/x",-500);
	set("coor/y",-230);
	set("coor/z",0);
	setup();

}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n�ɶ��ᶽ\n�����\n";
}