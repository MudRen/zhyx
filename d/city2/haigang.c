
inherit BUILD_ROOM;

void create()
{
	set("short", "����֮��");
	set("long", @LONG
������Ǵ�֮�����˻��Ĵ��Ž�ʯ����������������������һȺȺ��
Ÿ��ŷŷ..���ؽ��ţ���ʱ�����Ծ�����棬��������˻����������Ҵ�
��(chuan)�� �������ż����������ˣ��˴��ɶɹ��󺣵��ﺣ����һ�ˡ�
����һֱ�߾����ྩ�ˣ�������һ���޼ʵĴ󺣡���Ŀ���������������ؿ�
���������⳩����ȷ��һ���þӴ���
LONG );
	set("exits", ([
                "west" : __DIR__"road10",
	]));
	set("item_desc", ([
                "chuan" : "һ�Ҵ󷫴�����úܽ�ʵ���������Գ�Զ���ġ�\n",
	]));
	set("objects", ([
                __DIR__"npc/flowerg":2,
		"/d/shenlong/npc/chuanfu" :1,
	]));
        set("max_room", 3);
	set("outdoors", "city2");
	setup();
}

