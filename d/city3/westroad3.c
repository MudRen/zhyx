inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�㲻֪�����ؾ������˳ɶ������ǣ����������������Ե�
�������塣��ʯ�����ֻ����������ļ����ˣ����������й䡣
����������֣�������������һ����֣��������и��ô��ҩ
�꣬��һЩ�������˳��õ�ҩ�����ŵ��ӳ�������ҩ��
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
	    	"south"      : __DIR__"westroad2",
	    	"northeast"  : __DIR__"northroad1",
	    	"northwest"  : __DIR__"yaodian",
	]));
	set("objects", ([
	    	"/d/huashan/npc/haoke": 1,
	]));
	set("coor/x",-520);
	set("coor/y",-185);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
