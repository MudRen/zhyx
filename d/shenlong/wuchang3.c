// wuchang3.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
����һ���������Ϊ��������䳡��������ִ�̽���������Ů������
�������е�Ҳ��һ�Թۿ����ƺ��ڴ�Ħʲô��
LONG );
	set("exits", ([
		"west" : __DIR__"wuchang",
	]));
        set("for_family", "������");
        setup();
	//replace_program(ROOM);
}