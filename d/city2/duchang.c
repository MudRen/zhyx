// Room: /city2/duchang.c

inherit ROOM;
string* npcs = ({
        "/d/city2/npc/wuliuqi",
});

void create()
{
	int i = random(sizeof(npcs));
	set("short", "�ĳ�");
	set("long", @LONG
�����Ƕĳ��Ĵ��ã����ܵķ����ﴫ����ߺ������ĶĲ�����
ǽ�Ϲ���һ������(paizi)�� ¥�Ͽ��Թ���һ���ţ�ֻ��������
�����ӣ�ʮ�ֻ��ҡ���һ��Χ��һȺ�ˣ�����һ��һ������ͷ��ʮ
�����ۡ�һ���Ͻл��������Ƕĵ��𾢡�
LONG );

	set("item_desc", ([
		"paizi" : "��¥�Ĺ�������ʹ�ã�Ϊʲôû������?\n",
	]));
	set("exits", ([
                "up" : __DIR__"duchang2",
		"west" : __DIR__"xidan1",
	]));
	set("no_clean_up", 0);
	set("objects", ([
        	CLASS_D("shenlong")+"/shou": 1,
		npcs[i] : 1,
 	]));
	setup();
}
