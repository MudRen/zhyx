inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
���������ӿ��⸮�����ݸ��Ĺٵ�����������·�ΰ��Ϻ�
����Ҳ���١�����ͨ�򿪷⣬���������ݸ���
LONG);
        set("exits", ([
  		"west" : __DIR__"wroad2",
  		"east" : __DIR__"xijiao",
	]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        setup();
        //replace_program(ROOM);
}