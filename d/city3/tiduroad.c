inherit ROOM;

void create()
{
	set("short", "�ᶽ��");
	set("long", @LONG
�ᶽ�־�����Ϊͨ���ᶽ������������һ���������˺���
������ľ͸��Ǿ����ˡ��ᶽ���˺����������벻���ģ�����
�ö�����������������������ﶼ��������̤�롣
LONG);
        set("outdoors", "chengdu");
	set("exits", ([
	    	"south"  : __DIR__"southroad2",
	    	"north"  : __DIR__"guangchang",
	]));
	set("objects", ([
	    	"/d/city/npc/bing" : 3,
	]));
	set("coor/x",-500);
	set("coor/y",-210);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}