inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������ǿ��⸮�ڶ���������Ҫͨ������·�����˵��̸�
�ڲ��ϡ��������ƣ��۹�ģ�������ģ��ʽ���ģ���������
���ѵġ��������ɽ�¸ʻ�ݡ��������ݵ����Ͻ�¥��
LONG);
        set("objects", ([
  		__DIR__"npc/qigai" : 1,
	]));

        set("no_clean_up", 0);
        set("exits", ([
  		"south" : __DIR__"eroad1",
  		"north" : __DIR__"eroad3",
  		"east" : __DIR__"huiguan",
  		"westup" : __DIR__"jiaolou2",
	]));
        set("outdoors", "kaifeng");

        setup();
        //replace_program(ROOM);
}