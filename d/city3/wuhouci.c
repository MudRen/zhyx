inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����������������������������ڽ�һ����ǰ����
�����հ������и�������Ҳ�������������ڵ������ڵģ���
ʫʥ�Ÿ�������¶��ǧ��������������Ƶ�������£���������
�ϳ��ġ������������ǧ�ŷ緶��һ�����¡�
LONG );
	set("exits", ([
	    "southdown" : __DIR__"liubeidian",
	]));
	set("no_clean_up", 0);
	set("coor/x",-515);
	set("coor/y",-215);
	set("coor/z",10);
	setup();
	//replace_program(ROOM);
}