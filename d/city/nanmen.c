inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
�������ݳǵ��ϳ��ţ���ǽ�������˹���ƣ������˻���
���̸��и�ҵ�Ĺ�棬�ٸ��ĸ�ʾ(gaoshi)��˲�̫��Ŀ����
���Ǳ������Ļ���Ц�����������ƺ����Ǻ�������ִ�ڡ�һ��
��ֱ����ʯ�������ϱ��������졣
LONG);
        set("outdoors", "city");
	set("item_desc", ([
		"gaoshi" : "\n����֪��\n��ҩ��\n",
	]));

	set("exits", ([
		"south" : "/d/wudang/wdroad1",
		"north" : __DIR__"nandajie2",
		"west"  : __DIR__"jiaowai8",
		"east"  : __DIR__"jiaowai7",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 2,
                __DIR__"npc/bing" : 4,
                __DIR__"npc/shisong" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x",0);
	set("coor/y",-40);
	set("coor/z",0);
	setup();

}
