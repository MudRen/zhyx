inherit ROOM;

void create()
{
	set("short", "�м��ջ�ͷ�");
	set("long", @LONG
����һ��ܴ�Ŀͷ�������ʮ�ּ�ª����ǽ����ʮ����С
ľ�������ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ���������
���Ŵ��ǿյģ���������ŵ����˹�ȥ��
LONG );
	set("sleep_room", 1);
	set("no_fight", 1);      
	set("no_clean_up", 0);
	set("exits", ([
		"up" : __DIR__"kedian",
	]));	
	setup();
}

