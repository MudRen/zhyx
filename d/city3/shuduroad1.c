inherit ROOM;

void create()
{
	set("short", "�񶼵�");
	set("long", @LONG
�������񶼴���������Ϳ��Ե��ᶽ���ˡ������ĳ�����
������������ȥ�Ĺٲ�����ɣ�һЩ�ٱ���·��Ѳ�ڡ���
�е�һ��㺦�£����ڹս���������
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
	    	"east"  : __DIR__"eastroad2",
	    	"west"  : __DIR__"guangchang",
	]));

	set("objects", ([
	    	"/d/city/npc/bing" : 2,
	]));

	set("coor/x",-490);
	set("coor/y",-200);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}