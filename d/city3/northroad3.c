inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�����ڱ���ֵ���ʯ���ϣ������������ַǷ���ԭ������
�Ǿ��ǽ�ţ��ݣ���˵ÿ����ʦ���о����཭�����ﶼĽ
��ǰ���������������˲������ơ��������Ƕ���֣�һֱ
�������Ǳ���֡�
LONG );
        set("outdoors", "chengdu");
	set("exits", ([
	    	"west"       : __DIR__"northroad2",
	    	"southeast"  : __DIR__"eastroad1",
	    	"northeast"  : __DIR__"wuguan",
	]));
	set("objects", ([
	    	"/d/huashan/npc/haoke" : 2,
	    	"/d/taishan/npc/jian-ke" : 1,
	]));
	set("coor/x",-485);
        set("coor/y",-175);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
