inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�����ڶ�����ϣ����ż�ʵ����ʯ����档�����Ƕ�����
���������سǹٱ���ߺ�������������񶼴�����Ǳ�һ���ྲ
ԭ������Ϊ�ᶽ������ͷ���ϱ���һ����ֱ�Ĵ����
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
	    	"east"  : __DIR__"eastgate",
	    	"west"  : __DIR__"shuduroad1",
	    	"north" : __DIR__"eastroad1",
	    	"south" : __DIR__"eastroad3",
	]));
	set("objects", ([
	    	"/d/city/npc/liumangtou" : 1,
	    	"/d/city/npc/liumang"    : 2,
	]));
	set("coor/x",-480);
	set("coor/y",-200);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
